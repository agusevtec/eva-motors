

# File evamKickDecor.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamKickDecor.h**](evam_kick_decor_8h.md)

[Go to the documentation of this file](evam_kick_decor_8h.md)


```C++
#pragma once

#include <Arduino.h>
#include <evaTickable.h>

using namespace eva;

namespace evam
{
    template <class Motor, unsigned short kDefaultKickDuration = 20, signed short kDefaultKickPower = 1000>
    class KickDecor : public virtual Tickable, public Motor
    {
        static_assert(kDefaultKickDuration > 0, "kDefaultKickDuration must be > 0");
        static_assert(kDefaultKickPower >= -1000 && kDefaultKickPower <= 1000, "kDefaultKickPower out of range");

    private:
        signed short mTargetSpeed = 0;
        unsigned long mHoldingStartedAt = 0;

        unsigned short mKickDuration = kDefaultKickDuration;
        signed short mKickPower = kDefaultKickPower;

        signed short calculateKickPower(signed short aValue) const
        {
            if ((mTargetSpeed <= 0) && (aValue > 0))
                return mKickPower;

            if ((mTargetSpeed >= 0) && (aValue < 0))
                return -mKickPower;

            return 0;
        }

        void tick() override
        {
            if (!mHoldingStartedAt)
                return;

            if (millis() - mHoldingStartedAt < mKickDuration)
                return;

            Motor::Go(mTargetSpeed);
            mHoldingStartedAt = 0;
        }

    public:
        void SetupKickstart(unsigned short aKickDuration, signed short aKickPower)
        {
            SetKickDuration(aKickDuration);
            SetKickPower(aKickPower);
        }

        void SetKickDuration(unsigned short aDuration)
        {
            if (aDuration > 0)
                mKickDuration = aDuration;
        }

        unsigned short GetKickDuration() const
        {
            return mKickDuration;
        }

        void SetKickPower(signed short aPower)
        {
            mKickPower = constrain(aPower, -1000, 1000);
        }

        signed short GetKickPower() const
        {
            return mKickPower;
        }

        void Go(signed short aValue)
        {
            signed short needKick = calculateKickPower(aValue);
            mTargetSpeed = aValue;

            if (needKick)
            {
                Motor::Go(needKick);
                mHoldingStartedAt = millis();
                return;
            }

            if (mHoldingStartedAt)
                return;

            Motor::Go(aValue);
        }
    };
}
```


