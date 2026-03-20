#ifndef TURNSERVO_H_
#define TURNSERVO_H_

#include <Servo.h>
#include "TurnMotorBase.h"

class TurnServo: public TurnMotorBase
{
  Servo mServo;
   
private:
  void write(int pValue);

public:
  TurnServo(int pPin, int pLeft, int pMiddle, int pRight);
};


#endif
