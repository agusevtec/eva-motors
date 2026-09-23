

# Class evam::MinmaxDecor

**template &lt;class TMotor, unsigned char N&gt;**



[**ClassList**](annotated.md) **>** [**evam**](namespaceevam.md) **>** [**MinmaxDecor**](classevam_1_1_minmax_decor.md)



_Decorator applying a min-max (morphological) filter._ [More...](#detailed-description)

* `#include <evamMinmaxDecor.h>`



Inherits the following classes: TMotor


































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Go**](#function-go) (signed short value) <br>_Set the target control value._  |
|   | [**MinmaxDecor**](#function-minmaxdecor) (Args... args) <br> |




























## Detailed Description


OpenClose has no runtime parameters besides N.




**Template parameters:**


* `TMotor` Base motor class (must implement [**Go(signed short)**](classevam_1_1_minmax_decor.md#function-go)) 
* `N` Number of chunks and chunk size (total buffer size = N \* N) 




    
## Public Functions Documentation




### function Go 

_Set the target control value._ 
```C++
inline void evam::MinmaxDecor::Go (
    signed short value
) 
```





**Parameters:**


* `value` Target control value, range -1000..1000 




        

<hr>



### function MinmaxDecor 

```C++
template<typename... Args>
inline evam::MinmaxDecor::MinmaxDecor (
    Args... args
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/evamMinmaxDecor.h`

