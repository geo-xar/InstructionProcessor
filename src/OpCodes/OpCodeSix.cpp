// Copyright 2022 by Georgios Charitos.
// All rights reserved.

#include "OpCodeSix.h"

using namespace InstructionProcessor;

template <typename InputType, typename IteratorType, typename GetElementAtFunctionType, typename GetIterFromPosPlusOffsetFunctionType>
OpCodeSix<InputType, IteratorType, GetElementAtFunctionType, GetIterFromPosPlusOffsetFunctionType>::OpCodeSix(
    GetElementAtFunctionType& getElementAt,
    GetIterFromPosPlusOffsetFunctionType& getIterFromPosPlusOffset,
    const ParameterModeVector& parameterModes)
    : _getElementAt{ getElementAt }, _getIterFromPosPlusOffset{ getIterFromPosPlusOffset },
    _parameterModes{ parameterModes }
{}

template <typename InputType, typename IteratorType, typename GetElementAtFunctionType, typename GetIterFromPosPlusOffsetFunctionType>
OpCode::ReturnType OpCodeSix<InputType, IteratorType, GetElementAtFunctionType, GetIterFromPosPlusOffsetFunctionType>::Execute(
    std::any& nextElementIter, std::any& endIter)
{
    IteratorType& iterBegin = std::any_cast<IteratorType&>(nextElementIter);
    IteratorType& iterEnd = std::any_cast<IteratorType&>(endIter);

    // Check if there are enough numbers to be claimed to complete the operation.
    if (!AreThereEnoughElementsIntoTheCollection(iterBegin, iterEnd, 2))
    {
        return { std::nullopt, {} };
    }

    // Claim the first parameter based on parameter mode.
    InputType option;
    if (_parameterModes[0] == ParameterMode::Immediate)
    {
        option = *iterBegin;
    }
    else
    {
        option = _getElementAt(iterBegin);
    }

    // Jump to the next number.
    iterBegin++;

    // If non-zero number then do nothing.
    if (option != 0)
    {
        // Skip the number.
        iterBegin++;
        return { std::make_optional<Result>(), {iterBegin} };
    }

    // Move the instruction pointer to the index pointed by the second number.
    InputType number;
    if (_parameterModes[1] == ParameterMode::Immediate)
    {
        number = *iterBegin;
    }
    // ParameterMode::Position
    else
    {
        number = _getElementAt(iterBegin);
    }

    // Update instruction pointer.
    iterBegin = _getIterFromPosPlusOffset(number);

    // What we return here it is only useful for error reporting.
    // Whatever different than std::nullopt is equal to SUCCESS.
    return { std::make_optional<Result>(), {iterBegin} };
}
