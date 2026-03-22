#include <AUnit.h>
#include <evamKickDecor.h>
#include "MockMotor.h"
#include <evaTac.h>

using namespace aunit;
using namespace evam;


test(kick_simple)
{
    KickDecor<MockMotor<DefaultTrimm>, 20, 250> rd;
    rd.actuate(0);
    assertEqual(rd.resultLevel, 0);
    tac();
    rd.actuate(1);
    assertEqual(rd.resultLevel, 250);
    delay(50);
    tac();
    assertEqual(rd.resultLevel, 1);
    rd.actuate(2);
    assertEqual(rd.resultLevel, 2);
    tac();
    rd.actuate(-2);
    assertEqual(rd.resultLevel, -250);
}

test(kick_simple_alt2)
{
    KickDecor<MockMotor<>, 1000, 250> rd;
    rd.actuate(0);
    assertEqual(rd.resultLevel, 0);

    rd.actuate(1);
    assertEqual(rd.resultLevel, 250);
    tac();
    rd.actuate(2);
    assertEqual(rd.resultLevel, 250);

    tac();
    rd.actuate(-1);
    assertEqual(rd.resultLevel, -250);

    tac();
    rd.actuate(-2);
    assertEqual(rd.resultLevel, -250);

    tac();
    rd.actuate(0);
    assertEqual(rd.resultLevel, -250);
}
