#pragma once

#include "Utils.h"
#include <cassert>
#include <stdexcept>

/**
* OpCode mode options.
*/
enum class OpCodeMode : uint8_t
{
    Position,
    Parameter
};

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

inline void ValidateOpCodeMode(const uint8_t digit)
{
    if (digit != 0 && digit != 1)
    {
        throw std::runtime_error("Invalid OpCode mode: " + digit);
    }
}

/**
* Extract the OpCode modes given a number.
* @param number The number to extract the OpCode modes.
*/
using OpCodeModeVector = std::vector<OpCodeMode>;
template <typename NumberType>
[[nodiscard]] inline OpCodeModeVector ExtractParameterModesFromNumber(const NumberType number)
{
    auto digits = GetDigitsFromNumber(number);

    assert(!digits.empty());

    std::reverse(digits.begin(), digits.end());
    if (digits.size() <= 2)
    {
        return { OpCodeMode::Position, OpCodeMode::Position, OpCodeMode::Position };
    }
    else if (digits.size() == 3)
    {
        ValidateOpCodeMode(digits[2]);

        OpCodeMode opCodeMode = OpCodeMode::Position;
        if (digits[2] == 1)
        {
            opCodeMode = OpCodeMode::Parameter;
        }

        return { opCodeMode, OpCodeMode::Position, OpCodeMode::Position };
    }
    else if (digits.size() == 4)
    {
        ValidateOpCodeMode(digits[2]);
        ValidateOpCodeMode(digits[3]);

        OpCodeMode opCodeMode1 = OpCodeMode::Position;
        if (digits[2] == 1)
        {
            opCodeMode1 = OpCodeMode::Parameter;
        }

        OpCodeMode opCodeMode2 = OpCodeMode::Position;
        if (digits[3] == 1)
        {
            opCodeMode2 = OpCodeMode::Parameter;
        }

        return { opCodeMode1, opCodeMode2, OpCodeMode::Position };
    }
    else if (digits.size() == 5)
    {
        ValidateOpCodeMode(digits[2]);
        ValidateOpCodeMode(digits[3]);
        ValidateOpCodeMode(digits[4]);

        OpCodeMode opCodeMode1 = OpCodeMode::Position;
        if (digits[2] == 1)
        {
            opCodeMode1 = OpCodeMode::Parameter;
        }

        OpCodeMode opCodeMode2 = OpCodeMode::Position;
        if (digits[3] == 1)
        {
            opCodeMode2 = OpCodeMode::Parameter;
        }

        OpCodeMode opCodeMode3 = OpCodeMode::Position;
        if (digits[4] == 1)
        {
            opCodeMode3 = OpCodeMode::Parameter;
        }

        return { opCodeMode1, opCodeMode2, opCodeMode3 };
    }
    else
    {
        // We should never reach this else statement.
        assert(false);
        return { OpCodeMode::Position, OpCodeMode::Position, OpCodeMode::Position };
    }
}
