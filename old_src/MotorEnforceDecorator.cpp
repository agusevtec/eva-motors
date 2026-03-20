#include "MotorEnforceDecorator.h"
#include <Arduino.h>

MotorEnforceDecorator::MotorEnforceDecorator(IMotor &aMotor)
    : mMotor(aMotor), mLevel(1)
{
}

void MotorEnforceDecorator::SetEnforce(float aLevel)
{
  mLevel = aLevel;
}

void MotorEnforceDecorator::Go(int aSpeed)
{
  if (aSpeed >= 0)
    mMotor.Go(255 - pow((255 - aSpeed) / 255.0, mLevel) * 255);
  else
    mMotor.Go(-255 + pow((255 + aSpeed) / 255.0, mLevel) * 255);
}
