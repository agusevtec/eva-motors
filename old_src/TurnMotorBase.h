#ifndef TURNMOTORBASE_H_
#define TURNMOTORBASE_H_

class TurnMotorBase
{
public:
  TurnMotorBase(int aLeft, int aMiddle, int aRight);
  void Set(int pTurn);
  void SetMiddle(int aMiddle);
  void SetRange(int aLeft, int aRight);

private:
  virtual void write(int pTurn) = 0;

private:
  int mLeft, mMiddle, mRight;
};

#endif
