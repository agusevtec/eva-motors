

# File evamCurveDecor.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamCurveDecor.h**](evam_curve_decor_8h.md)

[Go to the documentation of this file](evam_curve_decor_8h.md)


```C++
#pragma once

#include <Arduino.h>

namespace evam
{
    constexpr signed short kDefaultBend = 0;
    constexpr signed short kMinBend = -10;
    constexpr signed short kMaxBend = 10;

    struct CurveConfig {
        signed short bend;
        
        CurveConfig(signed short bend) : bend(constrain(bend, kMinBend, kMaxBend)) {}
    };

    template <class TMotor, signed short tBend = kDefaultBend>
    class CurveDecor : public TMotor
    {
        static_assert(tBend >= kMinBend && tBend <= kMaxBend, "tBend out of range");
        
    private:
        CurveConfig mConfig;
        
        signed long f(signed long x) const
        {
            return mConfig.bend * (x - x * x / 1000) / 10;
        }

        unsigned short curve(unsigned short x) const
        {
            signed long fx_x = f(x) + x;
            return f(fx_x) + fx_x;
        }

    public:
        CurveDecor() : mConfig(tBend) {}
        
        template<typename... Args>
        CurveDecor(CurveConfig config, Args... args) : TMotor(args...), mConfig(config) {}

        void SetBend(signed short aValue)
        {
            mConfig.bend = constrain(aValue, -10, 10);
        }

        signed short GetBend() const
        {
            return mConfig.bend;
        }

        void Go(signed short aValue)
        {
            aValue = constrain(aValue, -1000, 1000);
            if (aValue >= 0)
                TMotor::Go(curve(aValue));
            else
                TMotor::Go(-curve(-aValue));
        }
    };
}
```


