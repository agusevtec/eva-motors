

# Class evam::InertiaDecor

**template &lt;class Motor, unsigned short kInertiaMass&gt;**



[**ClassList**](annotated.md) **>** [**evam**](namespaceevam.md) **>** [**InertiaDecor**](classevam_1_1_inertia_decor.md)



_Decorator that simulates mechanical inertia (flywheel effect)._ [More...](#detailed-description)

* `#include <evamInertiaDecor.h>`



Inherits the following classes: Tickable,  Motor


































## Public Functions

| Type | Name |
| ---: | :--- |
|  unsigned short | [**GetInertiaMass**](#function-getinertiamass) () const<br>_Get the current virtual mass (inertia) value._  |
|  void | [**Go**](#function-go) (int aSpeed) <br>_Apply the control value with inertia simulation._  |
|  void | [**SetInertiaMass**](#function-setinertiamass) (unsigned short aValue) <br>_Set the virtual mass (inertia) value._  |




























## Detailed Description


When decelerating or stopping, speed decreases gradually over time, simulating the effect of mass and inertia. Acceleration and direction changes are applied immediately.




**Template parameters:**


* `Motor` Base motor class (must implement Go(signed short)) 
* `kInertiaMass` Virtual mass. Larger values = slower deceleration. Range: 1..200. 




    
## Public Functions Documentation




### function GetInertiaMass 

_Get the current virtual mass (inertia) value._ 
```C++
inline unsigned short evam::InertiaDecor::GetInertiaMass () const
```





**Returns:**

Current mass value in range 1..200. 





        

<hr>



### function Go 

_Apply the control value with inertia simulation._ 
```C++
inline void evam::InertiaDecor::Go (
    int aSpeed
) 
```





**Parameters:**


* `aSpeed` Desired speed, range -1000..1000. 




        

<hr>



### function SetInertiaMass 

_Set the virtual mass (inertia) value._ 
```C++
inline void evam::InertiaDecor::SetInertiaMass (
    unsigned short aValue
) 
```





**Parameters:**


* `aValue` Mass value, clamped to 1..200. Higher = slower deceleration. 




        

<hr>

------------------------------
The documentation for this class was generated from the following file `src/evamInertiaDecor.h`

