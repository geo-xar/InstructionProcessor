#pragma once

#include "NonCopyable.h"
#include "NonMovable.h"
#include "OpCodeProcessorUtils.h"
#include "OpCodeOne.h"
#include "OpCodeTwo.h"
#include "OpCodeThree.h"
#include "OpCodeFour.h"
#include "OpCodeNinetyNine.h"

#include <vector>
#include <optional>
#include <tuple>
#include <deque>
#include <memory>

class OpCodeProcessor final : public NonCopyable, NonMovable
{
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
    * 99: The program is finished and shall immediately halt.
    *
    * @param inputCollection Collection of numbers to be processed.
    * @param userSelection Optional user input to be stored in the collection (OpCodeThree).
    *
    * @return Modified input collection and printed output.
    */
    template <typename T>
    [[nodiscard]] std::tuple<std::vector<T>, std::vector<T>> ProcessInstructions(
        const std::vector<T>& inputCollection,
        std::optional<T> userSelection = std::nullopt)
    {
        // There is no reason doing any kind of calculations if the input collection is empty.
        if (!inputCollection.size())
        {
            return { {}, {} };
        }

        using Vector = std::vector<T>;

        // Copy the input collection to a local variable.
        Vector input;
        input.resize(inputCollection.size());
        std::copy(inputCollection.begin(), inputCollection.end(), input.begin());

        // Declare the printed output collection.
        Vector printedOutput;

        // Declare the iterator which is used to manipulate the input collection.
        using Iterator = Vector::iterator;
        Iterator iterator = input.begin();

        // Declare an OpCode deque useful to manage the OpCode execution.
        using OpCodeUniquePtr = std::unique_ptr<OpCode>;
        std::deque<OpCodeUniquePtr> pendingInstructions;

        // Iterate the whole input.
        while (iterator < input.end())
        {
            // Extract the next OpCode and the ParameterModes.
            const auto opCode = ExtractOpCodeFromNumber(*iterator);
            auto parameterModes = ExtractParameterModesFromNumber(*iterator);

            // Jump to the next number.
            iterator++;

            switch (opCode)
            {

            // OpCode 1: Accumulate 2 numbers read from the first and the second position
            // and store the result in the index described by the third number.
            case 1:
            {
                pendingInstructions.emplace_back( std::move( std::make_unique<OpCodeOne<T>>(input, iterator, parameterModes) ) );
                break;
            }

            // OpCode 2: Multiply 2 numbers read from the first and the second position
            // and store the result in the index described by the third number.
            case 2:
            {
                pendingInstructions.emplace_back( std::move( std::make_unique<OpCodeTwo<T>>(input, iterator, parameterModes) ) );
                break;
            }

            // OpCode 3: Take a single number as user input
            // and store it in the index described by the unique number claimed.
            case 3:
            {
                pendingInstructions.emplace_back( std::move( std::make_unique<OpCodeThree<T>>(input, iterator, userSelection) ) );
                break;
            }

            // OpCode 4: Print the value in the index described by the unique number claimed.
            case 4:
            {
                pendingInstructions.emplace_back( std::move( std::make_unique<OpCodeFour<T>>(input, iterator, printedOutput) ) );
                break;
            }
/*
            case 5:
                // In each iteration we need to have at least 3 parameters left to be processed.
                if ((input.size() - index) < 3)
                {
                    return printedOutput;
                }

                if (input[index + 1] != 0)
                {
                    index = getInputValueGivenParameterMode(b, index + 2);
                }
                break;

            case 6:
                // In each iteration we need to have at least 3 parameters left to be processed.
                if ((input.size() - index) < 3)
                {
                    return printedOutput;
                }

                if (input[index + 1] == 0)
                {
                    index = getInputValueGivenParameterMode(b, index + 2);
                }
                break;

            case 7:
                // In each iteration we need to have at least 4 parameters left to be processed.
                if ((input.size() - index) < 4)
                {
                    return printedOutput;
                }

                if (input[input[index + 1]] < input[input[index + 2]])
                {
                    setInputValueGivenParameterMode(c, index + 3, 1);
                }
                else
                {
                    setInputValueGivenParameterMode(c, index + 3, 0);
                }

                index += 4;
                break;

            case 8:
                // In each iteration we need to have at least 4 parameters left to be processed.
                if ((input.size() - index) < 4)
                {
                    return printedOutput;
                }

                if (input[input[index + 1]] == input[input[index + 2]])
                {
                    setInputValueGivenParameterMode(c, index + 3, 1);
                    //input[index + 3] = 1;
                }
                else
                {
                    setInputValueGivenParameterMode(c, index + 3, 0);
                    //input[index + 3] = 0;
                }

                index += 4;
                break;*/

            // OpCode 99: The program is finished and shall immediately halt.
            case 99:
            {
                pendingInstructions.emplace_back( std::move( std::make_unique<OpCodeNinetyNine>() ) );
                break;
            }

            default:
            {
                // We should never reach this point.
                assert(false);
                return {input, printedOutput};
            }

            } // end of switch(OpCode)

            // If no more instructions to be processed then terminate the execution.
            if (pendingInstructions.empty())
            {
                return {input, printedOutput};
            }

            // Retrieve the first instruction to be executed.
            // If the result optional has no value then terminate the execution.
            OpCode* opCodeToBeExecuted = pendingInstructions.front().get();
            auto result = opCodeToBeExecuted->Execute();
            if (!result.has_value())
            {
                return {input, printedOutput};
            }

            // Remove the instruction which was just executed and jump to the next number (if any).
            pendingInstructions.pop_front();
            iterator++;
        }

        return {input, printedOutput};
    }
};
