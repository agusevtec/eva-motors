#pragma once

#include <Arduino.h>
#include <evaHeartbeat.h>
#include <evafMedian.h>
#include "evamValueReader.h"

using namespace eva;

namespace evam
{
    constexpr unsigned short kDefaultWindowSize = 5;
    constexpr unsigned short kMinWindowSize = 3;
    constexpr unsigned short kMaxWindowSize = 15;

    /**
     * @brief Decorator that applies median filtering with fixed time base.
     *
     * Samples the input at regular intervals and applies median filtering
     * to remove spikes and noise. Output updates at the sampling rate.
     *
     * @tparam Motor Base motor class (must implement Go(signed short))
     * @tparam kWindowSize Filter window size (odd number). Default: 5
     */
    template <class TMotor, unsigned short tWindowSize = kDefaultWindowSize>
    class MedianDecor : public virtual Heartbeat, public TMotor, private evaf::Median<ValueReader, tWindowSize>
    {
        static_assert(tWindowSize >= kMinWindowSize && tWindowSize <= kMaxWindowSize,
                      "tWindowSize out of range");
        static_assert(tWindowSize % 2 == 1,
                      "tWindowSize must be odd");

    private:
        static constexpr unsigned long kHeartbeatPeriodMs = 10;

        signed short mLastSample = 0;
        using BaseFilter = evaf::Median<ValueReader, tWindowSize>;

    protected:
        void onHeartbeat() override
        {
            this->setValue(mLastSample);
            signed short filtered = BaseFilter::getValue();
            TMotor::Go(filtered);
        }

    public:
        MedianDecor() :  Heartbeat(kHeartbeatPeriodMs) {}

        template <typename... Args>
        MedianDecor(Args... args)
            : TMotor(args...) {}

        /**
         * @brief Reset the filter buffer.
         */
        void Reset()
        {
            BaseFilter::reset();
        }

        void Go(signed short aValue)
        {
            mLastSample = constrain(aValue, -1000, 1000);
        }
    };

}
