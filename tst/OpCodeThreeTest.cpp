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
    auto result = opCodeProcessor.ProcessInstructions(input);
    auto [modifiedInput, printedOut] = result.value();
    REQUIRE(modifiedInput.size() == input.size());
    CHECK(modifiedInput == input);
}

TEST_CASE("OpCodeThree - Single element, input shall not be processed", "[OpCodeProcessor]")
{
    std::vector<uint8_t> input =
    {
        3
    };

    OpCodeProcessor<uint8_t> opCodeProcessor;
    auto result = opCodeProcessor.ProcessInstructions(input, 5);
    auto [modifiedInput, printedOut] = result.value();
    REQUIRE(modifiedInput.size() == input.size());
    CHECK(modifiedInput == input);
}

TEST_CASE("OpCodeThree - Two elements", "[OpCodeProcessor]")
{
    std::vector<int> input =
    {
        3,0
    };

    OpCodeProcessor<int> opCodeProcessor;
    auto result = opCodeProcessor.ProcessInstructions(input, -5);
    auto [modifiedInput, printedOut] = result.value();
    REQUIRE(modifiedInput.size() == input.size());
    REQUIRE(modifiedInput.size());
    CHECK(modifiedInput[0] == -5);
}

