#include "catch2.hpp"
#include "OpCodeProcessor.h"
#include <algorithm>

TEST_CASE("OpCodeSix - Single element, input shall not be processed", "[OpCodeProcessor]")
{
    std::vector<uint8_t> input =
    {
        6
    };

    OpCodeProcessor opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions<uint8_t>(input);
    REQUIRE(modifiedInput.size() == input.size());
    CHECK(std::equal(modifiedInput.begin(), modifiedInput.end(), input.begin()));
}

TEST_CASE("OpCodeSix - First parameter is non-zero, do nothing (ParameterMode::Immediate)", "[OpCodeProcessor]")
{
    std::vector<int> input =
    {
        106,1,99
    };

    OpCodeProcessor opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions<int>(input);
    REQUIRE(modifiedInput.size() == input.size());
    CHECK(std::equal(modifiedInput.begin(), modifiedInput.end(), input.begin()));
}

TEST_CASE("OpCodeSix - Move the instruction pointer to the end of the input and then exit (ParameterMode::Position)", "[OpCodeProcessor]")
{
    std::vector<int> input =
    {
        6,4,3,11,0,4,5,6,7,8,9,99
    };

    OpCodeProcessor opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions<int>(input);
    REQUIRE(modifiedInput.size() == input.size());
    CHECK(std::equal(modifiedInput.begin(), modifiedInput.end(), input.begin()));
}

TEST_CASE("OpCodeSix - Move the instruction pointer to the end of the input and then exit (ParameterMode::Immediate)", "[OpCodeProcessor]")
{
    std::vector<int> input =
    {
        1106,0,11,2,3,4,5,6,7,8,9,99
    };

    OpCodeProcessor opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions<int>(input);
    REQUIRE(modifiedInput.size() == input.size());
    CHECK(std::equal(modifiedInput.begin(), modifiedInput.end(), input.begin()));
}
