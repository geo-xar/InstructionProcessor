#pragma once

#include <algorithm>
#include <cstdint>

using DigitType = uint8_t;
using IndexType = std::size_t;
using IntegerType = uint32_t;

/**
* Build number given collection of digits.
* @param digits The collection of digits.
*/
template <typename NumberType, typename DigitsCollection>
[[nodiscard]] inline NumberType BuildNumberFromDigits(const DigitsCollection& digits)
{
    if (digits.empty())
    {
        return 0;
    }

    NumberType result = 0;
    IntegerType multiplier = 1;

    auto iterator = digits.end() - 1;
    while (true)
    {
        if (*iterator < 0)
        {
            result += ( (*iterator) * -1 ) * multiplier;
        }
        else
        {
            result += *iterator * multiplier;
        }
        multiplier *= 10;

        if (iterator == digits.begin())
        {
            break;
        }
        else
        {
            iterator--;
        }
    }
    return result;
}

/**
* Get the digits given a number.
* @param number The number to be split to digits. 
*/
template <typename NumberType>
[[nodiscard]] inline std::vector<DigitType> GetDigitsFromNumber(NumberType number)
{
    // If negative number then make it positive.
    if (number < 0)
    {
        number *= -1;
    }

    // If 0 then return 0.
    if (!number)
    {
        return {0};
    }

    std::vector<DigitType> digits;
    while (number)
    {
        digits.emplace_back(number % 10);
        number /= 10;
    }

    std::reverse(digits.begin(), digits.end());
    return digits;
}

/**
* Find if the distance between iterator and collection end is more or less than given input.
* @param collection A collection of numbers.
* @param iterator An iterator to the given collection.
* @param numberOfElements The number of elements that are needed for the calculation.
*/
template <typename CollectionType, typename Iterator>
[[nodiscard]] inline bool AreThereEnoughElementsIntoTheCollection(
    const CollectionType& collection,
    const Iterator iterator,
    IndexType numberOfElements)
{
    return static_cast<IndexType>(std::distance<typename CollectionType::const_iterator>(iterator, collection.end())) >= numberOfElements;
}
