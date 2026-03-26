#pragma once
#include <Arduino.h>

namespace evam
{
    /**
     * @brief Steering actuator (centered servo) controller.
     *
     * Maps input range -1000..1000 to output positions:
     * -1000 = left position, 0 = center, 1000 = right position.
     *
     * @tparam Driver Driver class (must implement actBipolar(signed short))
     * @tparam kLeftPos Output value at -1000 input (leftmost position)
     * @tparam kCenterPos Output value at 0 input (center position)
     * @tparam kRightPos Output value at 1000 input (rightmost position)
     */
    template <class Driver, signed short kLeftPos = -1000, signed short kCenterPos = 0, signed short kRightPos = 1000>
    class SteeringActuator : public Driver
    {
        static_assert(kLeftPos >= -1000 && kLeftPos <= 1000, "kLeftPos out of range");
        static_assert(kCenterPos >= -1000 && kCenterPos <= 1000, "kCenterPos out of range");
        static_assert(kRightPos >= -1000 && kRightPos <= 1000, "kRightPos out of range");

    private:
        signed short mLeftPos = kLeftPos;
        signed short mCenterPos = kCenterPos;
        signed short mRightPos = kRightPos;

        signed short compute(signed short aLevel) const
        {
            if (aLevel < 0)
                return map(constrain(aLevel, -1000, 0), -1000, 0, mLeftPos, mCenterPos);
            else
                return map(constrain(aLevel, 0, 1000), 0, 1000, mCenterPos, mRightPos);
        }

    public:
        /**
         * @brief Configure all position parameters at once.
         *
         * @param aLeftPos Output value at -1000 input (leftmost position), range -1000..1000
         * @param aCenterPos Output value at 0 input (center position), range -1000..1000
         * @param aRightPos Output value at 1000 input (rightmost position), range -1000..1000
         */
        void SetupRange(signed short aLeftPos, signed short aCenterPos, signed short aRightPos)
        {
            SetLeftPos(aLeftPos);
            SetCenterPos(aCenterPos);
            SetRightPos(aRightPos);
        }

        /**
         * @brief Set leftmost position output value.
         * @param aValue Output value, clamped to -1000..1000.
         */
        void SetLeftPos(signed short aValue)
        {
            mLeftPos = constrain(aValue, -1000, 1000);
        }

        /**
         * @brief Get leftmost position output value.
         * @return Current leftmost position output value.
         */
        signed short GetLeftPos() const
        {
            return mLeftPos;
        }

        /**
         * @brief Set center position output value.
         * @param aValue Output value, clamped to -1000..1000.
         */
        void SetCenterPos(signed short aValue)
        {
            mCenterPos = constrain(aValue, -1000, 1000);
        }

        /**
         * @brief Get center position output value.
         * @return Current center position output value.
         */
        signed short GetCenterPos() const
        {
            return mCenterPos;
        }

        /**
         * @brief Set rightmost position output value.
         * @param aValue Output value, clamped to -1000..1000.
         */
        void SetRightPos(signed short aValue)
        {
            mRightPos = constrain(aValue, -1000, 1000);
        }

        /**
         * @brief Get rightmost position output value.
         * @return Current rightmost position output value.
         */
        signed short GetRightPos() const
        {
            return mRightPos;
        }

        /**
         * @brief Apply the steering control value.
         * @param aLevel Input steering value, range -1000..1000.
         */
        void Go(signed short aLevel)
        {
            Driver::actBipolar(compute(aLevel));
        }
    };
}
