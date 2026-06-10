#pragma once

#include <Servo.h>
#include <Arduino.h>

namespace evam
{
    /**
     * @brief Configuration structure for ServoDriver
     */
    struct ServoConfig {
        int pin;
        int minPulse;
        int middlePulse;
        int maxPulse;
        
        ServoConfig(int pin, int minPulse, int middlePulse, int maxPulse) 
            : pin(pin), minPulse(minPulse), middlePulse(middlePulse), maxPulse(maxPulse) {}
    };

    /**
     * @brief Servo driver using standard Arduino Servo library.
     *
     * Supports both bipolar (centered) and unipolar (absolute) control modes.
     *
     * @tparam kPin Servo signal pin number.
     * @tparam kMinPulse Minimum pulse width in microseconds (default: 1000)
     * @tparam kMiddlePulse Middle pulse width in microseconds (default: 1500)
     * @tparam kMaxPulse Maximum pulse width in microseconds (default: 2000)
     */
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
         * Output: 1500Вµs В± input_mapped.
         * @param aValue Input value, range -1000..1000, clamped to 500..2500Вµs output.
         */
        void actBipolar(signed short aValue)
        {
            aValue = constrain(aValue, -1000, 1000);
            if (aValue < 0)
                mServo.writeMicroseconds(map(aValue, -1000, 0, mConfig.minPulse, mConfig.middlePulse));
            else
                mServo.writeMicroseconds(map(aValue, 0, 1000, mConfig.middlePulse, mConfig.maxPulse));
        }

        /**
         * @brief Unipolar (absolute) control. Input range 0..1000.
         * Output: 1000Вµs + input_mapped.
         * @param aValue Input value, range 0..1000, clamped to 500..2500Вµs output.
         */
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
