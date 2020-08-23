#pragma once

#include "NonMovable.h"
#include "NonCopyable.h"
#include <optional>

class Result final
{
public:
    Result() = default;
};

/**
* @intereface The OpCode interface which is implemented by different OpCode specialisations.
*/
class OpCode : public NonCopyable, NonMovable
{
public:
    /**
    * Execute the OpCode and return a result optional.
    * If the return optional is equal to std::nullopt then the execution was not successful.
    */
    virtual std::optional<Result> Execute() = 0;
};
