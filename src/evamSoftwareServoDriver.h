<evamSoftwareServoDriver.h>
#ifndef EVAM_SOFTWARE_SERVO_DRIVER_H_
#define EVAM_SOFTWARE_SERVO_DRIVER_H_

#pragma once

#include <Arduino.h>
#include <evaTickable.h>

using namespace eva;

namespace evam
{
    /**
     * @brief Software-based servo driver using millis() for timing.
     *
     * This driver implements servo control without using the hardware PWM
     * limitations of the Arduino Servo library. Each instance manages its
     * own timing and inherits from Tickable to integrate with the event loop.
     *
     * @tparam kPin Servo signal pin number.
     * @tparam kMinPulse Minimum pulse width in microseconds (default: 500)
     * @tparam kMaxPulse Maximum pulse width in microseconds (default: 2500)
     */
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
            
            // Всегда проверяем завершение активного импульса
            if (mPulseActive)
            {
                if (nowUs - mPulseStartUs >= mTargetPulseUs)
                {
                    digitalWrite(kPin, LOW);
                    mPulseActive = false;
                }
            }
            
            // Запуск нового импульса
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
        /**
         * @brief Constructor. Initializes the pin as output.
         */
        SoftwareServoDriver()
        {
            pinMode(kPin, OUTPUT);
            digitalWrite(kPin, LOW);
        }

    protected:
        /**
         * @brief Bipolar (centered) control. Input range -1000..1000.
         * Output: pulse width mapped to kMinPulse..kMaxPulse with center at mid-point.
         * @param aValue Input value, range -1000..1000.
         */
        void actBipolar(signed short aValue)
        {
            aValue = constrain(aValue, -1000, 1000);
            int centerPulse = (kMinPulse + kMaxPulse) / 2;
            int range = (kMaxPulse - kMinPulse) / 2;
            mTargetPulseUs = centerPulse + (aValue * range / 1000);
        }

        /**
         * @brief Unipolar (absolute) control. Input range 0..1000.
         * Output: pulse width mapped to kMinPulse..kMaxPulse.
         * @param aValue Input value, range 0..1000.
         */
        void actUnipolar(signed short aValue)
        {
            aValue = constrain(aValue, 0, 1000);
            mTargetPulseUs = map(aValue, 0, 1000, kMinPulse, kMaxPulse);
        }
    };

} // namespace evam

#endif // EVAM_SOFTWARE_SERVO_DRIVER_H_
</evamSoftwareServoDriver.h>