#pragma once
#include <FirstParamEqToSecondCmd.h>

namespace InstructionProcessor
{

/**
* @class OpCodeEight.
*/
class OpCodeEight final
{
public:
    OpCodeEight() = default;

    template <typename InputContainerType>
    [[nodiscard]] CmdPtrU Process(InputContainerType& input) const
    {
        return std::make_unique<FirstParamEqToSecondCmd<InputContainerType>>(input);
    }
};

}
