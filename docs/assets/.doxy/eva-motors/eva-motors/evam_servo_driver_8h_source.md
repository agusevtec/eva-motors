

# File evamServoDriver.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamServoDriver.h**](evam_servo_driver_8h.md)

[Go to the documentation of this file](evam_servo_driver_8h.md)


```C++
#pragma once

#include <Servo.h>
#include <Arduino.h>

namespace evam
{
    template <int kPin, int kMinPulse = 1000, int kMiddlePulse = 1500, int kMaxPulse = 2000>
    class ServoDriver
    {
        static_assert(kMinPulse >= 500 && kMinPulse <= 2500, "kMinPulse out of range 500..2500");
        static_assert(kMiddlePulse >= 500 && kMiddlePulse <= 2500, "kMiddlePulse out of range 500..2500");
        static_assert(kMaxPulse >= 500 && kMaxPulse <= 2500, "kMaxPulse out of range 500..2500");
        static_assert(kMinPulse < kMiddlePulse, "kMinPulse must be less than kMiddlePulse");
        static_assert(kMiddlePulse < kMaxPulse, "kMiddlePulse must be less than kMaxPulse");

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
            aValue = constrain(aValue, -1000, 1000);
            if (aVelue < 0)
                mServo.writeMicroseconds(map(aValue, -1000, 0), kMinPulse, kMiddlePulse))
            else
                mServo.writeMicroseconds(map(aValue, 0, 1000), kMiddlePulse, kMaxPulse))
        }

        void actUnipolar(signed short aValue)
        {
            aValue = constrain(aValue, 0, 1000);
            if (aVelue < 500)
                mServo.writeMicroseconds(map(aValue, 0, 500), kMinPulse, kMiddlePulse))
            else
                mServo.writeMicroseconds(map(aValue, 500, 1000), kMiddlePulse, kMaxPulse))
        }
    };
    
    template <int kPin, int kMinPulse, int kMaxPulse>
    using ServoFlatDriver = Servoriver<kPin, kMinPulse, (kMaxPulse - kMinPulse) / 2, kMaxPulse>
}
```


