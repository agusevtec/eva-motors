

# Class evam::ForwardMotor

**template &lt;class Driver, int kMinValue, int kMaxValue&gt;**



[**ClassList**](annotated.md) **>** [**evam**](namespaceevam.md) **>** [**ForwardMotor**](classevam_1_1_forward_motor.md)



_Unidirectional forward-only motor controller (e.g., aircraft ESC, throttle)._ [More...](#detailed-description)

* `#include <evamForwardMotor.h>`



Inherits the following classes: Driver


































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Go**](#function-go) (signed short aLevel) <br>_Apply the control value._  |
|  void | [**SetMaxValue**](#function-setmaxvalue) (int aValue) <br>_Set maximum output value._  |
|  void | [**SetMinValue**](#function-setminvalue) (int aValue) <br>_Set minimum output value._  |
|  void | [**SetupRange**](#function-setuprange) (int aMinValue, int aMaxValue) <br>_Configure the output range parameters at once._  |




























## Detailed Description


Maps input range 0..1000 to driver output. Negative inputs are treated as stop (0).




**Template parameters:**


* `Driver` Driver class (must implement actUnipolar(unsigned short)) 
* `kMinValue` Minimum output value (e.g., 20 = stop) 
* `kMaxValue` Maximum output value (e.g., 1000 = full throttle) 




    
## Public Functions Documentation




### function Go 

_Apply the control value._ 
```C++
inline void evam::ForwardMotor::Go (
    signed short aLevel
) 
```





**Parameters:**


* `aLevel` Input control value, range 0..1000 (negative treated as 0). 




        

<hr>



### function SetMaxValue 

_Set maximum output value._ 
```C++
inline void evam::ForwardMotor::SetMaxValue (
    int aValue
) 
```





**Parameters:**


* `aValue` Output value, clamped to -1000..1000. 




        

<hr>



### function SetMinValue 

_Set minimum output value._ 
```C++
inline void evam::ForwardMotor::SetMinValue (
    int aValue
) 
```





**Parameters:**


* `aValue` Output value, clamped to -1000..1000. 




        

<hr>



### function SetupRange 

_Configure the output range parameters at once._ 
```C++
inline void evam::ForwardMotor::SetupRange (
    int aMinValue,
    int aMaxValue
) 
```





**Parameters:**


* `aMinValue` Minimum output value (stop position) 
* `aMaxValue` Maximum output value (full throttle) 




        

<hr>

------------------------------
The documentation for this class was generated from the following file `src/evamForwardMotor.h`

