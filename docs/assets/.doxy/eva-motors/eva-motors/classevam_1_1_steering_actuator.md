

# Class evam::SteeringActuator

**template &lt;class Driver, signed short kLeftPos, signed short kCenterPos, signed short kRightPos&gt;**



[**ClassList**](annotated.md) **>** [**evam**](namespaceevam.md) **>** [**SteeringActuator**](classevam_1_1_steering_actuator.md)



_Steering actuator (centered servo) controller._ [More...](#detailed-description)

* `#include <evamSteeringActuator.h>`



Inherits the following classes: Driver


































## Public Functions

| Type | Name |
| ---: | :--- |
|  signed short | [**GetCenterPos**](#function-getcenterpos) () const<br>_Get center position output value._  |
|  signed short | [**GetLeftPos**](#function-getleftpos) () const<br>_Get leftmost position output value._  |
|  signed short | [**GetRightPos**](#function-getrightpos) () const<br>_Get rightmost position output value._  |
|  void | [**Go**](#function-go) (signed short aLevel) <br>_Apply the steering control value._  |
|  void | [**SetCenterPos**](#function-setcenterpos) (signed short aValue) <br>_Set center position output value._  |
|  void | [**SetLeftPos**](#function-setleftpos) (signed short aValue) <br>_Set leftmost position output value._  |
|  void | [**SetRightPos**](#function-setrightpos) (signed short aValue) <br>_Set rightmost position output value._  |
|  void | [**SetupRange**](#function-setuprange) (signed short aLeftPos, signed short aCenterPos, signed short aRightPos) <br>_Configure all position parameters at once._  |




























## Detailed Description


Maps input range -1000..1000 to output positions: -1000 = left position, 0 = center, 1000 = right position.




**Template parameters:**


* `Driver` Driver class (must implement actBipolar(signed short)) 
* `kLeftPos` Output value at -1000 input (leftmost position) 
* `kCenterPos` Output value at 0 input (center position) 
* `kRightPos` Output value at 1000 input (rightmost position) 




    
## Public Functions Documentation




### function GetCenterPos 

_Get center position output value._ 
```C++
inline signed short evam::SteeringActuator::GetCenterPos () const
```





**Returns:**

Current center position output value. 





        

<hr>



### function GetLeftPos 

_Get leftmost position output value._ 
```C++
inline signed short evam::SteeringActuator::GetLeftPos () const
```





**Returns:**

Current leftmost position output value. 





        

<hr>



### function GetRightPos 

_Get rightmost position output value._ 
```C++
inline signed short evam::SteeringActuator::GetRightPos () const
```





**Returns:**

Current rightmost position output value. 





        

<hr>



### function Go 

_Apply the steering control value._ 
```C++
inline void evam::SteeringActuator::Go (
    signed short aLevel
) 
```





**Parameters:**


* `aLevel` Input steering value, range -1000..1000. 




        

<hr>



### function SetCenterPos 

_Set center position output value._ 
```C++
inline void evam::SteeringActuator::SetCenterPos (
    signed short aValue
) 
```





**Parameters:**


* `aValue` Output value, clamped to -1000..1000. 




        

<hr>



### function SetLeftPos 

_Set leftmost position output value._ 
```C++
inline void evam::SteeringActuator::SetLeftPos (
    signed short aValue
) 
```





**Parameters:**


* `aValue` Output value, clamped to -1000..1000. 




        

<hr>



### function SetRightPos 

_Set rightmost position output value._ 
```C++
inline void evam::SteeringActuator::SetRightPos (
    signed short aValue
) 
```





**Parameters:**


* `aValue` Output value, clamped to -1000..1000. 




        

<hr>



### function SetupRange 

_Configure all position parameters at once._ 
```C++
inline void evam::SteeringActuator::SetupRange (
    signed short aLeftPos,
    signed short aCenterPos,
    signed short aRightPos
) 
```





**Parameters:**


* `aLeftPos` Output value at -1000 input (leftmost position), range -1000..1000 
* `aCenterPos` Output value at 0 input (center position), range -1000..1000 
* `aRightPos` Output value at 1000 input (rightmost position), range -1000..1000 




        

<hr>

------------------------------
The documentation for this class was generated from the following file `src/evamSteeringActuator.h`

