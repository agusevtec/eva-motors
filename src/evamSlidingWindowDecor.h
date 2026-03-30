/**
 * @file evamSlidingWindowDecor.h
 * @brief Simple moving average (sliding window) filter decorator
 */

#ifndef EVAM_SLIDING_WINDOW_DECOR_H_
#define EVAM_SLIDING_WINDOW_DECOR_H_

#include "evamRingBuffer.h"

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
 *
 */
template <class Motor, unsigned short N>
class SlidingWindowDecor : public Motor
{
private:
    RingBuffer<signed short, N> mRing;  ///< Ring buffer storing the last N values
    signed long mSum = 0;               ///< Running sum of values in buffer

public:
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

        Motor::Go(value);
    }
};

}

#endif // EVAM_SLIDING_WINDOW_DECOR_H_