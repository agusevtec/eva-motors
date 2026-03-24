#include <AUnit.h>
#include <evamCurveDecor.h>
#include "MockMotor.h"
#include <evaTac.h>

using namespace aunit;
using namespace evam;

test(curve_simple)
{
    CurveDecor<MockMotor, 0> rd;
    rd.actuate(0);
    assertEqual(rd.resultLevel, 0);

    rd.actuate(1000);
    assertEqual(rd.resultLevel, 1000);

    rd.actuate(500);
    assertEqual(rd.resultLevel, 500);
}

test(curve_bend_up)
{
    CurveDecor<MockMotor, 2> rd;
    rd.actuate(0); 
    assertEqual(rd.resultLevel, 0);

    rd.actuate(1000);
    assertEqual(rd.resultLevel, 1000);

    rd.actuate(200);
    assertMore(rd.resultLevel, 200);
}

test(curve_bend_down)
{
    CurveDecor<MockMotor, -2> rd;
    rd.actuate(0);
    assertEqual(rd.resultLevel, 0);

    rd.actuate(1000);
    assertEqual(rd.resultLevel, 1000);

    rd.actuate(200);
    assertLess(rd.resultLevel, 200);
}

test(curve_bend_negative)
{
    CurveDecor<MockMotor, -2> rd;
    rd.actuate(0);
    assertEqual(rd.resultLevel, 0);

    rd.actuate(1000);
    assertEqual(rd.resultLevel, 1000);

    rd.actuate(200);
    assertLess(rd.resultLevel, 200);
}