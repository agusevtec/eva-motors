

# Class evam::AdaptiveSmoothDecor

**template &lt;class Motor, unsigned short kMinTimeConstantMs, unsigned short kMaxTimeConstantMs&gt;**



[**ClassList**](annotated.md) **>** [**evam**](namespaceevam.md) **>** [**AdaptiveSmoothDecor**](classevam_1_1_adaptive_smooth_decor.md)



_Decorator with adaptive smoothing based on input rate of change._ [More...](#detailed-description)

* `#include <evamAdaptiveSmoothDecor.h>`



Inherits the following classes: Heartbeat,  Motor


































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**AdaptiveSmoothDecor**](#function-adaptivesmoothdecor) () <br> |
|  void | [**Go**](#function-go) (signed short aValue) <br> |
























## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**onHeartbeat**](#function-onheartbeat) () override<br> |




## Detailed Description


Automatically adjusts smoothing based on how fast the input is changing. Uses fixed time base from Heartbeat for consistent behavior.




**Template parameters:**


* `Motor` Base motor class (must implement Go(signed short)) 
* `kMinTimeConstantMs` Minimum time constant (fast response). Default: 10ms 
* `kMaxTimeConstantMs` Maximum time constant (heavy smoothing). Default: 150ms 




    
## Public Functions Documentation




### function AdaptiveSmoothDecor 

```C++
inline evam::AdaptiveSmoothDecor::AdaptiveSmoothDecor () 
```




<hr>



### function Go 

```C++
inline void evam::AdaptiveSmoothDecor::Go (
    signed short aValue
) 
```




<hr>
## Protected Functions Documentation




### function onHeartbeat 

```C++
inline void evam::AdaptiveSmoothDecor::onHeartbeat () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/evamAdaptiveSmoothDecor.h`

