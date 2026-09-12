#pragma once

#include <evaHeartbeat.h>
#include <evafSlidingWindow.h>
#include "evaStdReaders.h"

using namespace eva;

namespace evam
{
    /**
     * @brief Decorator applying a simple moving average (sliding window) filter.
     *
     * SlidingWindow has no runtime parameters besides N.
     *
     * @tparam TMotor Base motor class (must implement Go(signed short))
     * @tparam N Window size (number of values to average). Must be >= 1.
     */
    template <class TMotor, unsigned short N>
    class SlidingWindowDecor
        : public virtual eva::Heartbeat,
          public TMotor
    {
    private:
        static constexpr unsigned long kHeartbeatPeriodMs = 10;

        using Filter = evaf::SlidingWindow<eva::ValueReader, N>;

        Filter mFilter;

    protected:
        void onHeartbeat() override
        {
            TMotor::Go(mFilter.getValue());
        }

    public:
//        SlidingWindowDecor() : Heartbeat(kHeartbeatPeriodMs) {}

        template <typename... Args>
        SlidingWindowDecor(Args... args)
            : Heartbeat(kHeartbeatPeriodMs), TMotor(args...) {}

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
