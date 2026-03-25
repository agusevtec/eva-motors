#pragma once

class MockMotor
{
public:
    void Go(signed short level) 
    {
        this->resultLevel = level;
    }

    unsigned short min()
    {
        return -1000;
    }

    signed short resultLevel = 0;
};