/**
 * @file evamMinmaxDecor.h
 * @brief Min-max (minimax/maximin) filter decorator for motor control
 */

#ifndef EVAM_MINIMAX_FILTER_H_
#define EVAM_MINIMAX_FILTER_H_

#include "evamRingBuffer.h"

namespace evam
{

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
 *
 */
template <class Motor, unsigned char N>
class MinmaxDecor: public Motor
{
private:
    RingBuffer<signed short, N * N> mRing;  ///< Ring buffer of size N*N
    signed short mMaxBuffer[N];              ///< Stores maximum of each chunk
    signed short mMinBuffer[N];              ///< Stores minimum of each chunk

public:
    /**
     * @brief Default constructor.
     *
     * Initializes the filter with zero values. The buffer starts empty
     * and must be filled with N*N values before filtering begins.
     */
    MinmaxDecor()
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
            // Calculate max and min for each chunk
            for (unsigned char chunk = 0; chunk < N; chunk++)
            {
                unsigned char start = chunk * N;
                signed short maxVal = mRing.get(start);
                signed short minVal = maxVal;
                
                for (unsigned char i = 1; i < N; ++i)
                {
                    signed short val = mRing.get(start + i);
                    if (val > maxVal) maxVal = val;
                    if (val < minVal) minVal = val;
                }
                
                mMaxBuffer[chunk] = maxVal;
                mMinBuffer[chunk] = minVal;
            }
            
            // Output is average of minimax and maximin
            value = (getMinimax() + getMaximin()) / 2;
        }
        
        Motor::Go(value);
    }

    private:

    signed short getMinimax() const
    {
        signed short result = mMaxBuffer[0];
        for (unsigned char i = 1; i < N; ++i)
            if (mMaxBuffer[i] < result) result = mMaxBuffer[i];
        return result;
    }
    
    signed short getMaximin() const
    {
        signed short result = mMinBuffer[0];
        for (unsigned char i = 1; i < N; ++i)
            if (mMinBuffer[i] > result) result = mMinBuffer[i];
        return result;
    }
};

} // namespace evam

#endif // EVAM_MINIMAX_FILTER_H_