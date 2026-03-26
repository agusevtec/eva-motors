#ifndef EVAM_MEDIAN_DECOR_H_
#define EVAM_MEDIAN_DECOR_H_

#pragma once

#include <Arduino.h>

namespace evam
{
    /**
     * @brief Decorator that applies median filtering to eliminate spikes.
     *
     * Uses a sliding window median filter to remove impulse noise and
     * sudden spikes without adding significant delay. Useful for
     * eliminating occasional glitches from sensors or joysticks.
     *
     * @tparam Motor Base motor class (must implement Go(signed short))
     * @tparam kWindowSize Filter window size (3, 5, 7, etc.). Default: 3.
     *         Larger window = more smoothing but more delay.
     */
    template <class Motor, unsigned short kWindowSize = 3>
    class MedianDecor : public Motor
    {
        static_assert(kWindowSize >= 3 && kWindowSize <= 15, 
                      "kWindowSize out of range 3..15");
        static_assert(kWindowSize % 2 == 1, 
                      "kWindowSize must be odd for proper median");

    private:
        signed short mBuffer[kWindowSize];
        unsigned short mIndex = 0;
        bool mBufferFull = false;

        /**
         * @brief Calculate median of the buffer.
         * @return Median value
         */
        signed short calculateMedian()
        {
            // Copy buffer for sorting
            signed short sorted[kWindowSize];
            unsigned short count = mBufferFull ? kWindowSize : mIndex;
            
            for (unsigned short i = 0; i < count; i++)
                sorted[i] = mBuffer[i];
            
            // Simple bubble sort for small arrays
            for (unsigned short i = 0; i < count - 1; i++)
            {
                for (unsigned short j = 0; j < count - i - 1; j++)
                {
                    if (sorted[j] > sorted[j + 1])
                    {
                        signed short temp = sorted[j];
                        sorted[j] = sorted[j + 1];
                        sorted[j + 1] = temp;
                    }
                }
            }
            
            return sorted[count / 2];
        }

    public:
        /**
         * @brief Constructor. Initializes the buffer.
         */
        MedianDecor()
        {
            for (unsigned short i = 0; i < kWindowSize; i++)
                mBuffer[i] = 0;
        }

        /**
         * @brief Reset the filter buffer.
         */
        void ResetFilter()
        {
            mIndex = 0;
            mBufferFull = false;
            for (unsigned short i = 0; i < kWindowSize; i++)
                mBuffer[i] = 0;
        }

        /**
         * @brief Apply median filtering and pass to underlying motor.
         * @param aValue Raw input value, range -1000..1000.
         */
        void Go(signed short aValue)
        {
            aValue = constrain(aValue, -1000, 1000);
            
            // Add to circular buffer
            mBuffer[mIndex] = aValue;
            mIndex++;
            if (mIndex >= kWindowSize)
            {
                mIndex = 0;
                mBufferFull = true;
            }
            
            // Only output when buffer is full enough
            if (mBufferFull || mIndex > kWindowSize / 2)
            {
                signed short filtered = calculateMedian();
                Motor::Go(filtered);
            }
            else
            {
                // Not enough samples yet, pass through
                Motor::Go(aValue);
            }
        }
    };

} // namespace evam

#endif // EVAM_MEDIAN_DECOR_H_
