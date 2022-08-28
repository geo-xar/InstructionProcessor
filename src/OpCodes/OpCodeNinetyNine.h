#pragma once
#include <OpCode.h>
#include <ExitCmd.h>

namespace InstructionProcessor
{

/**
* @class OpCodeNinetyNine specialisation.
*/
class OpCodeNinetyNine final : public OpCode
{
public:
    OpCodeNinetyNine() = default;
    ~OpCodeNinetyNine() override final = default;

    [[nodiscard]] CmdPtrU Process() const override final
    {
        return std::make_unique<ExitCmd>();
    }
};

}
