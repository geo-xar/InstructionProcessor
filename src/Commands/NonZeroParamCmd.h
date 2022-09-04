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
class NonZeroParamCmd final : public BasicCmd<InputContainerType>
{
public:
    NonZeroParamCmd(InputContainerType& input) : BasicCmd<InputContainerType>(input) {};
    ~NonZeroParamCmd() override final = default;
    [[nodiscard]] CmdResult Execute() const override final
    {
        // Check if there are enough numbers to be claimed to complete the operation.
        // 2 numbers to be claimed.
        if (!this->_input.AreThereEnoughElementsToBeClaimed(2))
        {
            return std::nullopt;
        }

        return std::nullopt;
    }
};

}
