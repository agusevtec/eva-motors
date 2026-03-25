# Quick Start

## Complete RC Vehicle with All Features

```cpp
#include <evaTac.h>
#include <evaRepeatTimer.h>
#include <evaJoystick.h>
#include <evamTA6586Driver.h>
#include <evamDirectionalMotor.h>
#include <evamCurveDecor.h>
#include <evamInertiaDecor.h>
#include <evamKickDecor.h>

using namespace eva;

// Build the complete motor stack
using BaseMotor = evam::DirectionalMotor<evam::TA6586Driver<9, 10>>;
using PreciseMotor = evam::CurveDecor<BaseMotor, 5>;
using InertialMotor = evam::InertiaDecor<PreciseMotor, 15>;
using SmartMotor = evam::KickDecor<InertialMotor, 25, 900>;

class MotorController {
private:
    SmartMotor mMotor;
    RepeatTimer mTimer;
    int mCurrentSpeed = 0;
    int mDirection = 1;

    void onTimerTick(void* sender, CallbackInfo cbInfo) {
        mCurrentSpeed += mDirection * 50;
        
        if (mCurrentSpeed >= 1000) {
            mCurrentSpeed = 1000;
            mDirection = -1;
        }
        if (mCurrentSpeed <= -1000) {
            mCurrentSpeed = -1000;
            mDirection = 1;
        }
        
        mMotor.Go(mCurrentSpeed);
    }

public:
    MotorController() : mTimer({new Handler<MotorController>(this, &MotorController::onTimerTick)}) {
        mMotor.setup_range(-1000, -200, 200, 1000);
        mMotor.setup_curve(6);
        mMotor.SetInertiaMass(20);
        mMotor.setup_kickstart(30, 850);
        mTimer.start(100);
    }
};

MotorController controller;

void setup() {}

void loop() {
    eva::tac();
}
```

## Simple Joystick Control

```cpp
#include <evaTac.h>
#include <evaJoystick.h>
#include <evamTA6586Driver.h>
#include <evamDirectionalMotor.h>

using namespace eva;

using Motor = evam::DirectionalMotor<evam::TA6586Driver<9, 10>>;

class Car {
private:
    Motor mMotor;
    Joystick<A0> mJoystick;

public:
    Car() {
        mMotor.setup_range(-1000, -300, 300, 1000);
    }
    
    void update() {
        int speed = map(mJoystick.getValue(), 0, 1023, -1000, 1000);
        mMotor.Go(speed);
    }
};

Car car;

void setup() {}

void loop() {
    eva::tac();
    car.update();
}
```

## Aircraft ESC with Throttle Ramping

```cpp
#include <evaTac.h>
#include <evaRepeatTimer.h>
#include <evamPwmDriver.h>
#include <evamForwardMotor.h>
#include <evamCurveDecor.h>

using namespace eva;

using ESC = evam::CurveDecor<evam::ForwardMotor<evam::PwmDriver<9>>, 4>;

class ThrottleControl {
private:
    ESC mThrottle;
    RepeatTimer mTimer;
    int mTargetThrottle = 0;
    int mCurrentThrottle = 0;

    void onTimerTick(void* sender, CallbackInfo cbInfo) {
        if (mCurrentThrottle < mTargetThrottle) {
            mCurrentThrottle += 20;
            if (mCurrentThrottle > mTargetThrottle) mCurrentThrottle = mTargetThrottle;
        } else if (mCurrentThrottle > mTargetThrottle) {
            mCurrentThrottle -= 20;
            if (mCurrentThrottle < mTargetThrottle) mCurrentThrottle = mTargetThrottle;
        }
        mThrottle.Go(mCurrentThrottle);
    }

public:
    ThrottleControl() : mTimer({new Handler<ThrottleControl>(this, &ThrottleControl::onTimerTick)}) {
        mThrottle.setup_range(100, 1000);
        mTimer.start(50);
    }
    
    void setThrottle(int percent) {
        mTargetThrottle = constrain(percent, 0, 1000);
    }
};

ThrottleControl throttle;

void setup() {}

void loop() {
    eva::tac();
    
    static int pos = 0;
    static int dir = 1;
    
    pos += dir * 5;
    if (pos >= 1000) dir = -1;
    if (pos <= 0) dir = 1;
    
    throttle.setThrottle(pos);
    delay(10);
}
```

## Steering Servo with Automatic Sweep

```cpp
#include <evaTac.h>
#include <evaRepeatTimer.h>
#include <evamServoDriver.h>
#include <evamSteeringActuator.h>

using namespace eva;

using Steering = evam::SteeringActuator<evam::ServoDriver<9>>;

class SteeringControl {
private:
    Steering mSteering;
    RepeatTimer mTimer;
    int mCurrentPos = 0;
    int mDirection = 1;

    void onTimerTick(void* sender, CallbackInfo cbInfo) {
        mCurrentPos += mDirection * 100;
        
        if (mCurrentPos >= 800) {
            mCurrentPos = 800;
            mDirection = -1;
        }
        if (mCurrentPos <= -800) {
            mCurrentPos = -800;
            mDirection = 1;
        }
        
        mSteering.Go(mCurrentPos);
    }

public:
    SteeringControl() : mTimer({new Handler<SteeringControl>(this, &SteeringControl::onTimerTick)}) {
        mSteering.setup_range(-800, 0, 800);
        mTimer.start(100);
    }
};

SteeringControl steering;

void setup() {}

void loop() {
    eva::tac();
}
```

## Linear Actuator Position Control

```cpp
#include <evaTac.h>
#include <evaRepeatTimer.h>
#include <evamPwmDriver.h>
#include <evamLinearActuator.h>

using namespace eva;

using Actuator = evam::LinearActuator<evam::PwmDriver<10>>;

class PositionControl {
private:
    Actuator mActuator;
    RepeatTimer mTimer;
    int mTargetPos = 0;
    int mCurrentPos = 0;

    void onTimerTick(void* sender, CallbackInfo cbInfo) {
        if (mCurrentPos < mTargetPos) {
            mCurrentPos += 50;
            if (mCurrentPos > mTargetPos) mCurrentPos = mTargetPos;
        } else if (mCurrentPos > mTargetPos) {
            mCurrentPos -= 50;
            if (mCurrentPos < mTargetPos) mCurrentPos = mTargetPos;
        }
        mActuator.Go(mCurrentPos);
    }

public:
    PositionControl() : mTimer({new Handler<PositionControl>(this, &PositionControl::onTimerTick)}) {
        mActuator.setup_range(0, 1000);
        mTimer.start(50);
    }
    
    void setPosition(int pos) {
        mTargetPos = constrain(pos, 0, 1000);
    }
};

PositionControl actuator;

void setup() {}

void loop() {
    eva::tac();
    
    static int pos = 0;
    static int dir = 1;
    
    pos += dir * 20;
    if (pos >= 1000) dir = -1;
    if (pos <= 0) dir = 1;
    
    actuator.setPosition(pos);
    delay(20);
}
```