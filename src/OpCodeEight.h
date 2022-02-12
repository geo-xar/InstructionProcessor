#pragma once

#include "OpCodeInterface.h"
#include "OpCodeProcessorUtils.h"

namespace InstructionProcessor
{

/**
* @class OpCodeEight specialisation.
* If the first parameter is equal to the second parameter then
* store 1 in the position given by the third parameter, otherwise store 0.
*/
template <typename InputType, typename IteratorType, typename SetElementAtIndexFunctionType, typename GetElementAtFunctionType>
class OpCodeEight final : public OpCode
{
    static constexpr IndexType NumberOfParametersToClaim = 2;

public:
    /**
    * Constructor
    * @param setElementAtIndex Function to store an element to the given index.
    * @param getElementAt Function to retrieve an element given an iterator.
    * @param parameterModes The collection of the parameter modes.
    */
    OpCodeEight(
            SetElementAtIndexFunctionType &setElementAtIndex,
            GetElementAtFunctionType &getElementAt,
            const ParameterModeVector &parameterModes)
            : _setElementAtIndex{setElementAtIndex}, _getElementAt{getElementAt}, _parameterModes{parameterModes}
    {}

    ~OpCodeEight() final = default;

    /**
    * If the first parameter is equal to the second parameter then
    * store 1 in the position given by the third parameter, otherwise store 0.
    */
    [[nodiscard]] OpCode::ReturnType Execute(std::any &nextElementIter, std::any &endIter) final
    {
        IteratorType &iterBegin = std::any_cast<IteratorType &>(nextElementIter);
        IteratorType &iterEnd = std::any_cast<IteratorType &>(endIter);

        // Check if there are enough numbers to be claimed to complete the operation.
        // Numbers to be claimed are 2 for the comparison and 1 for the index to store the result.
        if (!AreThereEnoughElementsIntoTheCollection(iterBegin, iterEnd, NumberOfParametersToClaim + 1))
        {
            return {std::nullopt, {}};
        }

        // Claim the numbers to be compared based on the parameter modes.
        std::vector<InputType> claimedComparisonNumbers;
        for (IndexType i = 0; i < NumberOfParametersToClaim; i++)
        {
            if (_parameterModes[i] == ParameterMode::Immediate)
            {
                claimedComparisonNumbers.emplace_back(*iterBegin);
            }
            else if (_parameterModes[i] == ParameterMode::Position)
            {
                claimedComparisonNumbers.emplace_back(_getElementAt(iterBegin));
            }
            // ParameterMode::Relative
            else
            {

            }
            iterBegin++;
        }

        if (claimedComparisonNumbers[0] == claimedComparisonNumbers[1])
        {
            _setElementAtIndex(*iterBegin, 1);
        }
        else
        {
            _setElementAtIndex(*iterBegin, 0);
        }

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
