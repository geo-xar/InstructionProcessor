#pragma once
#include "Cmd.h"

namespace InstructionProcessor
{

/**
* @class Claim a number and store it
* in the printed output collection.
*/
class StoreOutputCmd final : public Cmd
{
public:
    StoreOutputCmd() = default;
    ~StoreOutputCmd() override final = default;
    [[nodiscard]] CmdResult Execute() const override final
    {
        return std::nullopt;
    }
};

}