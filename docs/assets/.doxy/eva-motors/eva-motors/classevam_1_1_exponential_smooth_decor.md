

# Class evam::ExponentialSmoothDecor

**template &lt;class TMotor, unsigned short tAlpha&gt;**



[**ClassList**](annotated.md) **>** [**evam**](namespaceevam.md) **>** [**ExponentialSmoothDecor**](classevam_1_1_exponential_smooth_decor.md)



_Decorator applying Exponential Moving Average (EMA) filtering._ [More...](#detailed-description)

* `#include <evamExponentialSmoothDecor.h>`



Inherits the following classes: TMotor


































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ExponentialSmoothDecor**](#function-exponentialsmoothdecor-12) () <br> |
|   | [**ExponentialSmoothDecor**](#function-exponentialsmoothdecor-22) ([**ExponentialSmoothConfig**](structevam_1_1_exponential_smooth_config.md) config, Args... args) <br> |
|  unsigned short | [**GetAlpha**](#function-getalpha) () const<br> |
|  void | [**Go**](#function-go) (signed short value) <br>_Set the target control value._  |
|  void | [**SetAlpha**](#function-setalpha) (unsigned short alpha) <br> |




























## Detailed Description


This decorator does not own a heartbeat; it only transforms the value. Wrap it with [**SampledDecor**](classevam_1_1_sampled_decor.md) to get periodic output: 




**Template parameters:**


* `TMotor` Base motor class (must implement [**Go(signed short)**](classevam_1_1_exponential_smooth_decor.md#function-go)) 
* `tAlpha` Default smoothing factor (1..1000). Default: 200 




    
## Public Functions Documentation




### function ExponentialSmoothDecor [1/2]

```C++
inline evam::ExponentialSmoothDecor::ExponentialSmoothDecor () 
```




<hr>



### function ExponentialSmoothDecor [2/2]

```C++
template<typename... Args>
inline evam::ExponentialSmoothDecor::ExponentialSmoothDecor (
    ExponentialSmoothConfig config,
    Args... args
) 
```




<hr>



### function GetAlpha 

```C++
inline unsigned short evam::ExponentialSmoothDecor::GetAlpha () const
```




<hr>



### function Go 

_Set the target control value._ 
```C++
inline void evam::ExponentialSmoothDecor::Go (
    signed short value
) 
```





**Parameters:**


* `value` Target control value, range -1000..1000 




        

<hr>



### function SetAlpha 

```C++
inline void evam::ExponentialSmoothDecor::SetAlpha (
    unsigned short alpha
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/evamExponentialSmoothDecor.h`

