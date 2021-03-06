#pragma once

#include "Utils.h"
#include <cassert>
#include <stdexcept>

/**
* Parameter mode options.
*/
enum class ParameterMode : uint8_t
{
    Position,
    Immediate
};

using ParameterModeVector = std::vector<ParameterMode>;

/**
* Extract the OpCode given a number.
* @param number The number to extract the OpCode
*/
template <typename NumberType>
[[nodiscard]] inline uint16_t ExtractOpCodeFromNumber(const NumberType number)
{
    auto digits = GetDigitsFromNumber(number);

    assert(!digits.empty());

    std::reverse(digits.begin(), digits.end());
    if (digits.size() == 1)
    {
        return digits[0];
    }
    else
    {
        return digits[1] * 10 + digits[0];
    }
}

inline void ValidateParameterMode(const uint8_t digit)
{
    if (digit != 0 && digit != 1)
    {
        throw std::runtime_error("Invalid OpCode mode: " + std::to_string(digit));
    }
}

/**
* Extract the parameter modes given a number.
* @param number The number to extract the parameter modes.
*/
template <typename NumberType>
[[nodiscard]] inline ParameterModeVector ExtractParameterModesFromNumber(const NumberType number)
{
    auto digits = GetDigitsFromNumber(number);

    assert(!digits.empty());

    std::reverse(digits.begin(), digits.end());
    if (digits.size() <= 2)
    {
        return { ParameterMode::Position, ParameterMode::Position, ParameterMode::Position };
    }
    else if (digits.size() == 3)
    {
        ValidateParameterMode(digits[2]);

        ParameterMode parameterMode = ParameterMode::Position;
        if (digits[2] == 1)
        {
            parameterMode = ParameterMode::Immediate;
        }

        return { parameterMode, ParameterMode::Position, ParameterMode::Position };
    }
    else if (digits.size() == 4)
    {
        ValidateParameterMode(digits[2]);
        ValidateParameterMode(digits[3]);

        ParameterMode parameterMode1 = ParameterMode::Position;
        if (digits[2] == 1)
        {
            parameterMode1 = ParameterMode::Immediate;
        }

        ParameterMode parameterMode2 = ParameterMode::Position;
        if (digits[3] == 1)
        {
            parameterMode2 = ParameterMode::Immediate;
        }

        return { parameterMode1, parameterMode2, ParameterMode::Position };
    }
    else if (digits.size() == 5)
    {
        ValidateParameterMode(digits[2]);
        ValidateParameterMode(digits[3]);
        ValidateParameterMode(digits[4]);

        ParameterMode parameterMode1 = ParameterMode::Position;
        if (digits[2] == 1)
        {
            parameterMode1 = ParameterMode::Immediate;
        }

        ParameterMode parameterMode2 = ParameterMode::Position;
        if (digits[3] == 1)
        {
            parameterMode2 = ParameterMode::Immediate;
        }

        ParameterMode parameterMode3 = ParameterMode::Position;
        if (digits[4] == 1)
        {
            parameterMode3 = ParameterMode::Immediate;
        }

        return { parameterMode1, parameterMode2, parameterMode3 };
    }
    else
    {
        // We should never reach this else statement.
        assert(false);
        return { ParameterMode::Position, ParameterMode::Position, ParameterMode::Position };
    }
}
