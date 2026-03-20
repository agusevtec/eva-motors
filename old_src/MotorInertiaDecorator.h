#ifndef MOTORINERTIADECORATOR_H
#define MOTORINERTIADECORATOR_H

#pragma once
#include "IMotor.h"
#include <evaTickable.h>
using namespace eva;

class MotorInertiaDecorator : public Tickable, public IMotor
{
public:
  MotorInertiaDecorator(IMotor &aMotor);
  void Go(int aSpeed) override;
  void tick() override;

private:
  void updateSpeed();

private:
  unsigned long mHeartbeatTimer;
  int mDesiredSpeed;
  int mSpeed;
  IMotor &mMotor;
};

#endif