#ifndef MOTORTB6612FNG_H_
#define MOTORTB6612FNG_H_

#include "IMotor.h"

class MotorTB6612FNG: public IMotor
{
  int mSpeedPin;
  int mModePin1;
  int mModePin2;
  
public:
  MotorTB6612FNG(int pSpeedPin, int pModePin1, int pModePin2);
  void Go(int pSpeed);
};

#endif
