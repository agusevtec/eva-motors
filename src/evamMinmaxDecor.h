#pragma once

#include <evaHeartbeat.h>
#include <evafMinmax.h>
#include <evaStdReaders.h>

namespace evam
{
    /**
     * @brief Decorator applying a min-max (morphological) filter.
     *
     * Minmax has no runtime parameters besides N.
     *
     * @tparam TMotor Base motor class (must implement Go(signed short))
     * @tparam N Number of chunks and chunk size (total buffer size = N * N)
     */
    template <class TMotor, unsigned char N>
    class MinmaxDecor
        : public virtual eva::Heartbeat,
          public TMotor
    {
    private:
        static constexpr unsigned long kHeartbeatPeriodMs = 10;

        using Filter = evaf::Minmax<eva::ValueReader, N>;

        Filter mFilter;

    protected:
        void onHeartbeat() override
        {
            TMotor::Go(mFilter.getValue());
        }

    public:
        MinmaxDecor() : eva::Heartbeat(kHeartbeatPeriodMs) {}

        template <typename... Args>
        MinmaxDecor(Args... args)
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
