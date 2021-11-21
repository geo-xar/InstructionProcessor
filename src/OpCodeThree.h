#pragma once

#include "OpCodeInterface.h"
#include "OpCodeProcessorUtils.h"

namespace InstructionProcessor
{

/**
* @class OpCodeThree specialisation.
* Claim a number and store the user input value to the index which it points to.
*/
template <typename InputType, typename IteratorType, typename SetElementAtIndexFunctionType>
class OpCodeThree final : public OpCode
{
public:
    /**
    * Constructor
    * @param setElementAtIndex Function to store an element to the given index.
    * @param userInput User selection optional.
    */
    OpCodeThree(SetElementAtIndexFunctionType &setElementAtIndex, const std::optional<InputType> &userInput)
            : _setElementAtIndex{setElementAtIndex}, _userInput{userInput}
    {}

    ~OpCodeThree() final = default;

    /**
    * Claim a number and store the user input value to the index which it points to.
    */
    [[nodiscard]] OpCode::ReturnType Execute(std::any &nextElementIter, std::any &endIter) final
    {
        IteratorType &iterBegin = std::any_cast<IteratorType &>(nextElementIter);
        IteratorType &iterEnd = std::any_cast<IteratorType &>(endIter);

        // Check if there are enough numbers to be claimed to complete the operation.
        // A single number is needed (index) to store the user input.
        if (!AreThereEnoughElementsIntoTheCollection(iterBegin, iterEnd, 1))
        {
            return {std::nullopt, {}};
        }

        // Store the user input value.
        assert(_userInput.has_value());
        _setElementAtIndex(*iterBegin, _userInput.value());

        // Jump to the next number (if any).
        iterBegin++;

        // What we return here it is only useful for error reporting.
        // Whatever different than std::nullopt is equal to SUCCESS.
        return {std::make_optional<Result>(), {iterBegin}};
    }

private:
    SetElementAtIndexFunctionType &_setElementAtIndex;
    const std::optional<InputType> &_userInput;
};

}
