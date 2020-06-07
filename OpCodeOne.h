#pragma once

#include "OpCodeInterface.h"
#include "OpCodeProcessorUtils.h"

/**
* @class OpCodeOne specialisation.
* Accumulate 2 numbers.
*/
class OpCodeOne final : public OpCode
{
public:
    /**
    * Constructor
    * @param firstValue The first number to be accumulated.
    * @param secondValue The second number to be accumulated.
    */
    OpCodeOne(uint64_t firstValue, uint64_t secondValue)
    : _firstValue{firstValue}
    , _secondValue{secondValue}
    {}

    ~OpCodeOne() final = default;

    /**
    * Accumulate 2 numbers and return the result.
    */
    [[nodiscard]] std::optional<uint64_t> Execute() final
    {
        return _firstValue + _secondValue;
    };

private:
    uint64_t _firstValue;
    uint64_t _secondValue;
};
