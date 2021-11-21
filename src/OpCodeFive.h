#pragma once

#include "OpCodeInterface.h"
#include "OpCodeProcessorUtils.h"

namespace InstructionProcessor
{

/**
* @class OpCodeFive specialisation.
* If the first parameter is non-zero then set the instruction pointer to the value from the second parameter.
* Otherwise do nothing.
*/
template <typename InputType, typename IteratorType, typename GetElementAtFunctionType, typename GetIterFromBeginPlusOffsetFunctionType>
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
            GetIterFromBeginPlusOffsetFunctionType &getIterFromBeginPlusOffset,
            const ParameterModeVector &parameterModes)
            : _getElementAt{getElementAt}, _getIterFromBeginPlusOffset{getIterFromBeginPlusOffset},
              _parameterModes{parameterModes}
    {}

    ~OpCodeFive() final = default;

    /**
    * If the first parameter is non-zero then set the instruction pointer to the value from the second parameter.
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
            // ParameterMode::Position
        else
        {
            option = _getElementAt(iterBegin);
        }

        // Jump to the next number no matter what the option value is.
        iterBegin++;

        // If zero number then do nothing.
        if (option == 0)
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
        iterBegin = _getIterFromBeginPlusOffset(number);

        // What we return here it is only useful for error reporting.
        // Whatever different than std::nullopt is equal to SUCCESS.
        return {std::make_optional<Result>(), {iterBegin}};
    }

private:
    GetElementAtFunctionType &_getElementAt;
    GetIterFromBeginPlusOffsetFunctionType &_getIterFromBeginPlusOffset;
    const ParameterModeVector &_parameterModes;
};

}
