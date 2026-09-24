#include <evaHeartbeat.h>
#include <evaTac.h>

#include <evamSoftwareServoDriver.h>
#include <evamLinearActuator.h>
#include <evamAdaptiveSmoothDecor.h>
#include <evamSimpleSmoothDecor.h>
#include <evamMedianDecor.h>
#include <evamMinmaxDecor.h>

using namespace eva;
using namespace evam;

using MyLinearActuator = LinearActuator<SoftwareServoDriver<3>>;

using SmoothServo = AdaptiveSmoothDecor<MyLinearActuator>;
//using SmoothServo = SimpleSmoothDecor<MyLinearActuator, 6>;
//using SmoothServo = MedianDecor<MyLinearActuator, 5>;

class App : Heartbeat {
  SmoothServo servo;

public:
  
  App()
    : Heartbeat(100) {
  }

  void onHeartbeat() override {
    int joystickValue = analogRead(A0);  // 0-1023
    int mappedValue = map(joystickValue, 0, 1023, -1000, 1000);
    servo.Go(mappedValue);
  }
};

void setup() {
  static App app;
}

void loop() {
  eva::tac();
}
