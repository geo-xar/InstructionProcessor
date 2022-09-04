#pragma once
#include <StoreInputCmd.h>

namespace InstructionProcessor
{

/**
* @class OpCodeThree.
*/
class OpCodeThree final
{
public:
    OpCodeThree() = default;

    [[nodiscard]] CmdPtrU Process() const
    {
        return std::make_unique<StoreInputCmd>();
    }
};

}
