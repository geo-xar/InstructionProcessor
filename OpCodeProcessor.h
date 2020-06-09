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
        std::optional<T> userSelection = {})
    {
        if (!inputCollection.size())
        {
            return { {}, {} };
        }

        using Vector = std::vector<T>;
        using Iterator = Vector::iterator;

        Vector input;
        input.resize(inputCollection.size());
        std::copy(inputCollection.begin(), inputCollection.end(), input.begin());
        Iterator iterator = input.begin();

        Vector printedOutput;

        auto TryToClaimNumbers =
        [&input, &iterator]
        (size_t howManyNumbersTakingIntoAccountOpCodeModes,
         size_t howManyNumbersUsedAsIndexes,
         const  ParameterModeVector& parameterModes) -> std::optional<Vector>
        {
            assert( parameterModes.size() >= howManyNumbersTakingIntoAccountOpCodeModes );
            assert( howManyNumbersUsedAsIndexes <= 1 );

            if ( std::distance(iterator, input.end()) <
                 (howManyNumbersTakingIntoAccountOpCodeModes + howManyNumbersUsedAsIndexes) )
            {
                return std::nullopt;
            }

            Vector claimedNumbers;

            for (size_t i = 0; i < howManyNumbersTakingIntoAccountOpCodeModes; i++)
            {
                if ( parameterModes[i] == ParameterMode::Immediate )
                {
                    claimedNumbers.emplace_back(*iterator);
                }
                // ParameterMode::Position
                else
                {
                    assert(*iterator >= 0);
                    assert(*iterator < input.size());
                    claimedNumbers.emplace_back(input[*iterator]);
                }
                iterator++;
            }

            // Claim also the index to store the calculation result.
            if (howManyNumbersUsedAsIndexes == 1)
            {
                claimedNumbers.emplace_back(*iterator);
                iterator++;
            }

            return claimedNumbers;
        };

        // Iterate the whole input.
        while (iterator < input.end())
        {
            // Extract the next OpCode and the ParameterModes.
            const auto opCode = ExtractOpCodeFromNumber(*iterator);
            auto parameterModes = ExtractParameterModesFromNumber(*iterator);

            // Jump to the next number.
            iterator++;

            std::optional<Vector> claimedNumbersOptional = std::nullopt;
            switch (opCode)
            {
            // OpCode 1: Accumulate 2 numbers read from the first and the second position
            // and store the result in the index described by the third position.
            case 1:
                // Try to claim 3 numbers.
                // The 2 first numbers will be part of the calculation.
                // The calculation result will be stored to the index which is pointed by the third number.
                claimedNumbersOptional = TryToClaimNumbers(2, 1, parameterModes);
                if (!claimedNumbersOptional.has_value())
                {
                    return {input, printedOutput};
                }

                // TODO: Proper error handling.
                assert(claimedNumbersOptional.value()[2] >= 0);
                assert(claimedNumbersOptional.value()[2] < input.size());
                input[claimedNumbersOptional.value()[2]] = claimedNumbersOptional.value()[0] + claimedNumbersOptional.value()[1];
                break;

            // OpCode 2: Multiply 2 numbers read from the first and the second position
            // and store the result in the index described by the third position.
            case 2:
                // Try to claim 3 numbers.
                // The 2 first numbers will be part of the calculation.
                // The calculation result will be stored to the index which is pointed by the third number.
                claimedNumbersOptional = TryToClaimNumbers(2, 1, parameterModes);
                if (!claimedNumbersOptional.has_value())
                {
                    return {input, printedOutput};
                }

                // TODO: Proper error handling.
                assert(claimedNumbersOptional.value()[2] >= 0);
                assert(claimedNumbersOptional.value()[2] < input.size());
                input[claimedNumbersOptional.value()[2]] = claimedNumbersOptional.value()[0] * claimedNumbersOptional.value()[1];
                break;

            case 3:
                // Try to claim 1 number.
                // The user input value will be stored to the index which is pointed by the claimed number.
                claimedNumbersOptional = TryToClaimNumbers(0, 1, parameterModes);
                if (!claimedNumbersOptional.has_value())
                {
                    return {input, printedOutput};
                }

                // TODO: Proper error handling.
                assert(claimedNumbersOptional.value()[0] >= 0);
                assert(claimedNumbersOptional.value()[0] < input.size());
                assert(userSelection.has_value());
                input[claimedNumbersOptional.value()[0]] = userSelection.value();
                break;

            case 4:
                // Try to claim 1 number.
                // Print the value stored to the index which is pointed by the claimed number.
                claimedNumbersOptional = TryToClaimNumbers(0, 1, parameterModes);
                if (!claimedNumbersOptional.has_value())
                {
                    return {input, printedOutput};
                }

                // TODO: Proper error handling.
                assert(claimedNumbersOptional.value()[0] >= 0);
                assert(claimedNumbersOptional.value()[0] < input.size());
                printedOutput.emplace_back(input[claimedNumbersOptional.value()[0]]);
                break;
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
