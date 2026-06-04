

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
    template <int kPin, int kMinPulse = 1000, int kMiddlePulse = 1500, int kMaxPulse = 2000>
    class SoftwareServoDriver : public virtual Tickable
    {
        static_assert(kMinPulse >= 500 && kMinPulse <= 2500, "kMinPulse out of range 500..2500");
        static_assert(kMiddlePulse >= 500 && kMiddlePulse <= 2500, "kMiddlePulse out of range 500..2500");
        static_assert(kMaxPulse >= 500 && kMaxPulse <= 2500, "kMaxPulse out of range 500..2500");
        static_assert(kMinPulse < kMiddlePulse, "kMinPulse must be less than kMiddlePulse");
        static_assert(kMiddlePulse < kMaxPulse, "kMiddlePulse must be less than kMaxPulse");

    private:
        static constexpr unsigned long kRefreshIntervalMs = 20; // 50Hz refresh rate

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
                    digitalWrite(kPin, LOW);
                    mPulseActive = false;
                }
            }

            if (!mPulseActive)
            {
                unsigned long nowMs = millis();
                if (nowMs - mLastRefreshMs >= kRefreshIntervalMs)
                {
                    mLastRefreshMs = nowMs;
                    digitalWrite(kPin, HIGH);
                    mPulseStartUs = nowUs;
                    mPulseActive = true;
                }
            }
        }

    public:
        SoftwareServoDriver()
        {
            pinMode(kPin, OUTPUT);
            digitalWrite(kPin, LOW);
        }

    protected:
        void actBipolar(signed short aValue)
        {
            aValue = constrain(aValue, -1000, 1000);
            if (aVelue < 0)
                mTargetPulseUs = map(aValue, -1000, 0), kMinPulse, kMiddlePulse)
            else
                mTargetPulseUs = map(aValue, 0, 1000), kMiddlePulse, kMaxPulse)
        }

        void actUnipolar(signed short aValue)
        {
            aValue = constrain(aValue, 0, 1000);
            if (aVelue < 500)
                mTargetPulseUs = map(aValue, 0, 500), kMinPulse, kMiddlePulse)
            else
                mTargetPulseUs = map(aValue, 500, 1000), kMiddlePulse, kMaxPulse)
        }
    };

    template <int kPin, int kMinPulse, int kMaxPulse>
    using ServoFlatDriver = Servoriver<kPin, kMinPulse, (kMaxPulse - kMinPulse) / 2, kMaxPulse>

} // namespace evam
```


