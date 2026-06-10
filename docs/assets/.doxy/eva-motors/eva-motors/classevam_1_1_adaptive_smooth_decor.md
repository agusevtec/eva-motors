

# Class evam::AdaptiveSmoothDecor

**template &lt;class TMotor, unsigned short tMinTimeConstantMs, unsigned short tMaxTimeConstantMs&gt;**



[**ClassList**](annotated.md) **>** [**evam**](namespaceevam.md) **>** [**AdaptiveSmoothDecor**](classevam_1_1_adaptive_smooth_decor.md)



_Decorator with adaptive smoothing based on input rate of change._ [More...](#detailed-description)

* `#include <evamAdaptiveSmoothDecor.h>`



Inherits the following classes: Heartbeat,  TMotor


































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**AdaptiveSmoothDecor**](#function-adaptivesmoothdecor-12) () <br> |
|   | [**AdaptiveSmoothDecor**](#function-adaptivesmoothdecor-22) ([**AdaptiveSmoothConfig**](structevam_1_1_adaptive_smooth_config.md) config, Args... args) <br> |
|  unsigned short | [**GetMaxTimeConstantMs**](#function-getmaxtimeconstantms) () const<br> |
|  unsigned short | [**GetMinTimeConstantMs**](#function-getmintimeconstantms) () const<br> |
|  void | [**Go**](#function-go) (signed short aValue) <br> |
|  void | [**SetMaxTimeConstantMs**](#function-setmaxtimeconstantms) (unsigned short value) <br> |
|  void | [**SetMinTimeConstantMs**](#function-setmintimeconstantms) (unsigned short value) <br> |
|  void | [**SetupRange**](#function-setuprange) (unsigned short minTimeConstantMs, unsigned short maxTimeConstantMs) <br> |
























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



### function GetMaxTimeConstantMs 

```C++
inline unsigned short evam::AdaptiveSmoothDecor::GetMaxTimeConstantMs () const
```




<hr>



### function GetMinTimeConstantMs 

```C++
inline unsigned short evam::AdaptiveSmoothDecor::GetMinTimeConstantMs () const
```




<hr>



### function Go 

```C++
inline void evam::AdaptiveSmoothDecor::Go (
    signed short aValue
) 
```




<hr>



### function SetMaxTimeConstantMs 

```C++
inline void evam::AdaptiveSmoothDecor::SetMaxTimeConstantMs (
    unsigned short value
) 
```




<hr>



### function SetMinTimeConstantMs 

```C++
inline void evam::AdaptiveSmoothDecor::SetMinTimeConstantMs (
    unsigned short value
) 
```




<hr>



### function SetupRange 

```C++
inline void evam::AdaptiveSmoothDecor::SetupRange (
    unsigned short minTimeConstantMs,
    unsigned short maxTimeConstantMs
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

