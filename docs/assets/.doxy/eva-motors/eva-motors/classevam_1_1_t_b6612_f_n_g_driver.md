

# Class evam::TB6612FNGDriver

**template &lt;int kPinSpeed, int kPinMode1, int kPinMode2&gt;**



[**ClassList**](annotated.md) **>** [**evam**](namespaceevam.md) **>** [**TB6612FNGDriver**](classevam_1_1_t_b6612_f_n_g_driver.md)



_Driver for the TB6612FNG dual H-bridge motor driver._ [More...](#detailed-description)

* `#include <evamTB6612Driver.h>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  int | [**GetMode1Pin**](#function-getmode1pin) () const<br>_Get the first direction pin number._  |
|  int | [**GetMode2Pin**](#function-getmode2pin) () const<br>_Get the second direction pin number._  |
|  int | [**GetSpeedPin**](#function-getspeedpin) () const<br>_Get the speed PWM pin number._  |
|   | [**TB6612FNGDriver**](#function-tb6612fngdriver) () <br>_Constructor. Initializes pins and stops the motor._  |
























## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**actBipolar**](#function-actbipolar) (signed short aValue) <br>_Set bipolar (signed) control value._  |




## Detailed Description


Pin connection:
* PWMA - speed control PWM pin
* AIN1 / AIN2 - direction control pins for motor A
* PWMB, BIN1, BIN2 for motor B (use separate instance)






**Template parameters:**


* `kPinSpeed` PWM pin for speed control 
* `kPinMode1` Direction pin 1 (IN1) 
* `kPinMode2` Direction pin 2 (IN2) 




    
## Public Functions Documentation




### function GetMode1Pin 

_Get the first direction pin number._ 
```C++
inline int evam::TB6612FNGDriver::GetMode1Pin () const
```





**Returns:**

Direction pin 1 (IN1) number. 





        

<hr>



### function GetMode2Pin 

_Get the second direction pin number._ 
```C++
inline int evam::TB6612FNGDriver::GetMode2Pin () const
```





**Returns:**

Direction pin 2 (IN2) number. 





        

<hr>



### function GetSpeedPin 

_Get the speed PWM pin number._ 
```C++
inline int evam::TB6612FNGDriver::GetSpeedPin () const
```





**Returns:**

Speed control PWM pin number. 





        

<hr>



### function TB6612FNGDriver 

_Constructor. Initializes pins and stops the motor._ 
```C++
inline evam::TB6612FNGDriver::TB6612FNGDriver () 
```




<hr>
## Protected Functions Documentation




### function actBipolar 

_Set bipolar (signed) control value._ 
```C++
inline void evam::TB6612FNGDriver::actBipolar (
    signed short aValue
) 
```





**Parameters:**


* `aValue` Range -1000..1000. Positive = forward, negative = reverse, 0 = stop. 




        

<hr>

------------------------------
The documentation for this class was generated from the following file `src/evamTB6612Driver.h`

