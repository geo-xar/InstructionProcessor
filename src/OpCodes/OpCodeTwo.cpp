// Copyright 2022 by Georgios Charitos.
// All rights reserved.

#include "OpCodeTwo.h"

using namespace InstructionProcessor;

template <typename InputType, typename IteratorType, typename SetElementAtIndexFunctionType, typename GetElementAtFunctionType>
OpCodeTwo<InputType, IteratorType, SetElementAtIndexFunctionType, GetElementAtFunctionType>::OpCodeTwo(
    SetElementAtIndexFunctionType& setElementAtIndex,
    GetElementAtFunctionType& getElementAt,
    const ParameterModeVector& parameterModes)
    : _setElementAtIndex{ setElementAtIndex }, _getElementAt{ getElementAt }, _parameterModes{ parameterModes }
{}

template <typename InputType, typename IteratorType, typename SetElementAtIndexFunctionType, typename GetElementAtFunctionType>
OpCode::ReturnType OpCodeTwo<InputType, IteratorType, SetElementAtIndexFunctionType, GetElementAtFunctionType>::Execute(std::any& nextElementIter, std::any& endIter)
{
    IteratorType& iterBegin = std::any_cast<IteratorType&>(nextElementIter);
    IteratorType& iterEnd = std::any_cast<IteratorType&>(endIter);

    // Check if there are enough numbers to be claimed to complete the operation.
    // Numbers to be claimed are 2 for the accumulation and 1 for the index to store the result.
    if (!AreThereEnoughElementsIntoTheCollection(iterBegin, iterEnd, NumberOfParametersToClaim + 1))
    {
        return { std::nullopt, {} };
    }

    // Claim the numbers to be multiplied based on the parameter modes.
    std::vector<InputType> claimedMultiplyNumbers;
    for (IndexType i = 0; i < NumberOfParametersToClaim; i++)
    {
        if (_parameterModes[i] == ParameterMode::Immediate)
        {
            claimedMultiplyNumbers.emplace_back(*iterBegin);
        }
        else if (_parameterModes[i] == ParameterMode::Position)
        {
            claimedMultiplyNumbers.emplace_back(_getElementAt(iterBegin));
        }
        // ParameterMode::Relative
        else
        {
            claimedMultiplyNumbers.emplace_back(_getElementAt(iterBegin, {}));
        }
        iterBegin++;
    }

    // Store the multiplication result.
    _setElementAtIndex(*iterBegin, claimedMultiplyNumbers[0] * claimedMultiplyNumbers[1]);

    // Jump to the next number (if any).
    iterBegin++;

    // What we return here it is only useful for error reporting.
    // Whatever different than std::nullopt is equal to SUCCESS.
    return { std::make_optional<Result>(), {iterBegin} };
}
