

# File evamSoftwareServoDriver.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evamSoftwareServoDriver.h**](evam_software_servo_driver_8h.md)

[Go to the documentation of this file](evam_software_servo_driver_8h.md)


```C++
#pragma once

#include <Arduino.h>
#include <evaTickable.h>

using namespace eva;

namespace evam
{
    struct SoftwareServoConfig {
        int pin;
        int minPulse;
        int middlePulse;
        int maxPulse;
        
        SoftwareServoConfig(int pin, int minPulse, int middlePulse, int maxPulse) 
            : pin(pin), minPulse(minPulse), middlePulse(middlePulse), maxPulse(maxPulse) {}
    };

    template <int kPin, int kMinPulse = 1000, int kMiddlePulse = 1500, int kMaxPulse = 2000>
    class SoftwareServoDriver : public virtual Tickable
    {
        static_assert(kMinPulse >= 500 && kMinPulse <= 2500, "kMinPulse out of range 500..2500");
        static_assert(kMiddlePulse >= 500 && kMiddlePulse <= 2500, "kMiddlePulse out of range 500..2500");
        static_assert(kMaxPulse >= 500 && kMaxPulse <= 2500, "kMaxPulse out of range 500..2500");
        static_assert(kMinPulse < kMiddlePulse, "kMinPulse must be less than kMiddlePulse");
        static_assert(kMiddlePulse < kMaxPulse, "kMiddlePulse must be less than kMaxPulse");

    private:
        static constexpr unsigned long kRefreshIntervalMs = 20;

        SoftwareServoConfig mConfig;
        
        unsigned long mTargetPulseUs = kMinPulse;
        unsigned long mPulseStartUs = 0;
        unsigned long mLastRefreshMs = 0;
        bool mPulseActive = false;

        void tick() override
        {
            unsigned long nowUs = micros();

            if (mPulseActive)
            {
                if (nowUs - mPulseStartUs >= mTargetPulseUs)
                {
                    digitalWrite(mConfig.pin, LOW);
                    mPulseActive = false;
                }
            }

            if (!mPulseActive)
            {
                unsigned long nowMs = millis();
                if (nowMs - mLastRefreshMs >= kRefreshIntervalMs)
                {
                    mLastRefreshMs = nowMs;
                    digitalWrite(mConfig.pin, HIGH);
                    mPulseStartUs = nowUs;
                    mPulseActive = true;
                }
            }
        }

    public:
        SoftwareServoDriver() : mConfig(kPin, kMinPulse, kMiddlePulse, kMaxPulse)
        {
            pinMode(mConfig.pin, OUTPUT);
            digitalWrite(mConfig.pin, LOW);
        }
        
        template<typename... Args>
        SoftwareServoDriver(SoftwareServoConfig config, Args... args) : mConfig(config)
        {
            pinMode(mConfig.pin, OUTPUT);
            digitalWrite(mConfig.pin, LOW);
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
                mTargetPulseUs = map(aValue, -1000, 0, mConfig.minPulse, mConfig.middlePulse);
            else
                mTargetPulseUs = map(aValue, 0, 1000, mConfig.middlePulse, mConfig.maxPulse);
        }

        void actUnipolar(signed short aValue)
        {
            aValue = constrain(aValue, 0, 1000);
            if (aValue < 500)
                mTargetPulseUs = map(aValue, 0, 500, mConfig.minPulse, mConfig.middlePulse);
            else
                mTargetPulseUs = map(aValue, 500, 1000, mConfig.middlePulse, mConfig.maxPulse);
        }
    };

    template <int kPin, int kMinPulse, int kMaxPulse>
    using SoftwareServoFlatDriver = SoftwareServoDriver<kPin, kMinPulse, (kMaxPulse - kMinPulse) / 2 + kMinPulse, kMaxPulse>;
}
```


