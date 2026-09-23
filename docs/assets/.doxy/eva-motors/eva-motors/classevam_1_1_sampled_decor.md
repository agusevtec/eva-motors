

# Class evam::SampledDecor

**template &lt;class TMotor&gt;**



[**ClassList**](annotated.md) **>** [**evam**](namespaceevam.md) **>** [**SampledDecor**](classevam_1_1_sampled_decor.md)



_Decorator that owns the heartbeat and periodically drives TMotor._ [More...](#detailed-description)

* `#include <evamSampledDecor.h>`



Inherits the following classes: eva::Heartbeat,  TMotor


































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Go**](#function-go) (signed short value) <br>_Set the target control value._  |
|   | [**SampledDecor**](#function-sampleddecor-12) () <br> |
|   | [**SampledDecor**](#function-sampleddecor-22) (Args... args) <br> |
























## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**onHeartbeat**](#function-onheartbeat) () override<br> |




## Detailed Description


[**SampledDecor**](classevam_1_1_sampled_decor.md) stores the target value and, on every heartbeat, forwards it to TMotor::Go(). Any filter decorators wrapped inside transform the value in their own [**Go()**](classevam_1_1_sampled_decor.md#function-go) before it reaches the motor.


Usage: [**SampledDecor&lt;SimpleSmoothDecor&lt;MyMotor, 5&gt;&gt;**](classevam_1_1_sampled_decor.md) a;




**Template parameters:**


* `TMotor` Wrapped class (must implement [**Go(signed short)**](classevam_1_1_sampled_decor.md#function-go)) 




    
## Public Functions Documentation




### function Go 

_Set the target control value._ 
```C++
inline void evam::SampledDecor::Go (
    signed short value
) 
```





**Parameters:**


* `value` Target control value, range -1000..1000 




        

<hr>



### function SampledDecor [1/2]

```C++
inline evam::SampledDecor::SampledDecor () 
```




<hr>



### function SampledDecor [2/2]

```C++
template<typename... Args>
inline evam::SampledDecor::SampledDecor (
    Args... args
) 
```




<hr>
## Protected Functions Documentation




### function onHeartbeat 

```C++
inline void evam::SampledDecor::onHeartbeat () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/evamSampledDecor.h`

