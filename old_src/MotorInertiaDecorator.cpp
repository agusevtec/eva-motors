#include "MotorInertiaDecorator.h"
#include <Arduino.h>

MotorInertiaDecorator::MotorInertiaDecorator(IMotor &aMotor)
    : mMotor(aMotor), mSpeed(0), mDesiredSpeed(0), mHeartbeatTimer(0)
{
}

void MotorInertiaDecorator::updateSpeed() 
{
    if (mDesiredSpeed * mSpeed < 0) 
    {
        mSpeed = mDesiredSpeed;
        return;
    }
    if (abs(mDesiredSpeed )> abs(mSpeed)) 
    {
        mSpeed = mDesiredSpeed;
        return;
    }
    mSpeed += (mDesiredSpeed - mSpeed) * 0.3;
}

void MotorInertiaDecorator::Go(int aSpeed)
{
    mDesiredSpeed = aSpeed;
    updateSpeed();
    mMotor.Go(mSpeed);
}

void MotorInertiaDecorator::tick()
{
    if (millis() < mHeartbeatTimer)
        return;
    updateSpeed();
    mMotor.Go(mSpeed);
}
