#pragma once

#include "OpCodeInterface.h"

/**
* @class OpCodeTwo specialisation.
* Multiply 2 numbers.
*/
class OpCodeTwo final : public OpCode
{
public:
    /**
    * Constructor
    * @param firstValue The first number to be multiplied.
    * @param secondValue The second number to be multiplied.
    */
    OpCodeTwo(uint64_t firstValue, uint64_t secondValue)
    : _firstValue{firstValue}
    , _secondValue{secondValue}
    {}

    ~OpCodeTwo() final = default;

    /**
    * Multiply 2 numbers and return the result.
    */
    [[nodiscard]] std::optional<uint64_t> Execute() final
    {
        return _firstValue * _secondValue;
    };

private:
    uint64_t _firstValue;
    uint64_t _secondValue;
};
