// Copyright 2022 by Georgios Charitos.
// All rights reserved.

#pragma once
#include "Cmd.h"

namespace InstructionProcessor
{

/**
* @class Store input command specialisation.
* Claim a number and store the user input value
* to the index which it points to.
*/
template <typename InputContainerType>
class StoreInputCmd final : public Cmd
{
public:
    StoreInputCmd(InputContainerType& input,
        std::optional<typename InputContainerType::InputValueType>& userSelection)
    : _input{input}
    , _userSelection{userSelection}
    {};

    ~StoreInputCmd() override final = default;

    [[nodiscard]] CmdResult Execute() const override final
    {
        // Check if there are enough numbers to be claimed to complete the operation.
        // Numbers to be claimed are:
        // - 1 or the OpCode,
        // - 1 for the index to store the result.
        if (!this->_input.AreThereEnoughElementsToBeClaimed(2))
        {
            return std::nullopt;
        }

        assert(_userSelection.has_value());

        // Store the user selection.
        _input.MoveToTheNextElement();
        _input.StoreElement(_userSelection.value());

        // What we return here it is only useful for error reporting.
        // Whatever different than std::nullopt is equal to SUCCESS.
        return std::make_optional<Result>();
    }

private:
    InputContainerType& _input;
    std::optional<typename InputContainerType::InputValueType>& _userSelection;
};

}