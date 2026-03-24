#pragma once

class MockDriver
{
public:
    void setMicroseconds(unsigned short value) 
    {
        this->resultSSS = value;
    }
    
    unsigned short resultSSS = 0;
};