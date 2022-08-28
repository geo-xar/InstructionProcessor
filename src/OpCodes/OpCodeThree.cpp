// Copyright 2022 by Georgios Charitos.
// All rights reserved.

template <typename InputType, typename IteratorType, typename SetElementAtIndexFunctionType>
OpCodeThree<InputType, IteratorType, SetElementAtIndexFunctionType>::OpCodeThree(
    SetElementAtIndexFunctionType& setElementAtIndex, const std::optional<InputType>& userInput)
    : _setElementAtIndex{ setElementAtIndex }, _userInput{ userInput }
{}

template <typename InputType, typename IteratorType, typename SetElementAtIndexFunctionType>
OpCode::ReturnType OpCodeThree<InputType, IteratorType, SetElementAtIndexFunctionType>::Execute(std::any& nextElementIter, std::any& endIter)
{
    IteratorType& iterBegin = std::any_cast<IteratorType&>(nextElementIter);
    IteratorType& iterEnd = std::any_cast<IteratorType&>(endIter);

    // Check if there are enough numbers to be claimed to complete the operation.
    // A single number is needed (index) to store the user input.
    if (!AreThereEnoughElementsIntoTheCollection(iterBegin, iterEnd, 1))
    {
        return { std::nullopt, {} };
    }

    // Store the user input value.
    assert(_userInput.has_value());
    _setElementAtIndex(*iterBegin, _userInput.value());

    // Jump to the next number (if any).
    iterBegin++;

    // What we return here it is only useful for error reporting.
    // Whatever different than std::nullopt is equal to SUCCESS.
    return { std::make_optional<Result>(), {iterBegin} };
}
