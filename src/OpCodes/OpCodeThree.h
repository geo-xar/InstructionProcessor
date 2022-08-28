#pragma once
#include <OpCode.h>
#include <StoreInputCmd.h>

namespace InstructionProcessor
{

/**
* @class OpCodeThree specialisation.
*/
class OpCodeThree final : public OpCode
{
public:
    OpCodeThree() = default;
    ~OpCodeThree() override final = default;

    [[nodiscard]] CmdPtrU Process() const override final
    {
        return std::make_unique<StoreInputCmd>();
    }
};

}
