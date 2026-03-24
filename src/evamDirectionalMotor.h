#pragma once
#include <Arduino.h>

namespace evam
{

    template <class DRIVER, signed short MAX_BACKWARD, signed short MIN_BACKWARD, signed short MIN_FORWARD, signed short MAX_FORWARD>
    class DirectionalMotor : public DRIVER
    {
    protected:
        signed short toSSS(signed short level, signed short mxb, signed short mnb, signed short mnf, signed short mxf)
        {
            if (level < 0)
                return map(constrain(level, -1000, 0), -1000, 0, mxb, mnb) + 1500;
            if (level > 0)
                return map(constrain(level, 0, 1000), 0, 1000, mnf, mxf) + 1500;
            return 1500;
        }

    public:
        void actuate(signed short level)
        {
            DRIVER::setMicroseconds(toSSS(level, MAX_BACKWARD, MIN_BACKWARD, MIN_FORWARD, MAX_FORWARD));
        }
    };

    template <class DRIVER, signed short MAX_BACKWARD, signed short MIN_BACKWARD, signed short MIN_FORWARD, signed short MAX_FORWARD>
    class DirectionalMutableMotor : public DirectionalMotor<DRIVER, 1000, 0, 0, 1000>
    {
    private:
        signed short maxBackward = MAX_BACKWARD;
        signed short minBackward = MIN_BACKWARD;
        signed short minForward = MIN_FORWARD;
        signed short maxForward = MAX_FORWARD;

    public:

        DirectionalMutableMotor *setMaxBackward(signed short value)
        {
            this->maxBackward = value;
            return this;
        }

        DirectionalMutableMotor *setMinBackward(signed short value)
        {
            this->minBackward = value;
            return this;
        }

        DirectionalMutableMotor *setMinForward(signed short value)
        {
            this->minForward = value;
            return this;
        }

        DirectionalMutableMotor *setMaxForward(signed short value)
        {
            this->maxForward = value;
            return this;
        }

        void actuate(signed short level)
        {
            DRIVER::setMicroseconds(this->toSSS(level, this->maxBackward, this->minBackward, this->minForward, this->maxForward));
        }
    };
}
