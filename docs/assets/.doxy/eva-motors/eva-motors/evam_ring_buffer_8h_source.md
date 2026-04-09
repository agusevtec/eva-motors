

# File evamRingBuffer.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamRingBuffer.h**](evam_ring_buffer_8h.md)

[Go to the documentation of this file](evam_ring_buffer_8h.md)


```C++
#pragma once

namespace evam
{
    template <typename T, unsigned char N>
    class RingBuffer
    {
    private:
        T mBuffer[N];
        unsigned char mHead = 0;
        unsigned char mSize = 0;

        inline unsigned char wrapIndex(unsigned char index) const
        {
            return index % N;
        }

    public:
        RingBuffer()
        {
            for (unsigned char i = 0; i < N; ++i)
                mBuffer[i] = T{};
        }

        void put(const T &value)
        {
            mBuffer[mHead] = value;
            mHead = wrapIndex(mHead + 1);
            if (mSize < N)
                mSize++;
        }

        T get(unsigned char index) const
        {
            unsigned char oldestPos = (mHead + N - mSize) % N;
            unsigned char physicalPos = wrapIndex(oldestPos + index);
            return mBuffer[physicalPos];
        }

        bool isFull() const
        {
            return mSize == N;
        }

        unsigned char size() const
        {
            return mSize;
        }
    };

} // namespace evam
```


