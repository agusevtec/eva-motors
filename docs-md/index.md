# EVA Motors

A modular motor control library for Arduino, built on EVA principles.

## What is EVA?

EVA (Elegant Virtual Architecture) is a design philosophy that makes Arduino development enjoyable:
- **Self-documenting** — code reads like a story
- **Testable** — components can be verified in isolation
- **Refactoring-friendly** — changing structure doesn't break behavior
- **Timing-aware** — components claim their slice of `loop()`

This library follows EVA principles, using `Tickable` from eva-core-sk for timing-dependent decorators.

## Quick Start

```cpp
#include <evamForwardMotor.h>
#include <evamPwmDriver.h>

ForwardMotor<PwmDriver<9>> motor;
motor.Go(750);  // 75% throttle
```

That's it. One line, one action, no magic numbers.

## What's Inside

### Motors & Actuators

| Class | Input | Use This For |
|-------|-------|--------------|
| `ForwardMotor` | 0..1000 | Aircraft ESC, throttle, simple motor |
| `DirectionalMotor` | -1000..1000 | Car, boat, reversible motor |
| `LinearActuator` | 0..1000 | Linear actuator, solenoid |
| `SteeringActuator` | -1000..1000 | Steering servo (center = straight) |

### Drivers

| Driver | Connects To |
|--------|-------------|
| `ServoDriver<3>` | Servo (standard 1000-2000µs) |
| `PwmDriver<9>` | MOSFET, simple ESC, LED |
| `TB6612FNGDriver<9,10,11>` | TB6612 H-bridge |
| `TA6586Driver<7,8>` | TA6586 H-bridge (see pinout below) |

### Decorators

Add behavior without changing the motor class:

```cpp
// S-curve response for smoother control
CurveDecor<ForwardMotor<PwmDriver<9>>, 5> motor;

// Inertia — protects transmission in high-reduction gearboxes
InertiaDecor<DirectionalMotor<TB6612Driver<9,10,11>>, 20> motor;

// Kick-start — gentle pulse to overcome static friction
// Long duration + low power = soft start, protects gears
KickDecor<ForwardMotor<PwmDriver<9>>, 100, 200> motor;
```

## Choosing the Right Motor

| I want... | Use this | With driver |
|-----------|----------|-------------|
| Throttle (ESC, LED) | `ForwardMotor` | `PwmDriver` or `ServoDriver` |
| Reversible motor (car) | `DirectionalMotor` | `TB6612Driver` or `TA6586Driver` |
| Linear actuator | `LinearActuator` | `ServoDriver` |
| Steering servo | `SteeringActuator` | `ServoDriver` |

## Visualizing the Curve

The `CurveDecor` transforms linear input into an S-curve. Here's how different bend values affect the response:

![Curve visualization](assets/images/curves.png)

This plot shows input (-1000..1000) vs output for bend values from -10 to 10. Use positive values for softer starts, negative for sharper initial response.

## Runtime Configuration

All parameters can be adjusted on the fly:

```cpp
DirectionalMotor<TB6612Driver<9,10,11>> motor;
motor.SetMaxForward(800);   // limit top speed
motor.SetMaxBackward(-600); // limit reverse
motor.SetMinForward(50);    // minimum to overcome friction
```

## Timing

Decorators that simulate physical effects (`InertiaDecor`, `KickDecor`) inherit from `Tickable` (eva-core-sk). They manage their own timing — you don't need to call anything. Just add them to your loop:

```cpp
#include <evaTickable.h>

void loop() {
    Tickable::tickAll();  // updates all timed decorators
    // your other code
}
```

## Installation

1. Download the library
2. Place in your Arduino `libraries/` folder
3. Include the headers you need

## License

MIT

## Version

1.0.0
