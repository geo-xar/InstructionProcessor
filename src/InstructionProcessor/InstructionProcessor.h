// Copyright 2022 by Georgios Charitos.
// All rights reserved.

#pragma once

#include <NonCopyable.h>
#include <NonMovable.h>
#include <InstructionProcessorUtils.h>
#include <InputContainer.h>
#include <OpCodeOne.h>
#include <OpCodeTwo.h>
#include <OpCodeThree.h>
#include <OpCodeFour.h>
#include <OpCodeFive.h>
#include <OpCodeSix.h>
#include <OpCodeSeven.h>
#include <OpCodeEight.h>
#include <OpCodeNine.h>
#include <OpCodeNinetyNine.h>
#include <Cmd.h>

#include <vector>
#include <optional>
#include <tuple>
#include <deque>
#include <memory>
#include <functional>
#include <sstream>

namespace InstructionProcessor
{

template <typename InputType>
class OpCodeProcessor final : public NonCopyable, NonMovable
{
    using Vector = std::vector<InputType>;
    using ResultType = std::optional<std::pair<Vector, Vector>>;

public:
    /**
    * Process OpCodes and update the input values.
    * 1:  Add together numbers read from two positions and store the result in a third position.
    * 2:  Work exactly like OpCode 1, but multiply the two inputs instead of adding them.
    * 3:  Take a single integer as user input and save it to the position given by the unique parameter.
    * 4:  Output the value of the unique parameter.
    * 5:  If the first parameter is non-zero then set the instruction pointer to the value from the second parameter.
    *     Otherwise do nothing.
    * 6:  If the first parameter is zero then set the instruction pointer to the value from the second parameter.
    *     Otherwise do nothing.
    * 7:  If the first parameter is less than the second parameter then store 1 in the position given by the third parameter.
    *     Otherwise store 0.
    * 8:  If the first parameter is equal to the second parameter then store 1 in the position given by the third parameter.
    *     Otherwise store 0.
    * 9:  It adjusts the relative base by the value of its only parameter.
    * 99: The program is finished and shall immediately halt.
    *
    * @param inputCollection Collection of numbers to be processed.
    * @param userSelection Optional user input to be stored in the collection (OpCodeThree).
    *
    * @return Modified input collection and printed output.
    */
    [[nodiscard]] ResultType ProcessInstructions(
            const Vector& inputCollection, [[maybe_unused]] std::optional<InputType> userSelection = std::nullopt)
    {
        // There is no reason doing any kind of calculations
        // if the input collection is less than 2.
        if (inputCollection.size() <= 2U)
        {
            return std::nullopt;
        }

        // InputContainer class will encapsulate and manage the user input.
        InputContainer input{inputCollection};

        Vector printedOutput;

        std::deque<CmdPtrU> pendingCommands;

        while (input.AreThereAnyNonProcessedOpCodes())
        {
            switch (input.GetOpCode())
            {
                case 1:
                {
                    pendingCommands.emplace_back(OpCodeOne{}.Process(input));
                    break;
                }
                case 2:
                {
                    pendingCommands.emplace_back(OpCodeTwo{}.Process(input));
                    break;
                }
                case 3:
                {
                    pendingCommands.emplace_back(OpCodeThree{}.Process(input, userSelection));
                    break;
                }
/*                 case 4:
                {
                    pendingCommands.emplace_back(OpCodeFour{}.Process(input));
                    break;
                }

                case 5:
                {
                    pendingCommands.emplace_back(OpCodeFive{}.Process(input));
                    break;
                }

                case 6:
                {
                    pendingCommands.emplace_back(OpCodeSix{}.Process(input));
                    break;
                }

                case 7:
                {
                    pendingCommands.emplace_back(OpCodeSeven{}.Process(input));
                    break;
                }

                case 8:
                {
                    pendingCommands.emplace_back(OpCodeEight{}.Process(input));
                    break;
                }

                case 9:
                {
                    pendingCommands.emplace_back(OpCodeNine{}.Process(input));
                    break;
                }

                case 99:
                {
                    pendingCommands.emplace_back(OpCodeNinetyNine{}.Process(input));
                    break;
                } */
                default:
                {
                    // We should never reach this point.
                    std::ostringstream oss;
                    oss << "Non-supported OpCode:" << input.GetOpCode();
                    throw std::runtime_error(oss.str());
                }
            } // end of switch(OpCode)

            // Retrieve the first command to be executed.
            // If the result optional has no value then terminate the execution.
            Cmd* cmdToBeExecuted = pendingCommands.front().get();
            auto result = cmdToBeExecuted->Execute();
            if (!result.has_value())
            {
                return std::make_pair<>(input.GetInputCollection(), printedOutput);
            }

            // Remove the command which has just been executed.
            pendingCommands.pop_front();
        }

        return std::make_pair<>(input.GetInputCollection(), printedOutput);
    }
};

}
