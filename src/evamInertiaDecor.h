#ifndef MOTORINERTIADECORATOR_H
#define MOTORINERTIADECORATOR_H

#pragma once
#include <Arduino.h>
#include <evaTickable.h>
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
     * @tparam kInertiaMass Virtual mass. Larger values = slower deceleration. Range: 1..200.
     */
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
        /**
         * @brief Set the virtual mass (inertia) value.
         * @param aValue Mass value, clamped to 1..200. Higher = slower deceleration.
         */
        void SetInertiaMass(unsigned short aValue)
        {
            mInertiaMass = constrain(aValue, 1, 200);
        }

        /**
         * @brief Get the current virtual mass (inertia) value.
         * @return Current mass value in range 1..200.
         */
        unsigned short GetInertiaMass() const
        {
            return mInertiaMass;
        }

        /**
         * @brief Apply the control value with inertia simulation.
         * @param aSpeed Desired speed, range -1000..1000.
         */
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
