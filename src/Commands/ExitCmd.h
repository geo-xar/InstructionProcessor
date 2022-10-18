// Copyright 2022 by Georgios Charitos.
// All rights reserved.

#pragma once
#include "Cmd.h"

namespace InstructionProcessor
{

/**
* @class The program is finished and should immediately halt.
*/
template <typename InputContainerType>
class ExitCmd final : public Cmd
{
public:
    ExitCmd(InputContainerType& input) : _input{input} {};
    ~ExitCmd() override final = default;
    [[nodiscard]] CmdResult Execute() const override final
    {
        return std::nullopt;
    }

private:
    InputContainerType& _input;
};

}
