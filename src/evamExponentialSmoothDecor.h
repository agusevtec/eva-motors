#pragma once

#include <evaHeartbeat.h>
#include <evafExponentialSmooth.h>
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
     * @tparam TMotor Base motor class (must implement Go(signed short))
     * @tparam tAlpha Default smoothing factor (1..1000). Default: 200
     */
    template <class TMotor, unsigned short tAlpha = 200>
    class ExponentialSmoothDecor
        : public virtual eva::Heartbeat,
          public TMotor
    {
    private:
        static constexpr unsigned long kHeartbeatPeriodMs = 10;

        using Filter = evaf::ExponentialSmooth<eva::ValueReader, tAlpha>;

        Filter mFilter;

    protected:
        void onHeartbeat() override
        {
            TMotor::Go(mFilter.getValue());
        }

    public:
        ExponentialSmoothDecor() : Heartbeat(kHeartbeatPeriodMs) {}

        template <typename... Args>
        ExponentialSmoothDecor(ExponentialSmoothConfig config, Args... args)
            : Heartbeat(kHeartbeatPeriodMs),
              TMotor(args...),
              mFilter(config.alpha) {}

        /**
         * @brief Set the target control value.
         * @param value Target control value, range -1000..1000
         */
        void Go(signed short value)
        {
            mFilter.setValue(constrain(value, -1000, 1000));
        }

        void setAlpha(unsigned short alpha)
        {
            mFilter.setAlpha(alpha);
        }

        unsigned short getAlpha() const
        {
            return mFilter.getAlpha();
        }
    };
}
