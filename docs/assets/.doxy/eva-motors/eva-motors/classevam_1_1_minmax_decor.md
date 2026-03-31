

# Class evam::MinmaxDecor

**template &lt;class Motor, unsigned char N&gt;**



[**ClassList**](annotated.md) **>** [**evam**](namespaceevam.md) **>** [**MinmaxDecor**](classevam_1_1_minmax_decor.md)



_Decorator that applies a min-max (morphological) filter to the control signal._ [More...](#detailed-description)

* `#include <evamMinmaxDecor.h>`



Inherits the following classes: Motor


































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Go**](#function-go) (signed short value) <br>_Apply the control value with min-max filtering._  |
|   | [**MinmaxDecor**](#function-minmaxdecor) () <br>_Default constructor._  |




























## Detailed Description


The filter effectively removes both positive and negative impulse noise while preserving edges better than a simple moving average. The output is the average of the morphological opening and closing operations, providing symmetric behavior.


This filter divides the ring buffer into N chunks of N elements each, then computes:
* minimax = min of chunk maximums (closing operation)
* maximin = max of chunk minimums (opening operation)
* output = (minimax + maximin) / 2






**Template parameters:**


* `Motor` Base motor class (must implement [**Go(signed short)**](classevam_1_1_minmax_decor.md#function-go)) 
* `N` Number of chunks and chunk size (total buffer size = N \* N)



**Note:**

The filter only produces filtered output after the buffer is full. Before that, values pass through unchanged. 





    
## Public Functions Documentation




### function Go 

_Apply the control value with min-max filtering._ 
```C++
inline void evam::MinmaxDecor::Go (
    signed short value
) 
```



Passes values through unchanged until the ring buffer is full. Once full, each new value triggers:
* Buffer update (overwrites oldest value)
* Recalculation of chunk maximums and minimums
* Output = (minimax + maximin) / 2






**Parameters:**


* `value` Input control value, range -1000..1000 




        

<hr>



### function MinmaxDecor 

_Default constructor._ 
```C++
inline evam::MinmaxDecor::MinmaxDecor () 
```



Initializes the filter with zero values. The buffer starts empty and must be filled with N\*N values before filtering begins. 


        

<hr>

------------------------------
The documentation for this class was generated from the following file `src/evamMinmaxDecor.h`

