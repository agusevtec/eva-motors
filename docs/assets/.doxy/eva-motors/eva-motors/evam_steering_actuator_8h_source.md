

# File evamSteeringActuator.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamSteeringActuator.h**](evam_steering_actuator_8h.md)

[Go to the documentation of this file](evam_steering_actuator_8h.md)


```C++
#pragma once
#include <Arduino.h>

namespace evam
{
    struct SteeringConfig {
        signed short leftPos;
        signed short centerPos;
        signed short rightPos;
        
        SteeringConfig(signed short leftPos, signed short centerPos, signed short rightPos)
            : leftPos(constrain(leftPos, -1000, 1000)),
              centerPos(constrain(centerPos, -1000, 1000)),
              rightPos(constrain(rightPos, -1000, 1000)) {}
    };

    template <class Driver, 
              signed short kLeftPos = -1000, 
              signed short kCenterPos = 0, 
              signed short kRightPos = 1000>
    class SteeringActuator : public Driver
    {
        static_assert(kLeftPos >= -1000 && kLeftPos <= 1000, "kLeftPos out of range");
        static_assert(kCenterPos >= -1000 && kCenterPos <= 1000, "kCenterPos out of range");
        static_assert(kRightPos >= -1000 && kRightPos <= 1000, "kRightPos out of range");

    private:
        SteeringConfig mConfig;
        
        signed short compute(signed short aLevel) const
        {
            if (aLevel < 0)
                return map(constrain(aLevel, -1000, 0), -1000, 0, mConfig.leftPos, mConfig.centerPos);
            else
                return map(constrain(aLevel, 0, 1000), 0, 1000, mConfig.centerPos, mConfig.rightPos);
        }

    public:
        SteeringActuator() : mConfig(kLeftPos, kCenterPos, kRightPos) {}
        
        template<typename... Args>
        SteeringActuator(SteeringConfig config, Args... args) : Driver(args...), mConfig(config) {}

        void SetupRange(signed short leftPos, signed short centerPos, signed short rightPos)
        {
            SetLeftPos(leftPos);
            SetCenterPos(centerPos);
            SetRightPos(rightPos);
        }

        void SetLeftPos(signed short aValue)
        {
            mConfig.leftPos = constrain(aValue, -1000, 1000);
        }

        signed short GetLeftPos() const
        {
            return mConfig.leftPos;
        }

        void SetCenterPos(signed short aValue)
        {
            mConfig.centerPos = constrain(aValue, -1000, 1000);
        }

        signed short GetCenterPos() const
        {
            return mConfig.centerPos;
        }

        void SetRightPos(signed short aValue)
        {
            mConfig.rightPos = constrain(aValue, -1000, 1000);
        }

        signed short GetRightPos() const
        {
            return mConfig.rightPos;
        }

        void Go(signed short aLevel)
        {
            Driver::actBipolar(compute(aLevel));
        }
    };
}
```


