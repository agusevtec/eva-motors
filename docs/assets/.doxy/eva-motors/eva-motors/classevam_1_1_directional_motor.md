

# Class evam::DirectionalMotor

**template &lt;class Driver, signed short kMaxBackward, signed short kMinBackward, signed short kMinForward, signed short kMaxForward&gt;**



[**ClassList**](annotated.md) **>** [**evam**](namespaceevam.md) **>** [**DirectionalMotor**](classevam_1_1_directional_motor.md)



_Bidirectional motor controller (forward/reverse)._ [More...](#detailed-description)

* `#include <evamDirectionalMotor.h>`



Inherits the following classes: Driver


































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Go**](#function-go) (signed short aLevel) <br>_Apply the control value._  |
|  void | [**SetMaxBackward**](#function-setmaxbackward) (signed short aValue) <br>_Set maximum reverse output value._  |
|  void | [**SetMaxForward**](#function-setmaxforward) (signed short aValue) <br>_Set maximum forward output value._  |
|  void | [**SetMinBackward**](#function-setminbackward) (signed short aValue) <br>_Set minimum reverse output value._  |
|  void | [**SetMinForward**](#function-setminforward) (signed short aValue) <br>_Set minimum forward output value._  |
|  void | [**SetupRange**](#function-setuprange) (signed short aMaxBackward, signed short aMinBackward, signed short aMinForward, signed short aMaxForward) <br>_Configure all range parameters at once._  |




























## Detailed Description


Maps a signed input range -1000..1000 to driver-specific output values. Negative values correspond to reverse, positive to forward.




**Template parameters:**


* `Driver` Driver class (must implement actBipolar(signed short)) 
* `kMaxBackward` Maximum reverse output value (e.g., -1000) 
* `kMinBackward` Minimum reverse output value (e.g., -50) 
* `kMinForward` Minimum forward output value (e.g., 50) 
* `kMaxForward` Maximum forward output value (e.g., 1000) 




    
## Public Functions Documentation




### function Go 

_Apply the control value._ 
```C++
inline void evam::DirectionalMotor::Go (
    signed short aLevel
) 
```





**Parameters:**


* `aLevel` Input control value, range -1000..1000. 




        

<hr>



### function SetMaxBackward 

_Set maximum reverse output value._ 
```C++
inline void evam::DirectionalMotor::SetMaxBackward (
    signed short aValue
) 
```





**Parameters:**


* `aValue` Output value, clamped to -1000..1000. 




        

<hr>



### function SetMaxForward 

_Set maximum forward output value._ 
```C++
inline void evam::DirectionalMotor::SetMaxForward (
    signed short aValue
) 
```





**Parameters:**


* `aValue` Output value, clamped to -1000..1000. 




        

<hr>



### function SetMinBackward 

_Set minimum reverse output value._ 
```C++
inline void evam::DirectionalMotor::SetMinBackward (
    signed short aValue
) 
```





**Parameters:**


* `aValue` Output value, clamped to -1000..1000. 




        

<hr>



### function SetMinForward 

_Set minimum forward output value._ 
```C++
inline void evam::DirectionalMotor::SetMinForward (
    signed short aValue
) 
```





**Parameters:**


* `aValue` Output value, clamped to -1000..1000. 




        

<hr>



### function SetupRange 

_Configure all range parameters at once._ 
```C++
inline void evam::DirectionalMotor::SetupRange (
    signed short aMaxBackward,
    signed short aMinBackward,
    signed short aMinForward,
    signed short aMaxForward
) 
```





**Parameters:**


* `aMaxBackward` Maximum reverse output value (-1000..1000) 
* `aMinBackward` Minimum reverse output value (-1000..1000) 
* `aMinForward` Minimum forward output value (-1000..1000) 
* `aMaxForward` Maximum forward output value (-1000..1000) 




        

<hr>

------------------------------
The documentation for this class was generated from the following file `src/evamDirectionalMotor.h`

