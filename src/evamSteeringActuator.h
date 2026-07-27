#pragma once
#include <Arduino.h>

namespace evam
{
    /**
     * @brief Configuration structure for SteeringActuator
     */
    struct SteeringConfig
    {
        signed short leftPos;
        signed short centerPos;
        signed short rightPos;

        SteeringConfig(signed short leftPos, signed short centerPos, signed short rightPos)
            : leftPos(constrain(leftPos, -1000, 1000)),
              centerPos(constrain(centerPos, -1000, 1000)),
              rightPos(constrain(rightPos, -1000, 1000)) {}
    };

    /**
     * @brief Steering actuator (centered servo) controller.
     *
     * Maps input range -1000..1000 to output positions:
     * -1000 = left position, 0 = center, 1000 = right position.
     *
     * @tparam Driver Driver class (must implement actBipolar(signed short))
     * @tparam tLeftPos Output value at -1000 input (leftmost position)
     * @tparam tCenterPos Output value at 0 input (center position)
     * @tparam tRightPos Output value at 1000 input (rightmost position)
     */
    template <class TDriver,
              signed short tLeftPos = -1000,
              signed short tCenterPos = 0,
              signed short tRightPos = 1000>
    class SteeringActuator : public TDriver
    {
        static_assert(tLeftPos >= -1000 && tLeftPos <= 1000, "tLeftPos out of range");
        static_assert(tCenterPos >= -1000 && tCenterPos <= 1000, "tCenterPos out of range");
        static_assert(tRightPos >= -1000 && tRightPos <= 1000, "tRightPos out of range");

    private:
        SteeringConfig mConfig;

        signed short compute(signed short aLevel) const
        {
            if (aLevel < 0)
                return map(constrain(aLevel, -1000, 0), -1000, 0, mConfig.leftPos, mConfig.centerPos);
            else
                return map(constrain(aLevel, 0, 1000), 0, 1000, mConfig.centerPos, mConfig.rightPos);
        }

    public:
        SteeringActuator() : mConfig(tLeftPos, tCenterPos, tRightPos)
        {
            Go(0);
        }

        template <typename... Args>
        SteeringActuator(SteeringConfig config, Args... args) : TDriver(args...), mConfig(config)
        {
            Go(0);
        }

        /**
         * @brief Configure all position parameters at once.
         *
         * @param aLeftPos Output value at -1000 input (leftmost position), range -1000..1000
         * @param aCenterPos Output value at 0 input (center position), range -1000..1000
         * @param aRightPos Output value at 1000 input (rightmost position), range -1000..1000
         */
        void SetupRange(signed short leftPos, signed short centerPos, signed short rightPos)
        {
            SetLeftPos(leftPos);
            SetCenterPos(centerPos);
            SetRightPos(rightPos);
        }

        /**
         * @brief Set leftmost position output value.
         * @param aValue Output value, clamped to -1000..1000.
         */
        void SetLeftPos(signed short aValue)
        {
            mConfig.leftPos = constrain(aValue, -1000, 1000);
        }

        /**
         * @brief Get leftmost position output value.
         * @return Current leftmost position output value.
         */
        signed short GetLeftPos() const
        {
            return mConfig.leftPos;
        }

        /**
         * @brief Set center position output value.
         * @param aValue Output value, clamped to -1000..1000.
         */
        void SetCenterPos(signed short aValue)
        {
            mConfig.centerPos = constrain(aValue, -1000, 1000);
        }

        /**
         * @brief Get center position output value.
         * @return Current center position output value.
         */
        signed short GetCenterPos() const
        {
            return mConfig.centerPos;
        }

        /**
         * @brief Set rightmost position output value.
         * @param aValue Output value, clamped to -1000..1000.
         */
        void SetRightPos(signed short aValue)
        {
            mConfig.rightPos = constrain(aValue, -1000, 1000);
        }

        /**
         * @brief Get rightmost position output value.
         * @return Current rightmost position output value.
         */
        signed short GetRightPos() const
        {
            return mConfig.rightPos;
        }

        /**
         * @brief Apply the steering control value.
         * @param aLevel Input steering value, range -1000..1000.
         */
        void Go(signed short aLevel)
        {
            TDriver::actBipolar(compute(aLevel));
        }
    };
}
