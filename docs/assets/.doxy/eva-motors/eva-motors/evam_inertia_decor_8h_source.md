

# File evamInertiaDecor.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamInertiaDecor.h**](evam_inertia_decor_8h.md)

[Go to the documentation of this file](evam_inertia_decor_8h.md)


```C++
#pragma once
#include <Arduino.h>
#include <evaHeartbeat.h>

using namespace eva;

namespace evam
{
    constexpr unsigned short kInertiaMass = 5;
    struct InertiaConfig
    {
        signed short inertiaMass;

        InertiaConfig(signed short inertiaMass) : inertiaMass(inertiaMass) {}
    };

    template <class TMotor, unsigned short tInertiaMass = kInertiaMass>
    class InertiaDecor : public Heartbeat, public TMotor
    {
        static_assert(0 < tInertiaMass, "tInertiaMass must be > 0");

    private:
        static constexpr unsigned long kHeartbeatPeriodMs = 100;

        InertiaConfig mConfig;
        signed short mDesiredSpeed = 0;
        signed short mSpeed = 0;

        signed short calcSpeed() const
        {
            if ((mDesiredSpeed != 0) && ((mDesiredSpeed > 0) ^ (mSpeed > 0)))
                return mDesiredSpeed;

            if (abs(mDesiredSpeed) > abs(mSpeed))
                return mDesiredSpeed;

            signed short delta = mDesiredSpeed - mSpeed;
            signed short step = delta / mConfig.inertiaMass;
            if (abs(step) < 2)
                return mDesiredSpeed;
            return mSpeed + step;
        }

    protected:
        void onHeartbeat() override
        {
            mSpeed = calcSpeed();
            TMotor::Go(mSpeed);
        }

    public:
        InertiaDecor() : Heartbeat(kHeartbeatPeriodMs), mConfig(tInertiaMass), mDesiredSpeed(0), mSpeed(0) {}

        template <typename... Args>
        InertiaDecor(InertiaConfig config, Args... args)
            : Heartbeat(kHeartbeatPeriodMs), TMotor(args...), mConfig(config), mDesiredSpeed(0), mSpeed(0) {}

        void SetInertiaMass(unsigned short aValue)
        {
            mConfig.inertiaMass = constrain(aValue, 1, 200);
        }

        unsigned short GetInertiaMass() const
        {
            return mConfig.inertiaMass;
        }

        void Go(int aSpeed)
        {
            mDesiredSpeed = aSpeed;
            if (aSpeed == calcSpeed())
            {
                mSpeed = aSpeed;
                TMotor::Go(mSpeed);
            }
        }
    };
}
```


