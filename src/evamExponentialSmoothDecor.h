#pragma once

#include <evafExponentialSmooth.h>
#include "evamValueReader.h"

namespace evam
{
    /**
     * @brief Configuration structure for ExponentialSmoothDecor
     */
    struct ExponentialSmoothConfig
    {
        unsigned short alpha;

        ExponentialSmoothConfig(unsigned short alpha) : alpha(alpha) {}
    };

    /**
     * @brief Decorator applying Exponential Moving Average (EMA) filtering to control signals.
     *
     * @tparam Motor Base motor class (must implement Go(signed short))
     * @tparam tAlpha Smoothing factor from 1 to 1000 (1000 = no filtering, 100 = heavy smoothing)
     */
    template <class TMotor, unsigned short tAlpha = 200>
    class ExponentialSmoothDecor : public TMotor, private evaf::ExponentialSmooth<ValueReader, tAlpha>
    {
    private:
        ExponentialSmoothConfig mConfig;
        using BaseFilter = evaf::ExponentialSmooth<ValueReader, tAlpha>;

    public:
        ExponentialSmoothDecor() : mConfig(tAlpha) {}

        template <typename... Args>
        ExponentialSmoothDecor(ExponentialSmoothConfig config, Args... args)
            : mConfig(config), TMotor(args...) {}

        /**
         * @brief Apply target value with exponential smoothing filtering.
         * @param value Target control value
         */
        void Go(signed short value)
        {
            this->setValue(value);
            signed short filtered = BaseFilter::getValue();
            TMotor::Go(filtered);
        }

        /**
         * @brief Resets the filter state to a new initial value.
         * @param initialValue Initial value to seed the filter
         */
        void Reset(signed short initialValue = 0)
        {
            BaseFilter::reset(initialValue);
        }

        void SetAlpha(unsigned short alpha)
        {
            mConfig.alpha = alpha;
            BaseFilter::setAlpha(alpha);
        }

        unsigned short GetAlpha() const
        {
            return BaseFilter::getAlpha();
        }
    };

}
