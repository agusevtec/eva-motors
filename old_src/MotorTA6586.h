#ifndef MOTORTA6586_H_
#define MOTORTA6586_H_
#include "IMotor.h"
#include <Arduino.h>

//       TA-6586
//       -------
//  5 - |       | - VCC
//  6 - |       | - GND
//  7 - |       | - FI
//  8 - |   _   | - BI
//       --/ \--

class MotorTA6586 : public IMotor
{

public:
  MotorTA6586(uint8_t aForwardPin, uint8_t aBackwardPin);
  MotorTA6586(uint8_t aForwardPin, uint8_t aBackwardPin, int aMaxBwdSpeed, int aMinBwdSpeed, int aMinFwdSpeed, int aMaxFwdSpeed);
  void SetUp(int aMaxBwdSpeed, int aMinBwdSpeed, int aMinFwdSpeed, int aMaxFwdSpeed);
  void Go(int aSpeed) override;

private:
  uint8_t mBackwardPin, mForwardPin;
  int mMaxBwdSpeed, mMinBwdSpeed, mMinFwdSpeed, mMaxFwdSpeed;
};

#endif
