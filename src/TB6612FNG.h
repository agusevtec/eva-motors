#ifndef TB6612FNG_DRIVER_H_
#define TB6612FNG_DRIVER_H_
#pragma once

template <int PIN_SPEED, int PIN_MODE1, int PIN_MODE2>
class TB6612FNG
{
public:
  TB6612FNG()
  {
    pinMode(PIN_SPEED, OUTPUT);
    pinMode(mModePin1, OUTPUT);
    pinMode(mModePin2, OUTPUT);
    actuate(0);
  }

  void actuate(unsigned short value)
  {
    analogWrite(map(constrain(value, -1000, 1000), -1000, 1000, -255, 255));
    digitalWrite(mModePin1, value > 0);
    digitalWrite(mModePin2, value < 0);
  }

  signed short min()
  {
    return -1000;
  }
};

#endif
