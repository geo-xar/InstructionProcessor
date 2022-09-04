#pragma once
#include <AdjustRelBaseCmd.h>

namespace InstructionProcessor
{

/**
* @class OpCodeNine.
*/
class OpCodeNine final
{
public:
    OpCodeNine() = default;

    [[nodiscard]] CmdPtrU Process() const
    {
        return std::make_unique<AdjustRelBaseCmd>();
    }
};

}
