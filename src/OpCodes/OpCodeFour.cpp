// Copyright 2022 by Georgios Charitos.
// All rights reserved.

template <typename InputType, typename IteratorType, typename GetElementAtFunctionType>
OpCodeFour<InputType, IteratorType, GetElementAtFunctionType>::OpCodeFour(
    GetElementAtFunctionType& getElementAt,
    const ParameterModeVector& parameterModes,
    std::vector<InputType>& printedOutput)
    : _getElementAt{ getElementAt }, _parameterModes{ parameterModes }, _printedOutput{ printedOutput }
{}

template <typename InputType, typename IteratorType, typename GetElementAtFunctionType>
OpCode::ReturnType OpCodeFour<InputType, IteratorType, GetElementAtFunctionType>::Execute(std::any& nextElementIter, std::any& endIter)
{
    IteratorType& iterBegin = std::any_cast<IteratorType&>(nextElementIter);
    IteratorType& iterEnd = std::any_cast<IteratorType&>(endIter);

    // Check if there are enough numbers to be claimed to complete the operation.
    // A single number is needed to be stored in the printed output collection.
    if (!AreThereEnoughElementsIntoTheCollection(iterBegin, iterEnd, 1))
    {
        return { std::nullopt, {} };
    }

    InputType number;
    if (_parameterModes[0] == ParameterMode::Immediate)
    {
        number = *iterBegin;
    }
    else
    {
        number = _getElementAt(iterBegin);
    }

    _printedOutput.emplace_back(number);

    // Jump to the next number (if any).
    iterBegin++;

    // What we return here it is only useful for error reporting.
    // Whatever different than std::nullopt is equal to SUCCESS.
    return { std::make_optional<Result>(), {iterBegin} };
}
