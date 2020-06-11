#pragma once

#include "OpCodeInterface.h"

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
    [[nodiscard]] std::optional<Result> Execute() final
    {
        return std::nullopt;
    };
};
