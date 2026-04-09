

# Class evam::MedianDecor

**template &lt;class Motor, unsigned short kWindowSize&gt;**



[**ClassList**](annotated.md) **>** [**evam**](namespaceevam.md) **>** [**MedianDecor**](classevam_1_1_median_decor.md)



_Decorator that applies median filtering with fixed time base._ [More...](#detailed-description)

* `#include <evamMedianDecor.h>`



Inherits the following classes: Heartbeat,  Motor


































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Go**](#function-go) (signed short aValue) <br> |
|   | [**MedianDecor**](#function-mediandecor) () <br> |
|  void | [**Reset**](#function-reset) () <br> |
























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



### function MedianDecor 

```C++
inline evam::MedianDecor::MedianDecor () 
```




<hr>



### function Reset 

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

