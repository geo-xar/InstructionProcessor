#pragma once
#include <OpCode.h>
#include <FirstParamLessThanSecondCmd.h>

namespace InstructionProcessor
{

/**
* @class OpCodeSeven specialisation.
*/
class OpCodeSeven final : public OpCode
{
public:
    OpCodeSeven() = default;
    ~OpCodeSeven() override final = default;

    [[nodiscard]] CmdPtrU Process() const override final
    {
        return std::make_unique<FirstParamLessThanSecondCmd>();
    }
};

}
