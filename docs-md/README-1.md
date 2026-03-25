# eva-motor

**Decorator-based motor control library for Arduino/EVA ecosystem**

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Platform: Arduino](https://img.shields.io/badge/platform-Arduino-blue)](https://www.arduino.cc/)

EVA Motor is a header-only C++ library that provides a flexible, decorator-based approach to motor control. Instead of rigid motor classes, you compose behavior by wrapping drivers with decorators that add specific features like S-curves, inertia simulation, or kick-start pulses.

## ✨ Key Features

- **Decorator Pattern** – Stack features without inheritance hell
- **Zero-cost Abstractions** – Everything resolves at compile time
- **Hardware Abstraction** – Same API for PWM, Servo, H-bridge drivers
- **EVA Ecosystem Ready** – Seamless integration with `Tickable` for time-based features
- **Standardized Interface** – All motors use `Go(value)` with range -1000..1000 or 0..1000

## 🎯 Philosophy

This library focuses on **decorators** – the building blocks that add realistic motor behavior. The motor wrappers (`DirectionalMotor`, `ForwardMotor`, etc.) are simple adapters that convert normalized signals to driver-specific formats. The real power comes from combining decorators:

```cpp
// Base motor
using Base = evam::DirectionalMotor<evam::TA6586Driver<9, 10>>;

// Add smooth start (S-curve)
using Smooth = evam::CurveDecor<Base, 5>;

// Add inertia (slow deceleration)
using Inertial = evam::InertiaDecor<Smooth, 15>;

// Add kick-start (overcome static friction)
using SmartMotor = evam::KickDecor<Inertial, 30, 800>;

SmartMotor motor;

void setup() {
    motor.setup_curve(7);           // Adjust curve shape
    motor.setup_kickstart(25, 900); // Configure kick pulse
    motor.setup_range(-1000, -200, 200, 1000); // Set dead zones
}

void loop() {
    motor.Go(800);  // Smooth acceleration with inertia
    delay(2000);
    motor.Go(0);    // Gradual deceleration
    delay(2000);
}
```

## 📦 Installation

### Arduino Library Manager
1. Open Arduino IDE
2. **Sketch → Include Library → Manage Libraries**
3. Search for **"eva-motor"**
4. Click Install

### Manual Installation
```bash
git clone https://github.com/agusevtec/eva-motor.git ~/Arduino/libraries/eva-motor
```

## 🚀 Quick Start

### 1. Simple DC Motor with H-bridge
```cpp
#include <evamTA6586Driver.h>
#include <evamDirectionalMotor.h>

// Motor on pins 9 (forward) and 10 (backward)
using Motor = evam::DirectionalMotor<evam::TA6586Driver<9, 10>>;
Motor motor;

void setup() {
    motor.setup_range(-1000, -300, 300, 1000); // Dead zone compensation
}

void loop() {
    motor.Go(800);  // 80% forward
    delay(2000);
    motor.Go(-800); // 80% reverse
    delay(2000);
    motor.Go(0);    // Stop
    delay(1000);
}
```

### 2. Aircraft ESC (Forward Only)
```cpp
#include <evamPwmDriver.h>
#include <evamForwardMotor.h>
#include <evamCurveDecor.h>

// ESC on pin 9 with S-curve for smooth throttle response
using ESC = evam::CurveDecor<evam::ForwardMotor<evam::PwmDriver<9>>, 4>;
ESC throttle;

void setup() {
    throttle.setup_range(100, 1000); // Calibrate ESC (100 = idle)
}

void loop() {
    // S-curve makes throttle response smoother
    for(int t = 0; t <= 1000; t += 10) {
        throttle.Go(t);
        delay(20);
    }
}
```

### 3. Steering Servo with Center
```cpp
#include <evamServoDriver.h>
#include <evamSteeringActuator.h>

// Steering servo on pin 9
using Steering = evam::SteeringActuator<evam::ServoDriver<9>>;
Steering steering;

void setup() {
    // Calibrate endpoints
    steering.setup_range(-800, 0, 800); // -800 = left, 0 = center, 800 = right
}

void loop() {
    steering.Go(500);  // Turn right
    delay(1000);
    steering.Go(-500); // Turn left
    delay(1000);
    steering.Go(0);    // Center
    delay(1000);
}
```

### 4. Linear Actuator (Position Control)
```cpp
#include <evamPwmDriver.h>
#include <evamLinearActuator.h>

// Linear actuator on pin 10
using Actuator = evam::LinearActuator<evam::PwmDriver<10>>;
Actuator actuator;

void setup() {
    actuator.setup_range(0, 1000); // Map 0-1000 to 0-100% PWM
}

void loop() {
    actuator.Go(0);     // Retract
    delay(2000);
    actuator.Go(1000);  // Extend
    delay(2000);
}
```

## 🏗️ Architecture

### Component Layers

```
┌─────────────────────────────────────────────┐
│           DECORATORS (Optional)              │
│  ┌─────────────┬─────────────┬─────────────┐│
│  │CurveDecor   │InertiaDecor │KickDecor    ││
│  │(S-curve)    │(Flywheel)   │(Kick-start) ││
│  └─────────────┴─────────────┴─────────────┘│
├─────────────────────────────────────────────┤
│           MOTOR WRAPPERS                     │
│  ┌─────────────┬─────────────┬─────────────┐│
│  │Directional  │ForwardMotor │Steering     ││
│  │Motor        │             │Actuator     ││
│  └─────────────┴─────────────┴─────────────┘│
│  ┌─────────────────────────────────────────┐│
│  │LinearActuator                           ││
│  └─────────────────────────────────────────┘│
├─────────────────────────────────────────────┤
│           HARDWARE DRIVERS                  │
│  ┌─────────────┬─────────────┬─────────────┐│
│  │PwmDriver    │ServoDriver  │TA6586Driver ││
│  │             │             │TB6612Driver ││
│  └─────────────┴─────────────┴─────────────┘│
└─────────────────────────────────────────────┘
```

## 🔌 Hardware Compatibility Matrix

| Driver | DirectionalMotor | ForwardMotor | SteeringActuator | LinearActuator | Best For |
|--------|------------------|--------------|------------------|----------------|----------|
| **PwmDriver** | ❌ | ✅ (unipolar) | ❌ | ✅ (unipolar) | Simple motors, LEDs, ESC (aircraft) |
| **ServoDriver** | ✅ (bipolar) | ✅ (unipolar) | ✅ (bipolar) | ❌ | Steering servos, throttle servos |
| **TA6586Driver** | ✅ | ❌ | ❌ | ❌ | DC motors (cars, boats, robots) |
| **TB6612Driver** | ✅ | ❌ | ❌ | ❌ | DC motors with separate direction pins |

### Legend
- ✅ Fully compatible
- ❌ Not compatible (interface mismatch)
- **(unipolar)** – Uses `actUnipolar()` method (0..1000 range)
- **(bipolar)** – Uses `actBipolar()` method (-1000..1000 range)

### Application Recommendations

| Application | Recommended Stack |
|-------------|-------------------|
| **Aircraft ESC** | `CurveDecor<ForwardMotor<PwmDriver>>` – Smooth throttle response |
| **Car/Boat Motor** | `KickDecor<InertiaDecor<DirectionalMotor<TA6586Driver>>>` – Realistic driving feel |
| **Steering Servo** | `SteeringActuator<ServoDriver>` – Centered servo control |
| **Robotic Arm** | `LinearActuator<PwmDriver>` – Position control |
| **Drone Motors** | `ForwardMotor<PwmDriver>` – Direct ESC control |

## 🎨 Decorators Explained

### CurveDecor – S-Curve Transformation
Converts linear input to S-shaped curve for smoother starts and finer mid-range control.

```cpp
template <class Motor, signed short kBend = 0>
class CurveDecor : public Motor
```

**Parameters:**
- `kBend`: -10..10 (0 = linear, positive = softer start, negative = sharper start)

```cpp
motor.setup_curve(5);  // Smooth acceleration
motor.setup_curve(-3); // Aggressive initial response
```

### InertiaDecor – Flywheel Effect
Simulates mechanical inertia – speed decreases gradually when stopping.

```cpp
template <class Motor, unsigned short kInertiaMass = 10>
class InertiaDecor : public virtual Tickable, public Motor
```

**⚠️ Requires EVA Tickable:** Must call `eva::tac()` in `loop()` or inherit from `Tickable` chain.

```cpp
#include <evaTac.h>

void loop() {
    eva::tac();  // Drives inertia updates
    // Your code...
}
```

**Parameters:**
- `kInertiaMass`: 1..200 (higher = slower deceleration)

```cpp
motor.SetInertiaMass(25);  // Heavy flywheel effect
```

### KickDecor – Static Friction Overcome
Applies momentary power pulse when starting or changing direction.

```cpp
template <class Motor, unsigned short kKickDuration = 20, signed short kKickPower = 1000>
class KickDecor : public virtual Tickable, public Motor
```

**⚠️ Requires EVA Tickable:** Must call `eva::tac()` in `loop()`.

```cpp
motor.setup_kickstart(30, 800);  // 30ms pulse at 80% power
```

## 🧩 Motor Wrappers

### DirectionalMotor
Bidirectional motor with configurable dead zones and max limits.

```cpp
template <class Driver, signed short kMaxBackward = -1000, 
          signed short kMinBackward = 0, signed short kMinForward = 0, 
          signed short kMaxForward = 1000>
class DirectionalMotor : public Driver
```

**Methods:**
- `setup_range(maxBack, minBack, minForw, maxForw)` – Configure all limits
- `SetMaxBackward(value)` – Max reverse power
- `SetMinBackward(value)` – Min reverse power (start threshold)
- `SetMinForward(value)` – Min forward power (start threshold)
- `SetMaxForward(value)` – Max forward power

### ForwardMotor
Unidirectional motor for ESCs, pumps, and forward-only applications.

```cpp
template <class Driver, int kMinValue = 0, int kMaxValue = 1000>
class ForwardMotor : public Driver
```

**Methods:**
- `setup_range(minVal, maxVal)` – Configure output range
- `SetMinValue(value)` – Minimum output (idle/stop)
- `SetMaxValue(value)` – Maximum output (full power)

### SteeringActuator
Centered servo control for steering applications.

```cpp
template <class Driver, signed short kLeftPos = -1000, 
          signed short kCenterPos = 0, signed short kRightPos = 1000>
class SteeringActuator : public Driver
```

**Methods:**
- `setup_range(leftPos, centerPos, rightPos)` – Configure endpoints
- `SetLeftPos(value)` – Leftmost position
- `SetCenterPos(value)` – Center position
- `SetRightPos(value)` – Rightmost position

### LinearActuator
Position control for linear actuators and servos.

```cpp
template <class Driver, int kMinValue = 0, int kMaxValue = 1000>
class LinearActuator : public Driver
```

**Methods:**
- `setup_range(minVal, maxVal)` – Configure position range
- `SetMinValue(value)` – Position at input 0
- `SetMaxValue(value)` – Position at input 1000

## 🔧 Complete Examples

### RC Car with Full Behavior Stack
```cpp
#include <evamTA6586Driver.h>
#include <evamDirectionalMotor.h>
#include <evamCurveDecor.h>
#include <evamInertiaDecor.h>
#include <evamKickDecor.h>
#include <evaTac.h>

// Build the complete motor stack
using BaseMotor = evam::DirectionalMotor<evam::TA6586Driver<9, 10>>;
using SmoothMotor = evam::CurveDecor<BaseMotor, 4>;
using InertialMotor = evam::InertiaDecor<SmoothMotor, 15>;
using RCMotor = evam::KickDecor<InertialMotor, 25, 900>;

RCMotor motor;

void setup() {
    // Configure all parameters
    motor.setup_range(-1000, -150, 150, 1000);  // Dead zone compensation
    motor.setup_curve(6);                       // Smooth acceleration
    motor.SetInertiaMass(20);                   // Realistic coasting
    motor.setup_kickstart(30, 850);             // Overcome static friction
}

void loop() {
    eva::tac();  // Required for InertiaDecor and KickDecor
    
    // Simulate throttle input
    static int throttle = 0;
    static int direction = 1;
    
    throttle += direction * 10;
    if (throttle >= 1000) direction = -1;
    if (throttle <= -1000) direction = 1;
    
    motor.Go(throttle);
    delay(20);
}
```

### RC Aircraft Throttle with S-Curve
```cpp
#include <evamPwmDriver.h>
#include <evamForwardMotor.h>
#include <evamCurveDecor.h>

// ESC on pin 9 with smooth S-curve
using ESC = evam::CurveDecor<evam::ForwardMotor<evam::PwmDriver<9>>, 5>;
ESC throttle;

void setup() {
    throttle.setup_range(100, 1000);  // ESC calibration
}

void loop() {
    // Smooth throttle response curve
    for(int t = 0; t <= 1000; t += 5) {
        throttle.Go(t);
        delay(10);
    }
    delay(1000);
    
    for(int t = 1000; t >= 0; t -= 5) {
        throttle.Go(t);
        delay(10);
    }
    delay(1000);
}
```

## 🌐 EVA Ecosystem Integration

This library is designed to work seamlessly with other EVA libraries:

- **eva-core-sk** – Provides `Tickable` for `InertiaDecor` and `KickDecor`
- **eva-button** – For RC input handling
- **eva-joystick** – For analog control sources

### Typical EVA Application
```cpp
#include <evaTac.h>
#include <evaJoystick.h>
#include <evamTA6586Driver.h>
#include <evamDirectionalMotor.h>
#include <evamCurveDecor.h>

// Motor setup
using Motor = evam::CurveDecor<evam::DirectionalMotor<evam::TA6586Driver<9, 10>>, 4>;
Motor motor;

// Joystick input on A0
Joystick<A0> joystick;

void setup() {
    motor.setup_range(-1000, -200, 200, 1000);
}

void loop() {
    eva::tac();  // Drives joystick updates
    
    int speed = map(joystick.getValue(), 0, 1023, -1000, 1000);
    motor.Go(speed);
}
```

## 📊 Performance

- **No dynamic allocation** – All objects are statically sized
- **Zero virtual calls** – Compile-time polymorphism
- **Minimal flash usage** – Features compile only when used
- **No runtime overhead** – Decorators inline completely

## 🤝 Contributing

Contributions are welcome! Please ensure:
1. Code follows existing style (templates, static_assert, doxygen comments)
2. New decorators maintain the `Go(value)` interface
3. Hardware drivers implement `actBipolar()` or `actUnipolar()`

## 📄 License

MIT License – See LICENSE file for details.

## 🔗 Links

- [Documentation](https://agusevtec.github.io/eva-motor)
- [EVA Ecosystem](https://agusevtec.github.io/eva-core-sk)
- [GitHub Repository](https://github.com/agusevtec/eva-motor)

---

**Part of the EVA Ecosystem** – Build better Arduino applications with event-driven architecture.