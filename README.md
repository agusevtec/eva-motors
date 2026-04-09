# EVA Motors

A modular C++ library for motor and actuator control on Arduino.

## Features

- **Unified interface** – All motors and actuators use the same `Go()` method
- **Plug-and-play drivers** – Servo, TB6612, TA6586, and PWM drivers included
- **Decorator pattern** – Add behaviors like curve shaping, inertia, and kick-start
- **Flexible range mapping** – Supports unipolar (0..1000) and bipolar (-1000..1000) control
- **Runtime configuration** – All parameters can be adjusted at runtime via setters
- **Compile-time safety** – `static_assert` validates template parameters

## Quick Start

### Basic Motor Control

```cpp
#include <evamForwardMotor.h>
#include <evamPwmDriver.h>

// PWM motor (e.g., ESC, LED, solenoid)
ForwardMotor<PwmDriver<9>> motor;
motor.Go(750);  // 75% throttle
```

### Servo Control

```cpp
#include <evamSteeringActuator.h>
#include <evamServoDriver.h>

// Steering servo (center = straight)
SteeringActuator<ServoDriver<3>> steering;
steering.Go(500);   // turn right
steering.Go(-300);  // turn left
```

### Bidirectional Motor (H-Bridge)

```cpp
#include <evamDirectionalMotor.h>
#include <evamTB6612Driver.h>

// Reversible motor using TB6612
DirectionalMotor<TB6612FNGDriver<9, 10, 11>> motor;
motor.Go(400);   // forward
motor.Go(-200);  // reverse
```

### Linear Actuator

```cpp
#include <evamLinearActuator.h>
#include <evamServoDriver.h>

// Linear actuator (0 = retracted, 1000 = extended)
LinearActuator<ServoDriver<5>> actuator;
actuator.Go(750);  // 75% extended
```

## Decorators

### Curve Shaping (S-Curve)

```cpp
#include <evamCurveDecor.h>

// Soft start and smooth response
CurveDecor<ForwardMotor<PwmDriver<9>>, 5> motor;
motor.Go(500);  // non-linear response
```

### Inertia Simulation

```cpp
#include <evamInertiaDecor.h>

// Gradual deceleration (flywheel effect)
InertiaDecor<DirectionalMotor<TB6612FNGDriver<9,10,11>>, 20> motor;
motor.Go(1000);   // full speed
motor.Go(0);      // decelerates slowly
```

### Kick-Start (Overcome Static Friction)

```cpp
#include <evamKickDecor.h>

// Full-power pulse when starting
KickDecor<ForwardMotor<PwmDriver<9>>, 30, 1000> motor;
motor.Go(100);  // brief full power then 10% throttle
```

## Drivers

| Driver | Description | Methods |
|--------|-------------|---------|
| `ServoDriver<kPin>` | Standard servo | `actBipolar()`, `actUnipolar()` |
| `PwmDriver<kPin>` | Simple PWM output | `actUnipolar()` |
| `TB6612FNGDriver<kSpeed,kMode1,kMode2>` | TB6612 H-bridge | `actBipolar()` |
| `TA6586Driver<kForward,kBackward>` | TA6586 H-bridge | `actBipolar()` |

## Motors & Actuators

| Class | Input Range | Semantics | Requires Driver Method |
|-------|-------------|-----------|------------------------|
| `ForwardMotor` | 0..1000 | Stop at 0 | `actUnipolar()` |
| `DirectionalMotor` | -1000..1000 | Neutral at 0 | `actBipolar()` |
| `LinearActuator` | 0..1000 | Min position at 0 | `actUnipolar()` |
| `SteeringActuator` | -1000..1000 | Center at 0 | `actBipolar()` |

## Decorators

| Decorator | Effect |
|-----------|--------|
| `CurveDecor` | S-curve (non-linear) response |
| `InertiaDecor` | Gradual deceleration (flywheel effect) |
| `KickDecor` | Full-power pulse at start/direction change |

## Runtime Configuration

All parameters can be adjusted at runtime:

```cpp
DirectionalMotor<TB6612FNGDriver<9,10,11>> motor;
motor.SetMaxForward(800);
motor.SetMinForward(100);
motor.SetMaxBackward(-800);
motor.SetMinBackward(-100);
motor.Go(500);
```

## Installation

Using Arduino Library Manager

Open Arduino IDE

Go to Sketch -> Include Library -> Manage Libraries

Search for "eva-core-sk"

Click Install

## License

This library is published under MIT licence.