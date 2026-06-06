#pragma once

#include "evamRingBuffer.h"

namespace evam
{
    /**
     * @brief Configuration structure for MinmaxDecor
     */
    struct MinmaxConfig {
        unsigned char n;
        
        MinmaxConfig(unsigned char size) : n(size) {}
    };

    /**
     * @brief Decorator that applies a min-max (morphological) filter to the control signal.
     *
     * The filter effectively removes both positive and negative impulse noise while
     * preserving edges better than a simple moving average. The output is the average
     * of the morphological opening and closing operations, providing symmetric behavior.
     *
     * This filter divides the ring buffer into N chunks of N elements each, then computes:
     * - minimax = min of chunk maximums (closing operation)
     * - maximin = max of chunk minimums (opening operation)
     * - output = (minimax + maximin) / 2
     *
     * @tparam Motor Base motor class (must implement Go(signed short))
     * @tparam N Number of chunks and chunk size (total buffer size = N * N)
     *
     * @note The filter only produces filtered output after the buffer is full.
     *       Before that, values pass through unchanged.
     */
    template <class TMotor, unsigned char N>
    class MinmaxDecor : public TMotor
    {
        static_assert(N >= 2 && N <= 5, "N out of range 2..5");
        
    private:
        MinmaxConfig mConfig;
        RingBuffer<signed short, N * N> mRing;
        signed short mMaxBuffer[N];
        signed short mMinBuffer[N];

    public:
        MinmaxDecor() : mConfig(N)
        {
            for (unsigned char i = 0; i < N; ++i)
            {
                mMaxBuffer[i] = 0;
                mMinBuffer[i] = 0;
            }
        }
        
        template<typename... Args>
        MinmaxDecor(MinmaxConfig config, Args... args) 
            : mConfig(config), TMotor(args...)
        {
            for (unsigned char i = 0; i < N; ++i)
            {
                mMaxBuffer[i] = 0;
                mMinBuffer[i] = 0;
            }
        }

        /**
         * @brief Apply the control value with min-max filtering.
         *
         * Passes values through unchanged until the ring buffer is full.
         * Once full, each new value triggers:
         * - Buffer update (overwrites oldest value)
         * - Recalculation of chunk maximums and minimums
         * - Output = (minimax + maximin) / 2
         *
         * @param value Input control value, range -1000..1000
         */
        void Go(signed short value)
        {
            mRing.put(value);

            if (mRing.isFull())
            {
                for (unsigned char chunk = 0; chunk < N; chunk++)
                {
                    unsigned char start = chunk * N;
                    signed short maxVal = mRing.get(start);
                    signed short minVal = maxVal;

                    for (unsigned char i = 1; i < N; ++i)
                    {
                        signed short val = mRing.get(start + i);
                        if (val > maxVal)
                            maxVal = val;
                        if (val < minVal)
                            minVal = val;
                    }

                    mMaxBuffer[chunk] = maxVal;
                    mMinBuffer[chunk] = minVal;
                }

                value = (getMinimax() + getMaximin()) / 2;
            }

            TMotor::Go(value);
        }

    private:
        signed short getMinimax() const
        {
            signed short result = mMaxBuffer[0];
            for (unsigned char i = 1; i < N; ++i)
                if (mMaxBuffer[i] < result)
                    result = mMaxBuffer[i];
            return result;
        }

        signed short getMaximin() const
        {
            signed short result = mMinBuffer[0];
            for (unsigned char i = 1; i < N; ++i)
                if (mMinBuffer[i] > result)
                    result = mMinBuffer[i];
            return result;
        }
    };
}
