

# File evamLinearActuator.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamLinearActuator.h**](evam_linear_actuator_8h.md)

[Go to the documentation of this file](evam_linear_actuator_8h.md)


```C++
#pragma once
#include <Arduino.h>

namespace evam
{
    struct LinearActuatorConfig {
        int minValue;
        int maxValue;
        
        LinearActuatorConfig(int minValue, int maxValue) : minValue(constrain(minValue, -1000, 1000)), maxValue(constrain(maxValue, -1000, 1000)) {}
    };

    template <class Driver, int kMinValue = 0, int kMaxValue = 1000>
    class LinearActuator : public Driver
    {
        static_assert(kMinValue >= -1000 && kMinValue <= 1000, "kMinValue out of range");
        static_assert(kMaxValue >= -1000 && kMaxValue <= 1000, "kMaxValue out of range");

    private:
        LinearActuatorConfig mConfig;
        
        signed short compute(signed short aLevel) const
        {
            return map(constrain(aLevel, 0, 1000), 0, 1000, mConfig.minValue, mConfig.maxValue);
        }

    public:
        LinearActuator() : mConfig(kMinValue, kMaxValue) {}
        
        template<typename... Args>
        LinearActuator(LinearActuatorConfig config, Args... args) : Driver(args...), mConfig(config) {}

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
            Driver::actUnipolar(compute(aLevel));
        }
    };
}
```


