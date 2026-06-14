#pragma once
#include <Arduino.h>
#include <evamUtils.h>

namespace evam
{
    /**
     * @brief Configuration structure for TB6612FNGDriver
     */
    struct TB6612Config
    {
        int pinSpeed;
        int pinMode1;
        int pinMode2;

        TB6612Config(int pinSpeed, int pinMode1, int pinMode2)
            : pinSpeed(pinSpeed), pinMode1(pinMode1), pinMode2(pinMode2) {}
    };

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
    template <int kPinSpeed = 0, int kPinMode1 = 0, int kPinMode2 = 0>
    class TB6612FNGDriver
    {
    private:
        TB6612Config mConfig;

    public:
        /**
         * @brief Constructor. Initializes pins and stops the motor.
         */
        TB6612FNGDriver() : mConfig(kPinSpeed, kPinMode1, kPinMode2)
        {
            pinMode(mConfig.pinSpeed, OUTPUT);
            pinMode(mConfig.pinMode1, OUTPUT);
            pinMode(mConfig.pinMode2, OUTPUT);
        }

        template <typename... Args>
        TB6612FNGDriver(TB6612Config config, Args... args) : mConfig(config)
        {
            pinMode(mConfig.pinSpeed, OUTPUT);
            pinMode(mConfig.pinMode1, OUTPUT);
            pinMode(mConfig.pinMode2, OUTPUT);
        }

        /**
         * @brief Get the speed PWM pin number.
         * @return Speed control PWM pin number.
         */
        int GetSpeedPin() const
        {
            return mConfig.pinSpeed;
        }

        /**
         * @brief Get the first direction pin number.
         * @return Direction pin 1 (IN1) number.
         */
        int GetMode1Pin() const
        {
            return mConfig.pinMode1;
        }

        /**
         * @brief Get the second direction pin number.
         * @return Direction pin 2 (IN2) number.
         */
        int GetMode2Pin() const
        {
            return mConfig.pinMode2;
        }

    protected:
        /**
         * @brief Set bipolar (signed) control value.
         * @param aValue Range -1000..1000.
         *        Positive = forward, negative = reverse, 0 = stop.
         */
        void actBipolar(signed short aValue)
        {
            digitalWrite(mConfig.pinMode1, aValue > 0);
            digitalWrite(mConfig.pinMode2, aValue < 0);
            universalWrite(mConfig.pinSpeed, map(constrain(abs(aValue), 0, 1000), 0, 1000, 0, 255));
        }
    };
}
