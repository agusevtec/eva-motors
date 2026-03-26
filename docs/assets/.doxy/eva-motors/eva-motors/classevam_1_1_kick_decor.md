

# Class evam::KickDecor

**template &lt;class Motor, unsigned short kKickDuration, signed short kKickPower&gt;**



[**ClassList**](annotated.md) **>** [**evam**](namespaceevam.md) **>** [**KickDecor**](classevam_1_1_kick_decor.md)



_Decorator that applies a momentary kick to overcome static friction._ [More...](#detailed-description)

* `#include <evamKickDecor.h>`



Inherits the following classes: Tickable,  Motor


































## Public Functions

| Type | Name |
| ---: | :--- |
|  unsigned short | [**GetKickDuration**](#function-getkickduration) () const<br>_Get kick pulse duration._  |
|  signed short | [**GetKickPower**](#function-getkickpower) () const<br>_Get kick power._  |
|  void | [**Go**](#function-go) (signed short aValue) <br>_Apply the control value with kick-start pulse._  |
|  void | [**SetKickDuration**](#function-setkickduration) (unsigned short aDuration) <br>_Set kick pulse duration._  |
|  void | [**SetKickPower**](#function-setkickpower) (signed short aPower) <br>_Set kick power._  |
|  void | [**SetupKickstart**](#function-setupkickstart) (unsigned short aKickDuration, signed short aKickPower) <br>_Configure kickstart parameters at once._  |




























## Detailed Description


When starting from stop or changing direction, a power pulse is applied for a short duration to overcome inertia and static friction.




**Template parameters:**


* `Motor` Base motor class (must implement [**Go(signed short)**](classevam_1_1_kick_decor.md#function-go)) 
* `kKickDuration` Kick pulse duration in milliseconds. Default: 20ms. 
* `kKickPower` Kick power. Range: -1000..1000. Default: 1000 (full power). 




    
## Public Functions Documentation




### function GetKickDuration 

_Get kick pulse duration._ 
```C++
inline unsigned short evam::KickDecor::GetKickDuration () const
```





**Returns:**

Kick duration in milliseconds. 





        

<hr>



### function GetKickPower 

_Get kick power._ 
```C++
inline signed short evam::KickDecor::GetKickPower () const
```





**Returns:**

Kick power value in range -1000..1000. 





        

<hr>



### function Go 

_Apply the control value with kick-start pulse._ 
```C++
inline void evam::KickDecor::Go (
    signed short aValue
) 
```





**Parameters:**


* `aValue` Desired control value, range -1000..1000. 




        

<hr>



### function SetKickDuration 

_Set kick pulse duration._ 
```C++
inline void evam::KickDecor::SetKickDuration (
    unsigned short aDuration
) 
```





**Parameters:**


* `aDuration` Duration in milliseconds, must be &gt; 0. 




        

<hr>



### function SetKickPower 

_Set kick power._ 
```C++
inline void evam::KickDecor::SetKickPower (
    signed short aPower
) 
```





**Parameters:**


* `aPower` Power value, clamped to -1000..1000. 




        

<hr>



### function SetupKickstart 

_Configure kickstart parameters at once._ 
```C++
inline void evam::KickDecor::SetupKickstart (
    unsigned short aKickDuration,
    signed short aKickPower
) 
```





**Parameters:**


* `aKickDuration` Kick pulse duration in milliseconds 
* `aKickPower` Kick power, range -1000..1000 




        

<hr>

------------------------------
The documentation for this class was generated from the following file `src/evamKickDecor.h`

