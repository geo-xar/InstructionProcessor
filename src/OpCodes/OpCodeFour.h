#pragma once
#include <StoreOutputCmd.h>

namespace InstructionProcessor
{

/**
* @class OpCodeFour.
*/
class OpCodeFour final
{
public:
    OpCodeFour() = default;

    [[nodiscard]] CmdPtrU Process() const
    {
        return std::make_unique<StoreOutputCmd>();
    }
};

}
