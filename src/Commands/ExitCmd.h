#pragma once
#include "Cmd.h"

namespace InstructionProcessor
{

/**
* @class The program is finished and should immediately halt.
*/
template <typename InputContainerType>
class ExitCmd final : public BasicCmd<InputContainerType>
{
public:
    ExitCmd(InputContainerType& input) : BasicCmd<InputContainerType>(input) {};
    ~ExitCmd() override final = default;
    [[nodiscard]] CmdResult Execute() const override final
    {
        return std::nullopt;
    }
};

}
