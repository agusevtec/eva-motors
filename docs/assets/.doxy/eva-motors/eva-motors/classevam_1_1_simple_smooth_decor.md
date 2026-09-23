

# Class evam::SimpleSmoothDecor

**template &lt;class TMotor, unsigned short N&gt;**



[**ClassList**](annotated.md) **>** [**evam**](namespaceevam.md) **>** [**SimpleSmoothDecor**](classevam_1_1_simple_smooth_decor.md)



_Decorator applying a simple moving average (sliding window) filter._ [More...](#detailed-description)

* `#include <evamSimpleSmoothDecor.h>`



Inherits the following classes: TMotor


































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Go**](#function-go) (signed short value) <br>_Set the target control value._  |
|   | [**SimpleSmoothDecor**](#function-simplesmoothdecor) (Args... args) <br> |




























## Detailed Description


SimpleAverageDecor has no runtime parameters besides N. This decorator does not own a heartbeat; it only transforms the value. Wrap it with [**SampledDecor**](classevam_1_1_sampled_decor.md) to get periodic output: 




**Template parameters:**


* `TMotor` Base motor class (must implement [**Go(signed short)**](classevam_1_1_simple_smooth_decor.md#function-go)) 
* `N` Window size (number of values to average). Must be &gt;= 1. 




    
## Public Functions Documentation




### function Go 

_Set the target control value._ 
```C++
inline void evam::SimpleSmoothDecor::Go (
    signed short value
) 
```





**Parameters:**


* `value` Target control value, range -1000..1000 




        

<hr>



### function SimpleSmoothDecor 

```C++
template<typename... Args>
inline evam::SimpleSmoothDecor::SimpleSmoothDecor (
    Args... args
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/evamSimpleSmoothDecor.h`

