#include "catch2/catch.hpp"
#include <InstructionProcessor.h>

using namespace InstructionProcessor;

TEST_CASE("OpCodeThree - No user selection (2nd argument is missing), no input process)", "[OpCodeProcessor]")
{
    std::vector<uint8_t> input =
    {
        3
    };

    OpCodeProcessor<uint8_t> opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input);
    CHECK(modifiedInput == input);
}

TEST_CASE("OpCodeThree - Single element, input shall not be processed", "[OpCodeProcessor]")
{
    std::vector<uint8_t> input =
    {
        3
    };

    OpCodeProcessor<uint8_t> opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input, 5);
    CHECK(modifiedInput == input);
}

TEST_CASE("OpCodeThree - Two elements", "[OpCodeProcessor]")
{
    std::vector<int> input =
    {
        3,0
    };

    OpCodeProcessor<int> opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input, -5);
    REQUIRE(modifiedInput.size());
    CHECK(modifiedInput[0] == -5);
}

