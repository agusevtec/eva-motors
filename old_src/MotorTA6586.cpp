#include "MotorTA6586.h"


MotorTA6586::MotorTA6586(uint8_t aForwardPin, uint8_t aBackwardPin)
    : MotorTA6586(aForwardPin, aBackwardPin, -255, -25, 25, 255)
{
}

MotorTA6586::MotorTA6586(uint8_t aForwardPin, uint8_t aBackwardPin, int aMaxBwdSpeed, int aMinBwdSpeed, int aMinFwdSpeed, int aMaxFwdSpeed)
    : mForwardPin(aForwardPin), mBackwardPin(aBackwardPin),
      mMaxBwdSpeed(aMaxBwdSpeed), mMinBwdSpeed(aMinBwdSpeed),
      mMinFwdSpeed(aMinFwdSpeed), mMaxFwdSpeed(aMaxFwdSpeed)
{
  pinMode(aForwardPin, OUTPUT);
  pinMode(aBackwardPin, OUTPUT);
  Go(0);
}

void MotorTA6586::SetUp(int aMaxBwdSpeed, int aMinBwdSpeed, int aMinFwdSpeed, int aMaxFwdSpeed)
{
  mMaxBwdSpeed = aMaxBwdSpeed;
  mMinBwdSpeed = aMinBwdSpeed;
  mMinFwdSpeed = aMinFwdSpeed;
  mMaxFwdSpeed = aMaxFwdSpeed;
}

void MotorTA6586::Go(int aSpeed)
{
  aSpeed = constrain(aSpeed, -255, 255);
  if (aSpeed == 0)
  {
    analogWrite(mForwardPin, 0);
    analogWrite(mBackwardPin, 0);
  }
  if (aSpeed > 0)
  {
    analogWrite(mForwardPin, map(aSpeed, 0, 255, mMinFwdSpeed, mMaxFwdSpeed));
    analogWrite(mBackwardPin, 0);
  }
  if (aSpeed < 0)
  {
    analogWrite(mForwardPin, 0);
    analogWrite(mBackwardPin, map(-aSpeed, 0, 255, -mMinBwdSpeed, -mMaxBwdSpeed));
  }
}
