

# Class evam::AdaptiveSmoothDecor

**template &lt;class TMotor, unsigned short tMinTimeConstantTicks, unsigned short tMaxTimeConstantTicks&gt;**



[**ClassList**](annotated.md) **>** [**evam**](namespaceevam.md) **>** [**AdaptiveSmoothDecor**](classevam_1_1_adaptive_smooth_decor.md)



_Decorator with adaptive smoothing based on input rate of change._ [More...](#detailed-description)

* `#include <evamAdaptiveSmoothDecor.h>`



Inherits the following classes: TMotor


































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**AdaptiveSmoothDecor**](#function-adaptivesmoothdecor-12) () <br> |
|   | [**AdaptiveSmoothDecor**](#function-adaptivesmoothdecor-22) ([**AdaptiveSmoothConfig**](structevam_1_1_adaptive_smooth_config.md) config, Args... args) <br> |
|  unsigned short | [**GetMaxTimeConstantTicks**](#function-getmaxtimeconstantticks) () const<br> |
|  unsigned short | [**GetMinTimeConstantTicks**](#function-getmintimeconstantticks) () const<br> |
|  void | [**Go**](#function-go) (signed short value) <br>_Set the target control value._  |
|  void | [**SetMaxTimeConstantTicks**](#function-setmaxtimeconstantticks) (unsigned short value) <br> |
|  void | [**SetMinTimeConstantTicks**](#function-setmintimeconstantticks) (unsigned short value) <br> |




























## Detailed Description


This decorator does not own a heartbeat; it only transforms the value. Wrap it with [**SampledDecor**](classevam_1_1_sampled_decor.md) to get periodic output: 




**Template parameters:**


* `TMotor` Base motor class (must implement [**Go(signed short)**](classevam_1_1_adaptive_smooth_decor.md#function-go)) 
* `tMinTimeConstantTicks` Default minimum time constant. Default: 1 
* `tMaxTimeConstantTicks` Default maximum time constant. Default: 15 




    
## Public Functions Documentation




### function AdaptiveSmoothDecor [1/2]

```C++
inline evam::AdaptiveSmoothDecor::AdaptiveSmoothDecor () 
```




<hr>



### function AdaptiveSmoothDecor [2/2]

```C++
template<typename... Args>
inline evam::AdaptiveSmoothDecor::AdaptiveSmoothDecor (
    AdaptiveSmoothConfig config,
    Args... args
) 
```




<hr>



### function GetMaxTimeConstantTicks 

```C++
inline unsigned short evam::AdaptiveSmoothDecor::GetMaxTimeConstantTicks () const
```




<hr>



### function GetMinTimeConstantTicks 

```C++
inline unsigned short evam::AdaptiveSmoothDecor::GetMinTimeConstantTicks () const
```




<hr>



### function Go 

_Set the target control value._ 
```C++
inline void evam::AdaptiveSmoothDecor::Go (
    signed short value
) 
```





**Parameters:**


* `value` Target control value, range -1000..1000 




        

<hr>



### function SetMaxTimeConstantTicks 

```C++
inline void evam::AdaptiveSmoothDecor::SetMaxTimeConstantTicks (
    unsigned short value
) 
```




<hr>



### function SetMinTimeConstantTicks 

```C++
inline void evam::AdaptiveSmoothDecor::SetMinTimeConstantTicks (
    unsigned short value
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/evamAdaptiveSmoothDecor.h`

