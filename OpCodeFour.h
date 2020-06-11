#pragma once

#include "OpCodeInterface.h"
#include <vector>

/**
* @class OpCodeFour specialisation.
* Claim a number and store it in the printed output collection.
*/
template <typename T>
class OpCodeFour final : public OpCode
{
using Vector = std::vector<T>;
using VectorIterator = typename Vector::iterator;

public:
    /**
    * Constructor
    * @param input    The user input vector.
    * @param iterator User input vector iterator
    *                 which points to the first number to be claimed.
    * @param printedOutput Collection of values to be printed out.
    */
    OpCodeFour(
        Vector& input,
        VectorIterator& iterator,
        Vector& printedOutput)
    : _input{input}
    , _iterator{iterator}
    , _printedOutput{printedOutput}
    {}

    ~OpCodeFour() final = default;

    /**
    * Claim a number and store it in the printed output collection.
    */
    [[nodiscard]] std::optional<Result> Execute() final
    {
        // Check if there are enough numbers to be claimed to complete the operation.
        // A single number is needed to be stored in the printed output collection.
        if ( std::distance(_iterator, _input.end()) < 1 )
        {
            return std::nullopt;
        }

        const T number = *_iterator;
        assert( (number >= 0) && (number < _input.size()) );
        _printedOutput.emplace_back(_input[number]);

        // What we return here it is only useful for error reporting.
        // Whatever different than std::nullopt is equal to SUCCESS.
        return std::make_optional<Result>();
    };

private:
    Vector& _input;
    VectorIterator& _iterator;
    Vector& _printedOutput;
};
