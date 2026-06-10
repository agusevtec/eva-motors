

# Namespace evam



[**Namespace List**](namespaces.md) **>** [**evam**](namespaceevam.md)




















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**AdaptiveSmoothConfig**](structevam_1_1_adaptive_smooth_config.md) <br>_Configuration structure for_ [_**AdaptiveSmoothDecor**_](classevam_1_1_adaptive_smooth_decor.md) _._ |
| class | [**AdaptiveSmoothDecor**](classevam_1_1_adaptive_smooth_decor.md) &lt;class TMotor, tMinTimeConstantMs, tMaxTimeConstantMs&gt;<br>_Decorator with adaptive smoothing based on input rate of change._  |
| struct | [**CurveConfig**](structevam_1_1_curve_config.md) <br>_Configuration structure for_ [_**CurveDecor**_](classevam_1_1_curve_decor.md) _._ |
| class | [**CurveDecor**](classevam_1_1_curve_decor.md) &lt;class TMotor, tBend&gt;<br>_Decorator that applies an S-curve (nonlinear) transformation to the control signal._  |
| struct | [**DirectionalConfig**](structevam_1_1_directional_config.md) <br>_Configuration structure for_ [_**DirectionalMotor**_](classevam_1_1_directional_motor.md) _._ |
| class | [**DirectionalMotor**](classevam_1_1_directional_motor.md) &lt;class Driver, kMaxBackward, kMinBackward, kMinForward, kMaxForward&gt;<br>_Bidirectional motor controller (forward/reverse)._  |
| struct | [**ForwardConfig**](structevam_1_1_forward_config.md) <br>_Configuration structure for_ [_**ForwardMotor**_](classevam_1_1_forward_motor.md) _._ |
| class | [**ForwardMotor**](classevam_1_1_forward_motor.md) &lt;class Driver, kMinValue, kMaxValue&gt;<br>_Unidirectional forward-only motor controller (e.g., aircraft ESC, throttle)._  |
| class | [**IMotor**](classevam_1_1_i_motor.md) <br> |
| class | [**IMotorMaker**](classevam_1_1_i_motor_maker.md) &lt;class TMotor&gt;<br> |
| struct | [**InertiaConfig**](structevam_1_1_inertia_config.md) <br>_Configuration structure for_ [_**InertiaDecor**_](classevam_1_1_inertia_decor.md) _._ |
| class | [**InertiaDecor**](classevam_1_1_inertia_decor.md) &lt;class TMotor, tInertiaMass&gt;<br>_Decorator that simulates mechanical inertia (flywheel effect)._  |
| struct | [**KickConfig**](structevam_1_1_kick_config.md) <br>_Configuration structure for_ [_**KickDecor**_](classevam_1_1_kick_decor.md) _._ |
| class | [**KickDecor**](classevam_1_1_kick_decor.md) &lt;class TMotor, tDefaultKickDurationMs, tDefaultKickPower&gt;<br>_Decorator that applies a momentary kick to overcome static friction._  |
| class | [**LinearActuator**](classevam_1_1_linear_actuator.md) &lt;class Driver, kMinValue, kMaxValue&gt;<br>_Linear actuator controller (position control)._  |
| struct | [**LinearActuatorConfig**](structevam_1_1_linear_actuator_config.md) <br>_Configuration structure for_ [_**LinearActuator**_](classevam_1_1_linear_actuator.md) _._ |
| struct | [**MedianConfig**](structevam_1_1_median_config.md) <br>_Configuration structure for_ [_**MedianDecor**_](classevam_1_1_median_decor.md) _._ |
| class | [**MedianDecor**](classevam_1_1_median_decor.md) &lt;class TMotor, tWindowSize&gt;<br>_Decorator that applies median filtering with fixed time base._  |
| struct | [**MinmaxConfig**](structevam_1_1_minmax_config.md) <br>_Configuration structure for_ [_**MinmaxDecor**_](classevam_1_1_minmax_decor.md) _._ |
| class | [**MinmaxDecor**](classevam_1_1_minmax_decor.md) &lt;class TMotor, N&gt;<br>_Decorator that applies a min-max (morphological) filter to the control signal._  |
| struct | [**PwmConfig**](structevam_1_1_pwm_config.md) <br>_Configuration structure for_ [_**PwmDriver**_](classevam_1_1_pwm_driver.md) _._ |
| class | [**PwmDriver**](classevam_1_1_pwm_driver.md) &lt;kPin&gt;<br>_Simple PWM output driver (unipolar)._  |
| class | [**RingBuffer**](classevam_1_1_ring_buffer.md) &lt;typename T, N&gt;<br> |
| struct | [**ServoConfig**](structevam_1_1_servo_config.md) <br>_Configuration structure for_ [_**ServoDriver**_](classevam_1_1_servo_driver.md) _._ |
| class | [**ServoDriver**](classevam_1_1_servo_driver.md) &lt;kPin, kMinPulse, kMiddlePulse, kMaxPulse&gt;<br>_Servo driver using standard Arduino Servo library._  |
| struct | [**SlidingWindowConfig**](structevam_1_1_sliding_window_config.md) <br>_Configuration structure for_ [_**SlidingWindowDecor**_](classevam_1_1_sliding_window_decor.md) _._ |
| class | [**SlidingWindowDecor**](classevam_1_1_sliding_window_decor.md) &lt;class TMotor, N&gt;<br>_Decorator that applies a simple moving average (sliding window) filter._  |
| struct | [**SoftwareServoConfig**](structevam_1_1_software_servo_config.md) <br>_Configuration structure for_ [_**SoftwareServoDriver**_](classevam_1_1_software_servo_driver.md) _._ |
| class | [**SoftwareServoDriver**](classevam_1_1_software_servo_driver.md) &lt;kPin, kMinPulse, kMiddlePulse, kMaxPulse&gt;<br>_Software-based servo driver using millis() for timing._  |
| class | [**SteeringActuator**](classevam_1_1_steering_actuator.md) &lt;class Driver, kLeftPos, kCenterPos, kRightPos&gt;<br>_Steering actuator (centered servo) controller._  |
| struct | [**SteeringConfig**](structevam_1_1_steering_config.md) <br>_Configuration structure for_ [_**SteeringActuator**_](classevam_1_1_steering_actuator.md) _._ |
| struct | [**TA6586Config**](structevam_1_1_t_a6586_config.md) <br>_Configuration structure for_ [_**TA6586Driver**_](classevam_1_1_t_a6586_driver.md) _._ |
| class | [**TA6586Driver**](classevam_1_1_t_a6586_driver.md) &lt;kForwardPin, kBackwardPin&gt;<br>_Driver for the TA6586 dual H-bridge motor driver._  |
| struct | [**TB6612Config**](structevam_1_1_t_b6612_config.md) <br>_Configuration structure for_ [_**TB6612FNGDriver**_](classevam_1_1_t_b6612_f_n_g_driver.md) _._ |
| class | [**TB6612FNGDriver**](classevam_1_1_t_b6612_f_n_g_driver.md) &lt;kPinSpeed, kPinMode1, kPinMode2&gt;<br>_Driver for the TB6612FNG dual H-bridge motor driver._  |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**ServoDriver**](classevam_1_1_servo_driver.md)&lt; kPin, kMinPulse,(kMaxPulse - kMinPulse)/2+kMinPulse, kMaxPulse &gt; | [**ServoFlatDriver**](#typedef-servoflatdriver)  <br> |
| typedef [**SoftwareServoDriver**](classevam_1_1_software_servo_driver.md)&lt; kPin, kMinPulse,(kMaxPulse - kMinPulse)/2+kMinPulse, kMaxPulse &gt; | [**SoftwareServoFlatDriver**](#typedef-softwareservoflatdriver)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  signed short | [**kDefaultBend**](#variable-kdefaultbend)   = `0`<br> |
|  unsigned short | [**kDefaultKickDurationMs**](#variable-kdefaultkickdurationms)   = `20`<br> |
|  signed short | [**kDefaultKickPower**](#variable-kdefaultkickpower)   = `1000`<br> |
|  unsigned short | [**kDefaultMaxTimeConstantMs**](#variable-kdefaultmaxtimeconstantms)   = `150`<br> |
|  unsigned short | [**kDefaultMinTimeConstantMs**](#variable-kdefaultmintimeconstantms)   = `10`<br> |
|  unsigned short | [**kDefaultWindowSize**](#variable-kdefaultwindowsize)   = `5`<br> |
|  unsigned short | [**kInertiaMass**](#variable-kinertiamass)   = `5`<br> |
|  signed short | [**kMaxBend**](#variable-kmaxbend)   = `10`<br> |
|  signed short | [**kMaxKickPower**](#variable-kmaxkickpower)   = `1000`<br> |
|  unsigned short | [**kMaxTimeConstantLimit**](#variable-kmaxtimeconstantlimit)   = `500`<br> |
|  unsigned short | [**kMaxWindowSize**](#variable-kmaxwindowsize)   = `15`<br> |
|  signed short | [**kMinBend**](#variable-kminbend)   = `-10`<br> |
|  unsigned short | [**kMinTimeConstantLimit**](#variable-kmintimeconstantlimit)   = `5`<br> |
|  unsigned short | [**kMinWindowSize**](#variable-kminwindowsize)   = `3`<br> |












































## Public Types Documentation




### typedef ServoFlatDriver 

```C++
using evam::ServoFlatDriver = ServoDriver<kPin, kMinPulse, (kMaxPulse - kMinPulse) / 2 + kMinPulse, kMaxPulse>;
```




<hr>



### typedef SoftwareServoFlatDriver 

```C++
using evam::SoftwareServoFlatDriver = SoftwareServoDriver<kPin, kMinPulse, (kMaxPulse - kMinPulse) / 2 + kMinPulse, kMaxPulse>;
```




<hr>
## Public Attributes Documentation




### variable kDefaultBend 

```C++
signed short evam::kDefaultBend;
```




<hr>



### variable kDefaultKickDurationMs 

```C++
unsigned short evam::kDefaultKickDurationMs;
```




<hr>



### variable kDefaultKickPower 

```C++
signed short evam::kDefaultKickPower;
```




<hr>



### variable kDefaultMaxTimeConstantMs 

```C++
unsigned short evam::kDefaultMaxTimeConstantMs;
```




<hr>



### variable kDefaultMinTimeConstantMs 

```C++
unsigned short evam::kDefaultMinTimeConstantMs;
```




<hr>



### variable kDefaultWindowSize 

```C++
unsigned short evam::kDefaultWindowSize;
```




<hr>



### variable kInertiaMass 

```C++
unsigned short evam::kInertiaMass;
```




<hr>



### variable kMaxBend 

```C++
signed short evam::kMaxBend;
```




<hr>



### variable kMaxKickPower 

```C++
signed short evam::kMaxKickPower;
```




<hr>



### variable kMaxTimeConstantLimit 

```C++
unsigned short evam::kMaxTimeConstantLimit;
```




<hr>



### variable kMaxWindowSize 

```C++
unsigned short evam::kMaxWindowSize;
```




<hr>



### variable kMinBend 

```C++
signed short evam::kMinBend;
```




<hr>



### variable kMinTimeConstantLimit 

```C++
unsigned short evam::kMinTimeConstantLimit;
```




<hr>



### variable kMinWindowSize 

```C++
unsigned short evam::kMinWindowSize;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/evabIMotor.h`

