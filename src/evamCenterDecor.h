#pragma once
#include <Arduino.h>

namespace evam
{

    template <class MOTOR, signed short LEFT_POS, signed short CENTER_POS, signed short RIGHT_POS>
    class CenterDecor : public MOTOR
    {
    protected:
        signed short calc(signed short level, signed short left, signed short center, signed short right)
        {
            if (level < 0)
                return map(constrain(level, MOTOR::min(), 0), MOTOR::min(), 0, left, center);
            else
                return map(constrain(level, 0, 1000), 0, 1000, center, right);
        }

    public:
        void actuate(signed short level)
        {
            MOTOR::actuate(calc(level, LEFT_POS, CENTER_POS, RIGHT_POS));
        }
    };

    template <class MOTOR, signed short LEFT_POS, signed short CENTER_POS, signed short RIGHT_POS>
    class CenterMutableDecor : public CenterDecor<MOTOR, 1000, 0, 1000>
    {
    private:
        signed short leftPosition = LEFT_POS;
        signed short centerPosition = CENTER_POS;
        signed short rightPosition = RIGHT_POS;

    public:

        CenterMutableDecor *setLeftPosition(signed short value)
        {
            this->leftPosition = value;
            return this;
        }

        CenterMutableDecor *setCenterPosition(signed short value)
        {
            this->centerPosition = value;
            return this;
        }

        CenterMutableDecor *setRightPosition(signed short value)
        {
            this->rightPosition = value;
            return this;
        }

        void actuate(signed short level)
        {
            MOTOR::actuate(this->calc(level, this->leftPosition, this->centerPosition,  this->rightPosition));
        }
    };
}
