#pragma once
#include "Cmd.h"

namespace InstructionProcessor
{

/**
* @class Adjust the relative base
* by the value of its only parameter.
*/
class AdjustRelBaseCmd final : public Cmd
{
public:
    AdjustRelBaseCmd() = default;
    ~AdjustRelBaseCmd() override final = default;
    [[nodiscard]] CmdResult Execute() const override final
    {
        return std::nullopt;
    }
};

}