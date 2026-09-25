#pragma once

#include <evafExponentialAverage.h>
#include "evaStdReaders.h"

namespace evam
{
    /**
     * @brief Configuration structure for ExponentialSmoothDecor.
     *
     * Runtime parameter for evaf::ExponentialSmooth.
     */
    struct ExponentialSmoothConfig
    {
        unsigned short alpha;

        ExponentialSmoothConfig(unsigned short alpha) : alpha(alpha) {}
    };

    /**
     * @brief Decorator applying Exponential Moving Average (EMA) filtering.
     *
     * This decorator does not own a heartbeat; it only transforms the value.
     * Wrap it with SampledDecor to get periodic output:
     *
     *     SampledDecor<ExponentialSmoothDecor<MyMotor, 200>> a;
     *
     * @tparam TMotor Base motor class (must implement Go(signed short))
     * @tparam tAlpha Default smoothing factor (1..1000). Default: 200
     */
    template <class TMotor, unsigned short tAlpha = 200>
    class ExponentialSmoothDecor
        : public TMotor
    {
    private:
        using Filter = evaf::ExponentialAverage<eva::ValueReader, tAlpha>;

        Filter mFilter;

    public:
        ExponentialSmoothDecor() : TMotor() {}

        template <typename... Args>
        ExponentialSmoothDecor(ExponentialSmoothConfig config, Args... args)
            : TMotor(args...),
              mFilter(config.alpha) {}

        /**
         * @brief Set the target control value.
         * @param value Target control value, range -1000..1000
         */
        void Go(signed short value)
        {
            mFilter.setValue(constrain(value, -1000, 1000));
            TMotor::Go(mFilter.getValue());
        }

        void SetAlpha(unsigned short alpha)
        {
            mFilter.setAlpha(alpha);
        }

        unsigned short GetAlpha() const
        {
            return mFilter.getAlpha();
        }
    };
}
