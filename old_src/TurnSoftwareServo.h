#ifndef TURNSOFTWARESERVO_H_
#define TURNSOFTWARESERVO_H_

#include "TurnMotorBase.h"
#include <SoftwareServo.h>
#include <evaTickable.h>
using namespace eva;

class TurnSoftwareServo : public TurnMotorBase, public Tickable
{
public:
  TurnSoftwareServo(int pPin, int pLeft, int pMiddle, int pRight);
  void Tick();

private:
  void write(int pValue);

private:
  SoftwareServo mServo;
};

#endif
