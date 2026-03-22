#include <AUnit.h>
#include <evamBiTrimmer.h>
#include "MockMotor.h"

using namespace aunit;
using namespace evam;


test(range_normal)
{
    MockMotor<BiTrimmer<-100, -30, 30, 500>> rd;

    rd.actuate(0);
    assertEqual(rd.resultLevel, 0);
    rd.actuate(1);
    assertMoreOrEqual(rd.resultLevel, 30);
    
    rd.actuate(-1001);
    assertEqual(rd.resultLevel, -100);
    rd.actuate(1001);
    assertEqual(rd.resultLevel, 500);
    rd.actuate(-1000);
    assertEqual(rd.resultLevel, -100);
    rd.actuate(1000);
    assertEqual(rd.resultLevel, 500);
}

test(range_reversed)
{
    MockMotor<BiTrimmer<100, 30, -30, -500>> rd;
    rd.actuate(0);
    assertEqual(rd.resultLevel, 0);
    rd.actuate(1001);
    assertEqual(rd.resultLevel, -500);
    rd.actuate(-1001);
    assertEqual(rd.resultLevel, 100);
    rd.actuate(1000);
    assertEqual(rd.resultLevel, -500);
    rd.actuate(-1000);
    assertEqual(rd.resultLevel, 100);
}


test(range_mutable)
{
    MockMotor<MutableBiTrimmer<-100, -30, 30, 500>> rd;
    rd.actuate(1);
    assertMoreOrEqual(rd.resultLevel, 30);
    rd.setMinForward(0);
    rd.actuate(2);
    assertEqual(rd.resultLevel, 1);
}