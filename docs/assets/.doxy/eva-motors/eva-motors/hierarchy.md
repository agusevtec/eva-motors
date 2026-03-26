
# Class Hierarchy

This inheritance list is sorted roughly, but not completely, alphabetically:


* **class** [**evam::PwmDriver**](classevam_1_1_pwm_driver.md) _Simple PWM output driver (unipolar)._ 
* **class** [**evam::ServoDriver**](classevam_1_1_servo_driver.md) _Servo driver using standard Arduino Servo library._ 
* **class** [**evam::TA6586Driver**](classevam_1_1_t_a6586_driver.md) _Driver for the TA6586 dual H-bridge motor driver._ 
* **class** [**evam::TB6612FNGDriver**](classevam_1_1_t_b6612_f_n_g_driver.md) _Driver for the TB6612FNG dual H-bridge motor driver._ 
* **class** **Motor**    
    * **class** [**evam::CurveDecor**](classevam_1_1_curve_decor.md) _Decorator that applies an S-curve (nonlinear) transformation to the control signal._ 
    * **class** [**evam::InertiaDecor**](classevam_1_1_inertia_decor.md) _Decorator that simulates mechanical inertia (flywheel effect)._ 
    * **class** [**evam::KickDecor**](classevam_1_1_kick_decor.md) _Decorator that applies a momentary kick to overcome static friction._ 
* **class** **Driver**    
    * **class** [**evam::DirectionalMotor**](classevam_1_1_directional_motor.md) _Bidirectional motor controller (forward/reverse)._ 
    * **class** [**evam::ForwardMotor**](classevam_1_1_forward_motor.md) _Unidirectional forward-only motor controller (e.g., aircraft ESC, throttle)._ 
    * **class** [**evam::LinearActuator**](classevam_1_1_linear_actuator.md) _Linear actuator controller (position control)._ 
    * **class** [**evam::SteeringActuator**](classevam_1_1_steering_actuator.md) _Steering actuator (centered servo) controller._ 
* **class** **Tickable**    
    * **class** [**evam::InertiaDecor**](classevam_1_1_inertia_decor.md) _Decorator that simulates mechanical inertia (flywheel effect)._ 
    * **class** [**evam::KickDecor**](classevam_1_1_kick_decor.md) _Decorator that applies a momentary kick to overcome static friction._ 

