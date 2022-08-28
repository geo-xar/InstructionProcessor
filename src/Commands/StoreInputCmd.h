#pragma once
#include "Cmd.h"

namespace InstructionProcessor
{

/**
* @class Store input command specialisation.
* Claim a number and store the user input value
* to the index which it points to.
*/
class StoreInputCmd final : public Cmd
{
public:
    StoreInputCmd() = default;
    ~StoreInputCmd() override final = default;
    [[nodiscard]] CmdResult Execute() const override final
    {
        return std::nullopt;
    }
};

}