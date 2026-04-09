

# File evamMinmaxDecor.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamMinmaxDecor.h**](evam_minmax_decor_8h.md)

[Go to the documentation of this file](evam_minmax_decor_8h.md)


```C++


#ifndef EVAM_MINIMAX_FILTER_H_
#define EVAM_MINIMAX_FILTER_H_

#include "evamRingBuffer.h"

namespace evam
{

template <class Motor, unsigned char N>
class MinmaxDecor: public Motor
{
private:
    RingBuffer<signed short, N * N> mRing;  
    signed short mMaxBuffer[N];              
    signed short mMinBuffer[N];              

public:
    MinmaxDecor()
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
```


