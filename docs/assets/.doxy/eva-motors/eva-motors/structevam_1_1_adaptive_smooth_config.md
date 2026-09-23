

# Struct evam::AdaptiveSmoothConfig



[**ClassList**](annotated.md) **>** [**evam**](namespaceevam.md) **>** [**AdaptiveSmoothConfig**](structevam_1_1_adaptive_smooth_config.md)



_Configuration structure for_ [_**AdaptiveSmoothDecor**_](classevam_1_1_adaptive_smooth_decor.md) _._[More...](#detailed-description)

* `#include <evamAdaptiveSmoothDecor.h>`





















## Public Attributes

| Type | Name |
| ---: | :--- |
|  unsigned short | [**maxTimeConstantTicks**](#variable-maxtimeconstantticks)  <br> |
|  unsigned short | [**minTimeConstantTicks**](#variable-mintimeconstantticks)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**AdaptiveSmoothConfig**](#function-adaptivesmoothconfig) (unsigned short minTimeConstantTicks, unsigned short maxTimeConstantTicks) <br> |




























## Detailed Description


Runtime parameters for evaf::AdaptiveSmooth. Range checking is delegated to evaf (template defaults + constructor constrain). 


    
## Public Attributes Documentation




### variable maxTimeConstantTicks 

```C++
unsigned short evam::AdaptiveSmoothConfig::maxTimeConstantTicks;
```




<hr>



### variable minTimeConstantTicks 

```C++
unsigned short evam::AdaptiveSmoothConfig::minTimeConstantTicks;
```




<hr>
## Public Functions Documentation




### function AdaptiveSmoothConfig 

```C++
inline evam::AdaptiveSmoothConfig::AdaptiveSmoothConfig (
    unsigned short minTimeConstantTicks,
    unsigned short maxTimeConstantTicks
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `src/evamAdaptiveSmoothDecor.h`

