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
    * @param iterator User input vector iterator
    *                 which points to the first number to be claimed.
    * @param parameterModes The collection of the parameter modes.
    */
    OpCodeFive(
        Vector& input,
        VectorIterator& iterator,
        const ParameterModeVector& parameterModes)
    : _input{input}
    , _iterator{iterator}
    , _parameterModes{parameterModes}
    {}

    ~OpCodeFive() final = default;

    /**
    * If the first parameter is non-zero then set the instruction pointer to the value from the second parameter.
    * Otherwise do nothing.
    */
    [[nodiscard]] std::optional<Result> Execute() final
    {
        // Check if there are enough numbers to be claimed to complete the operation.
        if (!AreThereEnoughElementsIntoTheCollection(_input, _iterator, 2))
        {
            return std::nullopt;
        }

        // Claim the first parameter based on parameter mode.
        T option;
        if ( _parameterModes[0] == ParameterMode::Immediate )
        {
            option = *_iterator;
        }
        // ParameterMode::Position
        else
        {
            assert(*_iterator >= 0);
            assert(static_cast<size_t>(*_iterator) < _input.size());
            option = _input[*_iterator];
        }

        // Jump to the next number no matter what the option value is.
        _iterator++;

        // If zero number then do nothing.
        if (option == 0)
        {
             // Skip the number.
            _iterator++;
            return std::make_optional<Result>();
        }

        // Move the instruction pointer to the index pointed by the second number.
        T number;
        if ( _parameterModes[1] == ParameterMode::Immediate )
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

        assert( number >= 0);
        assert( static_cast<size_t>(number) < _input.size() );
        // Update instruction pointer.
        _iterator = _input.begin() + number;

        // What we return here it is only useful for error reporting.
        // Whatever different than std::nullopt is equal to SUCCESS.
        return std::make_optional<Result>();
    };

private:
    Vector& _input;
    VectorIterator& _iterator;
    const ParameterModeVector& _parameterModes;
};
