#pragma once

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
     * This decorator does not own a heartbeat; it only transforms the value.
     * Wrap it with SampledDecor to get periodic output:
     *
     *     SampledDecor<SlewRateDecor<MyMotor, 50>> a;
     *
     * @tparam TMotor Base motor class (must implement Go(signed short))
     * @tparam tMaxStepPerTick Default maximum change per tick (1..1000). Default: 50
     */
    template <class TMotor, unsigned short tMaxStepPerTick = 50>
    class SlewRateDecor
        : public TMotor
    {
    private:
        using Filter = evaf::SlewRate<eva::ValueReader, tMaxStepPerTick>;

        Filter mFilter;

    public:
        SlewRateDecor() : TMotor() {}

        template <typename... Args>
        SlewRateDecor(SlewRateConfig config, Args... args)
            : TMotor(args...),
              mFilter(config.maxStepPerTick) {}

        /**
         * @brief Set the target control value.
         * @param value Target control value, range -1000..1000
         */
        void Go(signed short value)
        {
            mFilter.setValue(constrain(value, -1000, 1000));
            TMotor::Go(mFilter.getValue());
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
