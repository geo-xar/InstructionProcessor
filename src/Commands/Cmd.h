#pragma once
#include <optional>
#include <memory>

namespace InstructionProcessor
{

/**
* @class Handle an execution result.
*/
class Result
{
public:
    Result() = default;
};

/**
* An optional which represents a command execution result.
*/
using CmdResult = std::optional<Result>;

/**
* @interface The command interface which is implemented
* by different command specialisations.
*/
class Cmd
{
public:
    Cmd() = default;
    virtual ~Cmd() = default;

    /**
    * Execute a command and return the command execution result.
    */
    [[nodiscard]] virtual CmdResult Execute() const = 0;
};

/**
* Unique pointer to a Cmd object.
*/
using CmdPtrU = std::unique_ptr<Cmd>;

}
