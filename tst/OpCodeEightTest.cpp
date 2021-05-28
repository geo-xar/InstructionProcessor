#include "catch2.hpp"
#include "OpCodeProcessor.h"
#include <algorithm>

using namespace InstructionProcessor;

TEST_CASE("OpCodeEight - Single element, input shall not be processed", "[OpCodeProcessor]")
{
    std::vector<uint8_t> input =
    {
        8
    };

    OpCodeProcessor<uint8_t> opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input);
    REQUIRE(modifiedInput.size() == input.size());
    CHECK(std::equal(modifiedInput.begin(), modifiedInput.end(), input.begin()));
}

TEST_CASE("OpCodeEight - 2 elements, input shall not be processed", "[OpCodeProcessor]")
{
    std::vector<uint8_t> input =
    {
        8,1
    };

    OpCodeProcessor<uint8_t> opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input);
    REQUIRE(modifiedInput.size() == input.size());
    CHECK(std::equal(modifiedInput.begin(), modifiedInput.end(), input.begin()));
}

TEST_CASE("OpCodeEight - 3 elements, input shall not be processed", "[OpCodeProcessor]")
{
    std::vector<uint8_t> input =
    {
        8,1,2
    };

    OpCodeProcessor<uint8_t> opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input);
    REQUIRE(modifiedInput.size() == input.size());
    CHECK(std::equal(modifiedInput.begin(), modifiedInput.end(), input.begin()));
}

TEST_CASE("OpCodeEight - First parameter equal to second parameter, store 1 in the position given by the third parameter", "[OpCodeProcessor]")
{
    std::vector<int> input =
    {
        8,3,3,0,99
    };

    OpCodeProcessor<int> opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input);
    REQUIRE(modifiedInput.size() == input.size());
    CHECK(modifiedInput[0] == 1);
}

TEST_CASE("OpCodeEight - First parameter non-equal to second parameter, store 0 in the position given by the third parameter", "[OpCodeProcessor]")
{
    std::vector<int> input =
    {
        1108,1,-2,0,99
    };

    OpCodeProcessor<int> opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input);
    REQUIRE(modifiedInput.size() == input.size());
    CHECK(modifiedInput[0] == 0);
}
