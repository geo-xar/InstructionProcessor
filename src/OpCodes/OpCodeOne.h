// Copyright 2022 by Georgios Charitos.
// All rights reserved.

#pragma once
#include <InstructionProcessorUtils.h>
#include <OpCodeInterface.h>

namespace InstructionProcessor
{

/**
* @class OpCodeOne specialisation.
* Accumulate 2 numbers.
*/
template <typename InputType, typename IteratorType, typename SetElementAtIndexFunctionType, typename GetElementAtFunctionType>
class OpCodeOne final : public OpCode
{
    static constexpr IndexType NumberOfParametersToClaim = 2;

public:
    /**
    * Constructor
    * @param setElementAtIndex Function to store an element to the given index.
    * @param getElementAt Function to retrieve an element given an iterator.
    * @param parameterModes The collection of the parameter modes.
    */
    OpCodeOne(
            SetElementAtIndexFunctionType& setElementAtIndex,
            GetElementAtFunctionType& getElementAt,
            const ParameterModeVector& parameterModes);

    ~OpCodeOne() final = default;

    /**
    * Accumulate 2 numbers and store the result in the index pointed by the third number.
    */
    [[nodiscard]] OpCode::ReturnType Execute(std::any& nextElementIter, std::any& endIter) final;

private:
    SetElementAtIndexFunctionType& _setElementAtIndex;
    GetElementAtFunctionType& _getElementAt;
    const ParameterModeVector& _parameterModes;
};

}
