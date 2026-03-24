#pragma once

#include <Servo.h>
#include "evamDefaultTrimm.h"

namespace evam
{
    template <int PIN>
    class ServoDriver
    {
    public:
        ServoDriver()
        {
            servo.attach(PIN);
        }

        /// @brief
        /// @param aLevel 1000 to 2000 value
        void setMicroseconds(unsigned short value)
        {
            servo.writeMicroseconds(constrain(value, 500, 2500));
        }
        
        signed short min()
        {
            return -1000;
        }

    private:
        Servo servo;
    };
}
