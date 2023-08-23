#pragma once
#include "Cmd.h"

namespace InstructionProcessor
{

/**
* @class Adjust the relative base
* by the value of its only parameter.
*/
template <typename InputContainerType>
class AdjustRelBaseCmd final : public Cmd
{
public:
    AdjustRelBaseCmd(InputContainerType& input) : _input{input} {};
    ~AdjustRelBaseCmd() override final = default;
    [[nodiscard]] CmdResult Execute() const override final
    {
        // Check if there are enough numbers to be claimed to complete the operation.
        // Numbers to be claimed are:
        // - 1 for the OpCode,
        // - 1 for the relative base.
        if (!this->_input.AreThereEnoughElementsToBeClaimed(2))
        {
            return std::nullopt;
        }

        const auto [mode1, mode2, mode3] = _input.GetModes();

        _input.MoveToTheNextElement();
        _input.UpdateRelativeBase(mode1);

        // What we return here it is only useful for error reporting.
        // Whatever different than std::nullopt is equal to SUCCESS.
        return std::make_optional<Result>();
    }

private:
    InputContainerType& _input;
};

}
