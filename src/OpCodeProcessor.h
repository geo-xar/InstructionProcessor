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
    * 99: The program is finished and shall immediately halt.
    *
    * @param inputCollection Collection of numbers to be processed.
    * @param userSelection Optional user input to be stored in the collection (OpCodeThree).
    *
    * @return Modified input collection and printed output.
    */
    [[nodiscard]] ResultType ProcessInstructions(
        const Vector& inputCollection, std::optional<InputType> userSelection = std::nullopt)
    {
        // There is no reason doing any kind of calculations if the input collection is empty.
        if (!inputCollection.size())
        {
            return { {}, {} };
        }

        // Copy the input collection to a local variable.
        Vector input;
        input.resize(inputCollection.size());
        std::copy(inputCollection.begin(), inputCollection.end(), input.begin());

        // Declare the printed output collection.
        Vector printedOutput;

        // Declare the iterator which is used to manipulate the input collection.
        using IteratorType = typename Vector::iterator;
        IteratorType iterator = input.begin();

        // Function to set the element to the collection given an index
        using SetElementAtIndexFunction = std::function<void(IndexType index, InputType element)>;
        SetElementAtIndexFunction SetElementAtIndex =
        [&input](IndexType index, InputType element) mutable
        {
            assert( (index >= 0) && (index < input.size()) );
            input[index] = element;
        };

        // Function to get an element from the collection given an iterator by using the iterator value as index
        using GetElementAtFunction = std::function<InputType(IteratorType& iterator)>;
        GetElementAtFunction GetElementAt =
        [&input](IteratorType& iterator)
        {
            assert(*iterator >= 0);
            assert(static_cast<IndexType>(*iterator) < input.size());
            return input[*iterator];
        };

        // Function to get an iterator from the beginning of the collection plus given offset
        using GetIterFromBeginPlusOffsetFunction = std::function<IteratorType(InputType offset)>;
        GetIterFromBeginPlusOffsetFunction GetIterFromBeginPlusOffset =
        [&input](InputType offset)
        {
            assert(!input.empty());
            auto offsetCasted = static_cast<IndexType>(offset);
            assert(offsetCasted >= 0);
            assert(offsetCasted < input.size() );
            return input.begin() + offsetCasted;
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
                pendingInstructions.emplace_back( std::move(
                    std::make_unique< OpCodeOne<InputType, IteratorType, SetElementAtIndexFunction, GetElementAtFunction> >
                            (SetElementAtIndex, GetElementAt, parameterModes) ) );
                break;
            }

            case 2:
            {
                pendingInstructions.emplace_back( std::move(
                    std::make_unique< OpCodeTwo<InputType, IteratorType, SetElementAtIndexFunction, GetElementAtFunction> >
                            (SetElementAtIndex, GetElementAt, parameterModes) ) );
                break;
            }

            case 3:
            {
                pendingInstructions.emplace_back( std::move(
                    std::make_unique< OpCodeThree<InputType, IteratorType, SetElementAtIndexFunction> >
                            (SetElementAtIndex, userSelection) ) );
                break;
            }

            case 4:
            {
                pendingInstructions.emplace_back( std::move(
                    std::make_unique< OpCodeFour<InputType, IteratorType, GetElementAtFunction> >
                            (GetElementAt, parameterModes, printedOutput) ) );
                break;
            }

            case 5:
            {
                pendingInstructions.emplace_back( std::move(
                    std::make_unique<OpCodeFive<InputType, IteratorType, GetElementAtFunction, GetIterFromBeginPlusOffsetFunction> >
                            (GetElementAt, GetIterFromBeginPlusOffset, parameterModes) ) );
                break;
            }

            case 6:
            {
                pendingInstructions.emplace_back( std::move(
                    std::make_unique< OpCodeSix<InputType, IteratorType, GetElementAtFunction, GetIterFromBeginPlusOffsetFunction> >
                            (GetElementAt, GetIterFromBeginPlusOffset, parameterModes) ) );
                break;
            }

            case 7:
            {
                pendingInstructions.emplace_back( std::move(
                    std::make_unique< OpCodeSeven<InputType, IteratorType, SetElementAtIndexFunction, GetElementAtFunction> >
                            (SetElementAtIndex, GetElementAt, parameterModes) ) );
                break;
            }

            case 8:
            {
                pendingInstructions.emplace_back( std::move(
                    std::make_unique< OpCodeEight<InputType, IteratorType, SetElementAtIndexFunction, GetElementAtFunction> >
                            (SetElementAtIndex, GetElementAt, parameterModes) ) );
                break;
            }

            case 99:
            {
                pendingInstructions.emplace_back( std::make_unique<OpCodeNinetyNine>() );
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
