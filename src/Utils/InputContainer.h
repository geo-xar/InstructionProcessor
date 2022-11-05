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
public:
    using InputValueType = typename InputType::value_type;

    InputContainer(const InputType& input)
    : _input{input} // do a copy here
    , _currentElementIndex{0}
    // We assume that the provided collection is full
    , _lastElementIndex{_input.size() - 1}
    , _relativeBase{0}
    {}

    /**
    * Check if there are any non-processed OpCodes.
    */
    bool AreThereAnyNonProcessedOpCodes()
    {
        return _currentElementIndex <= _lastElementIndex;
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
    * Store an element based on current index.
    * @param element The element to store at the current index.
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
    * Store an element based on current index.
    * @param element The element to store at the current index.
    */
    void StoreElement(InputValueType element)
    {
        assert(static_cast<IndexType>(_input[_currentElementIndex]) <= _lastElementIndex);
        assert(_input[_currentElementIndex] >= 0);
        _input[_input[_currentElementIndex]] = element;
    };

    /**
    * Return the whole input collection.
    */
    auto GetInputCollection() const
    {
        return _input;
    }

    /**
    * Update the current index based on the current element value.
    * @param mode ParameterMode
    */
    void UpdateCurrentElementIndex(ParameterMode mode)
    {
        if (mode == ParameterMode::Position)
        {
            assert(static_cast<IndexType>(_input[_currentElementIndex]) <= _lastElementIndex);
            assert(_input[_currentElementIndex] >= 0);
            _currentElementIndex = _input[_input[_currentElementIndex]];
        }
        else // ParameterMode::Immediate
        {
            _currentElementIndex = _input[_currentElementIndex];
        }
    }

    /**
    * Update the relative base.
    * @param mode ParameterMode
    */
    void UpdateRelativeBase(ParameterMode mode)
    {
        if (mode == ParameterMode::Position)
        {
            assert(static_cast<IndexType>(_input[_currentElementIndex]) <= _lastElementIndex);
            assert(_input[_currentElementIndex] >= 0);
            _relativeBase += _input[_input[_currentElementIndex]];
        }
        else // ParameterMode::Immediate
        {
            _relativeBase += _input[_currentElementIndex];
        }
    }

private:
    InputType _input;
    IndexType _currentElementIndex;
    // The last element might not be in the last collection's position.
    // This might happen because of resizing the collection.
    IndexType _lastElementIndex;
    // Only modified by OpCodeNine
    InputValueType _relativeBase;
};

}
