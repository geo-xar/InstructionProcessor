#pragma once
#include <ZeroParamCmd.h>

namespace InstructionProcessor
{

/**
* @class OpCodeSix.
*/
class OpCodeSix final
{
public:
    OpCodeSix() = default;

    [[nodiscard]] CmdPtrU Process() const
    {
        return std::make_unique<ZeroParamCmd>();
    }
};

}
