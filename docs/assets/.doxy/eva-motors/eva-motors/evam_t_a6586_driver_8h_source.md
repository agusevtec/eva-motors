

# File evamTA6586Driver.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamTA6586Driver.h**](evam_t_a6586_driver_8h.md)

[Go to the documentation of this file](evam_t_a6586_driver_8h.md)


```C++
#pragma once

#include <Arduino.h>

namespace evam
{
    template <int kForwardPin, int kBackwardPin>
    class TA6586Driver
    {
    public:
        TA6586Driver()
        {
            pinMode(kForwardPin, OUTPUT);
            pinMode(kBackwardPin, OUTPUT);
            actBipolar(0);
        }

        int GetForwardPin() const
        {
            return kForwardPin;
        }

        int GetBackwardPin() const
        {
            return kBackwardPin;
        }

    protected:
        void actBipolar(signed short aValue)
        {
            int normalized = map(constrain(aValue, -1000, 1000), -1000, 1000, -255, 255);
            analogWrite(kForwardPin, max(0, normalized));
            analogWrite(kBackwardPin, max(0, -normalized));
        }
    };
}

```


