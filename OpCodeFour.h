#pragma once

#include "OpCodeInterface.h"
#include "OpCodeProcessorUtils.h"
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
    * @param parameterModes The collection of the parameter modes.
    * @param printedOutput Collection of values to be printed out.
    */
    OpCodeFour(
        const Vector& input,
        VectorIterator& iterator,
        const ParameterModeVector& parameterModes,
        Vector& printedOutput)
    : _input{input}
    , _iterator{iterator}
    , _parameterModes{parameterModes}
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
        if (!AreThereEnoughElementsIntoTheCollection(_input, _iterator, 1))
        {
            return std::nullopt;
        }

        T number;
        if ( _parameterModes[0] == ParameterMode::Immediate )
        {
            number = *_iterator;
        }
        // ParameterMode::Position
        else
        {
            assert(*_iterator >= 0);
            assert(static_cast<size_t>(*_iterator) < _input.size());
            number = _input[*_iterator];
        }

        _printedOutput.emplace_back(number);

        // Jump to the next number (if any).
        _iterator++;

        // What we return here it is only useful for error reporting.
        // Whatever different than std::nullopt is equal to SUCCESS.
        return std::make_optional<Result>();
    };

private:
    const Vector& _input;
    VectorIterator& _iterator;
    const ParameterModeVector& _parameterModes;
    Vector& _printedOutput;
};
