#pragma once

#include <evafAdaptiveAverage.h>
#include "evaStdReaders.h"

namespace evam
{
    /**
     * @brief Configuration structure for AdaptiveSmoothDecor.
     *
     * Runtime parameters for evaf::AdaptiveSmooth. Range checking is
     * delegated to evaf (template defaults + constructor constrain).
     */
    struct AdaptiveSmoothConfig
    {
        unsigned short minTimeConstantTicks;
        unsigned short maxTimeConstantTicks;

        AdaptiveSmoothConfig(unsigned short minTimeConstantTicks,
                             unsigned short maxTimeConstantTicks)
            : minTimeConstantTicks(minTimeConstantTicks),
              maxTimeConstantTicks(maxTimeConstantTicks) {}
    };

    /**
     * @brief Decorator with adaptive smoothing based on input rate of change.
     *
     * This decorator does not own a heartbeat; it only transforms the value.
     * Wrap it with SampledDecor to get periodic output:
     *
     *     SampledDecor<AdaptiveSmoothDecor<MyMotor>> a;
     *
     * @tparam TMotor Base motor class (must implement Go(signed short))
     * @tparam tMinTimeConstantTicks Default minimum time constant. Default: 1
     * @tparam tMaxTimeConstantTicks Default maximum time constant. Default: 15
     */
    template <class TMotor,
              unsigned short tMinTimeConstantTicks = evaf::kDefaultMinTimeConstantTicks,
              unsigned short tMaxTimeConstantTicks = evaf::kDefaultMaxTimeConstantTicks>
    class AdaptiveSmoothDecor
        : public TMotor
    {
    private:
        using Filter = evaf::AdaptiveAverage<eva::ValueReader,
                                            tMinTimeConstantTicks,
                                            tMaxTimeConstantTicks>;

        Filter mFilter;

    public:
        AdaptiveSmoothDecor() : TMotor() {}

        template <typename... Args>
        AdaptiveSmoothDecor(AdaptiveSmoothConfig config, Args... args)
            : TMotor(args...),
              mFilter(config.minTimeConstantTicks,
                      config.maxTimeConstantTicks) {}

        /**
         * @brief Set the target control value.
         * @param value Target control value, range -1000..1000
         */
        void Go(signed short value)
        {
            mFilter.setValue(constrain(value, -1000, 1000));
            TMotor::Go(mFilter.getValue());
        }

        void setMinTimeConstantTicks(unsigned short value)
        {
            mFilter.setMinTimeConstantTicks(value);
        }

        unsigned short getMinTimeConstantTicks() const
        {
            return mFilter.getMinTimeConstantTicks();
        }

        void setMaxTimeConstantTicks(unsigned short value)
        {
            mFilter.setMaxTimeConstantTicks(value);
        }

        unsigned short getMaxTimeConstantTicks() const
        {
            return mFilter.getMaxTimeConstantTicks();
        }
    };
}
