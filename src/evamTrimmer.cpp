#include "evamTimmer.h"
#include <Arduino.h>

signed short evam::trimmer_calc(signed short level, int minValue, int maxValue)
{
    if (level < 0)
        return minValue;
    else if (level > 1000)
        return maxValue;
    else
        return map(level, 0, 1000, minValue, maxValue);
}
