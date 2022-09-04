#pragma once
#include "Cmd.h"

namespace InstructionProcessor
{

/**
* @class Store input command specialisation.
* Claim a number and store the user input value
* to the index which it points to.
*/
template <typename InputContainerType>
class StoreInputCmd final : public BasicCmd<InputContainerType>
{
public:
    StoreInputCmd(InputContainerType& input) : BasicCmd<InputContainerType>(input) {};
    ~StoreInputCmd() override final = default;
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