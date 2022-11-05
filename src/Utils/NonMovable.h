// Copyright 2022 by Georgios Charitos.
// All rights reserved.

#pragma once

namespace InstructionProcessor
{

/**
 * NonMovable class.
 * Derive from this to make your class non-movable.
 */
class NonMovable
{
public:
    NonMovable() = default;
    virtual ~NonMovable() = default;
    NonMovable(NonMovable &&) = delete;
    NonMovable &operator=(NonMovable &&) = delete;
};

}
