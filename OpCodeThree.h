#pragma once

#include "OpCodeInterface.h"
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
    * @param iterator User input vector iterator
    *                 which points to the first number to be claimed.
    * @param userInput User selection optional.
    */
    OpCodeThree(
        Vector& input,
        VectorIterator& iterator,
        const std::optional<T>& userInput)
    : _input{input}
    , _iterator{iterator}
    , _userInput{userInput}
    {}

    ~OpCodeThree() final = default;

    /**
    * Claim a number and store the user input value to the index which it points to.
    */
    [[nodiscard]] std::optional<Result> Execute() final
    {
        // Check if there are enough numbers to be claimed to complete the operation.
        // A single number is needed (index) to store the user input.
        if ( std::distance(_iterator, _input.end()) < 1 )
        {
            return std::nullopt;
        }

        // Claim the index to store the user input value.
        const auto index = *_iterator;
        assert( (index >= 0) && (index < _input.size()) );
        assert(_userInput.has_value());
        _input[index] = _userInput.value();

        // What we return here it is only useful for error reporting.
        // Whatever different than std::nullopt is equal to SUCCESS.
        return std::make_optional<Result>();
    };

private:
    Vector& _input;
    VectorIterator& _iterator;
    const std::optional<T> _userInput;
};
