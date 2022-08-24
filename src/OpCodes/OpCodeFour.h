#pragma once
#include <InstructionProcessorUtils.h>
#include <OpCode.h>

namespace InstructionProcessor
{

/**
* @class OpCodeFour specialisation.
* Claim a number and store it in the printed output collection.
*/
template <typename InputType, typename IteratorType, typename GetElementAtFunctionType>
class OpCodeFour final : public OpCode
{
public:
    /**
    * Constructor
    * @param getElementAt Function to retrieve an element given an iterator.
    * @param parameterModes The collection of the parameter modes.
    * @param printedOutput Collection of values to be printed out.
    */
    OpCodeFour(
            GetElementAtFunctionType &getElementAt,
            const ParameterModeVector &parameterModes,
            std::vector<InputType> &printedOutput);

    ~OpCodeFour() final = default;

    /**
    * Claim a number and store it in the printed output collection.
    */
    [[nodiscard]] OpCode::ReturnType Execute(std::any &nextElementIter, std::any &endIter) final;

private:
    GetElementAtFunctionType &_getElementAt;
    const ParameterModeVector &_parameterModes;
    std::vector<InputType> &_printedOutput;
};

}
