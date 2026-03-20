#ifndef IMOTOR_H_
#define IMOTOR_H_

class IMotor
{
public:
  virtual void Go(int aSpeed) = 0;
};

#endif
