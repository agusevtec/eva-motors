

# File evamLinearActuator.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamLinearActuator.h**](evam_linear_actuator_8h.md)

[Go to the documentation of this file](evam_linear_actuator_8h.md)


```C++
#pragma once
#include <Arduino.h>

namespace evam
{
    struct LinearActuatorConfig
    {
        int minValue;
        int maxValue;

        LinearActuatorConfig(int minValue, int maxValue) : minValue(constrain(minValue, -1000, 1000)), maxValue(constrain(maxValue, -1000, 1000)) {}
    };

    template <class TDriver, int tMinValue = 0, int tMaxValue = 1000>
    class LinearActuator : public TDriver
    {
        static_assert(tMinValue >= -1000 && tMinValue <= 1000, "tMinValue out of range");
        static_assert(tMaxValue >= -1000 && tMaxValue <= 1000, "tMaxValue out of range");

    private:
        LinearActuatorConfig mConfig;

        signed short compute(signed short aLevel) const
        {
            return map(constrain(aLevel, 0, 1000), 0, 1000, mConfig.minValue, mConfig.maxValue);
        }

    public:
        LinearActuator() : mConfig(tMinValue, tMaxValue)
        {
            Go(0);
        }

        template <typename... Args>
        LinearActuator(LinearActuatorConfig config, Args... args) : TDriver(args...), mConfig(config)
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


