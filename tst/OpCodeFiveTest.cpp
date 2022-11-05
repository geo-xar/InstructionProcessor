// Copyright 2022 by Georgios Charitos.
// All rights reserved.

#include "catch2/catch.hpp"
#include <InstructionProcessor.h>
#include <algorithm>

using namespace InstructionProcessor;

TEST_CASE("OpCodeFive - Single element, input shall not be processed", "[OpCodeProcessor]")
{
    std::vector<uint8_t> input =
    {
        5
    };

    OpCodeProcessor<uint8_t> opCodeProcessor;
    auto result = opCodeProcessor.ProcessInstructions(input);
    REQUIRE(result.has_value());
    auto [modifiedInput, printedOut] = result.value();
    REQUIRE(modifiedInput.size() == input.size());
    CHECK(std::equal(modifiedInput.begin(), modifiedInput.end(), input.begin()));
}

TEST_CASE("OpCodeFive - First parameter is zero, do nothing (ParameterMode::Immediate)", "[OpCodeProcessor]")
{
    std::vector<int> input =
    {
        105,0,99
    };

    OpCodeProcessor<int> opCodeProcessor;
    auto result = opCodeProcessor.ProcessInstructions(input);
    REQUIRE(result.has_value());
    auto [modifiedInput, printedOut] = result.value();
    REQUIRE(modifiedInput.size() == input.size());
    CHECK(std::equal(modifiedInput.begin(), modifiedInput.end(), input.begin()));
}

TEST_CASE("OpCodeFive - Move the instruction pointer to the end of the input and then exit (ParameterMode::Position)", "[OpCodeProcessor]")
{
    std::vector<int> input =
    {
        5,11,1,2,3,4,5,6,7,8,9,99
    };

    OpCodeProcessor<int> opCodeProcessor;
    auto result = opCodeProcessor.ProcessInstructions(input);
    REQUIRE(result.has_value());
    auto [modifiedInput, printedOut] = result.value();
    REQUIRE(modifiedInput.size() == input.size());
    CHECK(std::equal(modifiedInput.begin(), modifiedInput.end(), input.begin()));
}

TEST_CASE("OpCodeFive - Move the instruction pointer to the end of the input and then exit (ParameterMode::Immediate)", "[OpCodeProcessor]")
{
    std::vector<int> input =
    {
        1105,1,11,2,3,4,5,6,7,8,9,99
    };

    OpCodeProcessor<int> opCodeProcessor;
    auto result = opCodeProcessor.ProcessInstructions(input);
    REQUIRE(result.has_value());
    auto [modifiedInput, printedOut] = result.value();
    REQUIRE(modifiedInput.size() == input.size());
    CHECK(std::equal(modifiedInput.begin(), modifiedInput.end(), input.begin()));
}
