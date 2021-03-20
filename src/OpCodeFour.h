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
    * @param input The user input vector.
    * @param parameterModes The collection of the parameter modes.
    * @param printedOutput Collection of values to be printed out.
    */
    OpCodeFour(const Vector& input, const ParameterModeVector& parameterModes, Vector& printedOutput)
    : _input{input}
    , _parameterModes{parameterModes}
    , _printedOutput{printedOutput}
    {}

    ~OpCodeFour() final = default;

    /**
    * Claim a number and store it in the printed output collection.
    */
    [[nodiscard]] OpCode::ReturnType Execute(std::any& nextElementIter, std::any& endIter) final
    {
        VectorIterator& iterBegin = std::any_cast<VectorIterator&>(nextElementIter);
        VectorIterator& iterEnd = std::any_cast<VectorIterator&>(endIter);

        // Check if there are enough numbers to be claimed to complete the operation.
        // A single number is needed to be stored in the printed output collection.
        if (!AreThereEnoughElementsIntoTheCollection(iterBegin, iterEnd, 1))
        {
            return { std::nullopt, {} };
        }

        T number;
        if ( _parameterModes[0] == ParameterMode::Immediate )
        {
            number = *iterBegin;
        }
        // ParameterMode::Position
        else
        {
            assert(*iterBegin >= 0);
            assert(static_cast<IndexType>(*iterBegin) < _input.size());
            number = _input[*iterBegin];
        }

        _printedOutput.emplace_back(number);

        // Jump to the next number (if any).
        iterBegin++;

        // What we return here it is only useful for error reporting.
        // Whatever different than std::nullopt is equal to SUCCESS.
        return { std::make_optional<Result>(), {iterBegin} };
    };

private:
    const Vector& _input;
    const ParameterModeVector& _parameterModes;
    Vector& _printedOutput;
};
