#pragma once
#include "Cmd.h"
#include <Utils.h>

namespace InstructionProcessor
{

/**
* @class Accumulate 2 numbers and store the result
* in the index pointed by the third number.
*/
template <typename InputContainerType>
class AddCmd final : public BasicCmd<InputContainerType>
{
public:
    AddCmd(InputContainerType& input) : BasicCmd<InputContainerType>(input) {};
    ~AddCmd() override final = default;
    [[nodiscard]] CmdResult Execute() const override final
    {
        // Check if there are enough numbers to be claimed to complete the operation.
        // Numbers to be claimed are 2 for the accumulation and 1 for the index to store the result.
        if (!this->_input.AreThereEnoughElementsToBeClaimed(3))
        {
            return std::nullopt;
        }

        return std::nullopt;
    }
};

}