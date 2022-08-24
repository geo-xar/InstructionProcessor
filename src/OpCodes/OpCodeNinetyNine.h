#pragma once

#include "OpCode.h"

namespace InstructionProcessor
{

/**
* @class OpCodeNinetyNine specialisation.
* The program is finished and should immediately halt.
*/
class OpCodeNinetyNine final : public OpCode
{
public:
    ~OpCodeNinetyNine() final = default;

    /**
    * The program is finished and should immediately halt.
    */
    [[nodiscard]] OpCode::ReturnType
    Execute([[maybe_unused]]std::any &nextElementIter, [[maybe_unused]]std::any &endIter) final
    {
        return {std::nullopt, {}};
    }
};

}
