

# File evamSlidingWindowDecor.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamSlidingWindowDecor.h**](evam_sliding_window_decor_8h.md)

[Go to the documentation of this file](evam_sliding_window_decor_8h.md)


```C++


#ifndef EVAM_SLIDING_WINDOW_DECOR_H_
#define EVAM_SLIDING_WINDOW_DECOR_H_

#include "evamRingBuffer.h"

namespace evam
{

template <class Motor, unsigned short N>
class SlidingWindowDecor : public Motor
{
private:
    RingBuffer<signed short, N> mRing;  
    signed long mSum = 0;               

public:
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
```


