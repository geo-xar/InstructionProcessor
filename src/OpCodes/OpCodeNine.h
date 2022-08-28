#pragma once
#include <OpCode.h>
#include <AdjustRelBaseCmd.h>

namespace InstructionProcessor
{

/**
* @class OpCodeNine specialisation.
*/
class OpCodeNine final : public OpCode
{
public:
    OpCodeNine() = default;
    ~OpCodeNine() override final = default;

    [[nodiscard]] CmdPtrU Process() const override final
    {
        return std::make_unique<AdjustRelBaseCmd>();
    }
};

}
