

# Namespace evam



[**Namespace List**](namespaces.md) **>** [**evam**](namespaceevam.md)




















## Classes

| Type | Name |
| ---: | :--- |
| class | [**AdaptiveSmoothDecor**](classevam_1_1_adaptive_smooth_decor.md) &lt;class Motor, kMinTimeConstantMs, kMaxTimeConstantMs&gt;<br>_Decorator with adaptive smoothing based on input rate of change._  |
| class | [**CurveDecor**](classevam_1_1_curve_decor.md) &lt;class Motor, kBend&gt;<br>_Decorator that applies an S-curve (nonlinear) transformation to the control signal._  |
| class | [**DirectionalMotor**](classevam_1_1_directional_motor.md) &lt;class Driver, kMaxBackward, kMinBackward, kMinForward, kMaxForward&gt;<br>_Bidirectional motor controller (forward/reverse)._  |
| class | [**ForwardMotor**](classevam_1_1_forward_motor.md) &lt;class Driver, kMinValue, kMaxValue&gt;<br>_Unidirectional forward-only motor controller (e.g., aircraft ESC, throttle)._  |
| class | [**InertiaDecor**](classevam_1_1_inertia_decor.md) &lt;class Motor, kInertiaMass&gt;<br>_Decorator that simulates mechanical inertia (flywheel effect)._  |
| class | [**KickDecor**](classevam_1_1_kick_decor.md) &lt;class Motor, kDefaultKickDuration, kDefaultKickPower&gt;<br>_Decorator that applies a momentary kick to overcome static friction._  |
| class | [**LinearActuator**](classevam_1_1_linear_actuator.md) &lt;class Driver, kMinValue, kMaxValue&gt;<br>_Linear actuator controller (position control)._  |
| class | [**MinmaxDecor**](classevam_1_1_minmax_decor.md) &lt;class Motor, N&gt;<br>_Decorator that applies a min-max (morphological) filter to the control signal._  |
| class | [**PwmDriver**](classevam_1_1_pwm_driver.md) &lt;kPin&gt;<br>_Simple PWM output driver (unipolar)._  |
| class | [**RingBuffer**](classevam_1_1_ring_buffer.md) &lt;typename T, N&gt;<br> |
| class | [**ServoDriver**](classevam_1_1_servo_driver.md) &lt;kPin&gt;<br>_Servo driver using standard Arduino Servo library._  |
| class | [**SlidingWindowDecor**](classevam_1_1_sliding_window_decor.md) &lt;class Motor, N&gt;<br>_Decorator that applies a simple moving average (sliding window) filter._  |
| class | [**SoftwareServoDriver**](classevam_1_1_software_servo_driver.md) &lt;kPin, kMinPulse, kMaxPulse&gt;<br>_Software-based servo driver using millis() for timing._  |
| class | [**SteeringActuator**](classevam_1_1_steering_actuator.md) &lt;class Driver, kLeftPos, kCenterPos, kRightPos&gt;<br>_Steering actuator (centered servo) controller._  |
| class | [**TA6586Driver**](classevam_1_1_t_a6586_driver.md) &lt;kForwardPin, kBackwardPin&gt;<br>_Driver for the TA6586 dual H-bridge motor driver._  |
| class | [**TB6612FNGDriver**](classevam_1_1_t_b6612_f_n_g_driver.md) &lt;kPinSpeed, kPinMode1, kPinMode2&gt;<br>_Driver for the TB6612FNG dual H-bridge motor driver._  |



















































------------------------------
The documentation for this class was generated from the following file `src/evamAdaptiveSmoothDecor.h`

