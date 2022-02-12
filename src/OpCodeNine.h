#pragma once

#include "OpCodeInterface.h"
#include "OpCodeProcessorUtils.h"

namespace InstructionProcessor
{

/**
* @class OpCodeNine specialisation.
* It adjusts the relative base by the value of its only parameter.
*/
template <typename InputType, typename IteratorType, typename SetElementAtIndexFunctionType, typename GetElementAtFunctionType>
class OpCodeNine final : public OpCode
{
    static constexpr IndexType NumberOfParametersToClaim = 1;

public:
    /**
    * Constructor
    * @param setElementAtIndex Function to store an element to the given index.
    * @param getElementAt Function to retrieve an element given an iterator.
    * @param parameterModes The collection of the parameter modes.
    */
    OpCodeNine(
            SetElementAtIndexFunctionType &setElementAtIndex,
            GetElementAtFunctionType &getElementAt,
            const ParameterModeVector &parameterModes)
            : _setElementAtIndex{setElementAtIndex}, _getElementAt{getElementAt}, _parameterModes{parameterModes}
    {}

    ~OpCodeNine() final = default;

    /**
    * It adjusts the relative base by the value of its only parameter.
    */
    [[nodiscard]] OpCode::ReturnType Execute(std::any &nextElementIter, std::any &endIter) final
    {
        IteratorType &iterBegin = std::any_cast<IteratorType &>(nextElementIter);
        IteratorType &iterEnd = std::any_cast<IteratorType &>(endIter);

        // Check if there are enough numbers to be claimed to complete the operation.
        // 1 number to be claimed.
        if (!AreThereEnoughElementsIntoTheCollection(iterBegin, iterEnd, NumberOfParametersToClaim + 1))
        {
            return {std::nullopt, {}};
        }

        InputType number;
        if (_parameterModes[i] == ParameterMode::Immediate)
        {
            number = *iterBegin;
        }
        else if (_parameterModes[i] == ParameterMode::Position)
        {
            number = _getElementAt(iterBegin);
        }
        // ParameterMode::Relative
        else
        {
            
        }

        iterBegin++;

        // What we return here it is only useful for error reporting.
        // Whatever different than std::nullopt is equal to SUCCESS.
        return {std::make_optional<Result>(), {iterBegin}};
    }

private:
    SetElementAtIndexFunctionType &_setElementAtIndex;
    GetElementAtFunctionType &_getElementAt;
    const ParameterModeVector &_parameterModes;
};

}
