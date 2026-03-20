#pragma once

namespace evam
{
    template <class Motor, int MAX_BACKWARD, int MIN_BACKWARD, int MIN_FORWARD, int MAX_FORWARD>
    class RangeDecor : public Motor
    {
    public:
        void set(signed short level)
        {
            if (level < -500)
                Motor::set(MAX_BACKWARD);
            else if (level > 500)
                Motor::set(MAX_FORWARD);
            else if (level == 0)
                Motor::set(0);
            else if (level < 0)
                Motor::set(map(level, -500, 0, MAX_BACKWARD, MIN_BACKWARD));
            else if (level > 0)
                Motor::set(map(level, 0, 500, MIN_FORWARD, MAX_FORWARD));
        }
    };
}


DeadzonRangeDecor<ESCMotor<3>, -1000, -40, 40, 1000>> car;

car.set(2*(js.getValue() - 1500))

RangeDecor<ForwardESCMotor<3>, -40, 1200>> airplane;

aitplane.set(js.getValue() - 1000)


CenteredServo.set /// -1000 ... 1000
LeftServo.set /// 0 ... 1000

ESCMotor
ForwardESCMotor