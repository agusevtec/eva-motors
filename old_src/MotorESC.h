#ifndef MOTORESC_H_
#define MOTORESC_H_

#include "IMotor.h"
#include <Servo.h>

class MotorESC: public IMotor
{
public:
  MotorESC(int pPin);
  MotorESC(int pPin, int aMaxBwdSpeed, int aMinBwdSpeed, int aMinFwdSpeed, int aMaxFwdSpeed);
  void Go(int pSpeed);
  void SetUp(int aMaxBwdSpeed, int aMinBwdSpeed, int aMinFwdSpeed, int aMaxFwdSpeed);

private:
  int mMaxBwdSpeed, mMinBwdSpeed, mMinFwdSpeed, mMaxFwdSpeed;
  Servo mServo;
};

#endif
