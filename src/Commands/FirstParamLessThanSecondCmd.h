#pragma once
#include "Cmd.h"

namespace InstructionProcessor
{

/**
* @class If the first parameter is less than the second parameter
* then store 1 in the position given by the third parameter,
* otherwise store 0.
*/
template <typename InputContainerType>
class FirstParamLessThanSecondCmd final : public BasicCmd<InputContainerType>
{
public:
    FirstParamLessThanSecondCmd(InputContainerType& input) : BasicCmd<InputContainerType>(input) {};
    ~FirstParamLessThanSecondCmd() override final = default;
    [[nodiscard]] CmdResult Execute() const override final
    {
        // Check if there are enough numbers to be claimed to complete the operation.
        // Numbers to be claimed are 2 for the condition check and 1 for the index to store the result.
        if (!this->_input.AreThereEnoughElementsToBeClaimed(3))
        {
            return std::nullopt;
        }

        return std::nullopt;
    }
};

}
