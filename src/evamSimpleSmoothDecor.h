#pragma once

#include <evafSimpleAverage.h>
#include <evaStdReaders.h>

namespace evam
{
    /**
     * @brief Decorator applying a simple moving average (sliding window) filter.
     *
     * SimpleAverageDecor has no runtime parameters besides N. This decorator does
     * not own a heartbeat; it only transforms the value. Wrap it with
     * SampledDecor to get periodic output:
     *
     *     SampledDecor<SimpleSmoothDecor<MyMotor, 5>> a;
     *
     * @tparam TMotor Base motor class (must implement Go(signed short))
     * @tparam N Window size (number of values to average). Must be >= 1.
     */
    template <class TMotor, unsigned short N>
    class SimpleSmoothDecor : public TMotor
    {
    private:
        evaf::SimpleAverage<eva::ValueReader, N> mFilter;

    public:
        //SimpleSmoothDecor() : TMotor() {}

        template <typename... Args>
        SimpleSmoothDecor(Args... args)
            : TMotor(args...) {}

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
