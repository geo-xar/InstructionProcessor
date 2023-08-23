#pragma once
#include <AddCmd.h>

namespace InstructionProcessor
{

/**
* @class OpCodeOne.
*/
class OpCodeOne final
{
public:
    OpCodeOne() = default;

    template <typename InputContainerType>
    [[nodiscard]] CmdPtrU Process(InputContainerType& input) const
    {
        return std::make_unique<AddCmd<InputContainerType>>(input);
    }
};

}
