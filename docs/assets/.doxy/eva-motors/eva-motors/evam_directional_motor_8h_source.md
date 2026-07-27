

# File evamDirectionalMotor.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamDirectionalMotor.h**](evam_directional_motor_8h.md)

[Go to the documentation of this file](evam_directional_motor_8h.md)


```C++
#pragma once
#include <Arduino.h>

namespace evam
{
    struct DirectionalConfig
    {
        signed short maxBackward;
        signed short minBackward;
        signed short minForward;
        signed short maxForward;

        DirectionalConfig(signed short maxBackward, signed short minBackward, signed short minForward, signed short maxForward)
            : maxBackward(constrain(maxBackward, -1000, 1000)),
              minBackward(constrain(minBackward, -1000, 1000)),
              minForward(constrain(minForward, -1000, 1000)),
              maxForward(constrain(maxForward, -1000, 1000)) {}
    };

    template <class TDriver,
              signed short tMaxBackward = -1000,
              signed short tMinBackward = 0,
              signed short tMinForward = 0,
              signed short tMaxForward = 1000>
    class DirectionalMotor : public TDriver
    {
        static_assert(tMaxBackward >= -1000 && tMaxBackward <= 1000, "tMaxBackward out of range");
        static_assert(tMinBackward >= -1000 && tMinBackward <= 1000, "tMinBackward out of range");
        static_assert(tMinForward >= -1000 && tMinForward <= 1000, "tMinForward out of range");
        static_assert(tMaxForward >= -1000 && tMaxForward <= 1000, "tMaxForward out of range");

    private:
        DirectionalConfig mConfig;

        signed short compute(signed short aLevel) const
        {
            if (aLevel < 0)
                return map(constrain(aLevel, -1000, 0), -1000, 0, mConfig.maxBackward, mConfig.minBackward);
            if (aLevel > 0)
                return map(constrain(aLevel, 0, 1000), 0, 1000, mConfig.minForward, mConfig.maxForward);
            return 0;
        }

    public:
        DirectionalMotor() : mConfig(tMaxBackward, tMinBackward, tMinForward, tMaxForward)
        {
            Go(0);
        }

        template <typename... Args>
        DirectionalMotor(DirectionalConfig config, Args... args) : TDriver(args...), mConfig(config)
        {
            Go(0);
        }

        void SetupRange(signed short maxBackward, signed short minBackward, signed short minForward, signed short maxForward)
        {
            SetMaxBackward(maxBackward);
            SetMinBackward(minBackward);
            SetMinForward(minForward);
            SetMaxForward(maxForward);
        }

        void SetMaxBackward(signed short aValue)
        {
            mConfig.maxBackward = constrain(aValue, -1000, 1000);
        }

        signed short GetMaxBackward() const
        {
            return mConfig.maxBackward;
        }

        void SetMinBackward(signed short aValue)
        {
            mConfig.minBackward = constrain(aValue, -1000, 1000);
        }

        signed short GetMinBackward() const
        {
            return mConfig.minBackward;
        }

        void SetMinForward(signed short aValue)
        {
            mConfig.minForward = constrain(aValue, -1000, 1000);
        }

        signed short GetMinForward() const
        {
            return mConfig.minForward;
        }

        void SetMaxForward(signed short aValue)
        {
            mConfig.maxForward = constrain(aValue, -1000, 1000);
        }

        signed short GetMaxForward() const
        {
            return mConfig.maxForward;
        }

        void Go(signed short aLevel)
        {
            TDriver::actBipolar(compute(aLevel));
        }
    };
}
```


