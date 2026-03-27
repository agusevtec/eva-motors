#ifndef MOTORINERTIADECORATOR_H
#define MOTORINERTIADECORATOR_H

#pragma once
#include <Arduino.h>
#include <evaHeartbeat.h>

using namespace eva;

namespace evam
{
    /**
     * @brief Decorator that simulates mechanical inertia (flywheel effect).
     *
     * When decelerating or stopping, speed decreases gradually over time,
     * simulating the effect of mass and inertia. Acceleration and direction
     * changes are applied immediately.
     *
     * @tparam Motor Base motor class (must implement Go(signed short))
     * @tparam kInertiaMass Virtual mass (positive). Larger values = slower deceleration.
     */
    template <class Motor, signed short kInertiaMass = 5>
    class InertiaDecor : public Heartbeat, public Motor
    {
        static_assert(0 < kInertiaMass, "kInertiaMass must be > 1");

    private:
        static constexpr unsigned long kHeartbeatPeriodMs = 100;
        
        signed short mDesiredSpeed = 0;
        signed short mSpeed = 0;
        signed short mInertiaMass = kInertiaMass;

        signed short calcSpeed() const
        {
            if ((mDesiredSpeed > 0) ^ (mSpeed > 0))
                return mDesiredSpeed;

            if (abs(mDesiredSpeed) > abs(mSpeed))
                return mDesiredSpeed;

            signed short delta = mDesiredSpeed - mSpeed;
            signed short step = 2* delta / mInertiaMass;
            signed short extraStep = (mDesiredSpeed > mSpeed) + (mDesiredSpeed < mSpeed);
            return mSpeed + step - extraStep;
        }

    protected:
        void onHeartbeat() override
        {
            mSpeed = calcSpeed();
            Motor::Go(mSpeed);
        }

    public:
        InertiaDecor() : Heartbeat(kHeartbeatPeriodMs)
        {
        }

        void SetInertiaMass(unsigned short aValue)
        {
            mInertiaMass = constrain(aValue, 1, 200);
        }

        unsigned short GetInertiaMass() const
        {
            return mInertiaMass;
        }

        void Go(int aSpeed)
        {
            mDesiredSpeed = aSpeed;
            if (aSpeed == calcSpeed())
            {
                mSpeed = aSpeed;
                Motor::Go(mSpeed);
            }
        }
    };
}
#endif
