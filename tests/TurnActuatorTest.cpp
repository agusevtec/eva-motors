#include <AUnit.h>
#include <evamSteeringActuator.h>
#include "MockDriver.h"

using namespace aunit;
using namespace evam;

test(turn_range_normal)
{
    SteeringActuator<MockDriver, -100, 30, 500> rd;

    rd.Go(0);
    assertEqual(rd.resultValue, 30);
    rd.Go(1000);
    assertEqual(rd.resultValue, 500);
    rd.Go(-1000);
    assertEqual(rd.resultValue, -100);
}

test(turn_range_reversed)
{
    SteeringActuator<MockDriver, 100, -30, -500> rd;
    rd.Go(0);
    assertEqual(rd.resultValue, -30);
    rd.Go(1000);
    assertEqual(rd.resultValue, -500);
    rd.Go(-1000);
    assertEqual(rd.resultValue, 100);
}
