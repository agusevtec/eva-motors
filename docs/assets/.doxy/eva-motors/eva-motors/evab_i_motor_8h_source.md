

# File evabIMotor.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**evabIMotor.h**](evab_i_motor_8h.md)

[Go to the documentation of this file](evab_i_motor_8h.md)


```C++
#pragma once

namespace evam
{
    class IMotor
    {
    public:
        virtual void Go(signed short aValue) = 0;
        virtual ~IMotor() = default;
    };

    template <class TMotor>
    class IMotorMaker : public IMotor
    {
    public:
        template <typename... Arg>
        IMotorMaker(Arg... args) : TMotor(args...)
        {
        }

        void Go(signed short aValue)
        {
            TMotor::Go(aValue);
        }
    };
}
```


