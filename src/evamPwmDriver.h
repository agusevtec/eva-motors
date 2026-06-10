#pragma once

#include <Arduino.h>

namespace evam
{
    /**
     * @brief Configuration structure for PwmDriver
     */
    struct PwmConfig
    {
        int pin;

        PwmConfig(int pin) : pin(pin) {}
    };

    /**
     * @brief Simple PWM output driver (unipolar).
     *
     * Converts 0..1000 input to 0..255 PWM duty cycle.
     * Suitable for MOSFETs and other unipolar devices.
     *
     * @tparam kPin PWM output pin number.
     */
    template <int kPin = 0>
    class PwmDriver
    {
    private:
        PwmConfig mConfig;

    public:
        PwmDriver() : mConfig(kPin)
        {
            pinMode(kPin, OUTPUT);
            actUnipolar(0);
        }

        template <typename... Args>
        PwmDriver(PwmConfig config, Args... args) : mConfig(config)
        {
            pinMode(mConfig.pin, OUTPUT);
            actUnipolar(0);
        }

        /**
         * @brief Get the PWM pin number.
         * @return Pin number.
         */
        int GetPin() const
        {
            return mConfig.pin;
        }

    protected:
        /**
         * @brief Set unipolar output value.
         * @param aValue Input range 0..1000, mapped to 0..255 PWM.
         */
        void actUnipolar(unsigned short aValue)
        {
            int pwm = map(constrain(aValue, 0, 1000), 0, 1000, 0, 255);
            analogWrite(mConfig.pin, pwm);
        }
    };
}
