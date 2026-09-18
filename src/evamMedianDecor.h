#pragma once

#include <evafMedian.h>
#include "evaStdReaders.h"

namespace evam
{
    /**
     * @brief Decorator applying median filtering.
     *
     * Median has no runtime parameters besides the template window size.
     * This decorator does not own a heartbeat; it only transforms the value.
     * Wrap it with SampledDecor to get periodic output:
     *
     *     SampledDecor<MedianDecor<MyMotor, 5>> a;
     *
     * @tparam TMotor Base motor class (must implement Go(signed short))
     * @tparam tWindowSize Filter window size (odd number). Default: 5
     */
    template <class TMotor, unsigned short tWindowSize = evaf::kDefaultWindowSize>
    class MedianDecor
        : public TMotor
    {
    private:
        using Filter = evaf::Median<eva::ValueReader, tWindowSize>;

        Filter mFilter;

    public:
        MedianDecor() : TMotor() {}

        template <typename... Args>
        MedianDecor(Args... args)
            : TMotor(args...) {}

        /**
         * @brief Set the target control value.
         * @param value Target control value, range -1000..1000
         */
        void Go(signed short value)
        {
            mFilter.setValue(constrain(value, -1000, 1000));
            TMotor::Go(mFilter.getValue());
        }
    };
}
