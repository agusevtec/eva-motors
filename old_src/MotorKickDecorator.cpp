#include "MotorKickDecorator.h"
#include <arduino.h>

MotorKickDecorator::MotorKickDecorator(IMotor &aMotor)
    : mMotor(aMotor), mSpeed(0), mWakeupTimer(0), mDuration(20)
{
}

void MotorKickDecorator::SetKick(unsigned char aDuration)
{
  mDuration = aDuration;
}

void MotorKickDecorator::Go(int aSpeed)
{
  aSpeed = constrain(aSpeed, -255, 255);
  if (mDuration > 0)
  {
    if ((mSpeed <= 0) and (aSpeed > 0))
    {
      mMotor.Go(127);
      mSpeed = aSpeed;
      mWakeupTimer = millis() + mDuration;
      return;
    }
    if ((mSpeed >= 0) and (aSpeed < 0))
    {
      mMotor.Go(-127);
      mSpeed = aSpeed;
      mWakeupTimer = millis() + mDuration;
      return;
    }
  }
  mMotor.Go(aSpeed);
  mSpeed = aSpeed;
}

void MotorKickDecorator::tick()
{
  if (mWakeupTimer and millis() > mWakeupTimer)
  {
    mMotor.Go(mSpeed);
    mWakeupTimer = 0;
  }
}
