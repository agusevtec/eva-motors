#pragma once
#include <Arduino.h>
namespace evam
{
    /**
     * @brief Driver for the TB6612FNG dual H-bridge motor driver.
     *
     * Pin connection:
     * - PWMA - speed control PWM pin
     * - AIN1 / AIN2 - direction control pins for motor A
     * - PWMB, BIN1, BIN2 for motor B (use separate instance)
     *
     * @tparam kPinSpeed PWM pin for speed control
     * @tparam kPinMode1 Direction pin 1 (IN1)
     * @tparam kPinMode2 Direction pin 2 (IN2)
     */
    template <int kPinSpeed, int kPinMode1, int kPinMode2>
    class TB6612FNGDriver
    {

    public:
        /**
         * @brief Constructor. Initializes pins and stops the motor.
         */
        TB6612FNGDriver()
        {
            pinMode(kPinSpeed, OUTPUT);
            pinMode(kPinMode1, OUTPUT);
            pinMode(kPinMode2, OUTPUT);
            actBipolar(0);
        }

        /**
         * @brief Get the speed PWM pin number.
         * @return Speed control PWM pin number.
         */
        int GetSpeedPin() const
        {
            return kPinSpeed;
        }

        /**
         * @brief Get the first direction pin number.
         * @return Direction pin 1 (IN1) number.
         */
        int GetMode1Pin() const
        {
            return kPinMode1;
        }

        /**
         * @brief Get the second direction pin number.
         * @return Direction pin 2 (IN2) number.
         */
        int GetMode2Pin() const
        {
            return kPinMode2;
        }

    protected:
        /**
         * @brief Set bipolar (signed) control value.
         * @param aValue Range -1000..1000.
         *        Positive = forward, negative = reverse, 0 = stop.
         */
        void actBipolar(signed short aValue)
        {
            int pwm = map(constrain(abs(aValue), 0, 1000), 0, 1000, 0, 255);
            digitalWrite(kPinMode1, aValue > 0);
            digitalWrite(kPinMode2, aValue < 0);
            analogWrite(kPinSpeed, pwm);
        }
    };
}

