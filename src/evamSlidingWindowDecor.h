#pragma once

#ifndef EVAM_SLIDING_WINDOW_DECOR_H_
#define EVAM_SLIDING_WINDOW_DECOR_H_

#include <evafSlidingWindow.h>
#include "evamValueReader.h"

namespace evam
{

    /**
     * @brief Decorator that applies a simple moving average (sliding window) filter.
     *
     * @tparam Motor Base motor class (must implement Go(signed short))
     * @tparam N Window size (number of values to average). Must be >= 1.
     *
     * @note The filter only produces filtered output after the buffer is full.
     *       Before that, values pass through unchanged. For N=1, the filter passes
     *       values through without any averaging (no effect).
     */
    template <class TMotor, unsigned short N>
    class SlidingWindowDecor : public TMotor, private evaf::SlidingWindow<ValueReader, N>
    {
        static_assert(N >= 1 && N <= 32, "N out of range 1..32");

    private:
        using BaseFilter = evaf::SlidingWindow<ValueReader, N>;

    public:
        SlidingWindowDecor() : {}

        template <typename... Args>
        SlidingWindowDecor(Args... args)
            : TMotor(args...) {}

        /**
         * @brief Apply the control value with moving average filtering.
         *
         * @param value Input control value, range -1000..1000
         */
        void Go(signed short value)
        {
            this->setValue(value);
            signed short filtered = BaseFilter::getValue();
            TMotor::Go(filtered);
        }
    };

}

#endif
