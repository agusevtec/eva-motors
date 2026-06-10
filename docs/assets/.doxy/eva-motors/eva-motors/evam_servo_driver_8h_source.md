

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

    template <int kPin = 0, int kMinPulse = 1000, int kMiddlePulse = 1500, int kMaxPulse = 2000>
    class ServoDriver
    {
        static_assert(kMinPulse >= 500 && kMinPulse <= 2500, "kMinPulse out of range 500..2500");
        static_assert(kMiddlePulse >= 500 && kMiddlePulse <= 2500, "kMiddlePulse out of range 500..2500");
        static_assert(kMaxPulse >= 500 && kMaxPulse <= 2500, "kMaxPulse out of range 500..2500");
        static_assert(kMinPulse < kMiddlePulse, "kMinPulse must be less than kMiddlePulse");
        static_assert(kMiddlePulse < kMaxPulse, "kMiddlePulse must be less than kMaxPulse");

    private:
        ServoConfig mConfig;
        Servo mServo;

    public:
        ServoDriver() : mConfig(kPin, kMinPulse, kMiddlePulse, kMaxPulse)
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
    
    template <int kPin, int kMinPulse, int kMaxPulse>
    using ServoFlatDriver = ServoDriver<kPin, kMinPulse, (kMaxPulse - kMinPulse) / 2 + kMinPulse, kMaxPulse>;
}
```


