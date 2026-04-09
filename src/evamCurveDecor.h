#pragma once

#include <Arduino.h>

namespace evam
{
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
    template <class Motor, signed short kBend = 0>
    class CurveDecor : public Motor
    {
        static_assert(kBend >= -10 && kBend <= 10, "kBend out of range -10..10");
    private:
        signed short mBend = kBend;

        signed long f(signed long x) const
        {
            return mBend * (x - x * x / 1000) / 10;
        }

        unsigned short curve(unsigned short x) const
        {
            signed long fx_x = f(x) + x;
            return f(fx_x) + fx_x;
        }

    public:
        /**
         * @brief Set the bend intensity at runtime.
         * @param aValue Bend value, clamped to -10..10.
         */
        void SetBend(signed short aValue)
        {
            mBend = constrain(aValue, -10, 10);
        }

        /**
         * @brief Get the current bend intensity value.
         * @return Current bend value in range -10..10.
         */
        signed short GetBend() const
        {
            return mBend;
        }

        /**
         * @brief Apply the curved transformation and pass to the underlying motor.
         * @param aValue Input control value, range -1000..1000.
         */
        void Go(signed short aValue)
        {
            aValue = constrain(aValue, -1000, 1000);
            if (aValue >= 0)
                Motor::Go(curve(aValue));
            else
                Motor::Go(-curve(-aValue));
        }
    };

}

