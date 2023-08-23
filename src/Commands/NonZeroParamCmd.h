#pragma once
#include "Cmd.h"

namespace InstructionProcessor
{

/**
* @class If the first parameter is non-zero then
* set the instruction pointer to the value from the second parameter.
* Otherwise do nothing.
*/
template <typename InputContainerType>
class NonZeroParamCmd final : public Cmd
{
public:
    NonZeroParamCmd(InputContainerType& input) : _input{input} {};
    ~NonZeroParamCmd() override final = default;
    [[nodiscard]] CmdResult Execute() const override final
    {
        // Check if there are enough numbers to be claimed to complete the operation.
        // Numbers to be claimed are:
        // - 1 for the OpCode,
        // - 1 for the parameter to check if it is a non-zero one,
        // - 1 for the index to set the instruction pointer. 
        if (!_input.AreThereEnoughElementsToBeClaimed(3))
        {
            return std::nullopt;
        }

        const auto [mode1, mode2, mode3] = _input.GetModes();

        // Get number.
        _input.MoveToTheNextElement();
        const auto number = _input.GetCurrentElementValue(mode1);

        _input.MoveToTheNextElement();
        if (number != 0)
        {
            // set the instruction pointer to the value from the second number
            _input.UpdateCurrentElementIndex(mode2);
        }
        else
        {
            _input.MoveToTheNextElement();
        }

        // What we return here it is only useful for error reporting.
        // Whatever different than std::nullopt is equal to SUCCESS.
        return std::make_optional<Result>();
    }

private:
    InputContainerType& _input;
};

}
