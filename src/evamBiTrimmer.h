#pragma once

namespace evam
{
    signed short bitrimmer_calc(signed short level,
                              signed short maxBackward, signed short minBackward,
                              signed short minForward, signed short maxForward);

    template <signed short MAX_BACKWARD, signed short MIN_BACKWARD, signed short MIN_FORWARD, signed short MAX_FORWARD>
    class BiTrimmer
    {
    public:
        signed short trim(signed short level)
        {
            return bitrimmer_calc(level, MAX_BACKWARD, MIN_BACKWARD, MIN_FORWARD, MAX_FORWARD);
        }
    };

    template <signed short MAX_BACKWARD, signed short MIN_BACKWARD, signed short MIN_FORWARD, signed short MAX_FORWARD>
    class MutableBiTrimmer
    {
    private:
        signed short maxBackward = MAX_BACKWARD;
        signed short minBackward = MIN_BACKWARD;
        signed short minForward = MIN_FORWARD;
        signed short maxForward = MAX_FORWARD;

    public:
        MutableBiTrimmer *setMaxBackward(signed short value)
        {
            this->maxBackward = value;
            return this;
        }

        MutableBiTrimmer *setMinBackward(signed short value)
        {
            this->minBackward = value;
            return this;
        }

        MutableBiTrimmer *setMinForward(signed short value)
        {
            this->minForward = value;
            return this;
        }

        MutableBiTrimmer *setMaxForward(signed short value)
        {
            this->maxForward = value;
            return this;
        }

        signed short trim(signed short level)
        {
            return bitrimmer_calc(level, this->maxBackward, this->minBackward, this->minForward, this->maxForward);
        }
    };
}
