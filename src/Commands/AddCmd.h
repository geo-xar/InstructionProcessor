#pragma once
#include "Cmd.h"

namespace InstructionProcessor
{

/**
* @class Accumulate 2 numbers and store the result
* in the index pointed by the third number.
*/
template <typename InputContainerType>
class AddCmd final : public Cmd
{
public:
    AddCmd(InputContainerType& input) : _input{input} {};
    ~AddCmd() override final = default;
    [[nodiscard]] CmdResult Execute() const override final
    {
        // Check if there are enough numbers to be claimed to complete the operation.
        // Numbers to be claimed are:
        // - 1 for the OpCode,
        // - 2 for the accumulation,
        // - 1 for the index to store the result.
        if (!_input.AreThereEnoughElementsToBeClaimed(4))
        {
            return std::nullopt;
        }

        const auto [mode1, mode2, mode3] = _input.GetModes();

        // Get first number.
        _input.MoveToTheNextElement();
        const auto firstNumber = _input.GetCurrentElementValue(mode1);
        // Get second number
        _input.MoveToTheNextElement();
        const auto secondNumber = _input.GetCurrentElementValue(mode2);

        // Store the accumulation result.
        _input.MoveToTheNextElement();
        _input.StoreElement(firstNumber + secondNumber, mode3);
        _input.MoveToTheNextElement();

        // What we return here it is only useful for error reporting.
        // Whatever different than std::nullopt is equal to SUCCESS.
        return std::make_optional<Result>();
    }

private:
    InputContainerType& _input;
};

}
