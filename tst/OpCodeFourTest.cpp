#include "catch2.hpp"
#include "OpCodeProcessor.h"

TEST_CASE("OpCodeFour - Single element, input shall not be processed", "[OpCodeProcessor]")
{
    std::vector<uint8_t> input =
    {
        4
    };

    OpCodeProcessor<uint8_t> opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input);
    CHECK(printedOut.empty());
}

TEST_CASE("OpCodeFour - Two elements - Position mode", "[OpCodeProcessor]")
{
    std::vector<int> input =
    {
        4,0
    };

    OpCodeProcessor<int> opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input);
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
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input);
    REQUIRE(printedOut.size());
    CHECK(printedOut[0] == -500);
}
