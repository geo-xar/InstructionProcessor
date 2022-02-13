#pragma once

#include "OpCodeInterface.h"
#include "OpCodeProcessorUtils.h"

namespace InstructionProcessor
{

/**
* @class OpCodeSix specialisation.
* If the first parameter is zero then set the instruction pointer to the value from the second parameter.
* Otherwise do nothing.
*/
template <typename InputType, typename IteratorType, typename GetElementAtFunctionType, typename GetIterFromPosPlusOffsetFunctionType>
class OpCodeSix final : public OpCode
{
public:
    /**
    * Constructor
    * @param getElementAt Function to retrieve an element given an iterator.
    * @param getIterFromBeginPlusOffset Function to retrieve the begin iterator of a collection plus given offset.
    * @param parameterModes The collection of the parameter modes.
    */
    OpCodeSix(
        GetElementAtFunctionType &getElementAt,
        GetIterFromPosPlusOffsetFunctionType &getIterFromPosPlusOffset,
        const ParameterModeVector &parameterModes)
        : _getElementAt{getElementAt}, _getIterFromPosPlusOffset{ getIterFromPosPlusOffset },
            _parameterModes{parameterModes}
    {}

    ~OpCodeSix() final = default;

    /**
    * If the first parameter is zero then set the instruction pointer to the value from the second parameter.
    * Otherwise do nothing.
    */
    [[nodiscard]] OpCode::ReturnType Execute(std::any &nextElementIter, std::any &endIter) final
    {
        IteratorType &iterBegin = std::any_cast<IteratorType &>(nextElementIter);
        IteratorType &iterEnd = std::any_cast<IteratorType &>(endIter);

        // Check if there are enough numbers to be claimed to complete the operation.
        if (!AreThereEnoughElementsIntoTheCollection(iterBegin, iterEnd, 2))
        {
            return {std::nullopt, {}};
        }

        // Claim the first parameter based on parameter mode.
        InputType option;
        if (_parameterModes[0] == ParameterMode::Immediate)
        {
            option = *iterBegin;
        }
        else if (_parameterModes[0] == ParameterMode::Position)
        {
            option = _getElementAt(iterBegin);
        }
        // ParameterMode::Relative
        else
        {
            option = _getElementAt(iterBegin, {});
        }

        // Jump to the next number.
        iterBegin++;

        // If non-zero number then do nothing.
        if (option != 0)
        {
            // Skip the number.
            iterBegin++;
            return {std::make_optional<Result>(), {iterBegin}};
        }

        // Move the instruction pointer to the index pointed by the second number.
        InputType number;
        if (_parameterModes[1] == ParameterMode::Immediate)
        {
            number = *iterBegin;
        }
            // ParameterMode::Position
        else
        {
            number = _getElementAt(iterBegin);
        }

        // Update instruction pointer.
        iterBegin = _getIterFromPosPlusOffset(number);

        // What we return here it is only useful for error reporting.
        // Whatever different than std::nullopt is equal to SUCCESS.
        return {std::make_optional<Result>(), {iterBegin}};
    }

private:
    GetElementAtFunctionType &_getElementAt;
    GetIterFromPosPlusOffsetFunctionType &_getIterFromPosPlusOffset;
    const ParameterModeVector &_parameterModes;
};

}
