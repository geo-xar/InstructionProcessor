#pragma once
#include <InstructionProcessorUtils.h>
#include <OpCode.h>

namespace InstructionProcessor
{

/**
* @class OpCodeFive specialisation.
* If the first parameter is non-zero then set the instruction pointer to the value from the second parameter.
* Otherwise do nothing.
*/
template <typename InputType, typename IteratorType, typename GetElementAtFunctionType, typename GetIterFromPosPlusOffsetFunctionType>
class OpCodeFive final : public OpCode
{
public:
    /**
    * Constructor
    * @param getElementAt Function to retrieve an element given an iterator.
    * @param getIterFromBeginPlusOffset Function to retrieve the begin iterator of a collection plus given offset.
    * @param parameterModes The collection of the parameter modes.
    */
    OpCodeFive(
        GetElementAtFunctionType &getElementAt,
        GetIterFromPosPlusOffsetFunctionType &getIterFromPosPlusOffset,
        const ParameterModeVector &parameterModes);

    ~OpCodeFive() final = default;

    /**
    * If the first parameter is non-zero then set the instruction pointer to the value from the second parameter.
    * Otherwise do nothing.
    */
    [[nodiscard]] OpCode::ReturnType Execute(std::any &nextElementIter, std::any &endIter) final;

private:
    GetElementAtFunctionType &_getElementAt;
    GetIterFromPosPlusOffsetFunctionType &_getIterFromPosPlusOffset;
    const ParameterModeVector &_parameterModes;
};

}
