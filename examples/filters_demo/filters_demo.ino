#include <evaTac.h>
#include <evaHeartbeat.h>
#include <evaJoystick.h>

#include <evamDirectionalMotor.h>
#include <evamCurveDecor.h>
#include <evamKickDecor.h>
#include <evamInertiaDecor.h>
#include <evamAdaptiveSmoothDecor.h>
#include <evamMedianDecor.h>
#include <evamSmoothDecor.h>

using namespace eva;
using namespace evam;

class DemoDriver {
public:
  signed short Value = 0;
  void actBipolar(signed short aValue) {
    Value = aValue;
  }
};

using DemoMotor = DirectionalMotor<DemoDriver>;

class App : Heartbeat {
private:
  //CurveDecor<DemoMotor, -6> mMotor;
  // KickDecor<DemoMotor, 25, 900> mMotor;
   InertiaDecor<DemoMotor, 30> mMotor;
  // AdaptiveSmoothDecor<DemoMotor> mMotor;
  //SmoothDecor<DemoMotor, 40> mMotor;
  // MedianDecor<DemoMotor, 5> mMotor;

  PinSymmetricJoystick<A6, INPUT, 100, 300> mThrottle;
  //PinJoystick<A6, INPUT, 100, 400/2, 300> mThrottle;

public:
  App()
    : Heartbeat(200) {
  }

  void onHeartbeat() override {
    signed short speed = map(mThrottle.getValue(), 1000, 2000, -1000, 1000);
    mMotor.Go(speed);
    Serial.print(-1000);
    Serial.print(" ");
    Serial.print(1000);
    Serial.print(" ");
    Serial.print(speed);
    Serial.print(" ");
    Serial.println(mMotor.Value);
  }
};

void setup() {
  pinMode(A4, OUTPUT);
  Serial.begin(9600);
  digitalWrite(A4, LOW);
  // Static ensures object persists after setup() exits
  static App app;
}

void loop() {
  // Single call drives timers, switches, and motor decorators
  eva::tac();
}