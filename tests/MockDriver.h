#pragma once

class MockDriver
{
protected:
    void actBipolar(signed short value)
    {
        this->resultValue = value;
    }

    void actUnipolar(signed short value)
    {
        this->resultValue = value;
    }

public:
    signed short resultValue = 0;
};