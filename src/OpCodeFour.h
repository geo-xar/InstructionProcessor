#pragma once

#include "OpCodeInterface.h"
#include "OpCodeProcessorUtils.h"

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
            std::vector<InputType> &printedOutput)
            : _getElementAt{getElementAt}, _parameterModes{parameterModes}, _printedOutput{printedOutput}
    {}

    ~OpCodeFour() final = default;

    /**
    * Claim a number and store it in the printed output collection.
    */
    [[nodiscard]] OpCode::ReturnType Execute(std::any &nextElementIter, std::any &endIter) final
    {
        IteratorType &iterBegin = std::any_cast<IteratorType &>(nextElementIter);
        IteratorType &iterEnd = std::any_cast<IteratorType &>(endIter);

        // Check if there are enough numbers to be claimed to complete the operation.
        // A single number is needed to be stored in the printed output collection.
        if (!AreThereEnoughElementsIntoTheCollection(iterBegin, iterEnd, 1))
        {
            return {std::nullopt, {}};
        }

        InputType number;
        if (_parameterModes[0] == ParameterMode::Immediate)
        {
            number = *iterBegin;
        }
        else if (_parameterModes[0] == ParameterMode::Position)
        {
            number = _getElementAt(iterBegin);
        }
        // ParameterMode::Relative
        else
        {
            number = _getElementAt(iterBegin, {});
        }

        _printedOutput.emplace_back(number);

        // Jump to the next number (if any).
        iterBegin++;

        // What we return here it is only useful for error reporting.
        // Whatever different than std::nullopt is equal to SUCCESS.
        return {std::make_optional<Result>(), {iterBegin}};
    }

private:
    GetElementAtFunctionType &_getElementAt;
    const ParameterModeVector &_parameterModes;
    std::vector<InputType> &_printedOutput;
};

}
