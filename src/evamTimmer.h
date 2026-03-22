#pragma once
namespace evam
{
    signed short trimmer_calc(signed short level, int minValue, int maxValue);

    template <int MIN_VALUE, int MAX_VALUE>
    class Trimmer
    {
    public:
        signed short trim(signed short level)
        {
            return trimmer_calc(level, MIN_VALUE, MAX_VALUE);
        }
    };

    template <class Motor, int MIN_VALUE, int MAX_VALUE>
    class MutableTrimmer
    {
    private:
        int minValue = MIN_VALUE;
        int maxValue = MAX_VALUE;

    public:
        MutableTrimmer *setMinValue(int value)
        {
            this->minValue = value;
            return this;
        }

        MutableTrimmer *setMaxValue(int value)
        {
            this->maxValue = value;
            return this;
        }

        signed short trim(signed short level) override
        {
            return trimmer_calc(level, this->minValue, this->maxValue);
        }
    };
}