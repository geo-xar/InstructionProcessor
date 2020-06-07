#pragma once

#include "NonCopyable.h"
#include "NonMovable.h"
#include "OpCodeProcessorUtils.h"
#include <vector>
#include <optional>

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

        Vector input;
        input.resize(inputCollection.size());
        std::copy(inputCollection.begin(), inputCollection.end(), input.begin());
        Iterator iterator = input.begin();

        Vector printedOutput;
        size_t index = 0;

        auto GetInputValuesGivenParameterModes =
        [&input]
        (const OpCodeMode opCodeModeA, const OpCodeMode opCodeModeB, const size_t index) -> std::tuple<T,T>
        {
            T tempValue1, tempValue2;

            assert(index < input.size());
            if (opCodeModeA == OpCodeMode::Parameter)
            {
                tempValue1 = input[index];
            }
            else
            {
                assert(input[index] >= 0);
                assert(input[index] < input.size());
                tempValue1 = input[input[index]];
            }

            assert( (index + 1) < input.size());
            if (opCodeModeB == OpCodeMode::Parameter)
            {
                tempValue2 = input[index + 1];
            }
            else
            {
                assert(input[index + 1] >= 0);
                assert(input[index + 1] < input.size());
                tempValue2 = input[input[index + 1]];
            }

            return { tempValue1 , tempValue2 };
        };

        auto GetInputValueGivenParameterMode =
        [&input]
        (const OpCodeMode opCodeMode, const size_t index) -> T
        {
            assert(index < input.size());
            if (opCodeMode == OpCodeMode::Parameter)
            {
                return input[index];
            }
            else
            {
                assert(input[index] >= 0);
                assert(input[index] < input.size());
                return input[input[index]];
            }
        };

        auto SetInputValueGivenParameterMode =
        [&input]
        (const OpCodeMode opCodeMode, const size_t index, const T value) -> void
        {
            assert(index < input.size());
            if (opCodeMode == OpCodeMode::Parameter)
            {
                input[index] = value;
            }
            else
            {
                assert(input[index] >= 0);
                assert(input[index] < input.size());
                input[input[index]] = value;
            }
        };

        auto tryToClaimNumbers = [&input](size_t howManyToClaim, Iterator& iterator) -> std::optional<Vector>
        {
            if ( std::distance(iterator, input.end()) < howManyToClaim )
            {
                return std::nullopt;
            }

            Vector claimedNumbers;
            while (howManyToClaim)
            {
                claimedNumbers.emplace_back(*iterator);
                iterator++;
                howManyToClaim--;
            }
            return claimedNumbers;
        };

        while (index < input.size())
        {
            const auto opCode = ExtractOpCodeFromNumber(input[index]);
            const auto [modA, modB, modC] = ExtractOpCodeModes(input[index]);

            std::tuple<T,T> values;

            switch (opCode)
            {
            case 1:
                // In each iteration we need to have at least 4 parameters left to be processed.
                if (!TryToClaimNumbers(input.size(), 4, index))
                {
                    return {input, printedOutput};
                }

                values = GetInputValuesGivenParameterModes(modA, modB, index + 1);
                SetInputValueGivenParameterMode(OpCodeMode::Position, index + 3, std::get<0>(values) + std::get<1>(values));

                index += 4;
                break;

            case 2:
                // In each iteration we need to have at least 4 parameters left to be processed.
                if (!TryToClaimNumbers(input.size(), 4, index))
                {
                    return {input, printedOutput};
                }

                values = GetInputValuesGivenParameterModes(modA, modB, index + 1);
                SetInputValueGivenParameterMode(OpCodeMode::Position, index + 3, std::get<0>(values) * std::get<1>(values));

                index += 4;
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
                index += 1;
                return {input, printedOutput};

            default:
                // We should never reach this point.
                assert(false);
                return {input, printedOutput};
            }
        }

        return {input, printedOutput};
    }

private:
    [[nodiscard]] bool TryToClaimNumbers(const size_t inputSize, const uint8_t howMany, const size_t index)
    {
        return (inputSize - index) >= howMany;
    }
};
