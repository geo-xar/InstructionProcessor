#pragma once

#include "OpCodeInterface.h"
#include "OpCodeProcessorUtils.h"
#include <vector>

/**
* @class OpCodeSeven specialisation.
* If the first parameter is less than the second parameter then
* store 1 in the position given by the third parameter, otherwise store 0.
*/
template <typename T>
class OpCodeSeven final : public OpCode
{
using Vector = std::vector<T>;
using VectorIterator = typename Vector::iterator;
static constexpr IndexType NumberOfParametersToClaim = 2;

public:
    /**
    * Constructor
    * @param input The user input vector.
    * @param parameterModes The collection of the parameter modes.
    */
    OpCodeSeven(
        Vector& input, const ParameterModeVector& parameterModes)
    : _input{input}
    , _parameterModes{parameterModes}
    {}

    ~OpCodeSeven() final = default;

    /**
    * If the first parameter is less than the second parameter then
    * store 1 in the position given by the third parameter, otherwise store 0.
    */
    [[nodiscard]] OpCode::ReturnType Execute(std::any& nextElementIter, std::any& endIter) final
    {
        VectorIterator& iterBegin = std::any_cast<VectorIterator&>(nextElementIter);
        VectorIterator& iterEnd = std::any_cast<VectorIterator&>(endIter);

        // Check if there are enough numbers to be claimed to complete the operation.
        // Numbers to be claimed are 2 for the comparison and 1 for the index to store the result.
        if (!AreThereEnoughElementsIntoTheCollection(iterBegin, iterEnd, NumberOfParametersToClaim + 1))
        {
            return { std::nullopt, {} };
        }

        // Claim the numbers to be compared based on the parameter modes.
        Vector claimedComparisonNumbers;
        for (IndexType i = 0; i < NumberOfParametersToClaim; i++)
        {
            if (_parameterModes[i] == ParameterMode::Immediate)
            {
                claimedComparisonNumbers.emplace_back(*iterBegin);
            }
            // ParameterMode::Position
            else
            {
                assert(*iterBegin >= 0);
                assert(static_cast<IndexType>(*iterBegin) < _input.size());
                claimedComparisonNumbers.emplace_back(_input[*iterBegin]);
            }
            iterBegin++;
        }

        // Claim the index to store the comparison result.
        const auto index = static_cast<IndexType>(*iterBegin);
        assert( (index >= 0) && (index < _input.size()) );

        if (claimedComparisonNumbers[0] < claimedComparisonNumbers[1])
        {
            _input[index] = 1;
        }
        else
        {
            _input[index] = 0;
        }

        // Jump to the next number (if any).
        iterBegin++;

        // What we return here it is only useful for error reporting.
        // Whatever different than std::nullopt is equal to SUCCESS.
        return { std::make_optional<Result>(), {iterBegin} };
    };

private:
    Vector& _input;
    const ParameterModeVector& _parameterModes;
};
