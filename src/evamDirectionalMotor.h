#pragma once
#include <Arduino.h>

namespace evam
{
    /**
     * @brief Configuration structure for DirectionalMotor
     */
    struct DirectionalConfig
    {
        signed short maxBackward;
        signed short minBackward;
        signed short minForward;
        signed short maxForward;

        DirectionalConfig(signed short maxBackward, signed short minBackward, signed short minForward, signed short maxForward)
            : maxBackward(constrain(maxBackward, -1000, 1000)),
              minBackward(constrain(minBackward, -1000, 1000)),
              minForward(constrain(minForward, -1000, 1000)),
              maxForward(constrain(maxForward, -1000, 1000)) {}
    };

    /**
     * @brief Bidirectional motor controller (forward/reverse).
     *
     * Maps a signed input range -1000..1000 to driver-specific output values.
     * Negative values correspond to reverse, positive to forward.
     *
     * @tparam TDriver TDriver class (must implement actBipolar(signed short))
     * @tparam tMaxBackward Maximum reverse output value (e.g., -1000)
     * @tparam tMinBackward Minimum reverse output value (e.g., -50)
     * @tparam tMinForward Minimum forward output value (e.g., 50)
     * @tparam tMaxForward Maximum forward output value (e.g., 1000)
     */
    template <class TDriver,
              signed short tMaxBackward = -1000,
              signed short tMinBackward = 0,
              signed short tMinForward = 0,
              signed short tMaxForward = 1000>
    class DirectionalMotor : public TDriver
    {
        static_assert(tMaxBackward >= -1000 && tMaxBackward <= 1000, "tMaxBackward out of range");
        static_assert(tMinBackward >= -1000 && tMinBackward <= 1000, "tMinBackward out of range");
        static_assert(tMinForward >= -1000 && tMinForward <= 1000, "tMinForward out of range");
        static_assert(tMaxForward >= -1000 && tMaxForward <= 1000, "tMaxForward out of range");

    private:
        DirectionalConfig mConfig;

        signed short compute(signed short aLevel) const
        {
            if (aLevel < 0)
                return map(constrain(aLevel, -1000, 0), -1000, 0, mConfig.maxBackward, mConfig.minBackward);
            if (aLevel > 0)
                return map(constrain(aLevel, 0, 1000), 0, 1000, mConfig.minForward, mConfig.maxForward);
            return 0;
        }

    public:
        DirectionalMotor() : mConfig(tMaxBackward, tMinBackward, tMinForward, tMaxForward)
        {
            Go(0);
        }

        template <typename... Args>
        DirectionalMotor(DirectionalConfig config, Args... args) : TDriver(args...), mConfig(config)
        {
            Go(0);
        }

        /**
         * @brief Configure all range parameters at once.
         *
         * @param aMaxBackward Maximum reverse output value (-1000..1000)
         * @param aMinBackward Minimum reverse output value (-1000..1000)
         * @param aMinForward Minimum forward output value (-1000..1000)
         * @param aMaxForward Maximum forward output value (-1000..1000)
         */
        void SetupRange(signed short maxBackward, signed short minBackward, signed short minForward, signed short maxForward)
        {
            SetMaxBackward(maxBackward);
            SetMinBackward(minBackward);
            SetMinForward(minForward);
            SetMaxForward(maxForward);
        }

        /**
         * @brief Set maximum reverse output value.
         * @param aValue Output value, clamped to -1000..1000.
         */
        void SetMaxBackward(signed short aValue)
        {
            mConfig.maxBackward = constrain(aValue, -1000, 1000);
        }

        /**
         * @brief Get maximum reverse output value.
         * @return Current maximum reverse output value.
         */
        signed short GetMaxBackward() const
        {
            return mConfig.maxBackward;
        }

        /**
         * @brief Set minimum reverse output value.
         * @param aValue Output value, clamped to -1000..1000.
         */
        void SetMinBackward(signed short aValue)
        {
            mConfig.minBackward = constrain(aValue, -1000, 1000);
        }

        /**
         * @brief Get minimum reverse output value.
         * @return Current minimum reverse output value.
         */
        signed short GetMinBackward() const
        {
            return mConfig.minBackward;
        }

        /**
         * @brief Set minimum forward output value.
         * @param aValue Output value, clamped to -1000..1000.
         */
        void SetMinForward(signed short aValue)
        {
            mConfig.minForward = constrain(aValue, -1000, 1000);
        }

        /**
         * @brief Get minimum forward output value.
         * @return Current minimum forward output value.
         */
        signed short GetMinForward() const
        {
            return mConfig.minForward;
        }

        /**
         * @brief Set maximum forward output value.
         * @param aValue Output value, clamped to -1000..1000.
         */
        void SetMaxForward(signed short aValue)
        {
            mConfig.maxForward = constrain(aValue, -1000, 1000);
        }

        /**
         * @brief Get maximum forward output value.
         * @return Current maximum forward output value.
         */
        signed short GetMaxForward() const
        {
            return mConfig.maxForward;
        }

        /**
         * @brief Apply the control value.
         * @param aLevel Input control value, range -1000..1000.
         */
        void Go(signed short aLevel)
        {
            TDriver::actBipolar(compute(aLevel));
        }
    };
}
