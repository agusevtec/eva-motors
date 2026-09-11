#pragma once

#include <evafSlewRate.h>
#include "evamValueReader.h"

namespace evam
{
    /**
     * @brief Configuration structure for SlewRateDecor
     */
    struct SlewRateConfig
    {
        unsigned short maxStepPerTick;

        SlewRateConfig(unsigned short maxStepPerTick) : maxStepPerTick(maxStepPerTick) {}
    };

    /**
     * @brief Decorator that limits maximum rate of change (slew rate / ramp) for the control signal.
     *
     * Prevents sharp steps by capping maximum delta per Go() call.
     *
     * @tparam Motor Base motor class (must implement Go(signed short))
     * @tparam tMaxStepPerTick Maximum allowed change per call tick (1..1000). Default: 50
     */
    template <class TMotor, unsigned short tMaxStepPerTick = 50>
    class SlewRateDecor : public TMotor, private evaf::SlewRate<ValueReader, tMaxStepPerTick>
    {
    private:
        SlewRateConfig mConfig;
        using BaseFilter = evaf::SlewRate<ValueReader, tMaxStepPerTick>;

    public:
        SlewRateDecor() : mConfig(tMaxStepPerTick) {}

        template <typename... Args>
        SlewRateDecor(SlewRateConfig config, Args... args)
            : mConfig(config), TMotor(args...) {}

        /**
         * @brief Apply target value with slew rate limiting.
         * @param value Target control value
         */
        void Go(signed short value)
        {
            this->setValue(value);
            signed short filtered = BaseFilter::getValue();
            TMotor::Go(filtered);
        }

        /**
         * @brief Resets current filter value instantly.
         * @param initialValue Initial target value
         */
        void Reset(signed short initialValue = 0)
        {
            BaseFilter::reset(initialValue);
        }

        void SetMaxStep(unsigned short maxStep)
        {
            mConfig.maxStepPerTick = maxStep;
            BaseFilter::setMaxStep(maxStep);
        }

        unsigned short GetMaxStep() const
        {
            return BaseFilter::getMaxStep();
        }
    };

}
