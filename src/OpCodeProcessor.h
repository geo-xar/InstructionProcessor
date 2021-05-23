#pragma once

#include "NonCopyable.h"
#include "NonMovable.h"
#include "OpCodeProcessorUtils.h"
#include "OpCodeOne.h"
#include "OpCodeTwo.h"
#include "OpCodeThree.h"
#include "OpCodeFour.h"
#include "OpCodeFive.h"
#include "OpCodeSix.h"
#include "OpCodeSeven.h"
#include "OpCodeEight.h"
#include "OpCodeNinetyNine.h"

#include <vector>
#include <optional>
#include <tuple>
#include <deque>
#include <memory>
#include <functional>

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
        using IteratorType = typename Vector::iterator;
        IteratorType iterator = input.begin();

        using SetFunctionType = std::function<void(IndexType index, T element)>;
        SetFunctionType SetElementAtIndex =
        [&input](IndexType index, T element) mutable
        {
            assert( (index >= 0) && (index < input.size()) );
            input[index] = element;
        };

        using GetFunctionType = std::function<T(IteratorType& iterator)>;
        GetFunctionType GetElementAt =
        [&input](IteratorType& iterator)
        {
            assert(*iterator >= 0);
            assert(static_cast<IndexType>(*iterator) < input.size());
            return input[*iterator];
        };

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

            case 1:
            {
                pendingInstructions.emplace_back( std::move( std::make_unique<OpCodeOne<T, IteratorType>>(SetElementAtIndex, GetElementAt, parameterModes) ) );
                break;
            }

            case 2:
            {
                pendingInstructions.emplace_back( std::move( std::make_unique<OpCodeTwo<T>>(input, parameterModes) ) );
                break;
            }

            case 3:
            {
                pendingInstructions.emplace_back( std::move( std::make_unique<OpCodeThree<T>>(input, userSelection) ) );
                break;
            }

            case 4:
            {
                pendingInstructions.emplace_back( std::move( std::make_unique<OpCodeFour<T>>(input, parameterModes, printedOutput) ) );
                break;
            }

            case 5:
            {
                pendingInstructions.emplace_back( std::move( std::make_unique<OpCodeFive<T>>(input, parameterModes) ) );
                break;
            }

            case 6:
            {
                pendingInstructions.emplace_back( std::move( std::make_unique<OpCodeSix<T>>(input, parameterModes) ) );
                break;
            }

            case 7:
            {
                pendingInstructions.emplace_back( std::move( std::make_unique<OpCodeSeven<T>>(input, parameterModes) ) );
                break;
            }

            case 8:
            {
                pendingInstructions.emplace_back( std::move( std::make_unique<OpCodeEight<T>>(input, parameterModes) ) );
                break;
            }

            case 99:
            {
                pendingInstructions.emplace_back( std::move( std::make_unique<OpCodeNinetyNine<T>>() ) );
                break;
            }

            default:
            {
                // We should never reach this point.
                throw std::runtime_error("Non-supported OpCode: " + opCode);
            }

            } // end of switch(OpCode)

            // If no more instructions to be processed then terminate the execution.
            // The following if statement will never be true at the moment since we always
            // emplace an instruction to the queue and immediately execute it.
            // It might be needed in the future if we produce more than we consume.
            //if (pendingInstructions.empty())
            //{
            //    return {input, printedOutput};
            //}

            // Retrieve the first instruction to be executed.
            // If the result optional has no value then terminate the execution.
            OpCode* opCodeToBeExecuted = pendingInstructions.front().get();
            std::any nextElement{iterator};
            std::any iterEnd{input.end()};
            auto result = opCodeToBeExecuted->Execute(nextElement, iterEnd);
            if (!result.first.has_value())
            {
                return {input, printedOutput};
            }
            else
            {
                iterator = std::any_cast<IteratorType&>(result.second);
            }

            // Remove the instruction which was just executed.
            pendingInstructions.pop_front();
        }

        return {input, printedOutput};
    }
};
