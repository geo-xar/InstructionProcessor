#pragma once
#include <iterator>

namespace InstructionProcessor
{

template <typename InputType>
class InputContainer final
{
public:
    InputContainer(const InputType& input)
    : _input{input}
    , _currentElement{_input.begin()}
    , _currentIndex{0}
    , _relativeBase{0}
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

    /**
    * Store an element based on given index.
    * @param index The index to store the element to.
    * @param element The element to store at the given index.
    */
    void SetElementAtIndex(InputType index, InputType element)
    {
        assert((index >= 0) && (static_cast<IndexType>(index) < _input.size()));
        _input[static_cast<IndexType>(index)] = element;
    };

    /**
    * Get an element given iterator.
    * @param it Iterator that points to the element to be returned.
    */
    InputType GetElementAt(typename InputType::const_iterator it) const
    {
        assert(*it >= 0);
        assert(static_cast<IndexType>(*it) < _input.size());
        return _input[static_cast<IndexType>(*it)];
    };

    /**
    * Get an iterator at given pos plus given offset.
    * @param offset Offset to add to given pos.
    * @param pos Pos to which offset is added.
    */
    typename InputType::const_iterator GetIterFromPosPlusOffset(
        InputType offset, InputType pos = 0) const
    {
        assert(!_input.empty());
        assert(offset >= 0);
        assert(pos >= 0);
        assert(static_cast<IndexType>(pos + offset) < _input.size());
        auto iter = _input.begin() + static_cast<IndexType>(pos);
        std::advance(iter, static_cast<IndexType>(offset));
        return iter;
    }

    /**
    * Update the relative base given the new one.
    * @param newRelativeBase New relative base.
    */
    void UpdateRelativeBase(InputType newRelativeBase)
    {
        _relativeBase += newRelativeBase;
    }

    /**
    * Get the whole input collection.
    */
    const InputType& GetInput() const { return _input; }

    /**
    * Iterate collection and run given function
    * by providing the current element iterator.
    * @param func Function to be run.
    */
    template <typename Functor>
    auto IterateCollection(Functor func)
    {
        while (_currentIndex < _input.size())
        {
            _currentElement = _input.begin() +_currentIndex;
            auto result = func(_currentElement);
            if (result.has_value())
            {
                return GetInput();
            }
        }

        return GetInput();
    }

private:
    InputType _input;
    typename InputType::const_iterator _currentElement;
    IndexType _currentIndex;
    // Only modified by OpCodeNine
    InputType _relativeBase;
};

}
