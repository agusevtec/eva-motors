#ifndef EVAM_ADAPTIVE_SMOOTH_DECOR_H_
#define EVAM_ADAPTIVE_SMOOTH_DECOR_H_

#pragma once

#include <Arduino.h>

namespace evam
{
    /**
     * @brief Decorator with adaptive smoothing based on input rate of change.
     *
     * Automatically adjusts smoothing based on how fast the input is changing.
     * When the signal is stable, heavy smoothing removes jitter. When the
     * signal changes rapidly, smoothing decreases for immediate response.
     * Best of both worlds: smooth at rest, responsive during movement.
     *
     * @tparam Motor Base motor class (must implement Go(signed short))
     * @tparam kMaxSmoothing Maximum smoothing factor (1..100). Default: 80
     * @tparam kMinSmoothing Minimum smoothing factor (1..100). Default: 20
     */
    template <class Motor, unsigned short kMaxSmoothing = 80, unsigned short kMinSmoothing = 20>
    class AdaptiveSmoothDecor : public Motor
    {
        static_assert(kMaxSmoothing >= 1 && kMaxSmoothing <= 100, 
                      "kMaxSmoothing out of range 1..100");
        static_assert(kMinSmoothing >= 1 && kMinSmoothing <= 100, 
                      "kMinSmoothing out of range 1..100");
        static_assert(kMinSmoothing <= kMaxSmoothing, 
                      "kMinSmoothing must be <= kMaxSmoothing");

    private:
        signed short mSmoothValue = 0;
        signed short mLastRawValue = 0;
        static constexpr signed short kDeadzone = 3;

        /**
         * @brief Calculate adaptive smoothing factor based on input change.
         * @param aValue Current raw input
         * @return Smoothing factor (higher = more smoothing)
         */
        unsigned short calculateSmoothingFactor(signed short aValue)
        {
            signed short change = abs(aValue - mLastRawValue);
            
            // Map change (0..2000) to smoothing factor (kMaxSmoothing..kMinSmoothing)
            // Large change = small smoothing (responsive)
            // Small change = large smoothing (stable)
            unsigned short factor;
            
            if (change <= 10)
                factor = kMaxSmoothing;
            else if (change >= 200)
                factor = kMinSmoothing;
            else
                factor = kMaxSmoothing - ((change - 10) * (kMaxSmoothing - kMinSmoothing) / 190);
            
            return factor;
        }

        /**
         * @brief Apply adaptive exponential smoothing.
         * @param aValue Raw input value
         * @return Smoothed output
         */
        signed short smooth(signed short aValue)
        {
            // Deadzone at center
            if (abs(aValue) <= kDeadzone && abs(mSmoothValue) <= kDeadzone)
            {
                mLastRawValue = aValue;
                mSmoothValue = 0;
                return 0;
            }
            
            unsigned short factor = calculateSmoothingFactor(aValue);
            
            // Exponential smoothing with adaptive factor
            long diff = aValue - mSmoothValue;
            long step = (diff * factor) / 100;
            mSmoothValue += step;
            
            mLastRawValue = aValue;
            return mSmoothValue;
        }

    public:
        /**
         * @brief Apply adaptive smoothing and pass to underlying motor.
         * @param aValue Raw input value, range -1000..1000.
         */
        void Go(signed short aValue)
        {
            aValue = constrain(aValue, -1000, 1000);
            Motor::Go(smooth(aValue));
        }

        /**
         * @brief Reset the smoothing state.
         */
        void Reset()
        {
            mSmoothValue = 0;
            mLastRawValue = 0;
        }
    };

} // namespace evam

#endif // EVAM_ADAPTIVE_SMOOTH_DECOR_H_
