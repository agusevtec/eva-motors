#pragma once

namespace evam
{
    /**
     * @brief Simple stateful reader acting as a bridge between raw control values and evaf filters.
     */
    class ValueReader
    {
    protected:
        signed short mValue = 0;

    public:
        void setValue(signed short value) { mValue = value; }
        signed short getValue() const { return mValue; }
        bool isValid() const { return true; }
    };

}
