# What is EVA Motors?

## Core Concept

EVA Motors is a decorator-based library for behavioral modification of micro-motors. 
EVA Motors lets you compose behavior by stacking decorators that add specific characteristics like S-curve response, inertia simulation, or kick-start pulses.

## Built on EVA Ecosystem

EVA Motors is part of the [EVA ecosystem](https://agusevtec.github.io/eva-core-sk/) – an event-driven architecture for Arduino. This integration provides:

- Non-blocking timing – Decorators like `InertiaDecor` and `KickDecor` use EVA's `Tickable` infrastructure
- Unified update cycle – Single `eva::tac()` call drives all time-based components
- Zero-polling design – Components update themselves when needed

```cpp
#include <evaTac.h>
#include <evamKickstartDecor.h>
using namescpace evam;

using Motor = KickstartDecor<DirectionalMotor<TA6586Driver<9, 10>>>;

void setup(){
    static Motor motor;
    motor.Go(50);  // will overhead initial friction by pulse
}
void loop() {
    eva::tac();
}
```

## Unified Interface

While decorators are the primary focus, this architecture naturally led to interface unification. All motor classes share a consistent `Go(value)` interface with a standardized range:

- **Signed motors**: `-1000` to `1000` (-100% to +100%)
- **Unsigned motors**: `0` to `1000` (0% to 100%)

This means you can use EVA Motors as a simple motor control library without decorators. Whether you need bidirectional DC motor control, ESC throttle, or servo positioning, the API remains consistent:

```cpp
using namespace evam;
// Simple motor without decorators
using Motor = DirectionalMotor<TA6586Driver<9, 10>>;
Motor motor;
motor.Go(750);  // 75% forward
motor.Go(-500); // 50% reverse
```


## Standard Combo Stack

The library follows a consistent three-layer architecture:

| Layer | Components |
|-------|------------|
| **DECORATORS** (Optional) | `CurveDecor` • `InertiaDecor` • `KickDecor` |
| **MOTOR** (Required) | `DirectionalMotor` • `ForwardMotor` • `SteeringActuator` • `LinearActuator` |
| **DRIVER** (Required) | `PwmDriver` • `ServoDriver` • `TA6586` • `TB6612` • `~CustomDriver~` |

Driver layer handles hardware specifics – pin assignments, PWM ranges, protocol details

Motor wrapper provides the unified Go() interface and handles input mapping (dead zones, min/max limits)

Motor wrapper and driver are always required – they form the foundation

Decorators add realistic behavior without modifying the base motor class

```cpp
using namespace evam;
using BaseMotor = DirectionalMotor<TA6586Driver<9, 10>>;
using PreciseMotor = CurveDecor<BaseMotor, -5>;
using InertialMotor = InertiaDecor<PreciseMotor, 15>;
using SmartMotor = KickDecor<InertialMotor, 25, 900>;
SmartMotor motor;
```

or more compact:

```cpp
KickDecor<InertiaDecor<CurveDecor<DirectionalMotor<TA6586Driver<9, 10>>, 5>, 15>, 25, 900> motor;
```


## Extensible Driver Layer

The library features a clean, extensible hardware abstraction layer. Adding support for new motor drivers is straightforward.

## License

This library is published under the **MIT License** – free for commercial and open-source use.

