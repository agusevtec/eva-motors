

# File evamTA6586Driver.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamTA6586Driver.h**](evam_t_a6586_driver_8h.md)

[Go to the documentation of this file](evam_t_a6586_driver_8h.md)


```C++
#pragma once

#include <Arduino.h>
#include <evamUtils.h>

namespace evam
{
    struct TA6586Config
    {
        int forwardPin;
        int backwardPin;

        TA6586Config(int forwardPin, int backwardPin) : forwardPin(forwardPin), backwardPin(backwardPin) {}
    };

    template <int tForwardPin = 0, int tBackwardPin = 0>
    class TA6586Driver
    {
    private:
        TA6586Config mConfig;

    public:
        TA6586Driver() : mConfig(tForwardPin, tBackwardPin)
        {
            pinMode(mConfig.forwardPin, OUTPUT);
            pinMode(mConfig.backwardPin, OUTPUT);
        }

        template <typename... Args>
        TA6586Driver(TA6586Config config, Args... args) : mConfig(config)
        {
            pinMode(mConfig.forwardPin, OUTPUT);
            pinMode(mConfig.backwardPin, OUTPUT);
        }

        int GetForwardPin() const
        {
            return mConfig.forwardPin;
        }

        int GetBackwardPin() const
        {
            return mConfig.backwardPin;
        }

    protected:
        void actBipolar(signed short aValue)
        {
            int normalized = map(constrain(aValue, -1000, 1000), -1000, 1000, -255, 255);
            universalWrite(mConfig.forwardPin, max(0, normalized));
            universalWrite(mConfig.backwardPin, max(0, -normalized));
        }
    };
}
```


