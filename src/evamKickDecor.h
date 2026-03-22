#ifndef MOTORKICKDECORATOR_H_
#define MOTORKICKDECORATOR_H_

#pragma once

#include <evaTickable.h>
using namespace eva;

namespace evam
{
    template <class MOTOR, unsigned short KICK_DURATION = 20, signed short KICK_POWER = 250>
    class KickDecor : public virtual Tickable, public MOTOR
    {
    public:
        signed short calculateKickPower(signed short value)
        {
            if ((this->targetSpeed <= 0) && (value > 0))
                return KICK_POWER;

            if ((this->targetSpeed >= 0) && (value < 0))
                return -KICK_POWER;
                
            return 0;
        }

        void actuate(signed short value)
        {
            signed short needKick = calculateKickPower(value);
            this->targetSpeed = value;

            if (needKick)
            {
                MOTOR::actuate(needKick);
                holdingStartedAt = millis();
                return;
            }

            if (holdingStartedAt)
                return;

            MOTOR::actuate(value);
        }

        void tick() override
        {
            if (!holdingStartedAt)
                return;

            if (millis() - holdingStartedAt < KICK_DURATION)
                return;

            MOTOR::actuate(targetSpeed);
            holdingStartedAt = 0;
        }

    private:
        int targetSpeed = 0;
        unsigned long holdingStartedAt = 0;
    };

}
#endif // MOTORKICKDECORATOR_H_