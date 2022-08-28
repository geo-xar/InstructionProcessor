#pragma once
#include "Cmd.h"

namespace InstructionProcessor
{

/**
* @class Multiply command specialisation.
* Multiply 2 numbers and store the result in the index
* pointed by the third number.
*/
class MultiplyCmd final : public Cmd
{
public:
    MultiplyCmd() = default;
    ~MultiplyCmd() override final = default;
    [[nodiscard]] CmdResult Execute() const override final
    {
        return std::nullopt;
    }
};

}