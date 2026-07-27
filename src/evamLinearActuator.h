#pragma once
#include <Arduino.h>

namespace evam
{
    /**
     * @brief Configuration structure for LinearActuator
     */
    struct LinearActuatorConfig
    {
        int minValue;
        int maxValue;

        LinearActuatorConfig(int minValue, int maxValue) : minValue(constrain(minValue, -1000, 1000)), maxValue(constrain(maxValue, -1000, 1000)) {}
    };

    /**
     * @brief Linear actuator controller (position control).
     *
     * Maps input range 0..1000 linearly to output values. 0 = minimum position, 1000 = maximum position.
     *
     * @tparam TDriver TDriver class (must implement actUnipolar(unsigned short))
     * @tparam tMinValue Output value at 0 input (minimum position)
     * @tparam tMaxValue Output value at 1000 input (maximum position)
     */
    template <class TDriver, int tMinValue = 0, int tMaxValue = 1000>
    class LinearActuator : public TDriver
    {
        static_assert(tMinValue >= -1000 && tMinValue <= 1000, "tMinValue out of range");
        static_assert(tMaxValue >= -1000 && tMaxValue <= 1000, "tMaxValue out of range");

    private:
        LinearActuatorConfig mConfig;

        signed short compute(signed short aLevel) const
        {
            return map(constrain(aLevel, 0, 1000), 0, 1000, mConfig.minValue, mConfig.maxValue);
        }

    public:
        LinearActuator() : mConfig(tMinValue, tMaxValue)
        {
            Go(0);
        }

        template <typename... Args>
        LinearActuator(LinearActuatorConfig config, Args... args) : TDriver(args...), mConfig(config)
        {
            Go(0);
        }

        /**
         * @brief Configure the position range parameters at once.
         *
         * @param aMinValue Output value at 0 input (minimum position), range -1000..1000
         * @param aMaxValue Output value at 1000 input (maximum position), range -1000..1000
         */
        void SetupRange(int minValue, int maxValue)
        {
            SetMinValue(minValue);
            SetMaxValue(maxValue);
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
            TDriver::actUnipolar(compute(aLevel));
        }
    };
}
