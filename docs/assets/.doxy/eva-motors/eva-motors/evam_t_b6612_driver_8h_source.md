

# File evamTB6612Driver.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamTB6612Driver.h**](evam_t_b6612_driver_8h.md)

[Go to the documentation of this file](evam_t_b6612_driver_8h.md)


```C++
#pragma once
#include <Arduino.h>
#include <evamUtils.h>

namespace evam
{
    struct TB6612Config
    {
        int pinSpeed;
        int pinMode1;
        int pinMode2;

        TB6612Config(int pinSpeed, int pinMode1, int pinMode2)
            : pinSpeed(pinSpeed), pinMode1(pinMode1), pinMode2(pinMode2) {}
    };

    template <int tPinSpeed = 0, int tPinMode1 = 0, int tPinMode2 = 0>
    class TB6612FNGDriver
    {
    private:
        TB6612Config mConfig;

    public:
        TB6612FNGDriver() : mConfig(tPinSpeed, tPinMode1, tPinMode2)
        {
            pinMode(mConfig.pinSpeed, OUTPUT);
            pinMode(mConfig.pinMode1, OUTPUT);
            pinMode(mConfig.pinMode2, OUTPUT);
        }

        template <typename... Args>
        TB6612FNGDriver(TB6612Config config, Args... args) : mConfig(config)
        {
            pinMode(mConfig.pinSpeed, OUTPUT);
            pinMode(mConfig.pinMode1, OUTPUT);
            pinMode(mConfig.pinMode2, OUTPUT);
        }

        int GetSpeedPin() const
        {
            return mConfig.pinSpeed;
        }

        int GetMode1Pin() const
        {
            return mConfig.pinMode1;
        }

        int GetMode2Pin() const
        {
            return mConfig.pinMode2;
        }

    protected:
        void actBipolar(signed short aValue)
        {
            digitalWrite(mConfig.pinMode1, aValue > 0);
            digitalWrite(mConfig.pinMode2, aValue < 0);
            universalWrite(mConfig.pinSpeed, map(constrain(abs(aValue), 0, 1000), 0, 1000, 0, 255));
        }
    };
}
```


