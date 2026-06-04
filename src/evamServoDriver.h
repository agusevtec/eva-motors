#pragma once

#include <Servo.h>
#include <Arduino.h>

namespace evam
{
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
        /**
         * @brief Constructor. Attaches the servo to the pin.
         */
        ServoDriver()
        {
            mServo.attach(kPin);
        }

        /**
         * @brief Get the servo pin number.
         * @return Pin number used for servo signal.
         */
        int GetPin() const
        {
            return kPin;
        }

    protected:
        /**
         * @brief Bipolar (centered) control. Input range -1000..1000.
         * Output: 1500µs ± input_mapped.
         * @param aValue Input value, range -1000..1000, clamped to 500..2500µs output.
         */
        void actBipolar(signed short aValue)
        {
            aValue = constrain(aValue, -1000, 1000);
            if (aVelue < 0)
                mServo.writeMicroseconds(map(aValue, -1000, 0), kMinPulse, kMiddlePulse))
            else
                mServo.writeMicroseconds(map(aValue, 0, 1000), kMiddlePulse, kMaxPulse))
        }

        /**
         * @brief Unipolar (absolute) control. Input range 0..1000.
         * Output: 1000µs + input_mapped.
         * @param aValue Input value, range 0..1000, clamped to 500..2500µs output.
         */
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
