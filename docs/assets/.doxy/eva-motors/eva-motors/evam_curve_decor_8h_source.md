

# File evamCurveDecor.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamCurveDecor.h**](evam_curve_decor_8h.md)

[Go to the documentation of this file](evam_curve_decor_8h.md)


```C++
#ifndef CURVEDECOR_H_
#define CURVEDECOR_H_

#pragma once

#include <Arduino.h>

namespace evam
{
    template <class Motor, signed short kBend = 0>
    class CurveDecor : public Motor
    {
        static_assert(kBend >= -10 && kBend <= 10, "kBend out of range -10..10");
    private:
        signed short mBend = kBend;

        signed long f(signed long x) const
        {
            return mBend * (x - x * x / 1000) / 10;
        }

        unsigned short curve(unsigned short x) const
        {
            signed long fx_x = f(x) + x;
            return f(fx_x) + fx_x;
        }

    public:
        void SetBend(signed short aValue)
        {
            mBend = constrain(aValue, -10, 10);
        }

        void Go(signed short aValue)
        {
            aValue = constrain(aValue, -1000, 1000);
            if (aValue >= 0)
                Motor::Go(curve(aValue));
            else
                Motor::Go(-curve(-aValue));
        }
    };

}
#endif // CURVEDECOR_H_
```


