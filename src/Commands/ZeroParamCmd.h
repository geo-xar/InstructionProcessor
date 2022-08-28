#pragma once
#include "Cmd.h"

namespace InstructionProcessor
{

/**
* @class If the first parameter is zero then
* set the instruction pointer to the value from the second parameter.
* Otherwise do nothing.
*/
class ZeroParamCmd final : public Cmd
{
public:
    ZeroParamCmd() = default;
    ~ZeroParamCmd() override final = default;
    [[nodiscard]] CmdResult Execute() const override final
    {
        return std::nullopt;
    }
};

}