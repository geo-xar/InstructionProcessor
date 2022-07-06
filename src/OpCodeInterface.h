#pragma once

#include "NonCopyable.h"
#include "NonMovable.h"
#include <any>
#include <optional>
#include <utility>

namespace InstructionProcessor
{

/**
* @class The Result class will be used for future error handling.
*/
class Result final
{
public:
    Result() = default;
};

/**
* The OpCode interface which is implemented by different OpCode specialisations.
*/
class OpCode : public NonCopyable, NonMovable
{
public:
    using ReturnType = std::pair<std::optional<Result>, std::any>;

    /**
    * Execute the OpCode and return a result optional and the updated iterator.
    * @param nextElementIter The iterator pointing to the next element of the integer collection to be processed.
    * @param endIter The iterator pointing to the end of the integer collection.
    * If the return optional is equal to std::nullopt then the execution was not successful.
    */
    virtual ReturnType Execute(std::any &nextElementIter, std::any &endIter) = 0;
};

}
