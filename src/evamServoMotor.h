#pragma once

#include <Servo.h>
#include "evamDefaultTrimm.h"

namespace evam
{
    template <int PIN, TRIMMER=DefaultTrimm>
    class ServoMotor
    {
    public:
        ServoMotor()
        {
            servo.attach(PIN);
        }

        /// @brief
        /// @param aLevel -0 to 1000 value
        void actuate(signed short level)
        {
            servo.writeMicroseconds(TRIMMER.trim(level) + 1000);
        }

    private:
        Servo servo;
    };
}