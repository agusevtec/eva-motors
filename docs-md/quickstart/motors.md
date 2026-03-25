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
| PwmDriver | | + | | + |
| ServoDriver | + | + | + | + |
| TA6586Driver | + | | + | |
| TB6612Driver | + | | + | |

**Notes:**
- **bipolar** – Uses `actBipolar()` method with range -1000..1000
- **unipolar** – Uses `actUnipolar()` method with range 0..1000
- Empty cells indicate incompatibility
- ServoDriver supports all motor types with appropriate interface
- TA6586Driver and TB6612Driver support SteeringActuator through bipolar interface

## DirectionalMotor

Bidirectional motor controller for DC motors with H-bridge drivers.

```cpp
template <class Driver, signed short kMaxBackward = -1000, 
          signed short kMinBackward = 0, signed short kMinForward = 0, 
          signed short kMaxForward = 1000>
class DirectionalMotor : public Driver
```

**Methods:**
- `setup_range(maxBack, minBack, minForw, maxForw)` – Configure all limits
- `SetMaxBackward(value)` – Max reverse power (-1000..1000)
- `SetMinBackward(value)` – Min reverse power (start threshold)
- `SetMinForward(value)` – Min forward power (start threshold)
- `SetMaxForward(value)` – Max forward power
- `Go(level)` – Set motor power (-1000..1000)

**Example:**
```cpp
using Motor = evam::DirectionalMotor<evam::TA6586Driver<9, 10>>;
Motor motor;
motor.setup_range(-1000, -200, 200, 1000);  // 20% dead zone
motor.Go(750);  // 75% forward
```

## ForwardMotor

Unidirectional motor controller for ESCs and forward-only applications.

```cpp
template <class Driver, int kMinValue = 0, int kMaxValue = 1000>
class ForwardMotor : public Driver
```

**Methods:**
- `setup_range(minVal, maxVal)` – Configure output range
- `SetMinValue(value)` – Minimum output (idle/stop)
- `SetMaxValue(value)` – Maximum output (full power)
- `Go(level)` – Set motor power (0..1000, negative treated as 0)

**Example:**
```cpp
using ESC = evam::ForwardMotor<evam::PwmDriver<9>>;
ESC throttle;
throttle.setup_range(100, 1000);  // ESC calibration
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
- `setup_range(leftPos, centerPos, rightPos)` – Configure endpoints
- `SetLeftPos(value)` – Leftmost position
- `SetCenterPos(value)` – Center position
- `SetRightPos(value)` – Rightmost position
- `Go(level)` – Set position (-1000..1000)

**Example:**
```cpp
using Steering = evam::SteeringActuator<evam::ServoDriver<9>>;
Steering steering;
steering.setup_range(-800, 0, 800);  // Calibrate endpoints
steering.Go(500);  // Turn right
```

## LinearActuator

Position controller for linear actuators and position servos.

```cpp
template <class Driver, int kMinValue = 0, int kMaxValue = 1000>
class LinearActuator : public Driver
```

**Methods:**
- `setup_range(minVal, maxVal)` – Configure position range
- `SetMinValue(value)` – Position at input 0
- `SetMaxValue(value)` – Position at input 1000
- `Go(position)` – Set position (0..1000)

**Example:**
```cpp
using Actuator = evam::LinearActuator<evam::PwmDriver<10>>;
Actuator actuator;
actuator.setup_range(0, 1000);
actuator.Go(750);  // 75% extended
```

## Drivers

### PwmDriver
Simple PWM output for unipolar devices.

```cpp
template <int kPin>
class PwmDriver
```

**Methods:**
- `actUnipolar(value)` – Set PWM (0..1000 → 0..255)

### ServoDriver
Standard servo control using Arduino Servo library.

```cpp
template <int kPin>
class ServoDriver
```

**Methods:**
- `actBipolar(value)` – Centered control (-1000..1000 → 500..2500µs)
- `actUnipolar(value)` – Absolute control (0..1000 → 1000..2000µs)

### TA6586Driver
Driver for TA6586 dual H-bridge.

```cpp
template <int kForwardPin, int kBackwardPin>
class TA6586Driver
```

**Methods:**
- `actBipolar(value)` – Bipolar control (-1000..1000 → -255..255 PWM)

### TB6612Driver
Driver for TB6612FNG dual H-bridge.

```cpp
template <int kPinSpeed, int kPinMode1, int kPinMode2>
class TB6612FNGDriver
```

**Methods:**
- `actBipolar(value)` – Bipolar control with direction pins