# Motors

## Motor Types by Interface

| | Speed | Position |
|---|-------|----------|
| **signed (-1000..1000)** | DirectionalMotor | SteeringActuator |
| **unsigned (0..1000)** | ForwardMotor | LinearActuator |

- **DirectionalMotor** – Bidirectional speed control. Used for DC motors in cars, boats, robots where forward/reverse and variable speed are needed.

- **ForwardMotor** – Unidirectional speed control. Used for aircraft ESCs, pumps, fans, and any application requiring only forward direction with variable speed.

- **SteeringActuator** – Bidirectional position control. Used for steering servos, pan/tilt mechanisms, and any application requiring centered positioning with left/right movement.

- **LinearActuator** – Unidirectional position control. Used for linear actuators, position servos, and applications requiring absolute position control from minimum to maximum.

## Hardware Compatibility Matrix

| Driver | DirectionalMotor | ForwardMotor | SteeringActuator | LinearActuator |
|--------|------------------|--------------|------------------|----------------|
| PwmDriver | — | ✅ | — | ✅ |
| ServoDriver | ✅ | ✅ | ✅ | ✅ |
| TA6586Driver | ✅ | — | ✅ | — |
| TB6612Driver | ✅ | — | ✅ | — |

## DirectionalMotor

Bidirectional motor controller for DC motors with H-bridge drivers.

```cpp
template <class Driver, signed short kMaxBackward = -1000, 
          signed short kMinBackward = 0, signed short kMinForward = 0, 
          signed short kMaxForward = 1000>
class DirectionalMotor : public Driver
```

**Methods:**

- `SetupRange(maxBack, minBack, minForw, maxForw)` – Configure all limits

- `SetMaxBackward(value)` – Max reverse power (-1000..1000)

- `SetMinBackward(value)` – Min reverse power (start threshold)

- `SetMinForward(value)` – Min forward power (start threshold)

- `SetMaxForward(value)` – Max forward power

- `Go(level)` – Set motor power (-1000..1000)

**Example:**
```cpp
using Motor = evam::DirectionalMotor<evam::TA6586Driver<9, 10>>;
Motor motor;
motor.SetupRange(-1000, -200, 200, 1000);  // 20% dead zone
motor.Go(750);  // 75% forward
```

## ForwardMotor

Unidirectional motor controller for ESCs and forward-only applications.

```cpp
template <class Driver, int kMinValue = 0, int kMaxValue = 1000>
class ForwardMotor : public Driver
```

**Methods:**

- `SetupRange(minVal, maxVal)` – Configure output range

- `SetMinValue(value)` – Minimum output (idle/stop)

- `SetMaxValue(value)` – Maximum output (full power)

- `Go(level)` – Set motor power (0..1000, negative treated as 0)

**Example:**
```cpp
using ESC = evam::ForwardMotor<evam::PwmDriver<9>>;
ESC throttle;
throttle.SetupRange(100, 1000);  // ESC calibration
throttle.Go(500);  // 50% throttle
```

## SteeringActuator

Centered servo controller for steering and positioning.

```cpp
template <class Driver, signed short kLeftPos = -1000, 
          signed short kCenterPos = 0, signed short kRightPos = 1000>
class SteeringActuator : public Driver
```

**Methods:**

- `SetupRange(leftPos, centerPos, rightPos)` – Configure endpoints

- `SetLeftPos(value)` – Leftmost position

- `SetCenterPos(value)` – Center position

- `SetRightPos(value)` – Rightmost position

- `Go(level)` – Set position (-1000..1000)

**Example:**
```cpp
using Steering = evam::SteeringActuator<evam::ServoDriver<9>>;
Steering steering;
steering.SetupRange(-800, 0, 800);  // Calibrate endpoints
steering.Go(500);  // Turn right
```

## LinearActuator

Position controller for linear actuators and position servos.

```cpp
template <class Driver, int kMinValue = 0, int kMaxValue = 1000>
class LinearActuator : public Driver
```

**Methods:**

- `SetupRange(minVal, maxVal)` – Configure position range

- `SetMinValue(value)` – Position at input 0

- `SetMaxValue(value)` – Position at input 1000

- `Go(position)` – Set position (0..1000)

**Example:**
```cpp
using Actuator = evam::LinearActuator<evam::PwmDriver<10>>;
Actuator actuator;
actuator.SetupRange(0, 1000);
actuator.Go(750);  // 75% extended
```

