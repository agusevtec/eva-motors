#include "MotorTB6612FNG.h"
#include <arduino.h>

MotorTB6612FNG::MotorTB6612FNG(int pSpeedPin, int pModePin1, int pModePin2):
  mSpeedPin(pSpeedPin), 
  mModePin1(pModePin1), 
  mModePin2(pModePin2)
{
  pinMode(pSpeedPin, OUTPUT);
  pinMode(mModePin1, OUTPUT);
  pinMode(mModePin2, OUTPUT);
  Go(0);
}

void MotorTB6612FNG::Go(int pSpeed)
{
  pSpeed = constrain(pSpeed, -255, 255);
  analogWrite(mSpeedPin, map(abs(pSpeed), 0, 255, 25, 255));
  digitalWrite(mModePin1, pSpeed > 0);
  digitalWrite(mModePin2, pSpeed < 0);
}
