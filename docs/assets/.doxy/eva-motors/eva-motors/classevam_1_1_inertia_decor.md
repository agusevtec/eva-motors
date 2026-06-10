

# Class evam::InertiaDecor

**template &lt;class TMotor, unsigned short tInertiaMass&gt;**



[**ClassList**](annotated.md) **>** [**evam**](namespaceevam.md) **>** [**InertiaDecor**](classevam_1_1_inertia_decor.md)



_Decorator that simulates mechanical inertia (flywheel effect)._ [More...](#detailed-description)

* `#include <evamInertiaDecor.h>`



Inherits the following classes: Heartbeat,  TMotor


































## Public Functions

| Type | Name |
| ---: | :--- |
|  unsigned short | [**GetInertiaMass**](#function-getinertiamass) () const<br>_Get the current inertia mass value._  |
|  void | [**Go**](#function-go) (int aSpeed) <br>_Apply the control value with inertia simulation._  |
|   | [**InertiaDecor**](#function-inertiadecor-12) () <br> |
|   | [**InertiaDecor**](#function-inertiadecor-22) ([**InertiaConfig**](structevam_1_1_inertia_config.md) config, Args... args) <br> |
|  void | [**SetInertiaMass**](#function-setinertiamass) (unsigned short aValue) <br>_Set the inertia mass value._  |
























## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**onHeartbeat**](#function-onheartbeat) () override<br> |




## Detailed Description


When decelerating or stopping, speed decreases gradually over time, simulating the effect of mass and inertia. Acceleration and direction changes are applied immediately.




**Template parameters:**


* `Motor` Base motor class (must implement Go(signed short)) 
* `tInertiaMass` Virtual mass (positive). Larger values = slower deceleration. 




    
## Public Functions Documentation




### function GetInertiaMass 

_Get the current inertia mass value._ 
```C++
inline unsigned short evam::InertiaDecor::GetInertiaMass () const
```





**Returns:**

Current inertia mass value 





        

<hr>



### function Go 

_Apply the control value with inertia simulation._ 
```C++
inline void evam::InertiaDecor::Go (
    int aSpeed
) 
```





**Parameters:**


* `aSpeed` Desired speed, range -1000..1000 




        

<hr>



### function InertiaDecor [1/2]

```C++
inline evam::InertiaDecor::InertiaDecor () 
```




<hr>



### function InertiaDecor [2/2]

```C++
template<typename... Args>
inline evam::InertiaDecor::InertiaDecor (
    InertiaConfig config,
    Args... args
) 
```




<hr>



### function SetInertiaMass 

_Set the inertia mass value._ 
```C++
inline void evam::InertiaDecor::SetInertiaMass (
    unsigned short aValue
) 
```





**Parameters:**


* `aValue` Virtual mass, clamped to 1..200 




        

<hr>
## Protected Functions Documentation




### function onHeartbeat 

```C++
inline void evam::InertiaDecor::onHeartbeat () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/evamInertiaDecor.h`

