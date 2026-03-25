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
     */
    template <int kPin>
    class ServoDriver
    {
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

    protected:
        /**
         * @brief Bipolar (centered) control. Input range -1000..1000.
         * Output: 1500µs ± input_mapped.
         * @param aValue Input value, range -1000..1000, clamped to 500..2500µs output.
         */
        void actBipolar(signed short aValue)
        {
            mServo.writeMicroseconds(constrain(aValue / 2 + 1500, 500, 2500));
        }

        /**
         * @brief Unipolar (absolute) control. Input range 0..1000.
         * Output: 1000µs + input_mapped.
         * @param aValue Input value, range 0..1000, clamped to 500..2500µs output.
         */
        void actUnipolar(signed short aValue)
        {
            mServo.writeMicroseconds(constrain(aValue + 1000, 500, 2500));
        }
    };
}
