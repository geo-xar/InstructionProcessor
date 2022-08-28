#pragma once
#include <OpCode.h>
#include <ZeroParamCmd.h>

namespace InstructionProcessor
{

/**
* @class OpCodeSix specialisation.
*/
class OpCodeSix final : public OpCode
{
public:
    OpCodeSix() = default;
    ~OpCodeSix() override final = default;

    [[nodiscard]] CmdPtrU Process() const override final
    {
        return std::make_unique<ZeroParamCmd>();
    }
};

}
