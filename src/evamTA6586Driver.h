#pragma once

#include <Arduino.h>

namespace evam
{
    /**
     * @brief Configuration structure for TA6586Driver
     */
    struct TA6586Config
    {
        int forwardPin;
        int backwardPin;

        TA6586Config(int forwardPin, int backwardPin) : forwardPin(forwardPin), backwardPin(backwardPin) {}
    };

    /**
     * @brief Driver for the TA6586 dual H-bridge motor driver.
     *
     * Pinout:
     * @verbatim
     *       TA-6586
     *       -------
     *  5 - |       | - VCC
     *  6 - |       | - GND
     *  7 - |       | - FI (Forward pin)
     *  8 - |   _   | - BI (Backward pin)
     *       --/ \--
     * @endverbatim
     *
     * @tparam kForwardPin PWM pin connected to FI (forward input)
     * @tparam kBackwardPin PWM pin connected to BI (backward input)
     */
    template <int kForwardPin = 0, int kBackwardPin = 0>
    class TA6586Driver
    {
    private:
        TA6586Config mConfig;

    public:
        /**
         * @brief Constructor. Initializes pins and stops the motor.
         */
        TA6586Driver() : mConfig(kForwardPin, kBackwardPin)
        {
            pinMode(mConfig.forwardPin, OUTPUT);
            pinMode(mConfig.backwardPin, OUTPUT);
            actBipolar(0);
        }

        template <typename... Args>
        TA6586Driver(TA6586Config config, Args... args) : mConfig(config)
        {
            pinMode(mConfig.forwardPin, OUTPUT);
            pinMode(mConfig.backwardPin, OUTPUT);
            actBipolar(0);
        }

        /**
         * @brief Get the forward pin number.
         * @return Forward PWM pin number.
         */
        int GetForwardPin() const
        {
            return mConfig.forwardPin;
        }

        /**
         * @brief Get the backward pin number.
         * @return Backward PWM pin number.
         */
        int GetBackwardPin() const
        {
            return mConfig.backwardPin;
        }

    protected:
        /**
         * @brief Set bipolar (signed) control value.
         * @param aValue Range -1000..1000, mapped to -255..255 PWM.
         *        Positive = forward, negative = reverse, 0 = stop.
         */
        void actBipolar(signed short aValue)
        {
            int normalized = map(constrain(aValue, -1000, 1000), -1000, 1000, -255, 255);
            analogWrite(mConfig.forwardPin, max(0, normalized));
            analogWrite(mConfig.backwardPin, max(0, -normalized));
        }
    };
}
