#pragma once
#include <Arduino.h>

namespace evam
{
    /**
     * @brief Configuration structure for LinearActuator
     */
    struct LinearActuatorConfig {
        int minValue;
        int maxValue;
        
        LinearActuatorConfig(int minVal, int maxVal) : minValue(minVal), maxValue(maxVal) {}
    };

    /**
     * @brief Linear actuator controller (position control).
     *
     * Maps input range 0..1000 linearly to output values. 0 = minimum position, 1000 = maximum position.
     *
     * @tparam Driver Driver class (must implement actUnipolar(unsigned short))
     * @tparam kMinValue Output value at 0 input (minimum position)
     * @tparam kMaxValue Output value at 1000 input (maximum position)
     */
    template <class Driver, int kMinValue = 0, int kMaxValue = 1000>
    class LinearActuator : public Driver
    {
        static_assert(kMinValue >= -1000 && kMinValue <= 1000, "kMinValue out of range");
        static_assert(kMaxValue >= -1000 && kMaxValue <= 1000, "kMaxValue out of range");

    private:
        LinearActuatorConfig mConfig;
        
        signed short compute(signed short aLevel) const
        {
            return map(constrain(aLevel, 0, 1000), 0, 1000, mConfig.minValue, mConfig.maxValue);
        }

    public:
        LinearActuator() : mConfig(kMinValue, kMaxValue) {}
        
        template<typename... Args>
        LinearActuator(LinearActuatorConfig config, Args... args) : Driver(args...), mConfig(config) {}

        /**
         * @brief Configure the position range parameters at once.
         *
         * @param aMinValue Output value at 0 input (minimum position), range -1000..1000
         * @param aMaxValue Output value at 1000 input (maximum position), range -1000..1000
         */
        void SetupRange(int aMinValue, int aMaxValue)
        {
            SetMinValue(aMinValue);
            SetMaxValue(aMaxValue);
        }

        /**
         * @brief Set minimum output value (position at 0 input).
         * @param aValue Output value, clamped to -1000..1000.
         */
        void SetMinValue(int aValue)
        {
            mConfig.minValue = constrain(aValue, -1000, 1000);
        }

        /**
         * @brief Get minimum output value (position at 0 input).
         * @return Current minimum output value.
         */
        int GetMinValue() const
        {
            return mConfig.minValue;
        }

        /**
         * @brief Set maximum output value (position at 1000 input).
         * @param aValue Output value, clamped to -1000..1000.
         */
        void SetMaxValue(int aValue)
        {
            mConfig.maxValue = constrain(aValue, -1000, 1000);
        }

        /**
         * @brief Get maximum output value (position at 1000 input).
         * @return Current maximum output value.
         */
        int GetMaxValue() const
        {
            return mConfig.maxValue;
        }

        /**
         * @brief Apply the position control value.
         * @param aLevel Input position, range 0..1000.
         */
        void Go(signed short aLevel)
        {
            Driver::actUnipolar(compute(aLevel));
        }
    };
}
