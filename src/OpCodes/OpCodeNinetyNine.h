#pragma once
#include <ExitCmd.h>

namespace InstructionProcessor
{

/**
* @class OpCodeNinetyNine.
*/
class OpCodeNinetyNine final
{
public:
    OpCodeNinetyNine() = default;

    template <typename InputContainerType>
    [[nodiscard]] CmdPtrU Process(InputContainerType& input) const
    {
        return std::make_unique<ExitCmd<InputContainerType>>(input);
    }
};

}
