#pragma once

class MockMotor
{
public:
    void Go(signed short level) 
    {
        this->resultLevel = level;
    }

    signed short resultLevel = 0;
};