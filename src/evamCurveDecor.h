#pragma once

#include <Arduino.h>

namespace evam
{
    constexpr signed short kDefaultBend = 0;
    constexpr signed short kMinBend = -10;
    constexpr signed short kMaxBend = 10;

    /**
     * @brief Configuration structure for CurveDecor
     */
    struct CurveConfig {
        signed short bend;
        
        CurveConfig(signed short bend) : bend(constrain(bend, kMinBend, kMaxBend)) {}
    };

    /**
     * @brief Decorator that applies an S-curve (nonlinear) transformation to the control signal.
     *
     * Converts linear input into an S-shaped curve, useful for smoother starts and
     * finer control in the mid-range. Positive bend values create a softer start,
     * negative values create a sharper initial response.
     *
     * @tparam Motor Base motor class (must implement Go(signed short))
     * @tparam kBend Bend intensity. Range: -10..10. 0 = linear.
     */
    template <class TMotor, signed short tBend = kDefaultBend>
    class CurveDecor : public TMotor
    {
        static_assert(tBend >= kMinBend && tBend <= kMaxBend, "tBend out of range");
        
    private:
        CurveConfig mConfig;
        
        signed long f(signed long x) const
        {
            return mConfig.bend * (x - x * x / 1000) / 10;
        }

        unsigned short curve(unsigned short x) const
        {
            signed long fx_x = f(x) + x;
            return f(fx_x) + fx_x;
        }

    public:
        CurveDecor() : mConfig(tBend) {}
        
        template<typename... Args>
        CurveDecor(CurveConfig config, Args... args) : TMotor(args...), mConfig(config) {}

        /**
         * @brief Set the bend intensity at runtime.
         * @param aValue Bend value, clamped to -10..10.
         */
        void SetBend(signed short aValue)
        {
            mConfig.bend = constrain(aValue, -10, 10);
        }

        /**
         * @brief Get the current bend intensity value.
         * @return Current bend value in range -10..10.
         */
        signed short GetBend() const
        {
            return mConfig.bend;
        }

        /**
         * @brief Apply the curved transformation and pass to the underlying motor.
         * @param aValue Input control value, range -1000..1000.
         */
        void Go(signed short aValue)
        {
            aValue = constrain(aValue, -1000, 1000);
            if (aValue >= 0)
                TMotor::Go(curve(aValue));
            else
                TMotor::Go(-curve(-aValue));
        }
    };
}
