#include "MotorESC.h"
#include <arduino.h>

MotorESC::MotorESC(int aPin)
    : MotorESC(aPin, 1000, 1500, 1500, 2000)
{
}

MotorESC::MotorESC(int pPin, int aMaxBwdSpeed, int aMinBwdSpeed, int aMinFwdSpeed, int aMaxFwdSpeed)
    : mMaxBwdSpeed(aMaxBwdSpeed), mMinBwdSpeed(aMinBwdSpeed), mMinFwdSpeed(aMinFwdSpeed), mMaxFwdSpeed(aMaxFwdSpeed)
{
  mServo.attach(pPin);
  Go(0);
}

void MotorESC::Go(int pSpeed)
{
  pSpeed = constrain(pSpeed, -255, 255);

  if (pSpeed == 0)
    mServo.writeMicroseconds(1500);
  if (pSpeed > 0)
    mServo.writeMicroseconds(map(pSpeed, 0, 255, mMinFwdSpeed, mMaxFwdSpeed)); // 1500 - stop
  if (pSpeed < 0)
    mServo.writeMicroseconds(map(pSpeed, -255, 0, mMaxBwdSpeed, mMinBwdSpeed)); // 1500 - stop
}

void MotorESC::SetUp(int aMaxBwdSpeed, int aMinBwdSpeed, int aMinFwdSpeed, int aMaxFwdSpeed)
{
  mMaxBwdSpeed = aMaxBwdSpeed;
  mMinBwdSpeed = aMinBwdSpeed;
  mMinFwdSpeed = aMinFwdSpeed;
  mMaxFwdSpeed = aMaxFwdSpeed;
}