#include <AUnit.h>
#include <evamDirectionalMotor.h>
#include "MockDriver.h"

using namespace aunit;
using namespace evam;

test(dire_range_normal)
{
    DirectionalMotor<MockDriver, -100, -30, 30, 500> rd;
    rd.actuate(0);
    assertEqual(rd.resultSSS, 1500 + 0);
    rd.actuate(1);
    assertMoreOrEqual(rd.resultSSS, 1500 + 30);
    rd.actuate(-1001);
    assertEqual(rd.resultSSS, 1500 - 100);
    rd.actuate(1001);
    assertEqual(rd.resultSSS, 1500 + 500);
    rd.actuate(-1000);
    assertEqual(rd.resultSSS, 1500 - 100);
    rd.actuate(1000);
    assertEqual(rd.resultSSS, 1500 + 500);
}

test(dire_range_reversed)
{
    DirectionalMotor<MockDriver, 100, 30, -30, -500> rd;
    rd.actuate(0);
    assertEqual(rd.resultSSS, 1500 + 0);
    rd.actuate(1001);
    assertEqual(rd.resultSSS, 1500 - 500);
    rd.actuate(-1001);
    assertEqual(rd.resultSSS, 1500 + 100);
    rd.actuate(1000);
    assertEqual(rd.resultSSS, 1500 - 500);
    rd.actuate(-1000);
    assertEqual(rd.resultSSS, 1500 + 100);
}

test(dire_range_mutable)
{
    DirectionalMutableMotor<MockDriver, -100, -30, 30, 500> rd;
    rd.actuate(1);
    assertMoreOrEqual(rd.resultSSS, 1500 + 30);
    rd.setMinForward(0);
    rd.actuate(2);
    assertEqual(rd.resultSSS, 1500 + 1);
}