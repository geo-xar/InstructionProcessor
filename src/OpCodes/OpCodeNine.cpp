// Copyright 2022 by Georgios Charitos.
// All rights reserved.

template <typename InputType, typename IteratorType, typename GetElementAtType, typename UpdateRelativeBaseType>
OpCodeNine<InputType, IteratorType, GetElementAtType, UpdateRelativeBaseType>::OpCodeNine(
    GetElementAtType& getElementAt,
    UpdateRelativeBaseType& updateRelativeBase,
    const ParameterModeVector& parameterModes)
    : _getElementAt{ getElementAt }, _updateRelativeBase{ updateRelativeBase }, _parameterModes{ parameterModes }
{}

template <typename InputType, typename IteratorType, typename GetElementAtType, typename UpdateRelativeBaseType>
OpCode::ReturnType OpCodeNine<InputType, IteratorType, GetElementAtType, UpdateRelativeBaseType>::Execute(
    std::any& nextElementIter, std::any& endIter)
{
    IteratorType& iterBegin = std::any_cast<IteratorType&>(nextElementIter);
    IteratorType& iterEnd = std::any_cast<IteratorType&>(endIter);

    // Check if there are enough numbers to be claimed to complete the operation.
    // A single number is needed to retrieve the relative base.
    if (!AreThereEnoughElementsIntoTheCollection(iterBegin, iterEnd, 1))
    {
        return { std::nullopt, {} };
    }

    InputType newRelativeBase{ 0 };
    if (_parameterModes[0] == ParameterMode::Immediate)
    {
        newRelativeBase = *iterBegin;
    }
    else
    {
        newRelativeBase = _getElementAt(iterBegin);
    }

    _updateRelativeBase(newRelativeBase);

    // Jump to the next number (if any).
    iterBegin++;

    // What we return here it is only useful for error reporting.
    // Whatever different than std::nullopt is equal to SUCCESS.
    return { std::make_optional<Result>(), {iterBegin} };
}
