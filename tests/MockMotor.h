#pragma once

class MockMotor
{
public:
    void actuate(signed short level) 
    {
        this->resultLevel = level;
    }

    unsigned short min()
    {
        return -1000;
    }

    signed short resultLevel = 0;
};