// Copyright 2022 by Georgios Charitos.
// All rights reserved.

#pragma once
#include <NonZeroParamCmd.h>

namespace InstructionProcessor
{

/**
* @class OpCodeFive.
*/
class OpCodeFive final
{
public:
    OpCodeFive() = default;

    template <typename InputContainerType>
    [[nodiscard]] CmdPtrU Process(InputContainerType& input) const
    {
        return std::make_unique<NonZeroParamCmd<InputContainerType>>(input);
    }
};

}
