#include <AUnit.h>
#include <evamForwardMotor.h>
#include "MockDriver.h"

using namespace aunit;
using namespace evam;

test(forw_range_normal)
{
    ForwardMotor<MockDriver, 30, 500> rd;

    rd.Go(0);
    assertEqual(rd.resultValue,  0);
    rd.Go(1);
    assertMoreOrEqual(rd.resultValue,  30);
    rd.Go(1000);
    assertEqual(rd.resultValue, 500);
}

test(forw_range_reversed)
{
    ForwardMotor<MockDriver, 100, -30> rd;
    rd.Go(0);
    assertEqual(rd.resultValue, 0);
    rd.Go(1000);
    assertEqual(rd.resultValue, -30);
}
