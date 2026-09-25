# Quick Start

## Motor Tester Example

This example demonstrates a motor tester with:

- Motor control with kick-start and S-curve for realistic driving feel

- Joystick throttle input

- Buttons to adjust curve behavior on the fly

- Non-blocking timer for consistent updates

```cpp
#include <evaTac.h>
#include <evaHeartbeat.h>
#include <evaJoystick.h>
#include <evaSwitch.h>

#include <evamTA6586Driver.h>
#include <evamDirectionalMotor.h>
#include <evamCurveDecor.h>
#include <evamKickDecor.h>

// Build the motor stack from bottom up:
// Driver (TA6586) -> DirectionalMotor -> KickDecor -> CurveDecor
// 25ms kick pulse at 90% power to overcome static friction
// Negative bend (-6) creates sharper initial response

using BaseMotor = evam::DirectionalMotor<evam::TA6586Driver<9, 10>, -1000, -200, 200, 1000>;
using KickMotor = evam::KickDecor<BaseMotor, 25, 900>;
using PreciseMotor = evam::CurveDecor<KickMotor, -6>;

class Vehicle : public eva::Heartbeat {
private:
  PreciseMotor mMotor;

  // Joystick on A0,  mapped to -1000..1000
  eva::PinSymmetricJoystick<A0, INPUT, 100, 600> mThrottle;

  // Button on pin changes bend (sharper response)
  eva::Handler<Vehicle> mButtonHandler{ this, &onButtonPress };
  eva::PullUpSwitch<3> mButton{ &mButtonHandler, eva::ON_PRESS };

  void onButtonPress(void* sender, eva::CallbackInfo cbInfo) {
    // Softer low-speed response, stronger high-end
    mMotor.SetBend(-mMotor.GetBend());
  }

public:
  Vehicle() : Heartbeat(100) {}

  void onHeartbeat() override {
    // Map joystick value (1000-2000) to motor range (-1000..1000)
    int speed = map(mThrottle.getValue(), 1000, 2000, -1000, 1000);
    mMotor.Go(speed);
  }
};

void setup() {
  // Static ensures object persists after setup() exits
  static Vehicle vehicle;
}

void loop() {
  // Single call drives heartbeat, switches, and motor decorators
  eva::tac();
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

- `Heartbeat` provides non-blocking periodic updates

- `Handler` binds events to methods without polling

- `PullupSwitch` handles button behaviour

For more information please visit [eva-core-sk documentation](https://agusevtec.github.io/eva-core-sk/)

### Customizing Behavior

| Parameter | Effect |
|-----------|--------|
| `KickDecor<..., 25, 900>` | 25ms pulse at 90% power to overcome static friction |
| `CurveDecor<..., -6>` | Negative bend = sharper initial response |
| `SetBend(5)` | Softer low-speed control, stronger high-end response |

