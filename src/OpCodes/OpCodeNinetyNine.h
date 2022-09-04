#pragma once
#include <ExitCmd.h>

namespace InstructionProcessor
{

/**
* @class OpCodeNinetyNine.
*/
class OpCodeNinetyNine final
{
public:
    OpCodeNinetyNine() = default;

    [[nodiscard]] CmdPtrU Process() const
    {
        return std::make_unique<ExitCmd>();
    }
};

}
