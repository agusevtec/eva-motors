#include <evamUtils.h>

#include <Arduino.h>

void evam::univeralWrite(unsigned char aPin, unsigned char aValue)
{
    if (aValue == 0)
        digitalWrite(aPin, LOW);
    else if (aValue == 255)
        digitalWrite(aPin, HIGH);
    else
        analogWrite(aPin, aValue);
}
