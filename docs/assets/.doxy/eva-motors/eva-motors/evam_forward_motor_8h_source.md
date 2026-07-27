

# File evamForwardMotor.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamForwardMotor.h**](evam_forward_motor_8h.md)

[Go to the documentation of this file](evam_forward_motor_8h.md)


```C++
#pragma once
#include <Arduino.h>

namespace evam
{
    struct ForwardConfig
    {
        int minValue;
        int maxValue;

        ForwardConfig(int minValue, int maxValue) : minValue(constrain(minValue, -1000, 1000)), maxValue(constrain(maxValue, -1000, 1000)) {}
    };

    template <class TDriver, int tMinValue = 0, int tMaxValue = 1000>
    class ForwardMotor : public TDriver
    {
        static_assert(tMinValue >= -1000 && tMinValue <= 1000, "tMinValue out of range");
        static_assert(tMaxValue >= -1000 && tMaxValue <= 1000, "tMaxValue out of range");

    private:
        ForwardConfig mConfig;

        signed short compute(signed short aLevel) const
        {
            if (aLevel > 0)
                return map(constrain(aLevel, 0, 1000), 0, 1000, mConfig.minValue, mConfig.maxValue);
            return 0;
        }

    public:
        ForwardMotor() : mConfig(tMinValue, tMaxValue)
        {
            Go(0);
        }

        template <typename... Args>
        ForwardMotor(ForwardConfig config, Args... args) : TDriver(args...), mConfig(config)
        {
            Go(0);
        }

        void SetupRange(int minValue, int maxValue)
        {
            SetMinValue(minValue);
            SetMaxValue(maxValue);
        }

        void SetMinValue(int aValue)
        {
            mConfig.minValue = constrain(aValue, -1000, 1000);
        }

        int GetMinValue() const
        {
            return mConfig.minValue;
        }

        void SetMaxValue(int aValue)
        {
            mConfig.maxValue = constrain(aValue, -1000, 1000);
        }

        int GetMaxValue() const
        {
            return mConfig.maxValue;
        }

        void Go(signed short aLevel)
        {
            TDriver::actUnipolar(compute(aLevel));
        }
    };
}
```


