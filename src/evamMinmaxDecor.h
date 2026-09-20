#pragma once

#include <evaHeartbeat.h>
#include <evafOpenClose.h>
#include <evaStdReaders.h>

namespace evam
{
    /**
     * @brief Decorator applying a min-max (morphological) filter.
     *
     * OpenClose has no runtime parameters besides N.
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


        using Filter = evaf::OpenClose<eva::ValueReader, N>;

        Filter mFilter;


    public:
//        MinmaxDecor() : eva::Heartbeat(kHeartbeatPeriodMs) {}

        template <typename... Args>
        MinmaxDecor(Args... args)
            :  TMotor(args...) {}

        /**
         * @brief Set the target control value.
         * @param value Target control value, range -1000..1000
         */
        void Go(signed short value)
        {
            mFilter.setValue(constrain(value, -1000, 1000));
            TMotor::Go(mFilter.getValue());
                }
    };
}
