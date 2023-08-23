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

    template <typename InputContainerType, typename Functor>
    [[nodiscard]] CmdPtrU Process(InputContainerType& input, Functor& storeElementToOutput) const
    {
        return std::make_unique<StoreOutputCmd<InputContainerType, Functor>>(input, storeElementToOutput);
    }
};

}
