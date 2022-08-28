#pragma once
#include "Cmd.h"

namespace InstructionProcessor
{

/**
* @class If the first parameter is less than the second parameter
* then store 1 in the position given by the third parameter,
* otherwise store 0.
*/
class FirstParamLessThanSecondCmd final : public Cmd
{
public:
    FirstParamLessThanSecondCmd() = default;
    ~FirstParamLessThanSecondCmd() override final = default;
    [[nodiscard]] CmdResult Execute() const override final
    {
        return std::nullopt;
    }
};

}