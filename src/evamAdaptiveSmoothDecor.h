#pragma once

#include <evaHeartbeat.h>
#include <evafAdaptiveSmooth.h>
#include "evamValueReader.h"

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
     * The evaf filter is held by composition. Go() writes the target value
     * straight into the filter via ValueReader::setValue; onHeartbeat()
     * pulls the filtered value out and forwards it to TMotor::Go().
     *
     * evaf setters/getters are mirrored under the same names so decorators
     * can be stacked without name clashes.
     *
     * @tparam TMotor Base motor class (must implement Go(signed short))
     * @tparam tMinTimeConstantTicks Default minimum time constant. Default: 1
     * @tparam tMaxTimeConstantTicks Default maximum time constant. Default: 15
     */
    template <class TMotor,
              unsigned short tMinTimeConstantTicks = evaf::kDefaultMinTimeConstantTicks,
              unsigned short tMaxTimeConstantTicks = evaf::kDefaultMaxTimeConstantTicks>
    class AdaptiveSmoothDecor
        : public virtual eva::Heartbeat,
          public TMotor
    {
    private:
        static constexpr unsigned long kHeartbeatPeriodMs = 10;

        using Filter = evaf::AdaptiveSmooth<ValueReader,
                                            tMinTimeConstantTicks,
                                            tMaxTimeConstantTicks>;

        Filter mFilter;

    protected:
        void onHeartbeat() override
        {
            TMotor::Go(mFilter.getValue());
        }

    public:
        AdaptiveSmoothDecor() : Heartbeat(kHeartbeatPeriodMs) {}

        template <typename... Args>
        AdaptiveSmoothDecor(AdaptiveSmoothConfig config, Args... args)
            : Heartbeat(kHeartbeatPeriodMs),
              TMotor(args...),
              mFilter(config.minTimeConstantTicks,
                      config.maxTimeConstantTicks) {}

        /**
         * @brief Set the target control value.
         * @param value Target control value, range -1000..1000
         */
        void Go(signed short value)
        {
            mFilter.setValue(constrain(value, -1000, 1000));
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
