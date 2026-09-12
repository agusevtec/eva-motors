#pragma once

#include <evaHeartbeat.h>
#include <evafSlewRate.h>
#include "evaStdReaders.h"

namespace evam
{
    /**
     * @brief Configuration structure for SlewRateDecor.
     *
     * Runtime parameter for evaf::SlewRate.
     */
    struct SlewRateConfig
    {
        unsigned short maxStepPerTick;

        SlewRateConfig(unsigned short maxStepPerTick)
            : maxStepPerTick(maxStepPerTick) {}
    };

    /**
     * @brief Decorator that limits maximum rate of change (slew rate / ramp).
     *
     * @tparam TMotor Base motor class (must implement Go(signed short))
     * @tparam tMaxStepPerTick Default maximum change per tick (1..1000). Default: 50
     */
    template <class TMotor, unsigned short tMaxStepPerTick = 50>
    class SlewRateDecor
        : public virtual eva::Heartbeat,
          public TMotor
    {
    private:
        static constexpr unsigned long kHeartbeatPeriodMs = 10;

        using Filter = evaf::SlewRate<eva::ValueReader, tMaxStepPerTick>;

        Filter mFilter;

    protected:
        void onHeartbeat() override
        {
            TMotor::Go(mFilter.getValue());
        }

    public:
        SlewRateDecor() : Heartbeat(kHeartbeatPeriodMs) {}

        template <typename... Args>
        SlewRateDecor(SlewRateConfig config, Args... args)
            : Heartbeat(kHeartbeatPeriodMs),
              TMotor(args...),
              mFilter(config.maxStepPerTick) {}

        /**
         * @brief Set the target control value.
         * @param value Target control value, range -1000..1000
         */
        void Go(signed short value)
        {
            mFilter.setValue(constrain(value, -1000, 1000));
        }

        void setMaxStep(unsigned short maxStep)
        {
            mFilter.setMaxStep(maxStep);
        }

        unsigned short getMaxStep() const
        {
            return mFilter.getMaxStep();
        }
    };
}
