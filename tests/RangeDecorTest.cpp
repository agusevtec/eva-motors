#include <AUnit.h>
#include <evamRangeDecor.h>
#include "MockMotor.h"

using namespace aunit;
using namespace evam;


test(range_normal)
{
    RangeDecor<MockMotor,-100, -30, 30, 500> rd;
    rd.set(0);
    assertEqual(rd.resultLevel, 0);
    rd.set(-501);
    assertEqual(rd.resultLevel, -100);
    rd.set(501);
    assertEqual(rd.resultLevel, 500);
    rd.set(-500);
    assertEqual(rd.resultLevel, -100);
    rd.set(500);
    assertEqual(rd.resultLevel, 500);


}

test(range_reversed)
{
    RangeDecor<MockMotor,100, 30, -30, -500> rd;
    rd.set(0);
    assertEqual(rd.resultLevel, 0);
    rd.set(501);
    assertEqual(rd.resultLevel, -500);
    rd.set(-501);
    assertEqual(rd.resultLevel, 100);
    rd.set(500);
    assertEqual(rd.resultLevel, -500);
    rd.set(-500);
    assertEqual(rd.resultLevel, 100);
}