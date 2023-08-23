#pragma once
#include <StoreInputCmd.h>

namespace InstructionProcessor
{

/**
* @class OpCodeThree.
*/
class OpCodeThree final
{
public:
    OpCodeThree() = default;

    template <typename InputContainerType>
    [[nodiscard]] CmdPtrU Process(InputContainerType& input,
        std::optional<typename InputContainerType::InputValueType>& userSelection) const
    {
        return std::make_unique<StoreInputCmd<InputContainerType>>(input, userSelection);
    }
};

}
