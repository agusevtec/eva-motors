using ServoDriver = evam::SoftwareServoDriver<9>;

using SmoothServo = evam::AdaptiveSmoothDecor<ServoDriver>;

// using SmoothServo = evam::SmoothDecor<ServoDriver, 40>;

// using SmoothServo = evam::MedianDecor<ServoDriver, 5>;

SmoothServo servo;

void loop() {
    int joystickValue = analogRead(A0); // 0-1023
    int mappedValue = map(joystickValue, 0, 1023, -1000, 1000);
    
    servo.Go(mappedValue);
}
