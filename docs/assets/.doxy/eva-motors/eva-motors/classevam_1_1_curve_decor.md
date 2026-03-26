

# Class evam::CurveDecor

**template &lt;class Motor, signed short kBend&gt;**



[**ClassList**](annotated.md) **>** [**evam**](namespaceevam.md) **>** [**CurveDecor**](classevam_1_1_curve_decor.md)



_Decorator that applies an S-curve (nonlinear) transformation to the control signal._ [More...](#detailed-description)

* `#include <evamCurveDecor.h>`



Inherits the following classes: Motor


































## Public Functions

| Type | Name |
| ---: | :--- |
|  signed short | [**GetBend**](#function-getbend) () const<br>_Get the current bend intensity value._  |
|  void | [**Go**](#function-go) (signed short aValue) <br>_Apply the curved transformation and pass to the underlying motor._  |
|  void | [**SetBend**](#function-setbend) (signed short aValue) <br>_Set the bend intensity at runtime._  |




























## Detailed Description


Converts linear input into an S-shaped curve, useful for smoother starts and finer control in the mid-range. Positive bend values create a softer start, negative values create a sharper initial response.




**Template parameters:**


* `Motor` Base motor class (must implement [**Go(signed short)**](classevam_1_1_curve_decor.md#function-go)) 
* `kBend` Bend intensity. Range: -10..10. 0 = linear. 




    
## Public Functions Documentation




### function GetBend 

_Get the current bend intensity value._ 
```C++
inline signed short evam::CurveDecor::GetBend () const
```





**Returns:**

Current bend value in range -10..10. 





        

<hr>



### function Go 

_Apply the curved transformation and pass to the underlying motor._ 
```C++
inline void evam::CurveDecor::Go (
    signed short aValue
) 
```





**Parameters:**


* `aValue` Input control value, range -1000..1000. 




        

<hr>



### function SetBend 

_Set the bend intensity at runtime._ 
```C++
inline void evam::CurveDecor::SetBend (
    signed short aValue
) 
```





**Parameters:**


* `aValue` Bend value, clamped to -10..10. 




        

<hr>

------------------------------
The documentation for this class was generated from the following file `src/evamCurveDecor.h`

