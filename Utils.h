#pragma once

#include <cstdint>
#include <algorithm>

/**
* Build number given collection of digits.
* @param digits The collection of digits.
*/
template <typename ReturnType, typename DigitsVector>
[[nodiscard]] inline ReturnType BuildNumberFromDigits(const DigitsVector& digits)
{
    if (digits.empty())
    {
        return 0;
    }

    ReturnType result = 0;
    uint16_t multiplier = 1;

    auto iterator = digits.end()-1;
    while (1)
    {
        result += *iterator * multiplier;
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
[[nodiscard]] inline std::vector<uint8_t> GetDigitsFromNumber(NumberType number)
{
    std::vector<uint8_t> digits;

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

    while (number)
    {
        digits.emplace_back(number % 10);
        number /= 10;
    }

    std::reverse(digits.begin(), digits.end());
    return digits;
}
