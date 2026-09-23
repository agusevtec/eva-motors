

# File evamMinmaxDecor.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamMinmaxDecor.h**](evam_minmax_decor_8h.md)

[Go to the documentation of this file](evam_minmax_decor_8h.md)


```C++
#pragma once

#include <evafMinmax.h>
#include <evaStdReaders.h>

namespace evam
{
    template <class TMotor, unsigned char N>
    class MinmaxDecor : public TMotor
    {
    private:
        evaf::Minmax<eva::ValueReader, N> mFilter;

    public:
        // MinmaxDecor() : eva::Heartbeat(kHeartbeatPeriodMs) {}

        template <typename... Args>
        MinmaxDecor(Args... args) : TMotor(args...) {}

        void Go(signed short value)
        {
            mFilter.setValue(constrain(value, -1000, 1000));
            TMotor::Go(mFilter.getValue());
        }
    };
}
```


