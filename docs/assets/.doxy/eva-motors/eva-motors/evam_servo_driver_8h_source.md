

# File evamServoDriver.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamServoDriver.h**](evam_servo_driver_8h.md)

[Go to the documentation of this file](evam_servo_driver_8h.md)


```C++
#pragma once

#include <Servo.h>
#include <Arduino.h>

namespace evam
{
    template <int kPin>
    class ServoDriver
    {
    private:
        Servo mServo;

    public:
        ServoDriver()
        {
            mServo.attach(kPin);
        }

        int GetPin() const
        {
            return kPin;
        }

    protected:
        void actBipolar(signed short aValue)
        {
            mServo.writeMicroseconds(constrain(aValue / 2 + 1500, 500, 2500));
        }

        void actUnipolar(signed short aValue)
        {
            mServo.writeMicroseconds(constrain(aValue + 1000, 500, 2500));
        }
    };
}
```


