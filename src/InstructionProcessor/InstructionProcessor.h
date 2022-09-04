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
    using ResultType = std::tuple<Vector, Vector>;

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
        // There is no reason doing any kind of calculations if the input collection is empty.
        if (!inputCollection.size())
        {
            return {{},
                    {}};
        }

        InputContainer input{inputCollection};

        // Declare the printed output collection.
        Vector printedOutput;

        // Function to set the element to the collection given an index
/*         auto SetElementAtIndex =
            [&input](InputType index, InputType element) mutable -> void
            {
                assert((index >= 0) && (static_cast<IndexType>(index) < input.size()));
                input[static_cast<IndexType>(index)] = element;
            };
 */
        // Useful for ParameterMode::Relative
        // Only modified by OpCodeNine
        //InputType relativeBase{ 0 };

        // Function to get an element from the collection given an iterator by using the iterator value as index
        // It can optionally take into consideration the relative base
/*         auto GetElementAt =
            [&input](IteratorType& it) -> InputType
            {
                assert(*it >= 0);
                assert(static_cast<IndexType>(*it) < input.size());
                return input[static_cast<IndexType>(*it)];
            }; */

        // Function to get an iterator from the given position of the collection plus given offset
/*         auto GetIterFromPosPlusOffset =
            [&input](InputType offset, InputType pos = 0) -> IteratorType
            {
                assert(!input.empty());
                assert(offset >= 0);
                assert(pos >= 0);
                assert(static_cast<IndexType>(pos + offset) < input.size());
                auto iter = input.begin() + static_cast<IndexType>(pos);
                std::advance(iter, static_cast<IndexType>(offset));
                return iter;
            }; */

        // Function to update the relative base (called only by OpCodeNine)
/*         auto UpdateRelativeBase =
            [&relativeBase](InputType newRelativeBase) mutable -> void
            {
                relativeBase += newRelativeBase;
            }; */

        std::deque<CmdPtrU> pendingCommands;

        // Iterate the whole input.
        auto iterator = inputCollection.begin();
        while (iterator < inputCollection.end())
        {
            // Extract the next OpCode and the ParameterModes.
            const auto opCode = ExtractOpCodeFromNumber(*iterator);
            auto parameterModes = ExtractParameterModesFromNumber(*iterator);

            // Jump to the next number.
            iterator++;

            switch (opCode)
            {
                case 1:
                {
                    pendingCommands.emplace_back(OpCodeOne{}.Process(input));
                    break;
                }
/*                 case 2:
                {
                    pendingCommands.emplace_back(OpCodeTwo{}.Process(input));
                    break;
                }
                case 3:
                {
                    pendingCommands.emplace_back(OpCodeThree{}.Process(input));
                    break;
                }
                case 4:
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
                    oss << "Non-supported OpCode:" << opCode;
                    throw std::runtime_error(oss.str());
                }

            } // end of switch(OpCode)

            // Retrieve the first command to be executed.
            // If the result optional has no value then terminate the execution.
            Cmd* cmdToBeExecuted = pendingCommands.front().get();
            //std::any nextElement{iterator};
            //std::any iterEnd{input.end()};
            auto result = cmdToBeExecuted->Execute();
            if (!result.has_value())
            {
                return {input.GetInput(), printedOutput};
            }
            else
            {
                //iterator = std::any_cast<IteratorType&>(result.second);
            }

            // Remove the command which was just executed.
            pendingCommands.pop_front();
        }

        return {input.GetInput(), printedOutput};
    }
};

}
