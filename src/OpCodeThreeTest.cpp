#include "catch2.hpp"
#include "OpCodeProcessor.h"

TEST_CASE("OpCodeThree - No user selection (ProcessInstructions 2nd argument is missing), input shall not be processed)", "[OpCodeProcessor]")
{
    std::vector<uint8_t> input =
    {
        3
    };

    OpCodeProcessor opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions<uint8_t>(input);
    CHECK(modifiedInput == input);
}

TEST_CASE("OpCodeThree - Single element, input shall not be processed", "[OpCodeProcessor]")
{
    std::vector<uint8_t> input =
    {
        3
    };

    OpCodeProcessor opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions<uint8_t>(input, 5);
    CHECK(modifiedInput == input);
}

TEST_CASE("OpCodeThree - Two elements", "[OpCodeProcessor]")
{
    std::vector<int> input =
    {
        3,0
    };

    OpCodeProcessor opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions<int>(input, -5);
    REQUIRE(modifiedInput.size());
    CHECK(modifiedInput[0] == -5);
}

