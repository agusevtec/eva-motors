

# File evamSimpleSmoothDecor.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamSimpleSmoothDecor.h**](evam_simple_smooth_decor_8h.md)

[Go to the documentation of this file](evam_simple_smooth_decor_8h.md)


```C++
#pragma once

#include <evafSimpleAverage.h>
#include <evaStdReaders.h>

namespace evam
{
    template <class TMotor, unsigned short N>
    class SimpleSmoothDecor : public TMotor
    {
    private:
        evaf::SimpleAverage<eva::ValueReader, N> mFilter;

    public:
        //SimpleSmoothDecor() : TMotor() {}

        template <typename... Args>
        SimpleSmoothDecor(Args... args)
            : TMotor(args...) {}

        void Go(signed short value)
        {
            mFilter.setValue(constrain(value, -1000, 1000));
            TMotor::Go(mFilter.getValue());
        }
    };
}
```


