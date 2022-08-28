#pragma once
#include <OpCode.h>
#include <MultiplyCmd.h>

namespace InstructionProcessor
{

/**
* @class OpCodeTwo specialisation.
*/
class OpCodeTwo final : public OpCode
{
public:
    OpCodeTwo() = default;
    ~OpCodeTwo() override final = default;

    [[nodiscard]] CmdPtrU Process() const override final
    {
        return std::make_unique<MultiplyCmd>();
    }
};

}
