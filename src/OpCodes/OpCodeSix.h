// Copyright 2022 by Georgios Charitos.
// All rights reserved.

#pragma once
#include <ZeroParamCmd.h>

namespace InstructionProcessor
{

/**
* @class OpCodeSix.
*/
class OpCodeSix final
{
public:
    OpCodeSix() = default;

    template <typename InputContainerType>
    [[nodiscard]] CmdPtrU Process(InputContainerType& input) const
    {
        return std::make_unique<ZeroParamCmd<InputContainerType>>(input);
    }
};

}
