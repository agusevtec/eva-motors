

# File evamKickDecor.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamKickDecor.h**](evam_kick_decor_8h.md)

[Go to the documentation of this file](evam_kick_decor_8h.md)


```C++
#pragma once

#include <Arduino.h>
#include <evaDelayTimer.h>
#include <evaHandler.h>

namespace evam
{
    constexpr unsigned short kDefaultKickDurationMs = 20;
    constexpr signed short kDefaultKickPower = 1000;
    constexpr signed short kMaxKickPower = 1000;

    struct KickConfig {
        unsigned short duration;
        signed short power;
        
        KickConfig(unsigned short duration, signed short power) : duration(duration > 0 ? duration : kDefaultKickDurationMs), power(constrain(power, 0, kMaxKickPower)) {}
    };

    template <class TMotor, 
              unsigned short tDefaultKickDurationMs = kDefaultKickDurationMs, 
              signed short tDefaultKickPower = kDefaultKickPower>
    class KickDecor : public TMotor
    {
        static_assert(tDefaultKickDurationMs > 0, "tDefaultKickDurationMs must be > 0");
        static_assert(tDefaultKickPower > 0 && tDefaultKickPower <= kMaxKickPower, "tDefaultKickPower out of range");

    private:
        KickConfig mConfig;

        signed short mTargetSpeed = 0;

        eva::Handler<KickDecor> mKickEndHandler{ this, &KickDecor::onKickEnd };
        eva::DelayTimer mKickTimer{ &mKickEndHandler };

        void onKickEnd(void *sender, eva::CallbackInfo cbInfo)
        {
            TMotor::Go(mTargetSpeed);
        }

        signed short calculateKickPower(signed short aValue) const
        {
            if ((mTargetSpeed <= 0) && (aValue > 0))
                return mConfig.power;

            if ((mTargetSpeed >= 0) && (aValue < 0))
                return -mConfig.power;

            return 0;
        }

    public:
        KickDecor() : mConfig(tDefaultKickDurationMs, tDefaultKickPower) {}
        
        template<typename... Args>
        KickDecor(KickConfig config, Args... args) : TMotor(args...), mConfig(config) {}

        void SetupKickstart(unsigned short duration, signed short power)
        {
            SetKickDuration(duration);
            SetKickPower(power);
        }

        void SetKickDuration(unsigned short aValue)
        {
            if (aValue > 0)
                mConfig.duration = aValue;
        }

        unsigned short GetKickDuration() const
        {
            return mConfig.duration;
        }

        void SetKickPower(signed short aValue)
        {
            mConfig.power = constrain(aValue, 0, 1000);
        }

        signed short GetKickPower() const
        {
            return mConfig.power;
        }

        void Go(signed short aValue)
        {
            signed short needKick = calculateKickPower(aValue);
            mTargetSpeed = aValue;

            if (needKick)
            {
                TMotor::Go(needKick);
                mKickTimer.start(mConfig.duration);
                return;
            }

            if (mKickTimer.isRunning())
                return;

            TMotor::Go(aValue);
        }
    };
}
```


