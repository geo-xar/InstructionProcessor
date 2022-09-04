#pragma once
#include <MultiplyCmd.h>

namespace InstructionProcessor
{

/**
* @class OpCodeTwo.
*/
class OpCodeTwo final
{
public:
    OpCodeTwo() = default;

    [[nodiscard]] CmdPtrU Process() const
    {
        return std::make_unique<MultiplyCmd>();
    }
};

}
