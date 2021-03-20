#pragma once

#include "OpCodeInterface.h"

/**
* @class OpCodeNinetyNine specialisation.
* The program is finished and should immediately halt.
*/
template <typename T>
class OpCodeNinetyNine final : public OpCode
{
using Vector = std::vector<T>;
using VectorIterator = typename Vector::iterator;

public:
    ~OpCodeNinetyNine() final = default;

    /**
    * The program is finished and should immediately halt.
    */
    [[nodiscard]] OpCode::ReturnType Execute([[maybe_unused]]std::any& nextElementIter, [[maybe_unused]]std::any& endIter) final
    {
        return { std::nullopt, {} };
    };
};
