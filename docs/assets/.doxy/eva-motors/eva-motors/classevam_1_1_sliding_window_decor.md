

# Class evam::SlidingWindowDecor

**template &lt;class TMotor, unsigned short N&gt;**



[**ClassList**](annotated.md) **>** [**evam**](namespaceevam.md) **>** [**SlidingWindowDecor**](classevam_1_1_sliding_window_decor.md)



_Decorator that applies a simple moving average (sliding window) filter._ [More...](#detailed-description)

* `#include <evamSlidingWindowDecor.h>`



Inherits the following classes: TMotor


































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Go**](#function-go) (signed short value) <br>_Apply the control value with moving average filtering._  |
|   | [**SlidingWindowDecor**](#function-slidingwindowdecor-12) () <br> |
|   | [**SlidingWindowDecor**](#function-slidingwindowdecor-22) ([**SlidingWindowConfig**](structevam_1_1_sliding_window_config.md) config, Args... args) <br> |




























## Detailed Description




**Template parameters:**


* `Motor` Base motor class (must implement [**Go(signed short)**](classevam_1_1_sliding_window_decor.md#function-go)) 
* `N` Window size (number of values to average). Must be &gt;= 1.



**Note:**

The filter only produces filtered output after the buffer is full. Before that, values pass through unchanged. For N=1, the filter passes values through without any averaging (no effect). 





    
## Public Functions Documentation




### function Go 

_Apply the control value with moving average filtering._ 
```C++
inline void evam::SlidingWindowDecor::Go (
    signed short value
) 
```





**Parameters:**


* `value` Input control value, range -1000..1000 




        

<hr>



### function SlidingWindowDecor [1/2]

```C++
inline evam::SlidingWindowDecor::SlidingWindowDecor () 
```




<hr>



### function SlidingWindowDecor [2/2]

```C++
template<typename... Args>
inline evam::SlidingWindowDecor::SlidingWindowDecor (
    SlidingWindowConfig config,
    Args... args
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/evamSlidingWindowDecor.h`

