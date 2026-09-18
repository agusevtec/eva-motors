#pragma once

#include <evaHeartbeat.h>
#include "evaStdReaders.h"

namespace evam
{
    /**
     * @brief Decorator that owns the heartbeat and periodically drives TMotor.
     *
     * SampledDecor stores the target value and, on every heartbeat, forwards
     * it to TMotor::Go(). Any filter decorators wrapped inside transform the
     * value in their own Go() before it reaches the motor.
     *
     * Usage:
     *     SampledDecor<SimpleSmoothDecor<MyMotor, 5>> a;
     *
     * @tparam TMotor Wrapped class (must implement Go(signed short))
     */
    template <class TMotor>
    class SampledDecor
        : public virtual eva::Heartbeat,
          public TMotor
    {
    private:
        static constexpr unsigned long kHeartbeatPeriodMs = 10;

        signed short mValue;

    protected:
        void onHeartbeat() override
        {
            TMotor::Go(mValue);
        }

    public:
        SampledDecor() : Heartbeat(kHeartbeatPeriodMs), mValue(0) {}

        template <typename... Args>
        SampledDecor(Args... args)
            : Heartbeat(kHeartbeatPeriodMs),
              TMotor(args...),
              mValue(0) {}

        /**
         * @brief Set the target control value.
         * @param value Target control value, range -1000..1000
         */
        void Go(signed short value)
        {
            mValue = constrain(value, -1000, 1000);
        }
    };
}
