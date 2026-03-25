# eva-motor

**Decorator-based motor control library for Arduino/EVA ecosystem**

[License: MIT](https://opensource.org/licenses/MIT) | [Platform: Arduino](https://www.arduino.cc/)

EVA Motor is a header-only C++ library that provides a flexible, decorator-based approach to motor control. Instead of rigid motor classes, you compose behavior by wrapping drivers with decorators that add specific features like S-curves, inertia simulation, or kick-start pulses.

## Features

- **Decorator Pattern** – Stack features without inheritance hell
- **Zero-cost Abstractions** – Everything resolves at compile time
- **Hardware Abstraction** – Same API for PWM, Servo, H-bridge drivers
- **EVA Ecosystem Ready** – Seamless integration with `Tickable` for time-based features
- **Standardized Interface** – All motors use `Go(value)` with range -1000..1000 or 0..1000

## Documentation

- [Quick Start](quickstart.md) – Get started with examples
- [Motors](motors.md) – Motor wrappers and hardware compatibility
- [Decorators](decorators.md) – Behavioral enhancements

## Installation

### Arduino Library Manager
1. Open Arduino IDE
2. **Sketch → Include Library → Manage Libraries**
3. Search for **"eva-motor"**
4. Click Install

### Manual Installation
```bash
git clone https://github.com/agusevtec/eva-motor.git ~/Arduino/libraries/eva-motor
```

## Quick Example

```cpp
#include <evaTac.h>
#include <evaRepeatTimer.h>
#include <evamTA6586Driver.h>
#include <evamDirectionalMotor.h>
#include <evamCurveDecor.h>

using namespace eva;

// Motor with S-curve for precise low-speed control
using Motor = evam::CurveDecor<evam::DirectionalMotor<evam::TA6586Driver<9, 10>>, 5>;

class Demo {
private:
    Motor mMotor;
    RepeatTimer mTimer;
    int mSpeed = 0;
    int mDirection = 1;

    void onTimerTick(void* sender, CallbackInfo cbInfo) {
        mSpeed += mDirection * 50;
        if (mSpeed >= 1000) { mSpeed = 1000; mDirection = -1; }
        if (mSpeed <= -1000) { mSpeed = -1000; mDirection = 1; }
        mMotor.Go(mSpeed);
    }

public:
    Demo() : mTimer({new Handler<Demo>(this, &Demo::onTimerTick)}) {
        mMotor.setup_range(-1000, -200, 200, 1000);
        mTimer.start(100);
    }
};

Demo demo;

void setup() {}
void loop() { eva::tac(); }
```

## License

MIT License

## Links

- [Documentation](https://agusevtec.github.io/eva-motor)
- [EVA Ecosystem](https://agusevtec.github.io/eva-core-sk)
- [GitHub Repository](https://github.com/agusevtec/eva-motor)