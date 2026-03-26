#ifndef EVAM_SMOOTH_DECOR_H_
#define EVAM_SMOOTH_DECOR_H_

#pragma once

#include <Arduino.h>

namespace evam
{
    /**
     * @brief Decorator that smooths control signals to eliminate jitter.
     *
     * Applies exponential smoothing (low-pass filter) to the control signal,
     * effectively removing high-frequency noise and jitter from joysticks
     * or other noisy inputs while maintaining responsive control.
     *
     * The smoothing factor determines the trade-off between smoothness and
     * response time. Lower values = smoother but more lag, higher values =
     * more responsive but less filtering.
     *
     * @tparam Motor Base motor class (must implement Go(signed short))
     * @tparam kSmoothingFactor Smoothing factor (1..100). Default: 30.
     *         Higher = more responsive, lower = smoother.
     */
    template <class Motor, unsigned short kSmoothingFactor = 30>
    class SmoothDecor : public Motor
    {
        static_assert(kSmoothingFactor >= 1 && kSmoothingFactor <= 100, 
                      "kSmoothingFactor out of range 1..100");

    private:
        signed short mSmoothValue = 0;
        unsigned short mSmoothingFactor = kSmoothingFactor;
        
        // Deadzone to prevent micro-jitter at rest
        static constexpr signed short kDeadzone = 5;

        /**
         * @brief Apply exponential smoothing to the input value.
         * @param aValue Raw input value (-1000..1000)
         * @return Smoothed output value
         */
        signed short smooth(signed short aValue)
        {
            // Apply deadzone when near zero to eliminate jitter at center
            if (abs(aValue) <= kDeadzone && abs(mSmoothValue) <= kDeadzone)
            {
                mSmoothValue = 0;
                return 0;
            }
            
            // Exponential smoothing (IIR low-pass filter)
            // output = output + (input - output) * factor / 100
            long diff = aValue - mSmoothValue;
            long step = (diff * mSmoothingFactor) / 100;
            mSmoothValue += step;
            
            return mSmoothValue;
        }

    public:
        /**
         * @brief Set the smoothing factor at runtime.
         * @param aValue Smoothing factor (1..100). Higher = more responsive,
         *               lower = smoother but more lag.
         */
        void SetSmoothingFactor(unsigned short aValue)
        {
            mSmoothingFactor = constrain(aValue, 1, 100);
        }

        /**
         * @brief Get the current smoothing factor.
         * @return Current smoothing factor (1..100)
         */
        unsigned short GetSmoothingFactor() const
        {
            return mSmoothingFactor;
        }

        /**
         * @brief Reset the smoothed value (useful after calibration).
         */
        void ResetSmoothing()
        {
            mSmoothValue = 0;
        }

        /**
         * @brief Apply smoothing and pass to underlying motor.
         * @param aValue Raw input value, range -1000..1000.
         */
        void Go(signed short aValue)
        {
            aValue = constrain(aValue, -1000, 1000);
            Motor::Go(smooth(aValue));
        }
    };

} // namespace evam

#endif // EVAM_SMOOTH_DECOR_H_
