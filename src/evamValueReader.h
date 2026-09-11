#pragma once

namespace evam
{
    /**
     * @brief Simple stateful reader acting as a bridge between raw control
     *        values and evaf filters.
     *
     * getValue()/isValid() are public because evaf filters call them.
     * setValue() is public so that decorators can push the target value
     * straight into the filter.
     */
    class ValueReader
    {
    private:
        signed short mValue = 0;

    public:
        void setValue(signed short value) { mValue = value; }
        signed short getValue() const { return mValue; }
        bool isValid() const { return true; }
    };
}
