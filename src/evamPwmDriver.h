#ifndef EVAM_PWM_DRIVER_H_
#define EVAM_PWM_DRIVER_H_

#pragma once

#include <Arduino.h>

namespace evam
{
    /**
     * @brief Simple PWM output driver (unipolar).
     *
     * Converts 0..1000 input to 0..255 PWM duty cycle.
     * Suitable for MOSFETs and other unipolar devices.
     *
     * @tparam kPin PWM output pin number.
     */
    template <int kPin>
    class PwmDriver
    {
    public:
        /**
         * @brief Constructor. Initializes the pin as output.
         */
        PwmDriver()
        {
            pinMode(kPin, OUTPUT);
            actUnipolar(0);
        }

    protected:
        /**
         * @brief Set unipolar output value.
         * @param aValue Input range 0..1000, mapped to 0..255 PWM.
         */
        void actUnipolar(unsigned short aValue)
        {
            int pwm = map(constrain(aValue, 0, 1000), 0, 1000, 0, 255);
            analogWrite(kPin, pwm);
        }
    };

} // namespace evam

#endif // EVAM_PWM_DRIVER_H_
