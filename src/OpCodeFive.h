#pragma once

#include "OpCodeInterface.h"
#include "OpCodeProcessorUtils.h"
#include <vector>

/**
* @class OpCodeFive specialisation.
* If the first parameter is non-zero then set the instruction pointer to the value from the second parameter.
* Otherwise do nothing.
*/
template <typename T>
class OpCodeFive final : public OpCode
{
using Vector = std::vector<T>;
using VectorIterator = typename Vector::iterator;

public:
    /**
    * Constructor
    * @param input    The user input vector.
    * @param parameterModes The collection of the parameter modes.
    */
    OpCodeFive(Vector& input, const ParameterModeVector& parameterModes)
    : _input{input}
    , _parameterModes{parameterModes}
    {}

    ~OpCodeFive() final = default;

    /**
    * If the first parameter is non-zero then set the instruction pointer to the value from the second parameter.
    * Otherwise do nothing.
    */
    [[nodiscard]] OpCode::ReturnType Execute(std::any& nextElementIter, std::any& endIter) final
    {
        VectorIterator& iterBegin = std::any_cast<VectorIterator&>(nextElementIter);
        VectorIterator& iterEnd = std::any_cast<VectorIterator&>(endIter);

        // Check if there are enough numbers to be claimed to complete the operation.
        if (!AreThereEnoughElementsIntoTheCollection(iterBegin, iterEnd, 2))
        {
            return { std::nullopt, {} };
        }

        // Claim the first parameter based on parameter mode.
        T option;
        if (_parameterModes[0] == ParameterMode::Immediate)
        {
            option = *iterBegin;
        }
        // ParameterMode::Position
        else
        {
            assert(*iterBegin >= 0);
            assert(static_cast<IndexType>(*iterBegin) < _input.size());
            option = _input[*iterBegin];
        }

        // Jump to the next number no matter what the option value is.
        iterBegin++;

        // If zero number then do nothing.
        if (option == 0)
        {
             // Skip the number.
            iterBegin++;
            return { std::make_optional<Result>(), {iterBegin} };
        }

        // Move the instruction pointer to the index pointed by the second number.
        T number;
        if (_parameterModes[1] == ParameterMode::Immediate)
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

        assert(number >= 0);
        assert(static_cast<IndexType>(number) < _input.size() );
        // Update instruction pointer.
        iterBegin = _input.begin() + number;

        // What we return here it is only useful for error reporting.
        // Whatever different than std::nullopt is equal to SUCCESS.
        return { std::make_optional<Result>(), {iterBegin} };
    };

private:
    Vector& _input;
    const ParameterModeVector& _parameterModes;
};
