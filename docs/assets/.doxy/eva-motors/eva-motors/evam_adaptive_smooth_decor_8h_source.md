

# File evamAdaptiveSmoothDecor.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamAdaptiveSmoothDecor.h**](evam_adaptive_smooth_decor_8h.md)

[Go to the documentation of this file](evam_adaptive_smooth_decor_8h.md)


```C++
#pragma once

#include <Arduino.h>
#include <evaHeartbeat.h>

using namespace eva;

namespace evam
{
    template <class Motor,
              unsigned short kMinTimeConstantMs = 10,
              unsigned short kMaxTimeConstantMs = 150>
    class AdaptiveSmoothDecor : public Heartbeat, public Motor
    {
        static_assert(kMinTimeConstantMs >= 5 && kMinTimeConstantMs <= 200,
                      "kMinTimeConstantMs out of range 5..200");
        static_assert(kMaxTimeConstantMs >= kMinTimeConstantMs && kMaxTimeConstantMs <= 500,
                      "kMaxTimeConstantMs must be >= kMinTimeConstantMs and <= 500");

    private:
        static constexpr unsigned long kHeartbeatPeriodMs = 10;
        static constexpr signed short kDeadzone = 3;

        signed short mTargetValue = 0;
        signed short mCurrentValue = 0;
        signed short mLastTargetValue = 0;

        unsigned short mCurrentTimeConstantMs = kMaxTimeConstantMs;

        unsigned short calculateTimeConstant()
        {
            signed short change = abs(mTargetValue - mLastTargetValue);

            if (change >= 200)
                return kMinTimeConstantMs;
            else if (change <= 5)
                return kMaxTimeConstantMs;
            else
            {
                return kMaxTimeConstantMs - ((change - 5) * (kMaxTimeConstantMs - kMinTimeConstantMs) / 195);
            }
        }

    protected:
        void onHeartbeat() override
        {
            mCurrentTimeConstantMs = calculateTimeConstant();
            mLastTargetValue = mTargetValue;

            if (abs(mTargetValue) <= kDeadzone && abs(mCurrentValue) <= kDeadzone)
            {
                if (mCurrentValue != 0)
                    mCurrentValue = 0;
            }
            else
            {
                signed long step = (signed long)(mTargetValue - mCurrentValue) * kHeartbeatPeriodMs * 1000 / mCurrentTimeConstantMs;
                mCurrentValue += step / 1000;
                mCurrentValue = constrain(mCurrentValue, -1000, 1000);
            }

            Motor::Go(mCurrentValue);
        }

    public:
        AdaptiveSmoothDecor() : Heartbeat(kHeartbeatPeriodMs)
        {
        }

        void Go(signed short aValue)
        {
            mTargetValue = constrain(aValue, -1000, 1000);
        }
    };

}

```


