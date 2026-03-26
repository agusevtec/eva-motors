

# File evamLinearActuator.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamLinearActuator.h**](evam_linear_actuator_8h.md)

[Go to the documentation of this file](evam_linear_actuator_8h.md)


```C++
#pragma once
#include <Arduino.h>
namespace evam
{
    template <class Driver, int kMinValue = 0, int kMaxValue = 1000>
    class LinearActuator : public Driver
    {
        static_assert(kMinValue >= -1000 && kMinValue <= 1000, "kMinValue out of range");
        static_assert(kMaxValue >= -1000 && kMaxValue <= 1000, "kMaxValue out of range");

    private:
        int mMinValue = kMinValue;
        int mMaxValue = kMaxValue;

        signed short compute(signed short aLevel) const
        {
            return map(constrain(aLevel, 0, 1000), 0, 1000, mMinValue, mMaxValue);
        }

    public:
        void SetupRange(int aMinValue, int aMaxValue)
        {
            SetMinValue(aMinValue);
            SetMaxValue(aMaxValue);
        }
        void SetMinValue(int aValue)
        {
            mMinValue = constrain(aValue, -1000, 1000);
        }

        void SetMaxValue(int aValue)
        {
            mMaxValue = constrain(aValue, -1000, 1000);
        }

        void Go(signed short aLevel)
        {
            Driver::actUnipolar(compute(aLevel));
        }
    };
}
```


