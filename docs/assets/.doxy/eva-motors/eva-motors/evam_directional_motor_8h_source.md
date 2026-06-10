

# File evamDirectionalMotor.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamDirectionalMotor.h**](evam_directional_motor_8h.md)

[Go to the documentation of this file](evam_directional_motor_8h.md)


```C++
#pragma once
#include <Arduino.h>

namespace evam
{
    struct DirectionalConfig {
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

    template <class Driver, 
              signed short kMaxBackward = -1000, 
              signed short kMinBackward = 0, 
              signed short kMinForward = 0, 
              signed short kMaxForward = 1000>
    class DirectionalMotor : public Driver
    {
        static_assert(kMaxBackward >= -1000 && kMaxBackward <= 1000, "kMaxBackward out of range");
        static_assert(kMinBackward >= -1000 && kMinBackward <= 1000, "kMinBackward out of range");
        static_assert(kMinForward >= -1000 && kMinForward <= 1000, "kMinForward out of range");
        static_assert(kMaxForward >= -1000 && kMaxForward <= 1000, "kMaxForward out of range");

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
        DirectionalMotor() : mConfig(kMaxBackward, kMinBackward, kMinForward, kMaxForward) {}
        
        template<typename... Args>
        DirectionalMotor(DirectionalConfig config, Args... args) : Driver(args...), mConfig(config) {}

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
            Driver::actBipolar(compute(aLevel));
        }
    };
}
```


