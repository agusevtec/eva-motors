

# File evamPwmDriver.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamPwmDriver.h**](evam_pwm_driver_8h.md)

[Go to the documentation of this file](evam_pwm_driver_8h.md)


```C++
#pragma once

#include <Arduino.h>
#include <evamUtils.h>

namespace evam
{
    struct PwmConfig
    {
        int pin;

        PwmConfig(int pin) : pin(pin) {}
    };

    template <int tPin = 0>
    class PwmDriver
    {
    private:
        PwmConfig mConfig;

    public:
        PwmDriver() : mConfig(tPin)
        {
            pinMode(tPin, OUTPUT);
        }

        template <typename... Args>
        PwmDriver(PwmConfig config, Args... args) : mConfig(config)
        {
            pinMode(mConfig.pin, OUTPUT);
        }

        int GetPin() const
        {
            return mConfig.pin;
        }

    protected:
        void actUnipolar(unsigned short aValue)
        {
            universalWrite(mConfig.pin, map(constrain(aValue, 0, 1000), 0, 1000, 0, 255));
        }
    };
}
```


