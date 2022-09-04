#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>
#include <optional>

namespace InstructionProcessor
{

using DigitType = uint8_t;
using IndexType = std::size_t;
using IntegerType = uint32_t;

/**
* Build number given collection of digits.
* @param digits The collection of digits.
*/
template <typename NumberType, typename DigitsCollection>
requires std::integral<NumberType> && std::is_same<NumberType, typename DigitsCollection::value_type>::value
[[nodiscard]] inline std::optional<NumberType> BuildNumberFromDigits(const DigitsCollection &digits)
{
    if (digits.empty())
    {
        return std::nullopt;
    }

    NumberType result = 0;
    NumberType multiplier = 1;

    auto iterator = digits.end() - 1;
    while (true)
    {
        if (*iterator < 0)
        {
            result += (static_cast<NumberType>(*iterator) * -1) * multiplier;
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
using DigitsCollection = std::vector<DigitType>;
template <typename NumberType>
requires std::integral<NumberType>
[[nodiscard]] inline DigitsCollection GetDigitsFromNumber(NumberType number)
{
    // If negative number then make it positive.
    if constexpr(std::is_signed_v<NumberType>)
    {
        if (number < 0)
        {
            number *= -1;
        }
    }

    // If 0 then return 0.
    if (!number)
    {
        return {0};
    }

    DigitsCollection digits;
    while (number)
    {
        digits.emplace_back(number % 10);
        number /= 10;
    }

    std::reverse(digits.begin(), digits.end());
    return digits;
}

}
