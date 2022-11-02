// Copyright 2022 by Georgios Charitos.
// All rights reserved.

#pragma once
#include "Cmd.h"

namespace InstructionProcessor
{

/**
* @class If the first parameter is equal to the second parameter
* then store 1 in the position given by the third parameter,
* otherwise store 0.
*/
template <typename InputContainerType>
class FirstParamEqToSecondCmd final : public Cmd
{
public:
    FirstParamEqToSecondCmd(InputContainerType& input) : _input{input} {};
    ~FirstParamEqToSecondCmd() override final = default;
    [[nodiscard]] CmdResult Execute() const override final
    {
        // Check if there are enough numbers to be claimed to complete the operation.
        // Numbers to be claimed are:
        // - 1 for the OpCode,
        // - 2 for the parameters to be compared,
        // - 1 for the index to store 1.
        if (!this->_input.AreThereEnoughElementsToBeClaimed(4))
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

        _input.MoveToTheNextElement();
        if (firstNumber == secondNumber)
        {
            // Store 1.
            _input.StoreElement(1, mode3);
        }
        else
        {
            // Store 0.
            _input.StoreElement(0, mode3);
        }
        _input.MoveToTheNextElement();

        // What we return here it is only useful for error reporting.
        // Whatever different than std::nullopt is equal to SUCCESS.
        return std::make_optional<Result>();
    }

private:
    InputContainerType& _input;
};

}
