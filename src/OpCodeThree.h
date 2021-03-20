#pragma once

#include "OpCodeInterface.h"
#include "OpCodeProcessorUtils.h"
#include <vector>

/**
* @class OpCodeThree specialisation.
* Claim a number and store the user input value to the index which it points to.
*/
template <typename T>
class OpCodeThree final : public OpCode
{
using Vector = std::vector<T>;
using VectorIterator = typename Vector::iterator;

public:
    /**
    * Constructor
    * @param input    The user input vector.
    * @param userInput User selection optional.
    */
    OpCodeThree(Vector& input, const std::optional<T>& userInput)
    : _input{input}
    , _userInput{userInput}
    {}

    ~OpCodeThree() final = default;

    /**
    * Claim a number and store the user input value to the index which it points to.
    */
    [[nodiscard]] OpCode::ReturnType Execute(std::any& nextElementIter, std::any& endIter) final
    {
        VectorIterator& iterBegin = std::any_cast<VectorIterator&>(nextElementIter);
        VectorIterator& iterEnd = std::any_cast<VectorIterator&>(endIter);

        // Check if there are enough numbers to be claimed to complete the operation.
        // A single number is needed (index) to store the user input.
        if (!AreThereEnoughElementsIntoTheCollection(iterBegin, iterEnd, 1))
        {
            return { std::nullopt, {} };
        }

        // Claim the index to store the user input value.
        const auto index = *iterBegin;
        assert( (index >= 0) && (static_cast<IndexType>(index) < _input.size()) );
        assert(_userInput.has_value());
        _input[index] = _userInput.value();

        // Jump to the next number (if any).
        iterBegin++;

        // What we return here it is only useful for error reporting.
        // Whatever different than std::nullopt is equal to SUCCESS.
        return { std::make_optional<Result>(), {iterBegin} };
    };

private:
    Vector& _input;
    const std::optional<T>& _userInput;
};
