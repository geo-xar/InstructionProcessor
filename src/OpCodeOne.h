#pragma once

#include "OpCodeInterface.h"
#include "OpCodeProcessorUtils.h"

namespace InstructionProcessor
{

/**
* @class OpCodeOne specialisation.
* Accumulate 2 numbers.
*/
template <typename InputType, typename IteratorType, typename SetElementAtIndexFunctionType, typename GetElementAtFunctionType>
class OpCodeOne final : public OpCode
{
    static constexpr IndexType NumberOfParametersToClaim = 2;

public:
    /**
    * Constructor
    * @param setElementAtIndex Function to store an element to the given index.
    * @param getElementAt Function to retrieve an element given an iterator.
    * @param parameterModes The collection of the parameter modes.
    */
    OpCodeOne(
            SetElementAtIndexFunctionType &setElementAtIndex,
            GetElementAtFunctionType &getElementAt,
            const ParameterModeVector &parameterModes)
            : _setElementAtIndex{setElementAtIndex}, _getElementAt{getElementAt}, _parameterModes{parameterModes}
    {}

    ~OpCodeOne() final = default;

    /**
    * Accumulate 2 numbers and store the result in the index pointed by the third number.
    */
    [[nodiscard]] OpCode::ReturnType Execute(std::any &nextElementIter, std::any &endIter) final
    {
        IteratorType &iterBegin = std::any_cast<IteratorType &>(nextElementIter);
        IteratorType &iterEnd = std::any_cast<IteratorType &>(endIter);

        // Check if there are enough numbers to be claimed to complete the operation.
        // Numbers to be claimed are 2 for the accumulation and 1 for the index to store the result.
        if (!AreThereEnoughElementsIntoTheCollection(iterBegin, iterEnd, NumberOfParametersToClaim + 1))
        {
            return {std::nullopt, {}};
        }

        // Claim the numbers to be accumulated based on the parameter modes.
        std::vector<InputType> claimedAccumulationNumbers;
        for (IndexType i = 0; i < NumberOfParametersToClaim; i++)
        {
            if (_parameterModes[i] == ParameterMode::Immediate)
            {
                claimedAccumulationNumbers.emplace_back(*iterBegin);
            }
            else if (_parameterModes[i] == ParameterMode::Position)
            {
                claimedAccumulationNumbers.emplace_back(_getElementAt(iterBegin));
            }
            // ParameterMode::Relative
            else
            {

            }
            iterBegin++;
        }

        // Store the accumulation result.
        _setElementAtIndex(*iterBegin, claimedAccumulationNumbers[0] + claimedAccumulationNumbers[1]);

        // Jump to the next number (if any).
        iterBegin++;

        // What we return here it is only useful for error reporting.
        // Whatever different than std::nullopt is equal to SUCCESS.
        return {std::make_optional<Result>(), {iterBegin}};
    }

private:
    SetElementAtIndexFunctionType &_setElementAtIndex;
    GetElementAtFunctionType &_getElementAt;
    const ParameterModeVector &_parameterModes;
};

}
