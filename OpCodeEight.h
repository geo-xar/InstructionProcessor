#pragma once

#include "OpCodeInterface.h"
#include "OpCodeProcessorUtils.h"
#include <vector>

/**
* @class OpCodeEight specialisation.
* If the first parameter is equal to the second parameter then
* store 1 in the position given by the third parameter, otherwise store 0.
*/
template <typename T>
class OpCodeEight final : public OpCode
{
using ParameterModeVector = std::vector<ParameterMode>;
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
    OpCodeEight(
        Vector& input,
        VectorIterator& iterator,
        const ParameterModeVector& parameterModes)
    : _input{input}
    , _iterator{iterator}
    , _parameterModes{parameterModes}
    {}

    ~OpCodeEight() final = default;

    /**
    * If the first parameter is equal to the second parameter then
    * store 1 in the position given by the third parameter, otherwise store 0.
    */
    [[nodiscard]] std::optional<Result> Execute() final
    {
        // Check if there are enough numbers to be claimed to complete the operation.
        // Numbers to be claimed are 2 for the comparison and 1 for the index to store the result.
        if ( std::distance(_iterator, _input.end()) < (NumberOfParametersToClaim + 1) )
        {
            return std::nullopt;
        }

        // Claim the numbers to be compared based on the parameter modes.
        Vector claimedComparisonNumbers;
        for (size_t i = 0; i < NumberOfParametersToClaim; i++)
        {
            if ( _parameterModes[i] == ParameterMode::Immediate )
            {
                claimedComparisonNumbers.emplace_back(*_iterator);
            }
            // ParameterMode::Position
            else
            {
                assert(*_iterator >= 0);
                assert(*_iterator < _input.size());
                claimedComparisonNumbers.emplace_back(_input[*_iterator]);
            }
            _iterator++;
        }

        // Claim the index to store the comparison result.
        const auto index = *_iterator;
        assert( (index >= 0) && (index < _input.size()) );

        if (claimedComparisonNumbers[0] == claimedComparisonNumbers[1])
        {
            _input[index] = 1;
        }
        else
        {
            _input[index] = 0;
        }

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
