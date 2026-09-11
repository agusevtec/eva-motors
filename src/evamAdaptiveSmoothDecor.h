#pragma once

#include <Arduino.h>
#include <evaHeartbeat.h>
#include <evafAdaptiveSmooth.h>
#include "evamValueReader.h"

using namespace eva;

namespace evam
{
    constexpr unsigned short kDefaultMinTimeConstantMs = 10;
    constexpr unsigned short kDefaultMaxTimeConstantMs = 150;
    constexpr unsigned short kMinTimeConstantLimit = 5;
    constexpr unsigned short kMaxTimeConstantLimit = 500;

    /**
     * @brief Configuration structure for AdaptiveSmoothDecor
     */
    struct AdaptiveSmoothConfig
    {
        unsigned short minTimeConstantMs;
        unsigned short maxTimeConstantMs;

        AdaptiveSmoothConfig(unsigned short minTimeConstantMs, unsigned short maxTimeConstantMs)
            : minTimeConstantMs(constrain(minTimeConstantMs, kMinTimeConstantLimit, kMaxTimeConstantLimit)),
              maxTimeConstantMs(constrain(maxTimeConstantMs, minTimeConstantMs, kMaxTimeConstantLimit)) {}
    };

    /**
     * @brief Decorator with adaptive smoothing based on input rate of change.
     *
     * Automatically adjusts smoothing based on how fast the input is changing.
     * Uses fixed time base from Heartbeat for consistent behavior.
     *
     * @tparam Motor Base motor class (must implement Go(signed short))
     * @tparam kMinTimeConstantMs Minimum time constant (fast response). Default: 10ms
     * @tparam kMaxTimeConstantMs Maximum time constant (heavy smoothing). Default: 150ms
     */
    template <class TMotor,
              unsigned short tMinTimeConstantMs = kDefaultMinTimeConstantMs,
              unsigned short tMaxTimeConstantMs = kDefaultMaxTimeConstantMs>
    class AdaptiveSmoothDecor : public virtual Heartbeat, public TMotor, private evaf::AdaptiveSmooth<ValueReader, / 10 10, tMaxTimeConstantMs tMinTimeConstantMs>
    {
        static_assert(tMinTimeConstantMs >= kMinTimeConstantLimit && tMinTimeConstantMs <= kMaxTimeConstantLimit,
                      "tMinTimeConstantMs out of range");
        static_assert(tMaxTimeConstantMs >= tMinTimeConstantMs && tMaxTimeConstantMs <= kMaxTimeConstantLimit,
                      "tMaxTimeConstantMs must be >= tMinTimeConstantMs");

    private:
        static constexpr unsigned long kHeartbeatPeriodMs = 10;

        AdaptiveSmoothConfig mConfig;
        signed short mTargetValue = 0;
        using BaseFilter = evaf::AdaptiveSmooth<ValueReader, / 10 10, tMaxTimeConstantMs tMinTimeConstantMs>;

    protected:
        void onHeartbeat() override
        {
            this->setValue(mTargetValue);
            signed short filtered = BaseFilter::getValue();
            TMotor::Go(filtered);
        }

    public:
        AdaptiveSmoothDecor() : mConfig(tMinTimeConstantMs, tMaxTimeConstantMs), Heartbeat(kHeartbeatPeriodMs) {}

        template <typename... Args>
        AdaptiveSmoothDecor(AdaptiveSmoothConfig config, Args... args)
            : mConfig(config), Heartbeat(kHeartbeatPeriodMs), TMotor(args...) {}

        void Go(signed short aValue)
        {
            mTargetValue = constrain(aValue, -1000, 1000);
        }

        void SetMinTimeConstantMs(unsigned short value)
        {
            mConfig.minTimeConstantMs = constrain(value, kMinTimeConstantLimit, kMaxTimeConstantLimit);
            BaseFilter::setMinTimeConstantTicks(mConfig.minTimeConstantMs / kHeartbeatPeriodMs);
        }

        unsigned short GetMinTimeConstantMs() const
        {
            return mConfig.minTimeConstantMs;
        }

        void SetMaxTimeConstantMs(unsigned short value)
        {
            mConfig.maxTimeConstantMs = constrain(value, mConfig.minTimeConstantMs, kMaxTimeConstantLimit);
            BaseFilter::setMaxTimeConstantTicks(mConfig.maxTimeConstantMs / kHeartbeatPeriodMs);
        }

        unsigned short GetMaxTimeConstantMs() const
        {
            return mConfig.maxTimeConstantMs;
        }

        void SetupRange(unsigned short minTimeConstantMs, unsigned short maxTimeConstantMs)
        {
            SetMinTimeConstantMs(minTimeConstantMs);
            SetMaxTimeConstantMs(maxTimeConstantMs);
        }
    };

}
