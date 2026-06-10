#pragma once
#include <Arduino.h>

namespace evam
{
    /**
     * @brief Configuration structure for DirectionalMotor
     */
    struct DirectionalConfig {
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
     * @tparam Driver Driver class (must implement actBipolar(signed short))
     * @tparam kMaxBackward Maximum reverse output value (e.g., -1000)
     * @tparam kMinBackward Minimum reverse output value (e.g., -50)
     * @tparam kMinForward Minimum forward output value (e.g., 50)
     * @tparam kMaxForward Maximum forward output value (e.g., 1000)
     */
    template <class Driver, 
              signed short kMaxBackward = -1000, 
              signed short kMinBackward = 0, 
              signed short kMinForward = 0, 
              signed short kMaxForward = 1000>
    class DirectionalMotor : public Driver
    {
        static_assert(kMaxBackward >= -1000 && kMaxBackward <= 1000, "kMaxBackward out of range");
        static_assert(kMinBackward >= -1000 && kMinBackward <= 1000, "kMinBackward out of range");
        static_assert(kMinForward >= -1000 && kMinForward <= 1000, "kMinForward out of range");
        static_assert(kMaxForward >= -1000 && kMaxForward <= 1000, "kMaxForward out of range");

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
        DirectionalMotor() : mConfig(kMaxBackward, kMinBackward, kMinForward, kMaxForward) {}
        
        template<typename... Args>
        DirectionalMotor(DirectionalConfig config, Args... args) : Driver(args...), mConfig(config) {}

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
            Driver::actBipolar(compute(aLevel));
        }
    };
}
