#pragma once
#include <Arduino.h>
#include <evaHeartbeat.h>

using namespace eva;

namespace evam
{
    constexpr unsigned short kInertiaMass = 5;
    /**
     * @brief Configuration structure for InertiaDecor
     */
    struct InertiaConfig
    {
        signed short inertiaMass;

        InertiaConfig(signed short inertiaMass) : inertiaMass(inertiaMass) {}
    };

    /**
     * @brief Decorator that simulates mechanical inertia (flywheel effect).
     *
     * When decelerating or stopping, speed decreases gradually over time,
     * simulating the effect of mass and inertia. Acceleration and direction
     * changes are applied immediately.
     *
     * @tparam Motor Base motor class (must implement Go(signed short))
     * @tparam tInertiaMass Virtual mass (positive). Larger values = slower deceleration.
     */
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

        /**
         * @brief Set the inertia mass value.
         * @param aValue Virtual mass, clamped to 1..200
         */
        void SetInertiaMass(unsigned short aValue)
        {
            mConfig.inertiaMass = constrain(aValue, 1, 200);
        }

        /**
         * @brief Get the current inertia mass value.
         * @return Current inertia mass value
         */
        unsigned short GetInertiaMass() const
        {
            return mConfig.inertiaMass;
        }

        /**
         * @brief Apply the control value with inertia simulation.
         * @param aSpeed Desired speed, range -1000..1000
         */
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
