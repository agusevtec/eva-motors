#pragma once
#include <evamDefaultTrimm.h>

template <class TRIMMER=DefaultTrimm>
class MockMotor: public TRIMMER
{
public:
    void actuate(signed short level) 
    {
        this->resultLevel = TRIMMER::trim(level);
    }
    signed short resultLevel = 0;
};