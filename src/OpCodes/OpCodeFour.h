#pragma once
#include <StoreOutputCmd.h>

namespace InstructionProcessor
{

/**
* @class OpCodeFour.
*/
class OpCodeFour final
{
public:
    OpCodeFour() = default;

    template <typename InputContainerType>
    [[nodiscard]] CmdPtrU Process(InputContainerType& input) const
    {
        return std::make_unique<StoreOutputCmd<InputContainerType>>(input);
    }
};

}
