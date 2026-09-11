#pragma once

#include <evafMinmax.h>
#include "evamValueReader.h"

namespace evam
{

    /**
     * @brief Decorator that applies a min-max (morphological) filter to the control signal.
     *
     * The filter effectively removes both positive and negative impulse noise while
     * preserving edges better than a simple moving average. The output is the average
     * of the morphological opening and closing operations, providing symmetric behavior.
     *
     * This filter divides the ring buffer into N chunks of N elements each, then computes:
     * - minimax = min of chunk maximums (closing operation)
     * - maximin = max of chunk minimums (opening operation)
     * - output = (minimax + maximin) / 2
     *
     * @tparam Motor Base motor class (must implement Go(signed short))
     * @tparam N Number of chunks and chunk size (total buffer size = N * N)
     *
     * @note The filter only produces filtered output after the buffer is full.
     *       Before that, values pass through unchanged.
     */
    template <class TMotor, unsigned char N>
    class MinmaxDecor : public TMotor, private evaf::Minmax<ValueReader, N>
    {
        static_assert(N >= 2 && N <= 5, "N out of range 2..5");

    private:
        using BaseFilter = evaf::Minmax<ValueReader, N>;

    public:
        MinmaxDecor() : mConfig(N) {}

        template <typename... Args>
        MinmaxDecor(MinmaxConfig config, Args... args)
            : TMotor(args...) {}

        /**
         * @brief Apply the control value with min-max filtering.
         *
         * Passes values through unchanged until the ring buffer is full.
         * Once full, each new value triggers:
         * - Buffer update (overwrites oldest value)
         * - Recalculation of chunk maximums and minimums
         * - Output = (minimax + maximin) / 2
         *
         * @param value Input control value, range -1000..1000
         */
        void Go(signed short value)
        {
            this->setValue(value);
            signed short filtered = BaseFilter::getValue();
            TMotor::Go(filtered);
        }
    };

}
