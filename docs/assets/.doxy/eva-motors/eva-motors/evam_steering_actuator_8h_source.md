

# File evamSteeringActuator.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamSteeringActuator.h**](evam_steering_actuator_8h.md)

[Go to the documentation of this file](evam_steering_actuator_8h.md)


```C++
#pragma once
#include <Arduino.h>

namespace evam
{
    template <class Driver, signed short kLeftPos = -1000, signed short kCenterPos = 0, signed short kRightPos = 1000>
    class SteeringActuator : public Driver
    {
        static_assert(kLeftPos >= -1000 && kLeftPos <= 1000, "kLeftPos out of range");
        static_assert(kCenterPos >= -1000 && kCenterPos <= 1000, "kCenterPos out of range");
        static_assert(kRightPos >= -1000 && kRightPos <= 1000, "kRightPos out of range");

    private:
        signed short mLeftPos = kLeftPos;
        signed short mCenterPos = kCenterPos;
        signed short mRightPos = kRightPos;

        signed short compute(signed short aLevel) const
        {
            if (aLevel < 0)
                return map(constrain(aLevel, -1000, 0), -1000, 0, mLeftPos, mCenterPos);
            else
                return map(constrain(aLevel, 0, 1000), 0, 1000, mCenterPos, mRightPos);
        }

    public:
        void SetupRange(signed short aLeftPos, signed short aCenterPos, signed short aRightPos)
        {
            SetLeftPos(aLeftPos);
            SetCenterPos(aCenterPos);
            SetRightPos(aRightPos);
        }
        void SetLeftPos(signed short aValue)
        {
            mLeftPos = constrain(aValue, -1000, 1000);
        }

        void SetCenterPos(signed short aValue)
        {
            mCenterPos = constrain(aValue, -1000, 1000);
        }

        void SetRightPos(signed short aValue)
        {
            mRightPos = constrain(aValue, -1000, 1000);
        }

        void Go(signed short aLevel)
        {
            Driver::actBipolar(compute(aLevel));
        }
    };
}
```


