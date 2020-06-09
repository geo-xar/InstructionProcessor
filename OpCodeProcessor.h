#pragma once

#include "NonCopyable.h"
#include "NonMovable.h"
#include "OpCodeProcessorUtils.h"
#include <vector>
#include <optional>
#include <tuple>

class OpCodeProcessor final : public NonCopyable, NonMovable
{
public:
    /**
    * Process OpCodes and update the input values.
    * 1:  Add together numbers read from two positions and store the result in a third position.
    * 2:  Work exactly like OpCode 1, but multiply the two inputs instead of adding them.
    * 3:  Take a single integer as input and save it to the position given by the unique parameter.
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
    * @input Collection of numbers to be processed.
    *
    * @return Modified input and printed output.
    */
    template <typename T>
    [[nodiscard]] std::tuple<std::vector<T>, std::vector<T>> ProcessInstructions(
        const std::vector<T>& inputCollection,
        [[maybe_unused]] const T userSelection)
    {
        if (!inputCollection.size())
        {
            return { {}, {} };
        }

        using Vector = std::vector<T>;
        using Iterator = Vector::iterator;
        using OpCodeModeOpt = std::optional<Vector>;

        Vector input;
        input.resize(inputCollection.size());
        std::copy(inputCollection.begin(), inputCollection.end(), input.begin());
        Iterator iterator = input.begin();

        Vector printedOutput;

        auto TryToClaimNumbers =
        [&input, &iterator]
        (size_t howManyNumbersRequiredToDoTheCalculation,
         const  OpCodeModeVector& parameterModes,
         size_t howManyIndexNumbersRequiredToStoreTheCalculationResult = 1) -> std::optional<Vector>
        {
            assert( (howManyNumbersRequiredToDoTheCalculation > 0) && (howManyNumbersRequiredToDoTheCalculation <= 2) );
            assert( parameterModes.size() >= howManyNumbersRequiredToDoTheCalculation );
            assert( howManyIndexNumbersRequiredToStoreTheCalculationResult == 1 );

            if ( std::distance(iterator, input.end()) <
                 (howManyNumbersRequiredToDoTheCalculation + howManyIndexNumbersRequiredToStoreTheCalculationResult) )
            {
                return std::nullopt;
            }

            Vector claimedNumbers;

            // At first claim the numbers that are part of the calculation
            for (size_t i = 0; i < howManyNumbersRequiredToDoTheCalculation; i++)
            {
                if ( parameterModes[i] == OpCodeMode::Parameter )
                {
                    claimedNumbers.emplace_back(*iterator);
                }
                // OpCodeMode::Parameter
                else
                {
                    assert(*iterator >= 0);
                    assert(*iterator < input.size());
                    claimedNumbers.emplace_back(input[*iterator]);
                }
                iterator++;
            }

            // Claim also the index to store the calculation result
            if (howManyIndexNumbersRequiredToStoreTheCalculationResult == 1)
            {
                claimedNumbers.emplace_back(*iterator);
                iterator++;
            }

            return claimedNumbers;
        };

        // Iterate the whole input
        while (iterator < input.end())
        {
            // Extract the next OpCode and the ParameterModes
            const auto opCode = ExtractOpCodeFromNumber(*iterator);
            auto parameterModes = ExtractParameterModesFromNumber(*iterator);

            // Jump to the next number
            iterator++;

            std::optional<Vector> claimedNumbersOptional = std::nullopt;
            switch (opCode)
            {
            // OpCode 1: Add 2 numbers read from the first and the second position
            // and store the result in the index described by the third position
            case 1:
                // In each iteration we need to have at least 3 parameters left to be processed
                claimedNumbersOptional = TryToClaimNumbers(2, parameterModes);
                if (!claimedNumbersOptional.has_value())
                {
                    return {input, printedOutput};
                }

                input[claimedNumbersOptional.value()[2]] = claimedNumbersOptional.value()[0] + claimedNumbersOptional.value()[1];
                break;

            // OpCode 2: Multiply 2 numbers read from the first and the second position
            // and store the result in the index described by the third position
            case 2:
                // In each iteration we need to have at least 3 parameters left to be processed.
                claimedNumbersOptional = TryToClaimNumbers(2, parameterModes);
                if (!claimedNumbersOptional.has_value())
                {
                    return {input, printedOutput};
                }

                input[claimedNumbersOptional.value()[2]] = claimedNumbersOptional.value()[0] * claimedNumbersOptional.value()[1];
                break;

/*            case 3:
                // In each iteration we need to have at least 2 parameters left to be processed.
                if ((input.size() - index) < 2)
                {
                    return printedOutput;
                }

                SetInputValueGivenParameterMode(Mode::Position, index + 1, userSelection);

                index += 2;
                break;

            case 4:
                // In each iteration we need to have at least 2 parameters left to be processed.
                if ((input.size() - index) < 2)
                {
                    return printedOutput;
                }

                printedOutput.push_back(GetInputValueGivenParameterMode(modA, index + 1));

                index += 2;
                break;

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

            case 99:
                return {input, printedOutput};

            default:
                // We should never reach this point.
                assert(false);
                return {input, printedOutput};
            }
        }

        return {input, printedOutput};
    }
};
