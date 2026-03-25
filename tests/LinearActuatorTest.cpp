#include <AUnit.h>
#include <evamLinearActuator.h>
#include "MockDriver.h"

using namespace aunit;
using namespace evam;

test(linear_range_normal)
{
    LinearActuator<MockDriver, 30, 500> rd;

    rd.Go(0);
    assertEqual(rd.resultValue, 30);
    rd.Go(1);
    assertMoreOrEqual(rd.resultValue, 30);
    rd.Go(1000);
    assertEqual(rd.resultValue, 500);
}

// test(forw_range_reversed)
// {
//     ForwardMotor<MockDriver, 100, -30> rd;
//     rd.Go(0);
//     assertEqual(rd.resultValue, 1000 );
//     rd.Go(1000);
//     assertEqual(rd.resultValue, 1000 - 30);
// }
