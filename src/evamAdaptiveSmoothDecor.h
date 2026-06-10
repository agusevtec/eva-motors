#pragma once

#include <Arduino.h>
#include <evaHeartbeat.h>

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
    struct AdaptiveSmoothConfig {
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
    class AdaptiveSmoothDecor : public Heartbeat, public TMotor
    {
        static_assert(tMinTimeConstantMs >= kMinTimeConstantLimit && tMinTimeConstantMs <= kMaxTimeConstantLimit,
                      "tMinTimeConstantMs out of range");
        static_assert(tMaxTimeConstantMs >= tMinTimeConstantMs && tMaxTimeConstantMs <= kMaxTimeConstantLimit,
                      "tMaxTimeConstantMs must be >= tMinTimeConstantMs");

    private:
        static constexpr unsigned long kHeartbeatPeriodMs = 10;
        static constexpr signed short kDeadzone = 3;

        AdaptiveSmoothConfig mConfig;
        
        signed short mTargetValue = 0;
        signed short mCurrentValue = 0;
        signed short mLastTargetValue = 0;
        unsigned short mCurrentTimeConstantMs = tMaxTimeConstantMs;

        unsigned short calculateTimeConstant()
        {
            signed short change = abs(mTargetValue - mLastTargetValue);

            if (change >= 200)
                return mConfig.minTimeConstantMs;
            else if (change <= 5)
                return mConfig.maxTimeConstantMs;
            else
            {
                return mConfig.maxTimeConstantMs - ((change - 5) * (mConfig.maxTimeConstantMs - mConfig.minTimeConstantMs) / 195);
            }
        }

    protected:
        void onHeartbeat() override
        {
            mCurrentTimeConstantMs = calculateTimeConstant();
            mLastTargetValue = mTargetValue;

            if (abs(mTargetValue) <= kDeadzone && abs(mCurrentValue) <= kDeadzone)
            {
                if (mCurrentValue != 0)
                    mCurrentValue = 0;
            }
            else
            {
                signed long step = (signed long)(mTargetValue - mCurrentValue) * kHeartbeatPeriodMs * 1000 / mCurrentTimeConstantMs;
                mCurrentValue += step / 1000;
                mCurrentValue = constrain(mCurrentValue, -1000, 1000);
            }

            TMotor::Go(mCurrentValue);
        }

    public:
        AdaptiveSmoothDecor() : mConfig(tMinTimeConstantMs, tMaxTimeConstantMs), Heartbeat(kHeartbeatPeriodMs) {}
        
        template<typename... Args>
        AdaptiveSmoothDecor(AdaptiveSmoothConfig config, Args... args) 
            : mConfig(config), Heartbeat(kHeartbeatPeriodMs), TMotor(args...) {}

        void Go(signed short aValue)
        {
            mTargetValue = constrain(aValue, -1000, 1000);
        }

        void SetMinTimeConstantMs(unsigned short value)
        {
            mConfig.minTimeConstantMs = constrain(value, kMinTimeConstantLimit, kMaxTimeConstantLimit);
        }

        unsigned short GetMinTimeConstantMs() const
        {
            return mConfig.minTimeConstantMs;
        }

        void SetMaxTimeConstantMs(unsigned short value)
        {
            mConfig.maxTimeConstantMs = constrain(value, mConfig.minTimeConstantMs, kMaxTimeConstantLimit);
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
