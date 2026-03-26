

# File evamTB6612Driver.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamTB6612Driver.h**](evam_t_b6612_driver_8h.md)

[Go to the documentation of this file](evam_t_b6612_driver_8h.md)


```C++
#ifndef TB6612FNG_DRIVER_H_
#define TB6612FNG_DRIVER_H_
#pragma once
#include <Arduino.h>
namespace evam
{
    template <int kPinSpeed, int kPinMode1, int kPinMode2>
    class TB6612FNGDriver
    {

    public:
        TB6612FNGDriver()
        {
            pinMode(kPinSpeed, OUTPUT);
            pinMode(kPinMode1, OUTPUT);
            pinMode(kPinMode2, OUTPUT);
            actBipolar(0);
        }

        int GetSpeedPin() const
        {
            return kPinSpeed;
        }

        int GetMode1Pin() const
        {
            return kPinMode1;
        }

        int GetMode2Pin() const
        {
            return kPinMode2;
        }

    protected:
        void actBipolar(signed short aValue)
        {
            int pwm = map(constrain(abs(aValue), 0, 1000), 0, 1000, 0, 255);
            digitalWrite(kPinMode1, aValue > 0);
            digitalWrite(kPinMode2, aValue < 0);
            analogWrite(kPinSpeed, pwm);
        }
    };
}
#endif
```


