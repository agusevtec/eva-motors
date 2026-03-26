

# Class evam::ServoDriver

**template &lt;int kPin&gt;**



[**ClassList**](annotated.md) **>** [**evam**](namespaceevam.md) **>** [**ServoDriver**](classevam_1_1_servo_driver.md)



_Servo driver using standard Arduino Servo library._ [More...](#detailed-description)

* `#include <evamServoDriver.h>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  int | [**GetPin**](#function-getpin) () const<br>_Get the servo pin number._  |
|   | [**ServoDriver**](#function-servodriver) () <br>_Constructor. Attaches the servo to the pin._  |
























## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**actBipolar**](#function-actbipolar) (signed short aValue) <br>_Bipolar (centered) control. Input range -1000..1000. Output: 1500µs ± input\_mapped._  |
|  void | [**actUnipolar**](#function-actunipolar) (signed short aValue) <br>_Unipolar (absolute) control. Input range 0..1000. Output: 1000µs + input\_mapped._  |




## Detailed Description


Supports both bipolar (centered) and unipolar (absolute) control modes.




**Template parameters:**


* `kPin` Servo signal pin number. 




    
## Public Functions Documentation




### function GetPin 

_Get the servo pin number._ 
```C++
inline int evam::ServoDriver::GetPin () const
```





**Returns:**

Pin number used for servo signal. 





        

<hr>



### function ServoDriver 

_Constructor. Attaches the servo to the pin._ 
```C++
inline evam::ServoDriver::ServoDriver () 
```




<hr>
## Protected Functions Documentation




### function actBipolar 

_Bipolar (centered) control. Input range -1000..1000. Output: 1500µs ± input\_mapped._ 
```C++
inline void evam::ServoDriver::actBipolar (
    signed short aValue
) 
```





**Parameters:**


* `aValue` Input value, range -1000..1000, clamped to 500..2500µs output. 




        

<hr>



### function actUnipolar 

_Unipolar (absolute) control. Input range 0..1000. Output: 1000µs + input\_mapped._ 
```C++
inline void evam::ServoDriver::actUnipolar (
    signed short aValue
) 
```





**Parameters:**


* `aValue` Input value, range 0..1000, clamped to 500..2500µs output. 




        

<hr>

------------------------------
The documentation for this class was generated from the following file `src/evamServoDriver.h`

