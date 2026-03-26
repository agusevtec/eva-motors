#include <evaTac.h>
#include <evaRepeatTimer.h>
#include <evaJoystick.h>
#include <evaSwitch.h>

#include <evamTA6586Driver.h>
#include <evamDirectionalMotor.h>
#include <evamCurveDecor.h>
#include <evamKickDecor.h>

using namespace eva;
using namespace evam;

// Build the motor stack from bottom up:
// Driver (TA6586) -> DirectionalMotor -> KickDecor -> CurveDecor
// 25ms kick pulse at 90% power to overcome static friction
// Negative bend (-6) creates sharper initial response

using BaseMotor = DirectionalMotor<TA6586Driver<9, 10>, -1000, -200, 200, 1000>;
using KickMotor = KickDecor<BaseMotor, 25, 900>;
using PreciseMotor = CurveDecor<KickMotor, -6>;

class Vehicle {
private:
  PreciseMotor mMotor;

  // Joystick on A0, outputs 1000-2000, mapped to -1000..1000
  PinSymmetricJoystick<A0, INPUT, 100, 600> mThrottle;

  // Timer updates motor every 100ms
  RepeatTimer mTimer{ 100, new Handler<Vehicle>(this, &Vehicle::onTimerTick) };

  // Button on pin 7 increases bend (softer low-speed control)
  PullupSwitch<7> mIncreaseButton{ new Handler<Vehicle>(this, &Vehicle::onIncreaseButtonPress), ON_PRESS };

  // Button on pin 8 decreases bend (sharper response)
  PullupSwitch<8> mDecreaseButton{ new Handler<Vehicle>(this, &Vehicle::onDecreaseButtonPress), ON_PRESS };

  void onIncreaseButtonPress(void* sender, CallbackInfo cbInfo) {
    // Softer low-speed response, stronger high-end
    mMotor.SetBend(5);
  }

  void onDecreaseButtonPress(void* sender, CallbackInfo cbInfo) {
    // Sharper initial response
    mMotor.SetBend(-5);
  }

  void onTimerTick(void* sender, CallbackInfo cbInfo) {
    // Map joystick value (1000-2000) to motor range (-1000..1000)
    int speed = map(mThrottle.getValue(), 1000, 2000, -1000, 1000);
    mMotor.Go(speed);
  }
};

void setup() {
  // Static ensures object persists after setup() exits
  static Vehicle vehicle;
}

void loop() {
  // Single call drives timers, switches, and motor decorators
  eva::tac();
}