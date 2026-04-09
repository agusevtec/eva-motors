

# Class evam::InertiaDecor

**template &lt;class Motor, signed short kInertiaMass&gt;**



[**ClassList**](annotated.md) **>** [**evam**](namespaceevam.md) **>** [**InertiaDecor**](classevam_1_1_inertia_decor.md)



_Decorator that simulates mechanical inertia (flywheel effect)._ [More...](#detailed-description)

* `#include <evamInertiaDecor.h>`



Inherits the following classes: Heartbeat,  Motor


































## Public Functions

| Type | Name |
| ---: | :--- |
|  unsigned short | [**GetInertiaMass**](#function-getinertiamass) () const<br> |
|  void | [**Go**](#function-go) (int aSpeed) <br> |
|   | [**InertiaDecor**](#function-inertiadecor) () <br> |
|  void | [**SetInertiaMass**](#function-setinertiamass) (unsigned short aValue) <br> |
























## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**onHeartbeat**](#function-onheartbeat) () override<br> |




## Detailed Description


When decelerating or stopping, speed decreases gradually over time, simulating the effect of mass and inertia. Acceleration and direction changes are applied immediately.




**Template parameters:**


* `Motor` Base motor class (must implement Go(signed short)) 
* `kInertiaMass` Virtual mass (positive). Larger values = slower deceleration. 




    
## Public Functions Documentation




### function GetInertiaMass 

```C++
inline unsigned short evam::InertiaDecor::GetInertiaMass () const
```




<hr>



### function Go 

```C++
inline void evam::InertiaDecor::Go (
    int aSpeed
) 
```




<hr>



### function InertiaDecor 

```C++
inline evam::InertiaDecor::InertiaDecor () 
```




<hr>



### function SetInertiaMass 

```C++
inline void evam::InertiaDecor::SetInertiaMass (
    unsigned short aValue
) 
```




<hr>
## Protected Functions Documentation




### function onHeartbeat 

```C++
inline void evam::InertiaDecor::onHeartbeat () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/evamInertiaDecor.h`

