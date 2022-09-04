#pragma once
#include "Cmd.h"

namespace InstructionProcessor
{

/**
* @class Multiply command specialisation.
* Multiply 2 numbers and store the result in the index
* pointed by the third number.
*/
template <typename InputContainerType>
class MultiplyCmd final : public BasicCmd<InputContainerType>
{
public:
    MultiplyCmd(InputContainerType& input) : BasicCmd<InputContainerType>(input) {};
    ~MultiplyCmd() override final = default;
    [[nodiscard]] CmdResult Execute() const override final
    {
        // Check if there are enough numbers to be claimed to complete the operation.
        // Numbers to be claimed are 2 for the multiplication and 1 for the index to store the result.
        if (!this->_input.AreThereEnoughElementsToBeClaimed(3))
        {
            return std::nullopt;
        }

        return std::nullopt;
    }
};

}
