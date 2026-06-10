

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
    constexpr unsigned short kDefaultMinTimeConstantMs = 10;
    constexpr unsigned short kDefaultMaxTimeConstantMs = 150;
    constexpr unsigned short kMinTimeConstantLimit = 5;
    constexpr unsigned short kMaxTimeConstantLimit = 500;

    struct AdaptiveSmoothConfig {
        unsigned short minTimeConstantMs;
        unsigned short maxTimeConstantMs;
        
        AdaptiveSmoothConfig(unsigned short minTimeConstantMs, unsigned short maxTimeConstantMs)
            : minTimeConstantMs(constrain(minTimeConstantMs, kMinTimeConstantLimit, kMaxTimeConstantLimit)),
              maxTimeConstantMs(constrain(maxTimeConstantMs, minTimeConstantMs, kMaxTimeConstantLimit)) {}
    };

    template <class TMotor,
              unsigned short tMinTimeConstantMs = kDefaultMinTimeConstantMs,
              unsigned short tMaxTimeConstantMs = kDefaultMaxTimeConstantMs>
    class AdaptiveSmoothDecor : public Heartbeat, public TMotor
    {
        static_assert(tMinTimeConstantMs >= kMinTimeConstantLimit && tMinTimeConstantMs <= kMaxTimeConstantLimit,
                      "tMinTimeConstantMs out of range");
        static_assert(tMaxTimeConstantMs >= tMinTimeConstantMs && tMaxTimeConstantMs <= kMaxTimeConstantLimit,
                      "tMaxTimeConstantMs must be >= tMinTimeConstantMs");

    private:
        static constexpr unsigned long kHeartbeatPeriodMs = 10;
        static constexpr signed short kDeadzone = 3;

        AdaptiveSmoothConfig mConfig;
        
        signed short mTargetValue = 0;
        signed short mCurrentValue = 0;
        signed short mLastTargetValue = 0;
        unsigned short mCurrentTimeConstantMs = tMaxTimeConstantMs;

        unsigned short calculateTimeConstant()
        {
            signed short change = abs(mTargetValue - mLastTargetValue);

            if (change >= 200)
                return mConfig.minTimeConstantMs;
            else if (change <= 5)
                return mConfig.maxTimeConstantMs;
            else
            {
                return mConfig.maxTimeConstantMs - ((change - 5) * (mConfig.maxTimeConstantMs - mConfig.minTimeConstantMs) / 195);
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

            TMotor::Go(mCurrentValue);
        }

    public:
        AdaptiveSmoothDecor() : mConfig(tMinTimeConstantMs, tMaxTimeConstantMs), Heartbeat(kHeartbeatPeriodMs) {}
        
        template<typename... Args>
        AdaptiveSmoothDecor(AdaptiveSmoothConfig config, Args... args) 
            : mConfig(config), Heartbeat(kHeartbeatPeriodMs), TMotor(args...) {}

        void Go(signed short aValue)
        {
            mTargetValue = constrain(aValue, -1000, 1000);
        }

        void SetMinTimeConstantMs(unsigned short value)
        {
            mConfig.minTimeConstantMs = constrain(value, kMinTimeConstantLimit, kMaxTimeConstantLimit);
        }

        unsigned short GetMinTimeConstantMs() const
        {
            return mConfig.minTimeConstantMs;
        }

        void SetMaxTimeConstantMs(unsigned short value)
        {
            mConfig.maxTimeConstantMs = constrain(value, mConfig.minTimeConstantMs, kMaxTimeConstantLimit);
        }

        unsigned short GetMaxTimeConstantMs() const
        {
            return mConfig.maxTimeConstantMs;
        }

        void SetupRange(unsigned short minTimeConstantMs, unsigned short maxTimeConstantMs)
        {
            SetMinTimeConstantMs(minTimeConstantMs);
            SetMaxTimeConstantMs(maxTimeConstantMs);
        }
    };
}
```


