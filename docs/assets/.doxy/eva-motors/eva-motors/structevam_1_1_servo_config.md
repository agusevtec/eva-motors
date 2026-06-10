

# Struct evam::ServoConfig



[**ClassList**](annotated.md) **>** [**evam**](namespaceevam.md) **>** [**ServoConfig**](structevam_1_1_servo_config.md)



_Configuration structure for_ [_**ServoDriver**_](classevam_1_1_servo_driver.md) _._

* `#include <evamServoDriver.h>`





















## Public Attributes

| Type | Name |
| ---: | :--- |
|  int | [**maxPulse**](#variable-maxpulse)  <br> |
|  int | [**middlePulse**](#variable-middlepulse)  <br> |
|  int | [**minPulse**](#variable-minpulse)  <br> |
|  int | [**pin**](#variable-pin)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ServoConfig**](#function-servoconfig) (int pin, int minPulse, int middlePulse, int maxPulse) <br> |




























## Public Attributes Documentation




### variable maxPulse 

```C++
int evam::ServoConfig::maxPulse;
```




<hr>



### variable middlePulse 

```C++
int evam::ServoConfig::middlePulse;
```




<hr>



### variable minPulse 

```C++
int evam::ServoConfig::minPulse;
```




<hr>



### variable pin 

```C++
int evam::ServoConfig::pin;
```




<hr>
## Public Functions Documentation




### function ServoConfig 

```C++
inline evam::ServoConfig::ServoConfig (
    int pin,
    int minPulse,
    int middlePulse,
    int maxPulse
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/evamServoDriver.h`

