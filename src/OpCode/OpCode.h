#pragma once
#include "NonCopyable.h"
#include "NonMovable.h"
#include "Cmd.h"

namespace InstructionProcessor
{

/**
* @interface The OpCode interface which is implemented
* by different OpCode specialisations.
*/
class OpCode : public NonCopyable, NonMovable
{
public:
    /**
    * Process the OpCode by returning a command to be executed.
    */
    [[nodiscard]] virtual CmdPtrU Process() const = 0;
};

}
