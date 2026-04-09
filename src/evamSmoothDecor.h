#pragma once

#include <Arduino.h>
#include <evaHeartbeat.h>

using namespace eva;

namespace evam
{
    /**
     * @brief Decorator that smooths control signals to eliminate jitter.
     *
     * Applies exponential smoothing (low-pass filter) to the control signal
     * using a fixed time base from Heartbeat. This ensures consistent smoothing
     * regardless of how often Go() is called.
     *
     * @tparam Motor Base motor class (must implement Go(signed short))
     * @tparam kTimeConstantMs Time constant in milliseconds. Default: 50ms.
     */
    template <class Motor, unsigned short kTimeConstantMs = 50>
    class SmoothDecor : public Heartbeat, public Motor
    {
        static_assert(kTimeConstantMs >= 5 && kTimeConstantMs <= 500, 
                      "kTimeConstantMs out of range 5..500");

    private:
        static constexpr unsigned long kHeartbeatPeriodMs = 10;
        
        signed short mTargetValue = 0;
        signed short mCurrentValue = 0;
        unsigned short mTimeConstantMs = kTimeConstantMs;
        static constexpr signed short kDeadzone = 5;

    protected:
        void onHeartbeat() override
        {
            // Calculate step based on time constant
            float step = (float)(mTargetValue - mCurrentValue) * kHeartbeatPeriodMs / mTimeConstantMs;
            
            // Apply step with deadzone to prevent micro-jitter
            if (abs(step) < 1.0f && abs(mCurrentValue) <= kDeadzone)
            {
                if (mCurrentValue != 0)
                    mCurrentValue = 0;
            }
            else
            {
                mCurrentValue += (signed short)step;
            }
            
            // Clamp to valid range
            mCurrentValue = constrain(mCurrentValue, -1000, 1000);
            
            // Output to motor
            Motor::Go(mCurrentValue);
        }

    public:
        /**
         * @brief Constructor.
         */
        SmoothDecor() : Heartbeat(kHeartbeatPeriodMs)
        {
        }

        /**
         * @brief Set the time constant at runtime.
         * @param aValue Time constant in milliseconds (5..500).
         *               Higher = smoother but more lag.
         */
        void SetTimeConstant(unsigned short aValue)
        {
            mTimeConstantMs = constrain(aValue, 5, 500);
        }

        /**
         * @brief Get the current time constant.
         * @return Current time constant in milliseconds.
         */
        unsigned short GetTimeConstant() const
        {
            return mTimeConstantMs;
        }

        /**
         * @brief Reset the smoothed value.
         */
        void Reset()
        {
            mCurrentValue = 0;
            mTargetValue = 0;
        }

        /**
         * @brief Set target value (called from main loop).
         * @param aValue Raw input value, range -1000..1000.
         */
        void Go(signed short aValue)
        {
            mTargetValue = constrain(aValue, -1000, 1000);
        }
    };

} // namespace evam

