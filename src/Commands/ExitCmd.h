#pragma once
#include "Cmd.h"

namespace InstructionProcessor
{

/**
* @class The program is finished and should immediately halt.
*/
class ExitCmd final : public Cmd
{
public:
    ExitCmd() = default;
    ~ExitCmd() override final = default;
    [[nodiscard]] CmdResult Execute() const override final
    {
        return std::nullopt;
    }
};

}