

# Class evam::SlewRateDecor

**template &lt;class TMotor, unsigned short tMaxStepPerTick&gt;**



[**ClassList**](annotated.md) **>** [**evam**](namespaceevam.md) **>** [**SlewRateDecor**](classevam_1_1_slew_rate_decor.md)



_Decorator that limits maximum rate of change (slew rate / ramp)._ [More...](#detailed-description)

* `#include <evamSlewRateDecor.h>`



Inherits the following classes: TMotor


































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Go**](#function-go) (signed short value) <br>_Set the target control value._  |
|   | [**SlewRateDecor**](#function-slewratedecor-12) () <br> |
|   | [**SlewRateDecor**](#function-slewratedecor-22) ([**SlewRateConfig**](structevam_1_1_slew_rate_config.md) config, Args... args) <br> |
|  unsigned short | [**getMaxStep**](#function-getmaxstep) () const<br> |
|  void | [**setMaxStep**](#function-setmaxstep) (unsigned short maxStep) <br> |




























## Detailed Description


This decorator does not own a heartbeat; it only transforms the value. Wrap it with [**SampledDecor**](classevam_1_1_sampled_decor.md) to get periodic output: 




**Template parameters:**


* `TMotor` Base motor class (must implement [**Go(signed short)**](classevam_1_1_slew_rate_decor.md#function-go)) 
* `tMaxStepPerTick` Default maximum change per tick (1..1000). Default: 50 




    
## Public Functions Documentation




### function Go 

_Set the target control value._ 
```C++
inline void evam::SlewRateDecor::Go (
    signed short value
) 
```





**Parameters:**


* `value` Target control value, range -1000..1000 




        

<hr>



### function SlewRateDecor [1/2]

```C++
inline evam::SlewRateDecor::SlewRateDecor () 
```




<hr>



### function SlewRateDecor [2/2]

```C++
template<typename... Args>
inline evam::SlewRateDecor::SlewRateDecor (
    SlewRateConfig config,
    Args... args
) 
```




<hr>



### function getMaxStep 

```C++
inline unsigned short evam::SlewRateDecor::getMaxStep () const
```




<hr>



### function setMaxStep 

```C++
inline void evam::SlewRateDecor::setMaxStep (
    unsigned short maxStep
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/evamSlewRateDecor.h`

