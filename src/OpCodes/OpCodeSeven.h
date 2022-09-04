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

    [[nodiscard]] CmdPtrU Process() const
    {
        return std::make_unique<FirstParamLessThanSecondCmd>();
    }
};

}
