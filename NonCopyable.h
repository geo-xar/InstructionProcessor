#pragma once

/**
 * @interface NonCopyable interface.
 * Derive from this to make your class non-copyable.
 */
class NonCopyable
{
public:
    NonCopyable() = default;
    virtual ~NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};
