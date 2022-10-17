// Copyright 2022 by Georgios Charitos.
// All rights reserved.

#pragma once
#include "Cmd.h"

namespace InstructionProcessor
{

/**
* @class Multiply command specialisation.
* Multiply 2 numbers and store the result in the index
* pointed by the third number.
*/
template <typename InputContainerType>
class MultiplyCmd final : public Cmd
{
public:
    MultiplyCmd(InputContainerType& input) : _input{input} {};
    ~MultiplyCmd() override final = default;
    [[nodiscard]] CmdResult Execute() const override final
    {
        // Check if there are enough numbers to be claimed to complete the operation.
        // Numbers to be claimed are:
        // - 1 for the OpCode,
        // - 2 for the multiplication,
        // - 1 for the index to store the result.
        if (!_input.AreThereEnoughElementsToBeClaimed(4))
        {
            return std::nullopt;
        }

        const auto [mode1, mode2, mode3] = _input.GetModes();

        // Get first number.
        _input.MoveToTheNextElement();
        const auto firstNumber = _input.GetCurrentElementValue(mode1);
        // Get second number
        _input.MoveToTheNextElement();
        const auto secondNumber = _input.GetCurrentElementValue(mode2);

        // Store the multiplication result.
        _input.MoveToTheNextElement();
        _input.StoreElement(firstNumber * secondNumber, mode3);

        // What we return here it is only useful for error reporting.
        // Whatever different than std::nullopt is equal to SUCCESS.
        return std::make_optional<Result>();
    }

private:
    InputContainerType& _input;
};

}
