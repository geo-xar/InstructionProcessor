#pragma once
#include "Cmd.h"

namespace InstructionProcessor
{

/**
* @class If the first parameter is equal to the second parameter
* then store 1 in the position given by the third parameter,
* otherwise store 0.
*/
class FirstParamEqToSecondCmd final : public Cmd
{
public:
    FirstParamEqToSecondCmd() = default;
    ~FirstParamEqToSecondCmd() override final = default;
    [[nodiscard]] CmdResult Execute() const override final
    {
        return std::nullopt;
    }
};

}