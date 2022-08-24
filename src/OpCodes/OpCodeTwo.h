#pragma once
#include <InstructionProcessorUtils.h>
#include <OpCode.h>

namespace InstructionProcessor
{

/**
* @class OpCodeTwo specialisation.
* Multiply 2 numbers.
*/
template <typename InputType, typename IteratorType, typename SetElementAtIndexFunctionType, typename GetElementAtFunctionType>
class OpCodeTwo final : public OpCode
{
    static constexpr IndexType NumberOfParametersToClaim = 2;

public:
    /**
    * Constructor
    * @param setElementAtIndex Function to store an element to the given index.
    * @param getElementAt Function to retrieve an element given an iterator.
    * @param parameterModes The collection of the parameter modes.
    */
    OpCodeTwo(
            SetElementAtIndexFunctionType &setElementAtIndex,
            GetElementAtFunctionType &getElementAt,
            const ParameterModeVector &parameterModes);

    ~OpCodeTwo() final = default;

    /**
    * Multiply 2 numbers and store the result in the index pointed by the third number.
    */
    [[nodiscard]] OpCode::ReturnType Execute(std::any &nextElementIter, std::any &endIter) final;

private:
    SetElementAtIndexFunctionType &_setElementAtIndex;
    GetElementAtFunctionType &_getElementAt;
    const ParameterModeVector &_parameterModes;
};

}
