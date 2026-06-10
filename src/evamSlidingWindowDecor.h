#pragma once

#ifndef EVAM_SLIDING_WINDOW_DECOR_H_
#define EVAM_SLIDING_WINDOW_DECOR_H_

#include "evamRingBuffer.h"

namespace evam
{
    /**
     * @brief Configuration structure for SlidingWindowDecor
     */
    struct SlidingWindowConfig {
        unsigned short windowSize;
        
        SlidingWindowConfig(unsigned short windowSize) : windowSize(windowSize) {}
    };

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
    class SlidingWindowDecor : public TMotor
    {
        static_assert(N >= 1 && N <= 32, "N out of range 1..32");
        
    private:
        SlidingWindowConfig mConfig;
        RingBuffer<signed short, N> mRing;
        signed long mSum = 0;

    public:
        SlidingWindowDecor() : mConfig(N) {}
        
        template<typename... Args>
        SlidingWindowDecor(SlidingWindowConfig config, Args... args) 
            : mConfig(config), TMotor(args...) {}

        /**
         * @brief Apply the control value with moving average filtering.
         *
         * @param value Input control value, range -1000..1000
         */
        void Go(signed short value)
        {
            if (mRing.isFull())
                mSum -= mRing.get(0);

            mRing.put(value);
            mSum += value;

            if (mRing.isFull())
                value = static_cast<signed short>(mSum / N);

            TMotor::Go(value);
        }
    };
}

#endif
