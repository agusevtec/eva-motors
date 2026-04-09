

# File evamPwmDriver.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamPwmDriver.h**](evam_pwm_driver_8h.md)

[Go to the documentation of this file](evam_pwm_driver_8h.md)


```C++
#pragma once

#include <Arduino.h>

namespace evam
{
    template <int kPin>
    class PwmDriver
    {
    public:
        PwmDriver()
        {
            pinMode(kPin, OUTPUT);
            actUnipolar(0);
        }

    protected:
        void actUnipolar(unsigned short aValue)
        {
            int pwm = map(constrain(aValue, 0, 1000), 0, 1000, 0, 255);
            analogWrite(kPin, pwm);
        }
    };

} // namespace evam


```


