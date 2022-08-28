// Copyright 2022 by Georgios Charitos.
// All rights reserved.

#pragma once
#include <OpCode.h>
#include <AddCmd.h>

namespace InstructionProcessor
{

/**
* @class OpCodeOne specialisation.
*/
class OpCodeOne final : public OpCode
{
public:
    OpCodeOne() = default;
    ~OpCodeOne() override final = default;

    [[nodiscard]] CmdPtrU Process() const override final
    {
        return std::make_unique<AddCmd>();
    }
};

}
