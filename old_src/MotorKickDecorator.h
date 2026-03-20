#ifndef MOTORKICKDECORATOR_H_
#define MOTORKICKDECORATOR_H_

#include <evaTickable.h>
using namespace eva;
#include "IMotor.h"

class MotorKickDecorator : public Tickable, public IMotor
{

public:
  MotorKickDecorator(IMotor &aMotor);
  void SetKick(unsigned char aLevel);
  void Go(int aSpeed) override;
  void tick() override;

private:
  int mSpeed;
  unsigned long mWakeupTimer;
  unsigned char mDuration;
  IMotor &mMotor;
};

#endif
