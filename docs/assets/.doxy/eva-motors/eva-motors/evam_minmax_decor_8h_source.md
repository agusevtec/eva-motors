

# File evamMinmaxDecor.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamMinmaxDecor.h**](evam_minmax_decor_8h.md)

[Go to the documentation of this file](evam_minmax_decor_8h.md)


```C++
#pragma once

#include "evamRingBuffer.h"

namespace evam
{
    struct MinmaxConfig {
        unsigned char n;
        
        MinmaxConfig(unsigned char n) : n(n) {}
    };

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
```


