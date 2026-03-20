#ifndef Servo_h
#define Servo_h

#pragma once
#include <Arduino.h>


#include <stdint.h>

#define INVALID_SERVO 255

class Servo {
public:
    uint8_t attach(int pin);
    uint8_t attach(int pin, int min, int max);
    void detach();
    void write(int value);
    void writeMicroseconds(int value);
    int read();
    int readMicroseconds();
    bool attached();
};

#endif