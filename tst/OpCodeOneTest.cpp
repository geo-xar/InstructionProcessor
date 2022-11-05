// Copyright 2022 by Georgios Charitos.
// All rights reserved.

#include "catch2/catch.hpp"
#include <InstructionProcessor.h>

using namespace InstructionProcessor;

TEST_CASE("OpCodeOne - Single element, input shall not be processed", "[OpCodeProcessor]")
{
    std::vector<uint8_t> input =
    {
        1
    };

    OpCodeProcessor<uint8_t> opCodeProcessor;
    auto result = opCodeProcessor.ProcessInstructions(input);
    REQUIRE(result.has_value());
    auto [modifiedInput, printedOut] = result.value();
    CHECK(modifiedInput == input);
}

TEST_CASE("OpCodeOne - Two elements, input shall not be processed", "[OpCodeProcessor]")
{
    std::vector<uint8_t> input =
    {
        1,2
    };

    OpCodeProcessor<uint8_t> opCodeProcessor;
    auto result = opCodeProcessor.ProcessInstructions(input);
    REQUIRE(result.has_value());
    auto [modifiedInput, printedOut] = result.value();
    CHECK(modifiedInput == input);
}

TEST_CASE("OpCodeOne - Three elements, input shall not be processed", "[OpCodeProcessor]")
{
    std::vector<uint8_t> input =
    {
        1,2,3
    };

    OpCodeProcessor<uint8_t> opCodeProcessor;
    auto result = opCodeProcessor.ProcessInstructions(input);
    REQUIRE(result.has_value());
    auto [modifiedInput, printedOut] = result.value();
    CHECK(modifiedInput == input);
}

TEST_CASE("OpCodeOne - Four elements - parameter modes: Position-Position", "[OpCodeProcessor]")
{
    std::vector<uint8_t> input =
    {
        1,1,2,0
    };

    OpCodeProcessor<uint8_t> opCodeProcessor;
    auto result = opCodeProcessor.ProcessInstructions(input);
    REQUIRE(result.has_value());
    auto [modifiedInput, printedOut] = result.value();
    REQUIRE(modifiedInput.size());
    CHECK(modifiedInput[0] == 3);
}

TEST_CASE("OpCodeOne - Four elements - parameter modes: Position-Parameter", "[OpCodeProcessor]")
{
    std::vector<int> input =
    {
        1001,1,-2,2
    };

    OpCodeProcessor<int> opCodeProcessor;
    auto result = opCodeProcessor.ProcessInstructions(input);
    REQUIRE(result.has_value());
    auto [modifiedInput, printedOut] = result.value();
    REQUIRE(modifiedInput.size() >= 3);
    CHECK(modifiedInput[2] == -1);
}

TEST_CASE("OpCodeOne - Four elements - parameter modes: Parameter-Position", "[OpCodeProcessor]")
{
    std::vector<int> input =
    {
        101,-1,2,2
    };

    OpCodeProcessor<int> opCodeProcessor;
    auto result = opCodeProcessor.ProcessInstructions(input);
    REQUIRE(result.has_value());
    auto [modifiedInput, printedOut] = result.value();
    REQUIRE(modifiedInput.size() >= 3);
    CHECK(modifiedInput[2] == 1);
}

TEST_CASE("OpCodeOne - Four elements - parameter modes: Parameter-Parameter", "[OpCodeProcessor]")
{
    std::vector<int> input =
    {
        1101,-1,-2,3
    };

    OpCodeProcessor<int> opCodeProcessor;
    auto result = opCodeProcessor.ProcessInstructions(input);
    REQUIRE(result.has_value());
    auto [modifiedInput, printedOut] = result.value();
    REQUIRE(modifiedInput.size() == 4);
    CHECK(modifiedInput[3] == -3);
}
