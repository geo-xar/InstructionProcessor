#pragma once
#include <AdjustRelBaseCmd.h>

namespace InstructionProcessor
{

/**
* @class OpCodeNine.
*/
class OpCodeNine final
{
public:
    OpCodeNine() = default;

    template <typename InputContainerType>
    [[nodiscard]] CmdPtrU Process(InputContainerType& input) const
    {
        return std::make_unique<AdjustRelBaseCmd<InputContainerType>>(input);
    }
};

}
