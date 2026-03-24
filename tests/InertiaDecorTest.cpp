#include <AUnit.h>
#include <evamInertiaDecor.h>
#include "MockMotor.h"
#include <evaTac.h>

using namespace aunit;
using namespace evam;


test(inertia_simple)
{
    InertiaDecor<MockMotor> rd;
    rd.actuate(0);
    assertEqual(rd.resultLevel, 0);

    rd.actuate(-1000);
    assertEqual(rd.resultLevel, -1000);

    rd.actuate(1000);
    assertEqual(rd.resultLevel, 1000);

    rd.actuate(30);
    assertEqual(rd.resultLevel, 1000);
    // for (int i =0 ; i < 30; i++)
    // {
    //     tac();
    //     delay(100);
    //     Serial.println(rd.resultLevel);
    // }

}

