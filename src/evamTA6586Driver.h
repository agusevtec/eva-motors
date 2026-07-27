#pragma once

#include <Arduino.h>
#include <evamUtils.h>

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
     * @brief Driver for the TA6586 (classic dual H-bridge) motor driver.
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
     * @tparam tForwardPin PWM pin connected to FI (forward input)
     * @tparam tBackwardPin PWM pin connected to BI (backward input)
     */
    template <int tForwardPin = 0, int tBackwardPin = 0>
    class TA6586Driver
    {
    private:
        TA6586Config mConfig;

    public:
        /**
         * @brief Constructor. Initializes pins and stops the motor.
         */
        TA6586Driver() : mConfig(tForwardPin, tBackwardPin)
        {
            pinMode(mConfig.forwardPin, OUTPUT);
            pinMode(mConfig.backwardPin, OUTPUT);
        }

        template <typename... Args>
        TA6586Driver(TA6586Config config, Args... args) : mConfig(config)
        {
            pinMode(mConfig.forwardPin, OUTPUT);
            pinMode(mConfig.backwardPin, OUTPUT);
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
            universalWrite(mConfig.forwardPin, max(0, normalized));
            universalWrite(mConfig.backwardPin, max(0, -normalized));
        }
    };
}
