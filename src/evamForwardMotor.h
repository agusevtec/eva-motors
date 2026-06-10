#pragma once
#include <Arduino.h>

namespace evam
{
    /**
     * @brief Configuration structure for ForwardMotor
     */
    struct ForwardConfig {
        int minValue;
        int maxValue;
        
        ForwardConfig(int minValue, int maxValue) : minValue(constrain(minValue, -1000, 1000)), maxValue(constrain(maxValue, -1000, 1000)) {}
    };

    /**
     * @brief Unidirectional forward-only motor controller (e.g., aircraft ESC, throttle).
     *
     * Maps input range 0..1000 to driver output. Negative inputs are treated as stop (0).
     *
     * @tparam Driver Driver class (must implement actUnipolar(unsigned short))
     * @tparam kMinValue Minimum output value (e.g., 20 = stop)
     * @tparam kMaxValue Maximum output value (e.g., 1000 = full throttle)
     */
    template <class Driver, int kMinValue = 0, int kMaxValue = 1000>
    class ForwardMotor : public Driver
    {
        static_assert(kMinValue >= -1000 && kMinValue <= 1000, "kMinValue out of range");
        static_assert(kMaxValue >= -1000 && kMaxValue <= 1000, "kMaxValue out of range");

    private:
        ForwardConfig mConfig;
        
        signed short compute(signed short aLevel) const
        {
            if (aLevel > 0)
                return map(constrain(aLevel, 0, 1000), 0, 1000, mConfig.minValue, mConfig.maxValue);
            return 0;
        }

    public:
        ForwardMotor() : mConfig(kMinValue, kMaxValue) {}
        
        template<typename... Args>
        ForwardMotor(ForwardConfig config, Args... args) : Driver(args...), mConfig(config) {}

        /**
         * @brief Configure the output range parameters at once.
         *
         * @param aMinValue Minimum output value (stop position)
         * @param aMaxValue Maximum output value (full throttle)
         */
        void SetupRange(int minValue, int maxValue)
        {
            SetMinValue(minValue);
            SetMaxValue(maxValue);
        }

        /**
         * @brief Set minimum output value.
         * @param aValue Output value, clamped to -1000..1000.
         */
        void SetMinValue(int aValue)
        {
            mConfig.minValue = constrain(aValue, -1000, 1000);
        }

        /**
         * @brief Get minimum output value.
         * @return Current minimum output value.
         */
        int GetMinValue() const
        {
            return mConfig.minValue;
        }

        /**
         * @brief Set maximum output value.
         * @param aValue Output value, clamped to -1000..1000.
         */
        void SetMaxValue(int aValue)
        {
            mConfig.maxValue = constrain(aValue, -1000, 1000);
        }

        /**
         * @brief Get maximum output value.
         * @return Current maximum output value.
         */
        int GetMaxValue() const
        {
            return mConfig.maxValue;
        }

        /**
         * @brief Apply the control value.
         * @param aLevel Input control value, range 0..1000 (negative treated as 0).
         */
        void Go(signed short aLevel)
        {
            Driver::actUnipolar(compute(aLevel));
        }
    };
}
