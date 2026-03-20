#pragma once

class MockMotor
{
public:
    void set(signed short level) 
    {
        this->resultLevel = level;
    }
    signed short resultLevel = 0;
};