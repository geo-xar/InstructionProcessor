// Copyright 2022 by Georgios Charitos.
// All rights reserved.

#pragma once
#include <MultiplyCmd.h>

namespace InstructionProcessor
{

/**
* @class OpCodeTwo.
*/
class OpCodeTwo final
{
public:
    OpCodeTwo() = default;

    template <typename InputContainerType>
    [[nodiscard]] CmdPtrU Process(InputContainerType& input) const
    {
        return std::make_unique<MultiplyCmd<InputContainerType>>(input);
    }
};

}
