

# File evamSlidingWindowDecor.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamSlidingWindowDecor.h**](evam_sliding_window_decor_8h.md)

[Go to the documentation of this file](evam_sliding_window_decor_8h.md)


```C++
#pragma once

#ifndef EVAM_SLIDING_WINDOW_DECOR_H_
#define EVAM_SLIDING_WINDOW_DECOR_H_

#include "evamRingBuffer.h"

namespace evam
{
    struct SlidingWindowConfig {
        unsigned short windowSize;
        
        SlidingWindowConfig(unsigned short windowSize) : windowSize(windowSize) {}
    };

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
```


