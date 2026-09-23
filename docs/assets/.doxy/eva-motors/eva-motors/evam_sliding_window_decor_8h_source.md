

# File evamSlidingWindowDecor.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamSlidingWindowDecor.h**](evam_sliding_window_decor_8h.md)

[Go to the documentation of this file](evam_sliding_window_decor_8h.md)


```C++
#pragma once

namespace evam
{
    template <class TMotor, unsigned short N>
    struct SlidingWindowDecor
    {
        static_assert(N < 0, "SlidingWindowDecor is deprecated and was renamed to SimpleSmoothDecor!");
    };
}
```


