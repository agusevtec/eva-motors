

# File evamSlewRateDecor.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamSlewRateDecor.h**](evam_slew_rate_decor_8h.md)

[Go to the documentation of this file](evam_slew_rate_decor_8h.md)


```C++
#pragma once

#include <evafSlewRate.h>
#include "evaStdReaders.h"

namespace evam
{
    struct SlewRateConfig
    {
        unsigned short maxStepPerTick;

        SlewRateConfig(unsigned short maxStepPerTick)
            : maxStepPerTick(maxStepPerTick) {}
    };

    template <class TMotor, unsigned short tMaxStepPerTick = 50>
    class SlewRateDecor
        : public TMotor
    {
    private:
        using Filter = evaf::SlewRate<eva::ValueReader, tMaxStepPerTick>;

        Filter mFilter;

    public:
        SlewRateDecor() : TMotor() {}

        template <typename... Args>
        SlewRateDecor(SlewRateConfig config, Args... args)
            : TMotor(args...),
              mFilter(config.maxStepPerTick) {}

        void Go(signed short value)
        {
            mFilter.setValue(constrain(value, -1000, 1000));
            TMotor::Go(mFilter.getValue());
        }

        void SetMaxStep(unsigned short maxStep)
        {
            mFilter.setMaxStep(maxStep);
        }

        unsigned short GetMaxStep() const
        {
            return mFilter.getMaxStep();
        }
    };
}
```


