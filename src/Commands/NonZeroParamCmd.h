#pragma once
#include "Cmd.h"

namespace InstructionProcessor
{

/**
* @class If the first parameter is non-zero then
* set the instruction pointer to the value from the second parameter.
* Otherwise do nothing.
*/
class NonZeroParamCmd final : public Cmd
{
public:
    NonZeroParamCmd() = default;
    ~NonZeroParamCmd() override final = default;
    [[nodiscard]] CmdResult Execute() const override final
    {
        return std::nullopt;
    }
};

}