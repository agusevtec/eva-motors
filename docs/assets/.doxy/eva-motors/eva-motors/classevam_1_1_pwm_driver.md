

# Class evam::PwmDriver

**template &lt;int kPin&gt;**



[**ClassList**](annotated.md) **>** [**evam**](namespaceevam.md) **>** [**PwmDriver**](classevam_1_1_pwm_driver.md)



_Simple PWM output driver (unipolar)._ [More...](#detailed-description)

* `#include <evamPwmDriver.h>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**PwmDriver**](#function-pwmdriver) () <br>_Constructor. Initializes the pin as output._  |
























## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**actUnipolar**](#function-actunipolar) (unsigned short aValue) <br>_Set unipolar output value._  |




## Detailed Description


Converts 0..1000 input to 0..255 PWM duty cycle. Suitable for MOSFETs and other unipolar devices.




**Template parameters:**


* `kPin` PWM output pin number. 




    
## Public Functions Documentation




### function PwmDriver 

_Constructor. Initializes the pin as output._ 
```C++
inline evam::PwmDriver::PwmDriver () 
```




<hr>
## Protected Functions Documentation




### function actUnipolar 

_Set unipolar output value._ 
```C++
inline void evam::PwmDriver::actUnipolar (
    unsigned short aValue
) 
```





**Parameters:**


* `aValue` Input range 0..1000, mapped to 0..255 PWM. 




        

<hr>

------------------------------
The documentation for this class was generated from the following file `src/evamPwmDriver.h`

