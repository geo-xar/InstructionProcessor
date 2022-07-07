#pragma once
#include <InstructionProcessorUtils.h>
#include <OpCodeInterface.h>

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
    OpCodeThree(SetElementAtIndexFunctionType &setElementAtIndex, const std::optional<InputType> &userInput);

    ~OpCodeThree() final = default;

    /**
    * Claim a number and store the user input value to the index which it points to.
    */
    [[nodiscard]] OpCode::ReturnType Execute(std::any &nextElementIter, std::any &endIter) final;

private:
    SetElementAtIndexFunctionType &_setElementAtIndex;
    const std::optional<InputType> &_userInput;
};

}
