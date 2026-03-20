#include "TurnMotorBase.h"

#include <arduino.h>

TurnMotorBase::TurnMotorBase(int aLeft, int aMiddle, int aRight) : mLeft(aLeft), mMiddle(aMiddle), mRight(aRight)
{
}

void TurnMotorBase::Set(int pTurn)
{
  if (pTurn >= 0)
    write(map(pTurn, 0, 127, mMiddle, mRight));
  else
    write(map(pTurn, -127, 0, mLeft, mMiddle));
}

void TurnMotorBase::SetMiddle(int aMiddle)
{
  mMiddle = aMiddle;
}

void TurnMotorBase::SetRange(int aLeft, int aRight)
{
  mLeft = aLeft;
  mRight = aRight;
}
