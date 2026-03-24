#include <AUnit.h>
#include <evamCenterDecor.h>
#include "MockMotor.h"

using namespace aunit;
using namespace evam;

test(turn_range_normal)
{
    CenterDecor<MockMotor, -100, 30, 500> rd;

    rd.actuate(0);
    assertEqual(rd.resultLevel, 30);
    rd.actuate(1000);
    assertEqual(rd.resultLevel, 500);
    rd.actuate(-1000);
    assertEqual(rd.resultLevel,  -100);
}

test(turn_range_reversed)
{
    CenterDecor<MockMotor, 100, -30, -500> rd;
    rd.actuate(0);
    assertEqual(rd.resultLevel, -30);
    rd.actuate(1000);
    assertEqual(rd.resultLevel, -500);
    rd.actuate(-1000);
    assertEqual(rd.resultLevel, 100);
}
