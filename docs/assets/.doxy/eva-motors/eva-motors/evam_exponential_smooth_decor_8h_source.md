

# File evamExponentialSmoothDecor.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamExponentialSmoothDecor.h**](evam_exponential_smooth_decor_8h.md)

[Go to the documentation of this file](evam_exponential_smooth_decor_8h.md)


```C++
#pragma once

#include <evafExponentialSmooth.h>
#include "evaStdReaders.h"

namespace evam
{
    struct ExponentialSmoothConfig
    {
        unsigned short alpha;

        ExponentialSmoothConfig(unsigned short alpha) : alpha(alpha) {}
    };

    template <class TMotor, unsigned short tAlpha = 200>
    class ExponentialSmoothDecor
        : public TMotor
    {
    private:
        using Filter = evaf::ExponentialSmooth<eva::ValueReader, tAlpha>;

        Filter mFilter;

    public:
        ExponentialSmoothDecor() : TMotor() {}

        template <typename... Args>
        ExponentialSmoothDecor(ExponentialSmoothConfig config, Args... args)
            : TMotor(args...),
              mFilter(config.alpha) {}

        void Go(signed short value)
        {
            mFilter.setValue(constrain(value, -1000, 1000));
            TMotor::Go(mFilter.getValue());
        }

        void setAlpha(unsigned short alpha)
        {
            mFilter.setAlpha(alpha);
        }

        unsigned short getAlpha() const
        {
            return mFilter.getAlpha();
        }
    };
}
```


