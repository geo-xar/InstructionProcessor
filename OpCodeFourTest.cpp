#include "catch2.hpp"
#include "OpCodeProcessor.h"

TEST_CASE("OpCodeFour - Single element, collection shall not be processed", "[OpCodeProcessor]")
{
    std::vector<uint8_t> input =
    {
        4
    };

    OpCodeProcessor opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions<uint8_t>(input);
    CHECK(printedOut.empty());
}

TEST_CASE("OpCodeFour - Two elements - Position mode", "[OpCodeProcessor]")
{
    std::vector<int> input =
    {
        4,0
    };

    OpCodeProcessor opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions<int>(input);
    REQUIRE(printedOut.size());
    CHECK(printedOut[0] == 4);
}

TEST_CASE("OpCodeFour - Two elements - Parameter mode", "[OpCodeProcessor]")
{
    std::vector<int> input =
    {
        104,-500
    };

    OpCodeProcessor opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions<int>(input);
    REQUIRE(printedOut.size());
    CHECK(printedOut[0] == -500);
}
