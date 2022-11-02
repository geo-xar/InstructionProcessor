// Copyright 2022 by Georgios Charitos.
// All rights reserved.

#pragma once
#include "Cmd.h"

namespace InstructionProcessor
{

/**
* @class Claim a number and store it
* in the printed output collection.
*/
template <typename InputContainerType, typename Functor>
class StoreOutputCmd final : public Cmd
{
public:
    StoreOutputCmd(InputContainerType& input, Functor& storeElementToOutput)
    : _input{input}
    , _storeElementToOutput{storeElementToOutput}
    {};

    ~StoreOutputCmd() override final = default;

    [[nodiscard]] CmdResult Execute() const override final
    {
        // Check if there are enough numbers to be claimed to complete the operation.
        // Numbers to be claimed are:
        // - 1 for the OpCode,
        // - 1 for the number to be stored to the output. 
        if (!this->_input.AreThereEnoughElementsToBeClaimed(2))
        {
            return std::nullopt;
        }

        const auto [mode1, mode2, mode3] = _input.GetModes();

        // Store the element to the output collection.
        _input.MoveToTheNextElement();
        _storeElementToOutput(_input.GetCurrentElementValue(mode1));
        _input.MoveToTheNextElement();

        // What we return here it is only useful for error reporting.
        // Whatever different than std::nullopt is equal to SUCCESS.
        return std::make_optional<Result>();
    }

private:
    InputContainerType& _input;
    Functor& _storeElementToOutput;
};

}
