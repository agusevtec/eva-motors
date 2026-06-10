

# Class evam::MedianDecor

**template &lt;class TMotor, unsigned short tWindowSize&gt;**



[**ClassList**](annotated.md) **>** [**evam**](namespaceevam.md) **>** [**MedianDecor**](classevam_1_1_median_decor.md)



_Decorator that applies median filtering with fixed time base._ [More...](#detailed-description)

* `#include <evamMedianDecor.h>`



Inherits the following classes: Heartbeat,  TMotor


































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Go**](#function-go) (signed short aValue) <br> |
|   | [**MedianDecor**](#function-mediandecor-12) () <br> |
|   | [**MedianDecor**](#function-mediandecor-22) ([**MedianConfig**](structevam_1_1_median_config.md) config, Args... args) <br> |
|  void | [**Reset**](#function-reset) () <br>_Reset the filter buffer._  |
























## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**onHeartbeat**](#function-onheartbeat) () override<br> |




## Detailed Description


Samples the input at regular intervals and applies median filtering to remove spikes and noise. Output updates at the sampling rate.




**Template parameters:**


* `Motor` Base motor class (must implement Go(signed short)) 
* `kWindowSize` Filter window size (odd number). Default: 5 




    
## Public Functions Documentation




### function Go 

```C++
inline void evam::MedianDecor::Go (
    signed short aValue
) 
```




<hr>



### function MedianDecor [1/2]

```C++
inline evam::MedianDecor::MedianDecor () 
```




<hr>



### function MedianDecor [2/2]

```C++
template<typename... Args>
inline evam::MedianDecor::MedianDecor (
    MedianConfig config,
    Args... args
) 
```




<hr>



### function Reset 

_Reset the filter buffer._ 
```C++
inline void evam::MedianDecor::Reset () 
```




<hr>
## Protected Functions Documentation




### function onHeartbeat 

```C++
inline void evam::MedianDecor::onHeartbeat () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/evamMedianDecor.h`

