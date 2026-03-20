#include "TurnSoftwareServo.h"

TurnSoftwareServo::TurnSoftwareServo(int pPin, int pLeft, int pMiddle, int pRight) : TurnMotorBase(pLeft, pMiddle, pRight)
{
  mServo.attach(pPin);
}

void TurnSoftwareServo::write(int pValue)
{
  mServo.write(pValue);
}

void TurnSoftwareServo::Tick()
{
  mServo.refresh();
}
