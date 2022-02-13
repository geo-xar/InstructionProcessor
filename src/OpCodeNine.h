#pragma once

#include "OpCodeInterface.h"
#include "OpCodeProcessorUtils.h"

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
        const ParameterModeVector& parameterModes)
        : _getElementAt{ getElementAt }, _updateRelativeBase{ updateRelativeBase }, _parameterModes{ parameterModes }
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
        // A single number is needed to retrieve the relative base.
        if (!AreThereEnoughElementsIntoTheCollection(iterBegin, iterEnd, 1))
        {
            return {std::nullopt, {}};
        }

        InputType newRelativeBase{0};
        if (_parameterModes[0] == ParameterMode::Immediate)
        {
            newRelativeBase = *iterBegin;
        }
        else if (_parameterModes[0] == ParameterMode::Position)
        {
            newRelativeBase = _getElementAt(iterBegin);
        }
        // ParameterMode::Relative
        else
        {
            newRelativeBase = _getElementAt(iterBegin, {});
        }

        _updateRelativeBase(newRelativeBase);

        // Jump to the next number (if any).
        iterBegin++;

        // What we return here it is only useful for error reporting.
        // Whatever different than std::nullopt is equal to SUCCESS.
        return {std::make_optional<Result>(), {iterBegin}};
    }

private:
    GetElementAtType& _getElementAt;
    UpdateRelativeBaseType& _updateRelativeBase;
    const ParameterModeVector& _parameterModes;
};

}
