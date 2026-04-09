

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
    template <int kPin, int kMinPulse = 500, int kMaxPulse = 2500>
    class SoftwareServoDriver : public virtual Tickable
    {
        static_assert(kMinPulse >= 500 && kMinPulse <= 2500, "kMinPulse out of range 500..2500");
        static_assert(kMaxPulse >= 500 && kMaxPulse <= 2500, "kMaxPulse out of range 500..2500");
        static_assert(kMinPulse < kMaxPulse, "kMinPulse must be less than kMaxPulse");

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
            int centerPulse = (kMinPulse + kMaxPulse) / 2;
            int range = (kMaxPulse - kMinPulse) / 2;
            mTargetPulseUs = centerPulse + (aValue * range / 1000);
        }

        void actUnipolar(signed short aValue)
        {
            aValue = constrain(aValue, 0, 1000);
            mTargetPulseUs = map(aValue, 0, 1000, kMinPulse, kMaxPulse);
        }
    };

} // namespace evam
```


