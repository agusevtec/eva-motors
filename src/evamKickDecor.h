#ifndef MOTORKICKDECORATOR_H_
#define MOTORKICKDECORATOR_H_

#pragma once

#include <Arduino.h>
#include <evaTickable.h>

using namespace eva;

namespace evam
{
    /**
     * @brief Decorator that applies a momentary kick to overcome static friction.
     *
     * When starting from stop or changing direction, a power pulse is applied
     * for a short duration to overcome inertia and static friction.
     *
     * @tparam Motor Base motor class (must implement Go(signed short))
     * @tparam kDefaultKickDuration Default kick pulse duration in milliseconds. Default: 20ms.
     * @tparam kDefaultKickPower Default kick power. Range: -1000..1000. Default: 1000 (full power).
     */
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
        /**
         * @brief Configure kickstart parameters at once.
         *
         * @param aKickDuration Kick pulse duration in milliseconds
         * @param aKickPower Kick power, range -1000..1000
         */
        void SetupKickstart(unsigned short aKickDuration, signed short aKickPower)
        {
            SetKickDuration(aKickDuration);
            SetKickPower(aKickPower);
        }

        /**
         * @brief Set kick pulse duration.
         * @param aDuration Duration in milliseconds, must be > 0.
         */
        void SetKickDuration(unsigned short aDuration)
        {
            if (aDuration > 0)
                mKickDuration = aDuration;
        }

        /**
         * @brief Get kick pulse duration.
         * @return Kick duration in milliseconds.
         */
        unsigned short GetKickDuration() const
        {
            return mKickDuration;
        }

        /**
         * @brief Set kick power.
         * @param aPower Power value, clamped to -1000..1000.
         */
        void SetKickPower(signed short aPower)
        {
            mKickPower = constrain(aPower, -1000, 1000);
        }

        /**
         * @brief Get kick power.
         * @return Kick power value in range -1000..1000.
         */
        signed short GetKickPower() const
        {
            return mKickPower;
        }

        /**
         * @brief Apply the control value with kick-start pulse.
         * @param aValue Desired control value, range -1000..1000.
         */
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