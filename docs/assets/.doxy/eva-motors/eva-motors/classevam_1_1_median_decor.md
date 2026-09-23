

# Class evam::MedianDecor

**template &lt;class TMotor, unsigned short tWindowSize&gt;**



[**ClassList**](annotated.md) **>** [**evam**](namespaceevam.md) **>** [**MedianDecor**](classevam_1_1_median_decor.md)



_Decorator applying median filtering._ [More...](#detailed-description)

* `#include <evamMedianDecor.h>`



Inherits the following classes: TMotor


































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Go**](#function-go) (signed short value) <br>_Set the target control value._  |
|   | [**MedianDecor**](#function-mediandecor-12) () <br> |
|   | [**MedianDecor**](#function-mediandecor-22) (Args... args) <br> |




























## Detailed Description


Median has no runtime parameters besides the template window size. This decorator does not own a heartbeat; it only transforms the value. Wrap it with [**SampledDecor**](classevam_1_1_sampled_decor.md) to get periodic output: 




**Template parameters:**


* `TMotor` Base motor class (must implement [**Go(signed short)**](classevam_1_1_median_decor.md#function-go)) 
* `tWindowSize` Filter window size (odd number). Default: 5 




    
## Public Functions Documentation




### function Go 

_Set the target control value._ 
```C++
inline void evam::MedianDecor::Go (
    signed short value
) 
```





**Parameters:**


* `value` Target control value, range -1000..1000 




        

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
    Args... args
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/evamMedianDecor.h`

