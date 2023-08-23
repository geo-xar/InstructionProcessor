#pragma once
#include <FirstParamLessThanSecondCmd.h>

namespace InstructionProcessor
{

/**
* @class OpCodeSeven.
*/
class OpCodeSeven final
{
public:
    OpCodeSeven() = default;

    template <typename InputContainerType>
    [[nodiscard]] CmdPtrU Process(InputContainerType& input) const
    {
        return std::make_unique<FirstParamLessThanSecondCmd<InputContainerType>>(input);
    }
};

}
