

# Class evam::TA6586Driver

**template &lt;int kForwardPin, int kBackwardPin&gt;**



[**ClassList**](annotated.md) **>** [**evam**](namespaceevam.md) **>** [**TA6586Driver**](classevam_1_1_t_a6586_driver.md)



_Driver for the TA6586 dual H-bridge motor driver._ [More...](#detailed-description)

* `#include <evamTA6586Driver.h>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**TA6586Driver**](#function-ta6586driver) () <br>_Constructor. Initializes pins and stops the motor._  |
























## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**actBipolar**](#function-actbipolar) (signed short aValue) <br>_Set bipolar (signed) control value._  |




## Detailed Description


Pinout: 




**Template parameters:**


* `kForwardPin` PWM pin connected to FI (forward input) 
* `kBackwardPin` PWM pin connected to BI (backward input) 




    
## Public Functions Documentation




### function TA6586Driver 

_Constructor. Initializes pins and stops the motor._ 
```C++
inline evam::TA6586Driver::TA6586Driver () 
```




<hr>
## Protected Functions Documentation




### function actBipolar 

_Set bipolar (signed) control value._ 
```C++
inline void evam::TA6586Driver::actBipolar (
    signed short aValue
) 
```





**Parameters:**


* `aValue` Range -1000..1000, mapped to -255..255 PWM. Positive = forward, negative = reverse, 0 = stop. 




        

<hr>

------------------------------
The documentation for this class was generated from the following file `src/evamTA6586Driver.h`

