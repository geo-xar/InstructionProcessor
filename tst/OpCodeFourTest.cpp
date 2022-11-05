// Copyright 2022 by Georgios Charitos.
// All rights reserved.

#include "catch2/catch.hpp"
#include <InstructionProcessor.h>

using namespace InstructionProcessor;

TEST_CASE("OpCodeFour - Single element, input shall not be processed", "[OpCodeProcessor]")
{
    std::vector<uint8_t> input =
    {
        4
    };

    OpCodeProcessor<uint8_t> opCodeProcessor;
    auto result = opCodeProcessor.ProcessInstructions(input);
    REQUIRE(result.has_value());
    auto [modifiedInput, printedOut] = result.value();
    CHECK(printedOut.empty());
}

TEST_CASE("OpCodeFour - Two elements - Position mode", "[OpCodeProcessor]")
{
    std::vector<int> input =
    {
        4,0
    };

    OpCodeProcessor<int> opCodeProcessor;
    auto result = opCodeProcessor.ProcessInstructions(input);
    REQUIRE(result.has_value());
    auto [modifiedInput, printedOut] = result.value();
    REQUIRE(printedOut.size());
    CHECK(printedOut[0] == 4);
}

TEST_CASE("OpCodeFour - Two elements - Parameter mode", "[OpCodeProcessor]")
{
    std::vector<int> input =
    {
        104,-500
    };

    OpCodeProcessor<int> opCodeProcessor;
    auto result = opCodeProcessor.ProcessInstructions(input);
    REQUIRE(result.has_value());
    auto [modifiedInput, printedOut] = result.value();
    REQUIRE(printedOut.size());
    CHECK(printedOut[0] == -500);
}
