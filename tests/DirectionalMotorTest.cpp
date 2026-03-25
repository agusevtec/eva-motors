#include <AUnit.h>
#include <evamDirectionalMotor.h>
#include "MockDriver.h"

using namespace aunit;
using namespace evam;

test(dire_range_normal)
{
    DirectionalMotor<MockDriver, -100, -30, 30, 500> rd;
    rd.Go(0);
    assertEqual(rd.resultValue, 0);
    rd.Go(1);
    assertMoreOrEqual(rd.resultValue, 30);
    rd.Go(-1001);
    assertEqual(rd.resultValue, -100);
    rd.Go(1001);
    assertEqual(rd.resultValue, 500);
    rd.Go(-1000);
    assertEqual(rd.resultValue, -100);
    rd.Go(1000);
    assertEqual(rd.resultValue, 500);
}

test(dire_range_reversed)
{
    DirectionalMotor<MockDriver, 100, 30, -30, -500> rd;
    rd.Go(0);
    assertEqual(rd.resultValue, 0);
    rd.Go(1001);
    assertEqual(rd.resultValue, -500);
    rd.Go(-1001);
    assertEqual(rd.resultValue, 100);
    rd.Go(1000);
    assertEqual(rd.resultValue, -500);
    rd.Go(-1000);
    assertEqual(rd.resultValue, 100);
}

test(dire_range_mutable)
{
    DirectionalMotor<MockDriver, -100, -30, 30, 500> rd;
    rd.Go(1);
    assertMoreOrEqual(rd.resultValue, 30);
    rd.SetMinForward(0);
    rd.Go(2);
    assertEqual(rd.resultValue, 1);
}