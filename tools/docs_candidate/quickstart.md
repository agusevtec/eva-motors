# Quick Start

## Complete RC Vehicle Example

This example demonstrates a complete RC vehicle with:
- Motor control with kick-start and S-curve for realistic driving feel
- Joystick throttle input
- Buttons to adjust curve behavior on the fly
- Non-blocking timer for consistent updates

```cpp
#include <evaTac.h>
#include <evaRepeatTimer.h>
#include <evaJoystick.h>
#include <evaSwitch.h>

#include <evamTA6586Driver.h>
#include <evamDirectionalMotor.h>
#include <evamCurveDecor.h>
#include <evamKickDecor.h>

using namespace eva;
using namespace evam;

// Build the motor stack from bottom up:
// Driver (TA6586) -> DirectionalMotor -> KickDecor -> CurveDecor
using BaseMotor = DirectionalMotor<TA6586Driver<9, 10>>;
using KickMotor = KickDecor<BaseMotor, 25, 900>;      // 25ms kick at 90% power
using PreciseMotor = CurveDecor<KickMotor, -6>;       // Negative bend = sharper response

class Vehicle {
private:
  PreciseMotor mMotor;                                 // Motor with all features

  // Joystick throttle input (pins A0, range 1000-2000 → -1000..1000)
  PinSymmetricJoystick<A0, INPUT, 100, 600> mThrottle;

  // Timer updates motor every 100ms
  RepeatTimer mTimer{ 100, new Handler<Vehicle>(this, &Vehicle::onTimerTick) };

  // Buttons to adjust curve behavior in real-time
  PullupSwitch<7> mIncreaseButton{ new Handler<Vehicle>(this, &Vehicle::onIncreaseButtonPress), ON_PRESS };
  PullupSwitch<8> mDecreaseButton{ new Handler<Vehicle>(this, &Vehicle::onDecreaseButtonPress), ON_PRESS };

  void onIncreaseButtonPress(void* sender, CallbackInfo cbInfo) {
    mMotor.SetBend(5);    // Softer low-speed response, stronger high-end
  }

  void onDecreaseButtonPress(void* sender, CallbackInfo cbInfo) {
    mMotor.SetBend(-5);   // Sharper initial response
  }

  void onTimerTick(void* sender, CallbackInfo cbInfo) {
    // Map joystick value (1000-2000) to motor range (-1000..1000)
    int speed = map(mThrottle.getValue(), 1000, 2000, -1000, 1000);
    mMotor.Go(speed);
  }

public:
  Vehicle() {
    // Configure motor limits (dead zone compensation)
    mMotor.setup_range(-1000, -200, 200, 1000);
  }
};

void setup() {
  static Vehicle vehicle;  // Static ensures object persists
}

void loop() {
  eva::tac();  // Single call drives timers, switches, and motor decorators
}
```

## Key Concepts Explained

### Motor Stack Composition

The motor is built by stacking components from the bottom up:

```
CurveDecor        ← Adds S-curve transformation
    ↑
KickDecor         ← Adds kick-start pulse
    ↑
DirectionalMotor  ← Converts -1000..1000 to driver format
    ↑
TA6586Driver      ← Interfaces with hardware (pins 9, 10)
```

### EVA Integration

- `eva::tac()` drives all time-based components (timer, decorators)
- `RepeatTimer` provides non-blocking periodic updates
- `Handler` binds events to methods without polling
- `PullupSwitch` handles button debouncing automatically

### Customizing Behavior

| Parameter | Effect |
|-----------|--------|
| `KickDecor<..., 25, 900>` | 25ms pulse at 90% power to overcome static friction |
| `CurveDecor<..., -6>` | Negative bend = sharper initial response |
| `SetBend(5)` | Softer low-speed control, stronger high-end response |

## Minimal Example

For a simple motor without decorators:

```cpp
#include <evaTac.h>
#include <evamTA6586Driver.h>
#include <evamDirectionalMotor.h>

using namespace evam;

using Motor = DirectionalMotor<TA6586Driver<9, 10>>;
Motor motor;

void setup() {
    motor.setup_range(-1000, -200, 200, 1000);
}

void loop() {
    motor.Go(500);  // 50% forward
    delay(1000);
    motor.Go(-500); // 50% reverse
    delay(1000);
}
```

## Next Steps

- Learn about [Motors](motors.md) – understand motor wrappers and hardware compatibility
- Explore [Decorators](decorators.md) – add S-curves, inertia, and kick-start
- Create [Custom Drivers](custom-drivers.md) – support your own hardware