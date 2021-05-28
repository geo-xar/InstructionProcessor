#pragma once

namespace InstructionProcessor
{

/**
 * @interface NonMovable interface.
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
