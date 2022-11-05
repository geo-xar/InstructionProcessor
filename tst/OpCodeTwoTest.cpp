// Copyright 2022 by Georgios Charitos.
// All rights reserved.

#include "catch2/catch.hpp"
#include <InstructionProcessor.h>

using namespace InstructionProcessor;

TEST_CASE("OpCodeTwo - Single element, input shall not be processed", "[OpCodeProcessor]")
{
    std::vector<uint8_t> input =
    {
        2
    };

    OpCodeProcessor<uint8_t> opCodeProcessor;
    auto result = opCodeProcessor.ProcessInstructions(input);
    auto [modifiedInput, printedOut] = result.value();
    REQUIRE(modifiedInput.size() == input.size());
    CHECK(modifiedInput == input);
}

TEST_CASE("OpCodeTwo - Two elements, input shall not be processed", "[OpCodeProcessor]")
{
    std::vector<uint8_t> input =
    {
        2,3
    };

    OpCodeProcessor<uint8_t> opCodeProcessor;
    auto result = opCodeProcessor.ProcessInstructions(input);
    auto [modifiedInput, printedOut] = result.value();
    REQUIRE(modifiedInput.size() == input.size());
    CHECK(modifiedInput == input);
}

TEST_CASE("OpCodeTwo - Three elements, input shall not be processed", "[OpCodeProcessor]")
{
    std::vector<uint8_t> input =
    {
        2,3,4
    };

    OpCodeProcessor<uint8_t> opCodeProcessor;
    auto result = opCodeProcessor.ProcessInstructions(input);
    auto [modifiedInput, printedOut] = result.value();
    REQUIRE(modifiedInput.size() == input.size());
    CHECK(modifiedInput == input);
}

TEST_CASE("OpCodeTwo - Four elements - parameter modes: Position-Position", "[OpCodeProcessor]")
{
    std::vector<uint8_t> input =
    {
        2,1,2,0
    };

    OpCodeProcessor<uint8_t> opCodeProcessor;
    auto result = opCodeProcessor.ProcessInstructions(input);
    auto [modifiedInput, printedOut] = result.value();
    REQUIRE(modifiedInput.size() == input.size());
    REQUIRE(modifiedInput.size());
    CHECK(modifiedInput[0] == 2);
}

TEST_CASE("OpCodeTwo - Four elements - parameter modes: Position-Parameter", "[OpCodeProcessor]")
{
    std::vector<int> input =
    {
        1002,1,-2,2
    };

    OpCodeProcessor<int> opCodeProcessor;
    auto result = opCodeProcessor.ProcessInstructions(input);
    auto [modifiedInput, printedOut] = result.value();
    REQUIRE(modifiedInput.size() == input.size());
    REQUIRE(modifiedInput.size() >= 3);
    CHECK(modifiedInput[2] == -2);
}

TEST_CASE("OpCodeTwo - Four elements - parameter modes: Parameter-Position", "[OpCodeProcessor]")
{
    std::vector<int> input =
    {
        102,-1,2,2
    };

    OpCodeProcessor<int> opCodeProcessor;
    auto result = opCodeProcessor.ProcessInstructions(input);
    auto [modifiedInput, printedOut] = result.value();
    REQUIRE(modifiedInput.size() == input.size());
    REQUIRE(modifiedInput.size() >= 3);
    CHECK(modifiedInput[2] == -2);
}

TEST_CASE("OpCodeTwo - Four elements - parameter modes: Parameter-Parameter", "[OpCodeProcessor]")
{
    std::vector<int> input =
    {
        1102,-1,-3,3
    };

    OpCodeProcessor<int> opCodeProcessor;
    auto result = opCodeProcessor.ProcessInstructions(input);
    auto [modifiedInput, printedOut] = result.value();
    REQUIRE(modifiedInput.size() == input.size());
    REQUIRE(modifiedInput.size() == 4);
    CHECK(modifiedInput[3] == 3);
}
