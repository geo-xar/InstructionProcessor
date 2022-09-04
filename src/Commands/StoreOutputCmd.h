#pragma once
#include "Cmd.h"

namespace InstructionProcessor
{

/**
* @class Claim a number and store it
* in the printed output collection.
*/
template <typename InputContainerType>
class StoreOutputCmd final : public Cmd
{
public:
    StoreOutputCmd(InputContainerType& input) : BasicCmd<InputContainerType>(input) {};
    ~StoreOutputCmd() override final = default;
    [[nodiscard]] CmdResult Execute() const override final
    {
        // Check if there are enough numbers to be claimed to complete the operation.
        // 1 number to be claimed.
        if (!this->_input.AreThereEnoughElementsToBeClaimed(1))
        {
            return std::nullopt;
        }

        return std::nullopt;
    }
};

}
