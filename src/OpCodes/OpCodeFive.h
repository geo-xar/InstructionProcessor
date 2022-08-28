#pragma once
#include <OpCode.h>
#include <NonZeroParamCmd.h>

namespace InstructionProcessor
{

/**
* @class OpCodeFive specialisation.
*/
class OpCodeFive final : public OpCode
{
public:
    OpCodeFive() = default;
    ~OpCodeFive() override final = default;

    [[nodiscard]] CmdPtrU Process() const override final
    {
        return std::make_unique<NonZeroParamCmd>();
    }
};

}
