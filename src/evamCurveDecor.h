#ifndef CURVEDECOR_H_
#define CURVEDECOR_H_

#pragma once

namespace evam
{
    template <class MOTOR, signed short ALPHA>
    class CurveDecor : public MOTOR
    {
    public:
        signed long f(signed long x)
        {
            return ALPHA * (x - x * x / 1000) / 10;
        }

        unsigned short bend(unsigned short x)
        {
            signed long fx_x = f(x) + x;
            return f(fx_x) + fx_x;
        }

        void actuate(signed short value)
        {
            value = constrain(value, -1000, 1000);
            if (value >= 0)
                MOTOR::actuate(bend(value));
            else
                MOTOR::actuate(-bend(-value));
        }
    };

}
#endif // CURVEDECOR_H_