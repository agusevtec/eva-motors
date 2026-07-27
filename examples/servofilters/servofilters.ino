#include <evamSoftwareServoDriver.h>
#include <evamLinearActuator.h>
#include <evamAdaptiveSmoothDecor.h>
#include <evamSlidingWindowDecor.h>
#include <evamMedianDecor.h>
#include <evamMinmaxDecor.h>

using namespace evam;

using MyServoDriver = SoftwareServoDriver<3>;
using MyLinearActuator = LinearActuator<MyServoDriver, 0, 1000>;

//using SmoothServo = AdaptiveSmoothDecor<MyLinearActuator>;
//using SmoothServo = SlidingWindowDecor<MyLinearActuator, 6>;
using SmoothServo = MedianDecor<MyLinearActuator, 5>;

SmoothServo servo;

void setup(){

}

void loop() {
    int joystickValue = analogRead(A0); // 0-1023
    int mappedValue = map(joystickValue, 0, 1023, -1000, 1000);
    
    servo.Go(mappedValue);
}
