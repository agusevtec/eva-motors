

# Class evam::LinearActuator

**template &lt;class Driver, int kMinValue, int kMaxValue&gt;**



[**ClassList**](annotated.md) **>** [**evam**](namespaceevam.md) **>** [**LinearActuator**](classevam_1_1_linear_actuator.md)



_Linear actuator controller (position control)._ [More...](#detailed-description)

* `#include <evamLinearActuator.h>`



Inherits the following classes: Driver


































## Public Functions

| Type | Name |
| ---: | :--- |
|  int | [**GetMaxValue**](#function-getmaxvalue) () const<br>_Get maximum output value (position at 1000 input)._  |
|  int | [**GetMinValue**](#function-getminvalue) () const<br>_Get minimum output value (position at 0 input)._  |
|  void | [**Go**](#function-go) (signed short aLevel) <br>_Apply the position control value._  |
|  void | [**SetMaxValue**](#function-setmaxvalue) (int aValue) <br>_Set maximum output value (position at 1000 input)._  |
|  void | [**SetMinValue**](#function-setminvalue) (int aValue) <br>_Set minimum output value (position at 0 input)._  |
|  void | [**SetupRange**](#function-setuprange) (int aMinValue, int aMaxValue) <br>_Configure the position range parameters at once._  |




























## Detailed Description


Maps input range 0..1000 linearly to output values. 0 = minimum position, 1000 = maximum position.




**Template parameters:**


* `Driver` Driver class (must implement actUnipolar(unsigned short)) 
* `kMinValue` Output value at 0 input (minimum position) 
* `kMaxValue` Output value at 1000 input (maximum position) 




    
## Public Functions Documentation




### function GetMaxValue 

_Get maximum output value (position at 1000 input)._ 
```C++
inline int evam::LinearActuator::GetMaxValue () const
```





**Returns:**

Current maximum output value. 





        

<hr>



### function GetMinValue 

_Get minimum output value (position at 0 input)._ 
```C++
inline int evam::LinearActuator::GetMinValue () const
```





**Returns:**

Current minimum output value. 





        

<hr>



### function Go 

_Apply the position control value._ 
```C++
inline void evam::LinearActuator::Go (
    signed short aLevel
) 
```





**Parameters:**


* `aLevel` Input position, range 0..1000. 




        

<hr>



### function SetMaxValue 

_Set maximum output value (position at 1000 input)._ 
```C++
inline void evam::LinearActuator::SetMaxValue (
    int aValue
) 
```





**Parameters:**


* `aValue` Output value, clamped to -1000..1000. 




        

<hr>



### function SetMinValue 

_Set minimum output value (position at 0 input)._ 
```C++
inline void evam::LinearActuator::SetMinValue (
    int aValue
) 
```





**Parameters:**


* `aValue` Output value, clamped to -1000..1000. 




        

<hr>



### function SetupRange 

_Configure the position range parameters at once._ 
```C++
inline void evam::LinearActuator::SetupRange (
    int aMinValue,
    int aMaxValue
) 
```





**Parameters:**


* `aMinValue` Output value at 0 input (minimum position), range -1000..1000 
* `aMaxValue` Output value at 1000 input (maximum position), range -1000..1000 




        

<hr>

------------------------------
The documentation for this class was generated from the following file `src/evamLinearActuator.h`

