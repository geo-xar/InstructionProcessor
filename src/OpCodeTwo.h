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
static constexpr IndexType NumberOfParametersToClaim = 2;

public:
    /**
    * Constructor
    * @param input The user input vector.
    * @param parameterModes The collection of the parameter modes.
    */
    OpCodeTwo(Vector& input, const ParameterModeVector& parameterModes)
    : _input{input}
    , _parameterModes{parameterModes}
    {}

    ~OpCodeTwo() final = default;

    /**
    * Multiply 2 numbers and store the result in the index pointed by the third number.
    */
    [[nodiscard]] OpCode::ReturnType Execute(std::any& nextElementIter, std::any& endIter) final
    {
        VectorIterator& iterBegin = std::any_cast<VectorIterator&>(nextElementIter);
        VectorIterator& iterEnd = std::any_cast<VectorIterator&>(endIter);

        // Check if there are enough numbers to be claimed to complete the operation.
        // Numbers to be claimed are 2 for the accumulation and 1 for the index to store the result.
        if (!AreThereEnoughElementsIntoTheCollection(iterBegin, iterEnd, NumberOfParametersToClaim + 1))
        {
            return { std::nullopt, {} };
        }

        // Claim the numbers to be multiplied based on the parameter modes.
        Vector claimedMultiplyNumbers;
        for (IndexType i = 0; i < NumberOfParametersToClaim; i++)
        {
            if (_parameterModes[i] == ParameterMode::Immediate)
            {
                claimedMultiplyNumbers.emplace_back(*iterBegin);
            }
            // ParameterMode::Position
            else
            {
                assert(*iterBegin >= 0);
                assert(static_cast<IndexType>(*iterBegin) < _input.size());
                claimedMultiplyNumbers.emplace_back(_input[*iterBegin]);
            }
            iterBegin++;
        }

        // Claim the index to store the multiplication result.
        const auto index = *iterBegin;
        assert( (index >= 0) && (static_cast<IndexType>(index) < _input.size()) );
        _input[index] = claimedMultiplyNumbers[0] * claimedMultiplyNumbers[1];

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
