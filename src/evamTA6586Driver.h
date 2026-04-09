#pragma once

#include <Arduino.h>

namespace evam
{
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
     *
     * @tparam kForwardPin PWM pin connected to FI (forward input)
     * @tparam kBackwardPin PWM pin connected to BI (backward input)
     */
    template <int kForwardPin, int kBackwardPin>
    class TA6586Driver
    {
    public:
        /**
         * @brief Constructor. Initializes pins and stops the motor.
         */
        TA6586Driver()
        {
            pinMode(kForwardPin, OUTPUT);
            pinMode(kBackwardPin, OUTPUT);
            actBipolar(0);
        }

        /**
         * @brief Get the forward pin number.
         * @return Forward PWM pin number.
         */
        int GetForwardPin() const
        {
            return kForwardPin;
        }

        /**
         * @brief Get the backward pin number.
         * @return Backward PWM pin number.
         */
        int GetBackwardPin() const
        {
            return kBackwardPin;
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
            analogWrite(kForwardPin, max(0, normalized));
            analogWrite(kBackwardPin, max(0, -normalized));
        }
    };
}

