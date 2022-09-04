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

    [[nodiscard]] CmdPtrU Process() const
    {
        return std::make_unique<FirstParamEqToSecondCmd>();
    }
};

}
