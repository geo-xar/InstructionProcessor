#pragma once
#include <OpCode.h>
#include <FirstParamEqToSecondCmd.h>

namespace InstructionProcessor
{

/**
* @class OpCodeEight specialisation.
*/
class OpCodeEight final : public OpCode
{
public:
    OpCodeEight() = default;
    ~OpCodeEight() override final = default;

    [[nodiscard]] CmdPtrU Process() const override final
    {
        return std::make_unique<FirstParamEqToSecondCmd>();
    }
};

}
