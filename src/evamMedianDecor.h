#ifndef EVAM_MEDIAN_DECOR_H_
#define EVAM_MEDIAN_DECOR_H_

#pragma once

#include <Arduino.h>
#include <evaHeartbeat.h>

using namespace eva;

namespace evam
{
    /**
     * @brief Decorator that applies median filtering with fixed time base.
     *
     * Samples the input at regular intervals and applies median filtering
     * to remove spikes and noise. Output updates at the sampling rate.
     *
     * @tparam Motor Base motor class (must implement Go(signed short))
     * @tparam kWindowSize Filter window size (odd number). Default: 5
     */
    template <class Motor, unsigned short kWindowSize = 5>
    class MedianDecor : public Heartbeat, public Motor
    {
        static_assert(kWindowSize >= 3 && kWindowSize <= 15, 
                      "kWindowSize out of range 3..15");
        static_assert(kWindowSize % 2 == 1, 
                      "kWindowSize must be odd");

    private:
        static constexpr unsigned long kHeartbeatPeriodMs = 10;
        
        signed short mBuffer[kWindowSize];
        unsigned short mIndex = 0;
        bool mBufferFull = false;
        signed short mLastSample = 0;

        signed short calculateMedian()
        {
            signed short sorted[kWindowSize];
            unsigned short count = mBufferFull ? kWindowSize : mIndex + 1;
            
            for (unsigned short i = 0; i < count; i++)
                sorted[i] = mBuffer[i];
            
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

    protected:
        void onHeartbeat() override
        {
            mBuffer[mIndex] = mLastSample;
            mIndex++;
            if (mIndex >= kWindowSize)
            {
                mIndex = 0;
                mBufferFull = true;
            }
            
            if (mBufferFull || mIndex > kWindowSize / 2)
            {
                Motor::Go(calculateMedian());
            }
        }

    public:
        MedianDecor() : Heartbeat(kHeartbeatPeriodMs)
        {
            for (unsigned short i = 0; i < kWindowSize; i++)
                mBuffer[i] = 0;
        }

        void Reset()
        {
            mIndex = 0;
            mBufferFull = false;
            for (unsigned short i = 0; i < kWindowSize; i++)
                mBuffer[i] = 0;
        }

        void Go(signed short aValue)
        {
            mLastSample = constrain(aValue, -1000, 1000);
        }
    };

} // namespace evam

#endif // EVAM_MEDIAN_DECOR_H_
