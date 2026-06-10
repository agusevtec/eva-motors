

# File evamTA6586Driver.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamTA6586Driver.h**](evam_t_a6586_driver_8h.md)

[Go to the documentation of this file](evam_t_a6586_driver_8h.md)


```C++
#pragma once

#include <Arduino.h>

namespace evam
{
    struct TA6586Config
    {
        int forwardPin;
        int backwardPin;

        TA6586Config(int forwardPin, int backwardPin) : forwardPin(forwardPin), backwardPin(backwardPin) {}
    };

    template <int kForwardPin = 0, int kBackwardPin = 0>
    class TA6586Driver
    {
    private:
        TA6586Config mConfig;

    public:
        TA6586Driver() : mConfig(kForwardPin, kBackwardPin)
        {
            pinMode(mConfig.forwardPin, OUTPUT);
            pinMode(mConfig.backwardPin, OUTPUT);
            actBipolar(0);
        }

        template <typename... Args>
        TA6586Driver(TA6586Config config, Args... args) : mConfig(config)
        {
            pinMode(mConfig.forwardPin, OUTPUT);
            pinMode(mConfig.backwardPin, OUTPUT);
            actBipolar(0);
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
            analogWrite(mConfig.forwardPin, max(0, normalized));
            analogWrite(mConfig.backwardPin, max(0, -normalized));
        }
    };
}
```


