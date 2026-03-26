

# File evamInertiaDecor.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamInertiaDecor.h**](evam_inertia_decor_8h.md)

[Go to the documentation of this file](evam_inertia_decor_8h.md)


```C++
#ifndef MOTORINERTIADECORATOR_H
#define MOTORINERTIADECORATOR_H

#pragma once
#include <Arduino.h>
#include <evaTickable.h>
using namespace eva;

namespace evam
{
    template <class Motor, unsigned short kInertiaMass = 10>
    class InertiaDecor : public virtual Tickable, public Motor
    {
        static_assert(0 < kInertiaMass && kInertiaMass < 200, "kInertiaMass must be  1 .. 100");

    private:
        static constexpr unsigned long kUpdateIntervalMs = 100;

        unsigned long mLastSpeedUpdateWasAt = 0;
        signed short mDesiredSpeed = 0;
        signed short mSpeed = 0;
        unsigned short mInertiaMass = kInertiaMass;

        signed short calcSpeed() const
        {
            if (mDesiredSpeed * mSpeed < 0)
                return mDesiredSpeed;

            if (abs(mDesiredSpeed) > abs(mSpeed))
                return mDesiredSpeed;

            signed short delta = mDesiredSpeed - mSpeed;
            signed short step = 2 * delta / mInertiaMass;
            signed short extraStep = (mDesiredSpeed > mSpeed) + (mDesiredSpeed < mSpeed);
            return mSpeed + step - extraStep;
        }

        void tick() override
        {
            unsigned long now = millis();
            if (now - mLastSpeedUpdateWasAt < kUpdateIntervalMs)
                return;
            mLastSpeedUpdateWasAt = now;

            mSpeed = calcSpeed();
            Motor::Go(mSpeed);
        }

    public:
        void SetInertiaMass(unsigned short aValue)
        {
            mInertiaMass = constrain(aValue, 1, 200);
        }

        void Go(int aSpeed)
        {
            mDesiredSpeed = aSpeed;
            if (aSpeed == calcSpeed())
            {
                mSpeed = aSpeed;
                Motor::Go(aSpeed);
            }
        }
    };
}
#endif
```


