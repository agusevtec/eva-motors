

# File evamKickDecor.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamKickDecor.h**](evam_kick_decor_8h.md)

[Go to the documentation of this file](evam_kick_decor_8h.md)


```C++
#ifndef MOTORKICKDECORATOR_H_
#define MOTORKICKDECORATOR_H_

#pragma once

#include <Arduino.h>
#include <evaTickable.h>

using namespace eva;

namespace evam
{
    template <class Motor, unsigned short kKickDuration = 20, signed short kKickPower = 1000>
    class KickDecor : public virtual Tickable, public Motor
    {
        static_assert(kKickDuration > 0, "kKickDuration must be > 0");
        static_assert(kKickPower >= -1000 && kKickPower <= 1000, "kKickPower out of range");

    private:
        signed short mTargetSpeed = 0;
        unsigned long mHoldingStartedAt = 0;

        signed short calculateKickPower(signed short aValue) const
        {
            if ((mTargetSpeed <= 0) && (aValue > 0))
                return kKickPower;

            if ((mTargetSpeed >= 0) && (aValue < 0))
                return -kKickPower;

            return 0;
        }

        void tick() override
        {
            if (!mHoldingStartedAt)
                return;

            if (millis() - mHoldingStartedAt < kKickDuration)
                return;

            Motor::Go(mTargetSpeed);
            mHoldingStartedAt = 0;
        }

    public:
        void SetupKickstart(unsigned short aKickDuration, signed short aKickPower)
        {
            // TODO: think care
            //  SetKickDuration(aKickDuration);
            //  SetKickPower(aKickPower);
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
#endif // MOTORKICKDECORATOR_H_
```


