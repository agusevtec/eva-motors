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
     * @tparam kKickDuration Kick pulse duration in milliseconds. Default: 20ms.
     * @tparam kKickPower Kick power. Range: -1000..1000. Default: 1000 (full power).
     */
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
        /**
         * @brief Configure kickstart parameters at once.
         *
         * @param aKickDuration Kick pulse duration in milliseconds
         * @param aKickPower Kick power, range -1000..1000
         */
        void SetupKickstart(unsigned short aKickDuration, signed short aKickPower)
        {
            // TODO: think care
            //  SetKickDuration(aKickDuration);
            //  SetKickPower(aKickPower);
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
