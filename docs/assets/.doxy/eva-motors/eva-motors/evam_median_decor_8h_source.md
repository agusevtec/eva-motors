

# File evamMedianDecor.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamMedianDecor.h**](evam_median_decor_8h.md)

[Go to the documentation of this file](evam_median_decor_8h.md)


```C++
#pragma once

#include <evafMedian.h>
#include "evaStdReaders.h"

namespace evam
{
    template <class TMotor, unsigned short tWindowSize = evaf::kDefaultWindowSize>
    class MedianDecor : public TMotor
    {
    private:
        evaf::Median<eva::ValueReader, tWindowSize> mFilter;

    public:
        MedianDecor() : TMotor() {}

        template <typename... Args>
        MedianDecor(Args... args) : TMotor(args...) {}

        void Go(signed short value)
        {
            mFilter.setValue(constrain(value, -1000, 1000));
            TMotor::Go(mFilter.getValue());
        }
    };
}
```


