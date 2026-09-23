

# File evamAdaptiveSmoothDecor.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamAdaptiveSmoothDecor.h**](evam_adaptive_smooth_decor_8h.md)

[Go to the documentation of this file](evam_adaptive_smooth_decor_8h.md)


```C++
#pragma once

#include <evafAdaptiveSmooth.h>
#include "evaStdReaders.h"

namespace evam
{
    struct AdaptiveSmoothConfig
    {
        unsigned short minTimeConstantTicks;
        unsigned short maxTimeConstantTicks;

        AdaptiveSmoothConfig(unsigned short minTimeConstantTicks,
                             unsigned short maxTimeConstantTicks)
            : minTimeConstantTicks(minTimeConstantTicks),
              maxTimeConstantTicks(maxTimeConstantTicks) {}
    };

    template <class TMotor,
              unsigned short tMinTimeConstantTicks = evaf::kDefaultMinTimeConstantTicks,
              unsigned short tMaxTimeConstantTicks = evaf::kDefaultMaxTimeConstantTicks>
    class AdaptiveSmoothDecor
        : public TMotor
    {
    private:
        using Filter = evaf::AdaptiveSmooth<eva::ValueReader,
                                            tMinTimeConstantTicks,
                                            tMaxTimeConstantTicks>;

        Filter mFilter;

    public:
        AdaptiveSmoothDecor() : TMotor() {}

        template <typename... Args>
        AdaptiveSmoothDecor(AdaptiveSmoothConfig config, Args... args)
            : TMotor(args...),
              mFilter(config.minTimeConstantTicks,
                      config.maxTimeConstantTicks) {}

        void Go(signed short value)
        {
            mFilter.setValue(constrain(value, -1000, 1000));
            TMotor::Go(mFilter.getValue());
        }

        void setMinTimeConstantTicks(unsigned short value)
        {
            mFilter.setMinTimeConstantTicks(value);
        }

        unsigned short getMinTimeConstantTicks() const
        {
            return mFilter.getMinTimeConstantTicks();
        }

        void setMaxTimeConstantTicks(unsigned short value)
        {
            mFilter.setMaxTimeConstantTicks(value);
        }

        unsigned short getMaxTimeConstantTicks() const
        {
            return mFilter.getMaxTimeConstantTicks();
        }
    };
}
```


