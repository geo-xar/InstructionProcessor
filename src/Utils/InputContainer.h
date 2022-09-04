#pragma once
#include <iterator>

namespace InstructionProcessor
{

template <typename InputType>
class InputContainer final
{
public:
    explicit InputContainer(const InputType& input)
    : _input{input}, _currentElement {_input.begin()}
    {}

    /**
    * Get an iterator to the beginning of the collection.
    */
    auto Begin() const { return _input.begin(); }

    /**
    * Get an iterator to the end of the collection.
    */
    auto End() const { return _input.end(); }

    /**
    * Find if the container size is large enough to claim the given number of elements.
    * @param numberOfElements The number of elements that are needed for the calculation.
    */
    bool AreThereEnoughElementsToBeClaimed(IndexType numberOfElements) const
    {
        return static_cast<IndexType>(std::distance(_currentElement, _input.end())) >= numberOfElements;
    }

    auto GetInput() const
    {
        return _input;
    }

private:
    InputType _input;
    typename InputType::const_iterator _currentElement;
};

}
