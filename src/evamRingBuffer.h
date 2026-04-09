#ifndef EVAM_CIRCULAR_BUFFER_H_
#define EVAM_CIRCULAR_BUFFER_H_

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

#endif // EVAM_CIRCULAR_BUFFER_H_