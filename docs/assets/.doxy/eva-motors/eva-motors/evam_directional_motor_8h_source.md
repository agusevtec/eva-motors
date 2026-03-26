

# File evamDirectionalMotor.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamDirectionalMotor.h**](evam_directional_motor_8h.md)

[Go to the documentation of this file](evam_directional_motor_8h.md)


```C++
#pragma once
#include <Arduino.h>

namespace evam
{
    template <class Driver, signed short kMaxBackward = -1000, signed short kMinBackward = 0, signed short kMinForward = 0, signed short kMaxForward = 1000>
    class DirectionalMotor : public Driver
    {
        static_assert(kMaxBackward >= -1000 && kMaxBackward <= 1000, "kMaxBackward out of range");
        static_assert(kMinBackward >= -1000 && kMinBackward <= 1000, "kMinBackward out of range");
        static_assert(kMinForward >= -1000 && kMinForward <= 1000, "kMinForward out of range");
        static_assert(kMaxForward >= -1000 && kMaxForward <= 1000, "kMaxForward out of range");

    private:
        signed short mMaxBackward = kMaxBackward;
        signed short mMinBackward = kMinBackward;
        signed short mMinForward = kMinForward;
        signed short mMaxForward = kMaxForward;

        signed short compute(signed short aLevel) const
        {
            if (aLevel < 0)
                return map(constrain(aLevel, -1000, 0), -1000, 0, mMaxBackward, mMinBackward);
            if (aLevel > 0)
                return map(constrain(aLevel, 0, 1000), 0, 1000, mMinForward, mMaxForward);
            return 0;
        }

    public:
        void SetupRange(signed short aMaxBackward, signed short aMinBackward, signed short aMinForward, signed short aMaxForward)
        {
            SetMaxBackward(aMaxBackward);
            SetMinBackward(aMinBackward);
            SetMinForward(aMinForward);
            SetMaxForward(aMaxForward);
        }

        void SetMaxBackward(signed short aValue)
        {
            mMaxBackward = constrain(aValue, -1000, 1000);
        }

        signed short GetMaxBackward() const
        {
            return mMaxBackward;
        }

        void SetMinBackward(signed short aValue)
        {
            mMinBackward = constrain(aValue, -1000, 1000);
        }

        signed short GetMinBackward() const
        {
            return mMinBackward;
        }

        void SetMinForward(signed short aValue)
        {
            mMinForward = constrain(aValue, -1000, 1000);
        }

        signed short GetMinForward() const
        {
            return mMinForward;
        }

        void SetMaxForward(signed short aValue)
        {
            mMaxForward = constrain(aValue, -1000, 1000);
        }

        signed short GetMaxForward() const
        {
            return mMaxForward;
        }

        void Go(signed short aLevel)
        {
            Driver::actBipolar(compute(aLevel));
        }
    };
}
```


