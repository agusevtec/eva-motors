#include <AUnit.h>
#include <evamLinearMotor.h>
#include "MockDriver.h"

using namespace aunit;
using namespace evam;

test(linear_range_normal)
{
    LinearMotor<MockDriver, 30, 500> rd;

    rd.actuate(0);
    assertEqual(rd.resultSSS, 1000 + 30);
    rd.actuate(1);
    assertMoreOrEqual(rd.resultSSS, 1000 + 30);
    rd.actuate(1000);
    assertEqual(rd.resultSSS, 1000 + 500);
}

// test(forw_range_reversed)
// {
//     ForwardMotor<MockDriver, 100, -30> rd;
//     rd.actuate(0);
//     assertEqual(rd.resultSSS, 1000 );
//     rd.actuate(1000);
//     assertEqual(rd.resultSSS, 1000 - 30);
// }
