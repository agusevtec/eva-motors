

# File evamServoDriver.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamServoDriver.h**](evam_servo_driver_8h.md)

[Go to the documentation of this file](evam_servo_driver_8h.md)


```C++
#pragma once

#include <Servo.h>
#include <Arduino.h>

namespace evam
{
    struct ServoConfig {
        int pin;
        int minPulse;
        int middlePulse;
        int maxPulse;
        
        ServoConfig(int pin, int minPulse, int middlePulse, int maxPulse) 
            : pin(pin), minPulse(minPulse), middlePulse(middlePulse), maxPulse(maxPulse) {}
    };

    template <int tPin = 0, int tMinPulse = 1000, int tMiddlePulse = 1500, int tMaxPulse = 2000>
    class ServoDriver
    {
        static_assert(tMinPulse >= 500 && tMinPulse <= 2500, "tMinPulse out of range 500..2500");
        static_assert(tMiddlePulse >= 500 && tMiddlePulse <= 2500, "tMiddlePulse out of range 500..2500");
        static_assert(tMaxPulse >= 500 && tMaxPulse <= 2500, "tMaxPulse out of range 500..2500");
        //static_assert(tMinPulse < tMiddlePulse, "tMinPulse must be less than tMiddlePulse");
        //static_assert(tMiddlePulse < tMaxPulse, "tMiddlePulse must be less than tMaxPulse");

    private:
        ServoConfig mConfig;
        Servo mServo;

    public:
        ServoDriver() : mConfig(tPin, tMinPulse, tMiddlePulse, tMaxPulse)
        {
            mServo.attach(mConfig.pin);
        }
        
        template<typename... Args>
        ServoDriver(ServoConfig config, Args... args) : mConfig(config)
        {
            mServo.attach(mConfig.pin);
        }

        int GetPin() const
        {
            return mConfig.pin;
        }

    protected:
        void actBipolar(signed short aValue)
        {
            aValue = constrain(aValue, -1000, 1000);
            if (aValue < 0)
                mServo.writeMicroseconds(map(aValue, -1000, 0, mConfig.minPulse, mConfig.middlePulse));
            else
                mServo.writeMicroseconds(map(aValue, 0, 1000, mConfig.middlePulse, mConfig.maxPulse));
        }

        void actUnipolar(signed short aValue)
        {
            aValue = constrain(aValue, 0, 1000);
            if (aValue < 500)
                mServo.writeMicroseconds(map(aValue, 0, 500, mConfig.minPulse, mConfig.middlePulse));
            else
                mServo.writeMicroseconds(map(aValue, 500, 1000, mConfig.middlePulse, mConfig.maxPulse));
        }
    };
    
    template <int tPin, int tMinPulse, int tMaxPulse>
    using ServoFlatDriver = ServoDriver<tPin, tMinPulse, (tMaxPulse + tMinPulse) / 2, tMaxPulse>;
}
```


