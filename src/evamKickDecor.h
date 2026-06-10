#pragma once

#include <Arduino.h>
#include <evaTickable.h>

using namespace eva;

namespace evam
{
    constexpr unsigned short kDefaultKickDurationMs = 20;
    constexpr signed short kDefaultKickPower = 1000;
    constexpr signed short kMaxKickPower = 1000;

    /**
     * @brief Configuration structure for KickDecor
     */
    struct KickConfig {
        unsigned short duration;
        signed short power;
        
        KickConfig(unsigned short duration, signed short power) : duration(duration > 0 ? duration : kDefaultKickDurationMs), power(constrain(power, 0, kMaxKickPower)) {}
    };

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
    template <class TMotor, 
              unsigned short tDefaultKickDurationMs = kDefaultKickDurationMs, 
              signed short tDefaultKickPower = kDefaultKickPower>
    class KickDecor : public virtual Tickable, public TMotor
    {
        static_assert(tDefaultKickDurationMs > 0, "tDefaultKickDurationMs must be > 0");
        static_assert(tDefaultKickPower > 0 && tDefaultKickPower <= kMaxKickPower, "tDefaultKickPower out of range");

    private:
        KickConfig mConfig;
        
        signed short mTargetSpeed = 0;
        unsigned long mHoldingStartedAt = 0;

        signed short calculateKickPower(signed short aValue) const
        {
            if ((mTargetSpeed <= 0) && (aValue > 0))
                return mConfig.power;

            if ((mTargetSpeed >= 0) && (aValue < 0))
                return -mConfig.power;

            return 0;
        }

        void tick() override
        {
            if (!mHoldingStartedAt)
                return;

            if (millis() - mHoldingStartedAt < mConfig.duration)
                return;

            TMotor::Go(mTargetSpeed);
            mHoldingStartedAt = 0;
        }

    public:
        KickDecor() : mConfig(tDefaultKickDurationMs, tDefaultKickPower) {}
        
        template<typename... Args>
        KickDecor(KickConfig config, Args... args) : mConfig(config), TMotor(args...) {}

        /**
         * @brief Configure kickstart parameters at once.
         *
         * @param aKickDuration Kick pulse duration in milliseconds
         * @param aKickPower Kick power, range -1000..1000
         */
        void SetupKickstart(unsigned short duration, signed short power)
        {
            SetKickDuration(duration);
            SetKickPower(power);
        }

        /**
         * @brief Set kick pulse duration.
         * @param aDuration Duration in milliseconds, must be > 0.
         */
        void SetKickDuration(unsigned short aValue)
        {
            if (aValue > 0)
                mConfig.duration = aValue;
        }

        /**
         * @brief Get kick pulse duration.
         * @return Kick duration in milliseconds.
         */
        unsigned short GetKickDuration() const
        {
            return mConfig.duration;
        }

        /**
         * @brief Set kick power.
         * @param aPower Power value, clamped to 0..1000.
         */
        void SetKickPower(signed short aValue)
        {
            mConfig.power = constrain(aValue, 0, 1000);
        }

        /**
         * @brief Get kick power.
         * @return Kick power value in range 0..1000.
         */
        signed short GetKickPower() const
        {
            return mConfig.power;
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
                TMotor::Go(needKick);
                mHoldingStartedAt = millis();
                return;
            }

            if (mHoldingStartedAt)
                return;

            TMotor::Go(aValue);
        }
    };
}
