#pragma once
#include <InstructionProcessorUtils.h>
#include <OpCode.h>

namespace InstructionProcessor
{

/**
* @class OpCodeNine specialisation.
* It adjusts the relative base by the value of its only parameter.
*/
template <typename InputType, typename IteratorType, typename GetElementAtType, typename UpdateRelativeBaseType>
class OpCodeNine final : public OpCode
{
public:
    /**
    * Constructor
    * @param getElementAt Function to retrieve an element given an iterator.
    * @param updateRelativeBase Function to update relative base to the given one.
    * @param parameterModes The collection of the parameter modes.
    */
    OpCodeNine(
        GetElementAtType& getElementAt,
        UpdateRelativeBaseType& updateRelativeBase,
        const ParameterModeVector& parameterModes);

    ~OpCodeNine() final = default;

    /**
    * It adjusts the relative base by the value of its only parameter.
    */
    [[nodiscard]] OpCode::ReturnType Execute(std::any &nextElementIter, std::any &endIter) final;

private:
    GetElementAtType& _getElementAt;
    UpdateRelativeBaseType& _updateRelativeBase;
    const ParameterModeVector& _parameterModes;
};

}
