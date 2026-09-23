

# File evamSampledDecor.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamSampledDecor.h**](evam_sampled_decor_8h.md)

[Go to the documentation of this file](evam_sampled_decor_8h.md)


```C++
#pragma once

#include <evaHeartbeat.h>
#include "evaStdReaders.h"

namespace evam
{
    template <class TMotor>
    class SampledDecor : public eva::Heartbeat, public TMotor
    {
    private:
        static constexpr unsigned long kHeartbeatPeriodMs = 10;
        signed short mValue;

    protected:
        void onHeartbeat() override
        {
            TMotor::Go(mValue);
        }

    public:
        SampledDecor() : eva::Heartbeat(kHeartbeatPeriodMs), mValue(0) {}

        template <typename... Args>
        SampledDecor(Args... args) : Heartbeat(kHeartbeatPeriodMs), TMotor(args...), mValue(0) {}

        void Go(signed short value)
        {
            mValue = constrain(value, -1000, 1000);
        }
    };
}
```


