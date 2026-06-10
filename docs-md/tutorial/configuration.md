## Configuration System

EVA Motors provides flexible configuration through dedicated config structures. Each decorator and motor wrapper includes its own config structure that can be used either at compile-time (template parameters) or runtime (config objects).

### Two Ways to Configure

**1. Template parameters (compile-time) – for fixed configurations:**

```cpp
// Using template parameters
using Motor = CurveDecor<
    DirectionalMotor<
        TA6586Driver<9, 10>,
        -1000, -200, 200, 1000  // DirectionalMotor template params
    >,
    -3  // CurveDecor template param: bend = -3
>;
```

**2. Config structures (runtime) – for dynamic configuration:**

```cpp
// Using config structures

  CurveDecor<DirectionalMotor<TA6586Driver<>>> motorr = {
    CurveConfig{ -3 },
    DirectionalConfig{ -1000, -200, 200, 1000 },
    TA6586Config{ 9, 10 }
  };

```

### Config Structure Initialization

All config structures use consistent parameter names matching their fields:

```cpp
// Adaptive smoothing
AdaptiveSmoothConfig smoothConfig(10, 150);  // minTimeConstantMs, maxTimeConstantMs

// Curve (S-curve) behavior
CurveConfig curveConfig(-3);  // bend (-10..10)

// Directional motor range
DirectionalConfig dirConfig(-1000, -200, 200, 1000);  // maxBackward, minBackward, minForward, maxForward

// Forward-only motor
ForwardConfig forwardConfig(150, 1000);  // minValue, maxValue

// Inertia simulation
InertiaConfig inertiaConfig(10);  // inertiaMass

// Kick-start
KickConfig kickConfig(25, 900);  // duration, power

// Linear actuator
LinearActuatorConfig linearConfig(0, 1000);  // minValue, maxValue

// Median filter
MedianConfig medianConfig(5);  // windowSize

// Steering actuator
SteeringConfig steeringConfig(-1000, 0, 1000);  // leftPos, centerPos, rightPos

// PWM driver
PwmConfig pwmConfig(9);  // pin

// Servo driver
ServoConfig servoConfig(9, 1000, 1500, 2000);  // pin, minPulse, middlePulse, maxPulse

// TA6586 driver
TA6586Config ta6586Config(9, 10);  // forwardPin, backwardPin

// TB6612 driver
TB6612Config tb6612Config(5, 6, 7);  // pinSpeed, pinMode1, pinMode2
```

### Runtime Parameter Changes

All configurable parameters can be changed at runtime using `SetXxx()` / `GetXxx()` methods:

```cpp
InertiaDecor<ForwardMotor<PwmDriver<9>>> motor;

// Change inertia mass at runtime
motor.SetInertiaMass(20);
unsigned short mass = motor.GetInertiaMass();  // returns 20

// Change direction range at runtime
motor.SetMaxForward(800);
motor.SetMinForward(100);
```

### Complete Example: Dynamic Configuration

```cpp
#include <evaTac.h>
#include <evamAdaptiveSmoothDecor.h>

using namespace evam;

// Type definition without compile-time parameters
using SmoothMotor = AdaptiveSmoothDecor<DirectionalMotor<TA6586Driver<>>>;

void setup() {
    // Create config structures with desired values
    AdaptiveSmoothConfig smoothConfig(15, 200);  // custom time constants
    DirectionalConfig dirConfig(-1000, -150, 150, 1000);
    TA6586Config driverConfig(9, 10);
    
    // Initialize motor with runtime config
    static SmoothMotor motor(smoothConfig, dirConfig, driverConfig);
    
    // Adjust parameters on the fly
    motor.SetMinForward(180);
    motor.SetMaxTimeConstantMs(250);
    
    motor.Go(500);
}

void loop() {
    eva::tac();
}
```

