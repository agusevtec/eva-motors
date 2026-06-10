#pragma once

#include <Arduino.h>
#include <evaTickable.h>

using namespace eva;

namespace evam
{
    /**
     * @brief Configuration structure for SoftwareServoDriver
     */
    struct SoftwareServoConfig {
        int pin;
        int minPulse;
        int middlePulse;
        int maxPulse;
        
        SoftwareServoConfig(int pin, int minPulse, int middlePulse, int maxPulse) 
            : pin(pin), minPulse(minPulse), middlePulse(middlePulse), maxPulse(maxPulse) {}
    };

    /**
     * @brief Software-based servo driver using millis() for timing.
     *
     * This driver implements servo control without using the hardware PWM
     * limitations of the Arduino Servo library. Each instance manages its
     * own timing and inherits from Tickable to integrate with the event loop.
     *
     * @tparam kPin Servo signal pin number.
     * @tparam kMinPulse Minimum pulse width in microseconds (default: 1000)
     * @tparam kMiddlePulse Middle pulse width in microseconds (default: 1500)
     * @tparam kMaxPulse Maximum pulse width in microseconds (default: 2000)
     */
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
        /**
         * @brief Constructor. Initializes the pin as output.
         */
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

        /**
         * @brief Get the servo pin number.
         * @return Pin number used for servo signal.
         */
        int GetPin() const
        {
            return mConfig.pin;
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
            if (aValue < 0)
                mTargetPulseUs = map(aValue, -1000, 0, mConfig.minPulse, mConfig.middlePulse);
            else
                mTargetPulseUs = map(aValue, 0, 1000, mConfig.middlePulse, mConfig.maxPulse);
        }

        /**
         * @brief Unipolar (absolute) control. Input range 0..1000.
         * Output: pulse width mapped to kMinPulse..kMaxPulse.
         * @param aValue Input value, range 0..1000.
         */
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
