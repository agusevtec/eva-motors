#pragma once
namespace evam
{

    template <class DRIVER, int MIN_VALUE, int MAX_VALUE>
    class ForwardMotor: public DRIVER
    {
    public:
        signed short toSSS(signed short level, signed short minValue, signed short maxValue)
        {
            if (level > 0)
                return map(constrain(level, 0, 1000), 0, 1000, minValue, maxValue) + 1000;
            return 1000;
        }
        void actuate(signed short level)
        {
            DRIVER::setMicroseconds(toSSS(level, MIN_VALUE, MAX_VALUE));
        }
    };

    template <class DRIVER, int MIN_VALUE, int MAX_VALUE>
    class ForwardMutableMotor: public ForwardMotor<DRIVER, MIN_VALUE, MAX_VALUE>
    {
    private:
        int minValue = MIN_VALUE;
        int maxValue = MAX_VALUE;

    public:
        ForwardMutableMotor *setMinValue(int value)
        {
            this->minValue = value;
            return this;
        }

        ForwardMutableMotor *setMaxValue(int value)
        {
            this->maxValue = value;
            return this;
        }

         void actuate(signed short level)
        {
            DRIVER::setMicroseconds(this->toSSS(level, this->minValue, this->maxValue));
        }
    };
}
