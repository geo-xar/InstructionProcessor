#pragma once

#include "NonMovable.h"
#include "NonCopyable.h"
#include <optional>

/**
* @intereface The OpCode interface which is implemented by different OpCode specialisations.
*/
class OpCode : public NonCopyable, NonMovable
{
public:
    /**
    * Execute the OpCode.
    */
    virtual std::optional<uint64_t> Execute() = 0;
};
