#include <AUnit.h>
#include <evamKickDecor.h>
#include "MockMotor.h"
#include <evaTac.h>

using namespace aunit;
using namespace evam;


test(kick_simple)
{
    KickDecor<MockMotor, 20, 250> rd;
    rd.Go(0);
    assertEqual(rd.resultLevel, 0);
    tac();
    rd.Go(1);
    assertEqual(rd.resultLevel, 250);
    delay(50);
    tac();
    assertEqual(rd.resultLevel, 1);
    rd.Go(2);
    assertEqual(rd.resultLevel, 2);
    tac();
    rd.Go(-2);
    assertEqual(rd.resultLevel, -250);
}

test(kick_simple_alt2)
{
    KickDecor<MockMotor, 1000, 250> rd;
    rd.Go(0);
    assertEqual(rd.resultLevel, 0);

    rd.Go(1);
    assertEqual(rd.resultLevel, 250);
    tac();
    rd.Go(2);
    assertEqual(rd.resultLevel, 250);

    tac();
    rd.Go(-1);
    assertEqual(rd.resultLevel, -250);

    tac();
    rd.Go(-2);
    assertEqual(rd.resultLevel, -250);

    tac();
    rd.Go(0);
    assertEqual(rd.resultLevel, -250);
}
