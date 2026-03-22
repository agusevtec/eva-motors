#ifndef MOTORINERTIADECORATOR_H
#define MOTORINERTIADECORATOR_H

#pragma once
#include <evaTickable.h>
using namespace eva;

namespace evam
{
  template <class Motor>
  class InertiaDecor : public virtual Tickable, public Motor
  {
  public:
    void actuate(int speed)
    {
      this->desiredSpeed = speed;
      if (speed == calcSpeed())
      {
        this->speed = speed;
        Motor::actuate(speed);
      }
    }

  private:
    signed short calcSpeed()
    {
      if (this->desiredSpeed * this->speed < 0)
        return this->desiredSpeed;

      if (abs(this->desiredSpeed) > abs(this->speed))
        return this->desiredSpeed;

      signed short step = 2*(this->desiredSpeed - this->speed)/10;
      signed short signStep = (this->desiredSpeed > this->speed) + (this->desiredSpeed < this->speed);
      return this->speed + step - signStep;
    }

    void tick()
    {
      unsigned long now = millis();
      if (now - lastSpeedUpdateWasAt < 100)
        return;
      lastSpeedUpdateWasAt = now;
      
      this->speed = calcSpeed();
      Motor::actuate(this->speed);
    }

  private:
    unsigned long lastSpeedUpdateWasAt = 0;
    signed short desiredSpeed = 0;
    signed short speed = 0;
  };
}
#endif