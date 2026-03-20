#include "TurnServo.h"


TurnServo::TurnServo(int pPin, int pLeft, int pMiddle, int pRight):
  TurnMotorBase(pLeft, pMiddle, pRight)
{
   mServo.attach(pPin);
}

void TurnServo::write(int pValue)
{
  mServo.write(pValue);
}
