#pragma once
#include <NonZeroParamCmd.h>

namespace InstructionProcessor
{

/**
* @class OpCodeFive.
*/
class OpCodeFive final
{
public:
    OpCodeFive() = default;

    [[nodiscard]] CmdPtrU Process() const
    {
        return std::make_unique<NonZeroParamCmd>();
    }
};

}
