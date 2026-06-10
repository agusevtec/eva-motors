

# Class evam::SoftwareServoDriver

**template &lt;int kPin, int kMinPulse, int kMiddlePulse, int kMaxPulse&gt;**



[**ClassList**](annotated.md) **>** [**evam**](namespaceevam.md) **>** [**SoftwareServoDriver**](classevam_1_1_software_servo_driver.md)



_Software-based servo driver using millis() for timing._ [More...](#detailed-description)

* `#include <evamSoftwareServoDriver.h>`



Inherits the following classes: Tickable


































## Public Functions

| Type | Name |
| ---: | :--- |
|  int | [**GetPin**](#function-getpin) () const<br>_Get the servo pin number._  |
|   | [**SoftwareServoDriver**](#function-softwareservodriver-12) () <br>_Constructor. Initializes the pin as output._  |
|   | [**SoftwareServoDriver**](#function-softwareservodriver-22) ([**SoftwareServoConfig**](structevam_1_1_software_servo_config.md) config, Args... args) <br> |
























## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**actBipolar**](#function-actbipolar) (signed short aValue) <br>_Bipolar (centered) control. Input range -1000..1000. Output: pulse width mapped to kMinPulse..kMaxPulse with center at mid-point._  |
|  void | [**actUnipolar**](#function-actunipolar) (signed short aValue) <br>_Unipolar (absolute) control. Input range 0..1000. Output: pulse width mapped to kMinPulse..kMaxPulse._  |




## Detailed Description


This driver implements servo control without using the hardware PWM limitations of the Arduino Servo library. Each instance manages its own timing and inherits from Tickable to integrate with the event loop.




**Template parameters:**


* `kPin` Servo signal pin number. 
* `kMinPulse` Minimum pulse width in microseconds (default: 1000) 
* `kMiddlePulse` Middle pulse width in microseconds (default: 1500) 
* `kMaxPulse` Maximum pulse width in microseconds (default: 2000) 




    
## Public Functions Documentation




### function GetPin 

_Get the servo pin number._ 
```C++
inline int evam::SoftwareServoDriver::GetPin () const
```





**Returns:**

Pin number used for servo signal. 





        

<hr>



### function SoftwareServoDriver [1/2]

_Constructor. Initializes the pin as output._ 
```C++
inline evam::SoftwareServoDriver::SoftwareServoDriver () 
```




<hr>



### function SoftwareServoDriver [2/2]

```C++
template<typename... Args>
inline evam::SoftwareServoDriver::SoftwareServoDriver (
    SoftwareServoConfig config,
    Args... args
) 
```




<hr>
## Protected Functions Documentation




### function actBipolar 

_Bipolar (centered) control. Input range -1000..1000. Output: pulse width mapped to kMinPulse..kMaxPulse with center at mid-point._ 
```C++
inline void evam::SoftwareServoDriver::actBipolar (
    signed short aValue
) 
```





**Parameters:**


* `aValue` Input value, range -1000..1000. 




        

<hr>



### function actUnipolar 

_Unipolar (absolute) control. Input range 0..1000. Output: pulse width mapped to kMinPulse..kMaxPulse._ 
```C++
inline void evam::SoftwareServoDriver::actUnipolar (
    signed short aValue
) 
```





**Parameters:**


* `aValue` Input value, range 0..1000. 




        

<hr>

------------------------------
The documentation for this class was generated from the following file `src/evamSoftwareServoDriver.h`

