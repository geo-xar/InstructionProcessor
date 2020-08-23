#pragma once

#include "OpCodeInterface.h"
#include "OpCodeProcessorUtils.h"
#include <vector>

/**
* @class OpCodeTwo specialisation.
* Multiply 2 numbers.
*/
template <typename T>
class OpCodeTwo final : public OpCode
{
using Vector = std::vector<T>;
using VectorIterator = typename Vector::iterator;
static const size_t NumberOfParametersToClaim = 2;

public:
    /**
    * Constructor
    * @param input The user input vector.
    * @param iterator User input vector iterator
    *                 which points to the first number to be claimed.
    * @param parameterModes The collection of the parameter modes.
    */
    OpCodeTwo(
        Vector& input,
        VectorIterator& iterator,
        const ParameterModeVector& parameterModes)
    : _input{input}
    , _iterator{iterator}
    , _parameterModes{parameterModes}
    {}

    ~OpCodeTwo() final = default;

    /**
    * Multiply 2 numbers and store the result in the index pointed by the third number.
    */
    [[nodiscard]] std::optional<Result> Execute() final
    {
        // Check if there are enough numbers to be claimed to complete the operation.
        // Numbers to be claimed are 2 for the accumulation and 1 for the index to store the result.
        if (!AreThereEnoughElementsIntoTheCollection(_input, _iterator, NumberOfParametersToClaim + 1))
        {
            return std::nullopt;
        }

        // Claim the numbers to be multiplied based on the parameter modes.
        Vector claimedMultiplyNumbers;
        for (size_t i = 0; i < NumberOfParametersToClaim; i++)
        {
            if ( _parameterModes[i] == ParameterMode::Immediate )
            {
                claimedMultiplyNumbers.emplace_back(*_iterator);
            }
            // ParameterMode::Position
            else
            {
                assert(*_iterator >= 0);
                assert(static_cast<size_t>(*_iterator) < _input.size());
                claimedMultiplyNumbers.emplace_back(_input[*_iterator]);
            }
            _iterator++;
        }

        // Claim the index to store the multiplication result.
        const auto index = *_iterator;
        assert( (index >= 0) && (static_cast<size_t>(index) < _input.size()) );
        _input[index] = claimedMultiplyNumbers[0] * claimedMultiplyNumbers[1];

        // Jump to the next number (if any).
        _iterator++;

        // What we return here it is only useful for error reporting.
        // Whatever different than std::nullopt is equal to SUCCESS.
        return std::make_optional<Result>();
    };

private:
    Vector& _input;
    VectorIterator& _iterator;
    const ParameterModeVector& _parameterModes;
};
