#ifndef SoftwareServo_h
#define SoftwareServo_h

#pragma once
#include <Arduino.h>


#include <stdint.h>


class SoftwareServo {
public:
    uint8_t attach(int pin);
    uint8_t attach(int pin, int min, int max);
    void detach();
    void write(int value);
    void writeMicroseconds(int value);
    int read();
    int readMicroseconds();
    bool attached();
    void refresh();
};

#endif