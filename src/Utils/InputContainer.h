// Copyright 2022 by Georgios Charitos.
// All rights reserved.

#pragma once
#include <InstructionProcessorUtils.h>
#include <cassert>

namespace InstructionProcessor
{

template <typename InputType>
class InputContainer final
{
using InputValueType = InputType::value_type;

public:
    InputContainer(const InputType& input)
    : _input{input} // do a copy here
    , _currentElementIndex{0}
    // We assume thah the provided collection is full
    , _lastElementIndex{_input.size() - 1}
    , _relativeBase{0}
    {}

    /**
    * Check if there are any non-processed OpCodes.
    */
    bool AreThereAnyNonProcessedOpCodes() const
    {
        return _currentElementIndex < _lastElementIndex;
    }

    /**
    * Get the current element.
    * @param mode ParameterMode
    */
    auto GetCurrentElementValue(ParameterMode mode) const
    {
        if (mode == ParameterMode::Position)
        {
            assert(static_cast<IndexType>(_input[_currentElementIndex]) <= _lastElementIndex);
            assert(_input[_currentElementIndex] >= 0);
            return _input[_input[_currentElementIndex]];
        }
        else // ParameterMode::Immediate
        {
            return _input[_currentElementIndex];
        }
    }

    /**
    * Move to the next element.
    */
    void MoveToTheNextElement()
    {
        _currentElementIndex++;
        assert(_currentElementIndex < _input.size());
    }

    /**
    * Extract OpCode from the current element.
    */
    auto GetOpCode() const
    {
        return ExtractOpCodeFromNumber(_input[_currentElementIndex]);
    }

    /**
    * Extract parameter modes from the current element.
    */
    auto GetModes() const
    {
        return ExtractParameterModesFromNumber(_input[_currentElementIndex]);
    }

    /**
    * Find if the container size is large enough to claim the given number of elements.
    * @param numberOfElements The number of elements that are needed for the calculation.
    */
    bool AreThereEnoughElementsToBeClaimed(IndexType numberOfElements) const
    {
        return static_cast<IndexType>(std::distance(_input.begin() + _currentElementIndex, _input.end())) >= numberOfElements;
    }

    /**
    * Store an element based on given index.
    * @param element The element to store at the given index.
    * @param mode ParameterMode
    */
    void StoreElement(InputValueType element, ParameterMode mode)
    {
        if (mode == ParameterMode::Position)
        {
            assert(static_cast<IndexType>(_input[_currentElementIndex]) <= _lastElementIndex);
            assert(_input[_currentElementIndex] >= 0);
            _input[_input[_currentElementIndex]] = element;
        }
        else // ParameterMode::Immediate
        {
            _input[_currentElementIndex] = element;
        }
    };

    /**
    * Return the whole input collection.
    */
    auto GetInputCollection() const
    {
        return _input;
    }

    /**
    * Get an element given iterator.
    * @param it Iterator that points to the element to be returned.
    */
/*     InputType GetElementAt(typename InputType::const_iterator it) const
    {
        assert(*it >= 0);
        assert(static_cast<IndexType>(*it) < _input.size());
        return _input[static_cast<IndexType>(*it)];
    }; */

    /**
    * Get an iterator at given pos plus given offset.
    * @param offset Offset to add to given pos.
    * @param pos Pos to which offset is added.
    */
/*     typename InputType::const_iterator GetIterFromPosPlusOffset(
        InputType offset, InputType pos = 0) const
    {
        assert(!_input.empty());
        assert(offset >= 0);
        assert(pos >= 0);
        assert(static_cast<IndexType>(pos + offset) < _input.size());
        auto iter = _input.begin() + static_cast<IndexType>(pos);
        std::advance(iter, static_cast<IndexType>(offset));
        return iter;
    } */

    /**
    * Update the relative base given the new one.
    * @param newRelativeBase New relative base.
    */
/*     void UpdateRelativeBase(InputType newRelativeBase)
    {
        _relativeBase += newRelativeBase;
    } */

    /**
    * Iterate collection and run given function
    * by providing the current element iterator.
    * @param func Function to be run.
    */
/*     template <typename Functor>
    auto IterateCollection(Functor func)
    {
        while (_currentIndex < _input.size())
        {
            _currentElement = _input.begin() + _currentIndex;
            auto result = func(_currentElement);
            if (result.has_value())
            {
                return GetInput();
            }
        }

        return GetInput();
    } */

private:
    InputType _input;
    IndexType _currentElementIndex;
    // The last element might not be in the last collection's position.
    // This might happen because of resizing the collection.
    IndexType _lastElementIndex;
    // Only modified by OpCodeNine
    InputType _relativeBase;
};

}
