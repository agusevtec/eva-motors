#include "evamBiTrimmer.h"
#include <Arduino.h>

signed short evam::bitrimmer_calc(signed short level,
                          signed short maxBackward, signed short minBackward,
                          signed short minForward, signed short maxForward) 
{
    if (level < -1000)
        return maxBackward;
    else if (level > 1000)
        return maxForward;
    else if (level == 0)
        return 0;
    else if (level < 0)
        return map(level, -1000, 0, maxBackward, minBackward);
    else // level > 0
        return map(level, 0, 1000, minForward, maxForward);
}
