#pragma once
#include "Cmd.h"

namespace InstructionProcessor
{

/**
* @class Adjust the relative base
* by the value of its only parameter.
*/
template <typename InputContainerType>
class AdjustRelBaseCmd final : public BasicCmd<InputContainerType>
{
public:
    AdjustRelBaseCmd(InputContainerType& input) : BasicCmd<InputContainerType>(input) {};
    ~AdjustRelBaseCmd() override final = default;
    [[nodiscard]] CmdResult Execute() const override final
    {
        // Check if there are enough numbers to be claimed to complete the operation.
        // 1 number to be claimed to retrieve the relative base.
        if (!this->_input.AreThereEnoughElementsToBeClaimed(1))
        {
            return std::nullopt;
        }

        return std::nullopt;
    }
};

}
