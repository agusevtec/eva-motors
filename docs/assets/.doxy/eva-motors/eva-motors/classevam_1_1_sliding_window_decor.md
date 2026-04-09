

# Class evam::SlidingWindowDecor

**template &lt;class Motor, unsigned short N&gt;**



[**ClassList**](annotated.md) **>** [**evam**](namespaceevam.md) **>** [**SlidingWindowDecor**](classevam_1_1_sliding_window_decor.md)



_Decorator that applies a simple moving average (sliding window) filter._ [More...](#detailed-description)

* `#include <evamSlidingWindowDecor.h>`



Inherits the following classes: Motor


































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Go**](#function-go) (signed short value) <br>_Apply the control value with moving average filtering._  |




























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

------------------------------
The documentation for this class was generated from the following file `src/evamSlidingWindowDecor.h`

