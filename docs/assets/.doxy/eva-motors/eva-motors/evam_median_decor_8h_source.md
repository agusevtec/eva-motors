

# File evamMedianDecor.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamMedianDecor.h**](evam_median_decor_8h.md)

[Go to the documentation of this file](evam_median_decor_8h.md)


```C++
#pragma once

#include <Arduino.h>
#include <evaHeartbeat.h>

using namespace eva;

namespace evam
{
    constexpr unsigned short kDefaultWindowSize = 5;
    constexpr unsigned short kMinWindowSize = 3;
    constexpr unsigned short kMaxWindowSize = 15;

    struct MedianConfig {
        unsigned short windowSize;
        
        MedianConfig(unsigned short windowSize) : windowSize(windowSize) {}
    };

    template <class TMotor, unsigned short tWindowSize = kDefaultWindowSize>
    class MedianDecor : public Heartbeat, public TMotor
    {
        static_assert(tWindowSize >= kMinWindowSize && tWindowSize <= kMaxWindowSize, 
                      "tWindowSize out of range");
        static_assert(tWindowSize % 2 == 1, 
                      "tWindowSize must be odd");

    private:
        static constexpr unsigned long kHeartbeatPeriodMs = 10;
        
        MedianConfig mConfig;
        
        signed short mBuffer[tWindowSize];
        unsigned short mIndex = 0;
        bool mBufferFull = false;
        signed short mLastSample = 0;

        signed short calculateMedian()
        {
            signed short sorted[tWindowSize];
            unsigned short count = mBufferFull ? tWindowSize : mIndex + 1;
            
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
            if (mIndex >= tWindowSize)
            {
                mIndex = 0;
                mBufferFull = true;
            }
            
            if (mBufferFull || mIndex > tWindowSize / 2)
            {
                TMotor::Go(calculateMedian());
            }
        }

    public:
        MedianDecor() : mConfig(tWindowSize), Heartbeat(kHeartbeatPeriodMs)
        {
            for (unsigned short i = 0; i < tWindowSize; i++)
                mBuffer[i] = 0;
        }
        
        template<typename... Args>
        MedianDecor(MedianConfig config, Args... args) 
            : mConfig(config), Heartbeat(kHeartbeatPeriodMs), TMotor(args...)
        {
            for (unsigned short i = 0; i < tWindowSize; i++)
                mBuffer[i] = 0;
        }

        void Reset()
        {
            mIndex = 0;
            mBufferFull = false;
            for (unsigned short i = 0; i < tWindowSize; i++)
                mBuffer[i] = 0;
        }

        void Go(signed short aValue)
        {
            mLastSample = constrain(aValue, -1000, 1000);
        }
    };
}
```


