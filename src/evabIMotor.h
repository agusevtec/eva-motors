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
