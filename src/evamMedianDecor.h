#pragma once

#include <evaHeartbeat.h>
#include <evafMedian.h>
#include "evaStdReaders.h"

namespace evam
{
    /**
     * @brief Decorator applying median filtering.
     *
     * Median has no runtime parameters besides the template window size.
     *
     * @tparam TMotor Base motor class (must implement Go(signed short))
     * @tparam tWindowSize Filter window size (odd number). Default: 5
     */
    template <class TMotor, unsigned short tWindowSize = evaf::kDefaultWindowSize>
    class MedianDecor
        : public virtual Heartbeat,
          public TMotor
    {
    private:
        static constexpr unsigned long kHeartbeatPeriodMs = 10;

        using Filter = evaf::Median<eva::ValueReader, tWindowSize>;

        Filter mFilter;

    protected:
        void onHeartbeat() override
        {
            TMotor::Go(mFilter.getValue());
        }

    public:
        MedianDecor() : Heartbeat(kHeartbeatPeriodMs) {}

        template <typename... Args>
        MedianDecor(Args... args)
            : eva::Heartbeat(kHeartbeatPeriodMs), TMotor(args...) {}

        /**
         * @brief Set the target control value.
         * @param value Target control value, range -1000..1000
         */
        void Go(signed short value)
        {
            mFilter.setValue(constrain(value, -1000, 1000));
        }
    };
}
