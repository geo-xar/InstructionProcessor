// Copyright 2022 by Georgios Charitos.
// All rights reserved.

#include "catch2/catch.hpp"
#include <InstructionProcessor.h>
#include <algorithm>

using namespace InstructionProcessor;

TEST_CASE("OpCodeSix - Single element, input shall not be processed", "[OpCodeProcessor]")
{
    std::vector<uint8_t> input =
    {
        6
    };

    OpCodeProcessor<uint8_t> opCodeProcessor;
    auto result = opCodeProcessor.ProcessInstructions(input);
    REQUIRE(result.has_value());
    auto [modifiedInput, printedOut] = result.value();
    REQUIRE(modifiedInput.size() == input.size());
    CHECK(std::equal(modifiedInput.begin(), modifiedInput.end(), input.begin()));
}

TEST_CASE("OpCodeSix - 1st parameter is non-zero, do nothing", "[OpCodeProcessor]")
{
    std::vector<int> input =
    {
        106,1,99
    };

    OpCodeProcessor<int> opCodeProcessor;
    auto result = opCodeProcessor.ProcessInstructions(input);
    REQUIRE(result.has_value());
    auto [modifiedInput, printedOut] = result.value();
    REQUIRE(modifiedInput.size() == input.size());
    CHECK(std::equal(modifiedInput.begin(), modifiedInput.end(), input.begin()));
}

TEST_CASE("OpCodeSix - Move the instruction pointer to the end of the input and then exit (ParameterMode::Position)", "[OpCodeProcessor]")
{
    std::vector<int> input =
    {
        6,4,3,11,0,4,5,6,7,8,9,99
    };

    OpCodeProcessor<int> opCodeProcessor;
    auto result = opCodeProcessor.ProcessInstructions(input);
    auto [modifiedInput, printedOut] = result.value();
    REQUIRE(modifiedInput.size() == input.size());
    CHECK(std::equal(modifiedInput.begin(), modifiedInput.end(), input.begin()));
}

TEST_CASE("OpCodeSix - Move the instruction pointer to the end of the input and then exit (ParameterMode::Immediate)", "[OpCodeProcessor]")
{
    std::vector<int> input =
    {
        1106,0,11,2,3,4,5,6,7,8,9,99
    };

    OpCodeProcessor<int> opCodeProcessor;
    auto result = opCodeProcessor.ProcessInstructions(input);
    auto [modifiedInput, printedOut] = result.value();
    REQUIRE(modifiedInput.size() == input.size());
    CHECK(std::equal(modifiedInput.begin(), modifiedInput.end(), input.begin()));
}
