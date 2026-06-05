#pragma once

#include <Arduino.h>
#include <evaHeartbeat.h>

using namespace eva;

namespace evam
{
    /**
     * @brief Configuration structure for AdaptiveSmoothDecor
     */
    struct AdaptiveSmoothConfig {
        unsigned short minTimeConstantMs;
        unsigned short maxTimeConstantMs;
        
        AdaptiveSmoothConfig(unsigned short minTc, unsigned short maxTc)
            : minTimeConstantMs(minTc), maxTimeConstantMs(maxTc) {}
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
    template <class Motor,
              unsigned short kMinTimeConstantMs = 10,
              unsigned short kMaxTimeConstantMs = 150>
    class AdaptiveSmoothDecor : public Heartbeat, public Motor
    {
        static_assert(kMinTimeConstantMs >= 5 && kMinTimeConstantMs <= 200,
                      "kMinTimeConstantMs out of range 5..200");
        static_assert(kMaxTimeConstantMs >= kMinTimeConstantMs && kMaxTimeConstantMs <= 500,
                      "kMaxTimeConstantMs must be >= kMinTimeConstantMs and <= 500");

    private:
        static constexpr unsigned long kHeartbeatPeriodMs = 10;
        static constexpr signed short kDeadzone = 3;

        AdaptiveSmoothConfig mConfig;
        
        signed short mTargetValue = 0;
        signed short mCurrentValue = 0;
        signed short mLastTargetValue = 0;
        unsigned short mCurrentTimeConstantMs = kMaxTimeConstantMs;

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

            Motor::Go(mCurrentValue);
        }

    public:
        AdaptiveSmoothDecor() : mConfig(kMinTimeConstantMs, kMaxTimeConstantMs), Heartbeat(kHeartbeatPeriodMs) {}
        
        template<typename... Args>
        AdaptiveSmoothDecor(AdaptiveSmoothConfig config, Args... args) 
            : mConfig(config), Heartbeat(kHeartbeatPeriodMs), Motor(args...) {}

        void Go(signed short aValue)
        {
            mTargetValue = constrain(aValue, -1000, 1000);
        }
    };
}
