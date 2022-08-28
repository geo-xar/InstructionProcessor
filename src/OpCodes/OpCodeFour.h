#pragma once
#include <OpCode.h>
#include <StoreOutputCmd.h>

namespace InstructionProcessor
{

/**
* @class OpCodeFour specialisation.
*/
class OpCodeFour final : public OpCode
{
public:
    OpCodeFour() = default;
    ~OpCodeFour() override final = default;

    [[nodiscard]] CmdPtrU Process() const override final
    {
        return std::make_unique<StoreOutputCmd>();
    }
};

}
