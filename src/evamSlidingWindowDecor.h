#pragma once

namespace evam
{
    template <class TMotor, unsigned short N>
    struct SlidingWindowDecor
    {
        static_assert(N < 0, "SlidingWindowDecor is deprecated and was renamed to SimpleSmoothDecor!");
    };
}
