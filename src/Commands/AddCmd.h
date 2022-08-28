#pragma once
#include "Cmd.h"

namespace InstructionProcessor
{

/**
* @class Accumulate 2 numbers and store the result
* in the index pointed by the third number.
*/
class AddCmd final : public Cmd
{
public:
    AddCmd() = default;
    ~AddCmd() override final = default;
    [[nodiscard]] CmdResult Execute() const override final
    {
        return std::nullopt;
    }
};

}