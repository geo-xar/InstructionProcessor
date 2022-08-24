#pragma once
#include <InstructionProcessorUtils.h>
#include <OpCode.h>

namespace InstructionProcessor
{

/**
* @class OpCodeEight specialisation.
* If the first parameter is equal to the second parameter then
* store 1 in the position given by the third parameter, otherwise store 0.
*/
template <typename InputType, typename IteratorType, typename SetElementAtIndexFunctionType, typename GetElementAtFunctionType>
class OpCodeEight final : public OpCode
{
    static constexpr IndexType NumberOfParametersToClaim = 2;

public:
    /**
    * Constructor
    * @param setElementAtIndex Function to store an element to the given index.
    * @param getElementAt Function to retrieve an element given an iterator.
    * @param parameterModes The collection of the parameter modes.
    */
    OpCodeEight(
            SetElementAtIndexFunctionType &setElementAtIndex,
            GetElementAtFunctionType &getElementAt,
            const ParameterModeVector &parameterModes);

    ~OpCodeEight() final = default;

    /**
    * If the first parameter is equal to the second parameter then
    * store 1 in the position given by the third parameter, otherwise store 0.
    */
    [[nodiscard]] OpCode::ReturnType Execute(std::any &nextElementIter, std::any &endIter) final;

private:
    SetElementAtIndexFunctionType &_setElementAtIndex;
    GetElementAtFunctionType &_getElementAt;
    const ParameterModeVector &_parameterModes;
};

}
