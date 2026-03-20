#ifndef MOTORENFORCEDECORATOR_H
#define MOTORENFORCEDECORATOR_H

#pragma once

#include "IMotor.h"

class MotorEnforceDecorator : public IMotor
{
public:
  MotorEnforceDecorator(IMotor &aMotor);
  void SetEnforce(float aLevel);
  void Go(int aSpeed) override;

private:
  IMotor &mMotor;
  float mLevel;
};

#endif