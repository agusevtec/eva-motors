

# Class evam::ForwardMotor

**template &lt;class Driver, int kMinValue, int kMaxValue&gt;**



[**ClassList**](annotated.md) **>** [**evam**](namespaceevam.md) **>** [**ForwardMotor**](classevam_1_1_forward_motor.md)



_Unidirectional forward-only motor controller (e.g., aircraft ESC, throttle)._ [More...](#detailed-description)

* `#include <evamForwardMotor.h>`



Inherits the following classes: Driver


































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ForwardMotor**](#function-forwardmotor-12) () <br> |
|   | [**ForwardMotor**](#function-forwardmotor-22) ([**ForwardConfig**](structevam_1_1_forward_config.md) config, Args... args) <br> |
|  int | [**GetMaxValue**](#function-getmaxvalue) () const<br>_Get maximum output value._  |
|  int | [**GetMinValue**](#function-getminvalue) () const<br>_Get minimum output value._  |
|  void | [**Go**](#function-go) (signed short aLevel) <br>_Apply the control value._  |
|  void | [**SetMaxValue**](#function-setmaxvalue) (int aValue) <br>_Set maximum output value._  |
|  void | [**SetMinValue**](#function-setminvalue) (int aValue) <br>_Set minimum output value._  |
|  void | [**SetupRange**](#function-setuprange) (int minValue, int maxValue) <br>_Configure the output range parameters at once._  |




























## Detailed Description


Maps input range 0..1000 to driver output. Negative inputs are treated as stop (0).




**Template parameters:**


* `Driver` Driver class (must implement actUnipolar(unsigned short)) 
* `kMinValue` Minimum output value (e.g., 20 = stop) 
* `kMaxValue` Maximum output value (e.g., 1000 = full throttle) 




    
## Public Functions Documentation




### function ForwardMotor [1/2]

```C++
inline evam::ForwardMotor::ForwardMotor () 
```




<hr>



### function ForwardMotor [2/2]

```C++
template<typename... Args>
inline evam::ForwardMotor::ForwardMotor (
    ForwardConfig config,
    Args... args
) 
```




<hr>



### function GetMaxValue 

_Get maximum output value._ 
```C++
inline int evam::ForwardMotor::GetMaxValue () const
```





**Returns:**

Current maximum output value. 





        

<hr>



### function GetMinValue 

_Get minimum output value._ 
```C++
inline int evam::ForwardMotor::GetMinValue () const
```





**Returns:**

Current minimum output value. 





        

<hr>



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
    int minValue,
    int maxValue
) 
```





**Parameters:**


* `aMinValue` Minimum output value (stop position) 
* `aMaxValue` Maximum output value (full throttle) 




        

<hr>

------------------------------
The documentation for this class was generated from the following file `src/evamForwardMotor.h`

