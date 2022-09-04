#include "catch2/catch.hpp"
#include <InstructionProcessor.h>
#include <algorithm>

using namespace InstructionProcessor;

TEST_CASE("OpCodeSeven - Single element, input shall not be processed", "[OpCodeProcessor]")
{
    std::vector<uint8_t> input =
    {
        7
    };

    OpCodeProcessor<uint8_t> opCodeProcessor;
    auto result = opCodeProcessor.ProcessInstructions(input);
    REQUIRE(result.has_value());
    auto [modifiedInput, printedOut] = result.value();
    REQUIRE(modifiedInput.size() == input.size());
    CHECK(std::equal(modifiedInput.begin(), modifiedInput.end(), input.begin()));
}

TEST_CASE("OpCodeSeven - 2 elements, input shall not be processed", "[OpCodeProcessor]")
{
    std::vector<uint8_t> input =
    {
        7,1
    };

    OpCodeProcessor<uint8_t> opCodeProcessor;
    auto result = opCodeProcessor.ProcessInstructions(input);
    REQUIRE(result.has_value());
    auto [modifiedInput, printedOut] = result.value();
    REQUIRE(modifiedInput.size() == input.size());
    CHECK(std::equal(modifiedInput.begin(), modifiedInput.end(), input.begin()));
}

TEST_CASE("OpCodeSeven - 3 elements, input shall not be processed", "[OpCodeProcessor]")
{
    std::vector<uint8_t> input =
    {
        7,1,2
    };

    OpCodeProcessor<uint8_t> opCodeProcessor;
    auto result = opCodeProcessor.ProcessInstructions(input);
    REQUIRE(result.has_value());
    auto [modifiedInput, printedOut] = result.value();
    REQUIRE(modifiedInput.size() == input.size());
    CHECK(std::equal(modifiedInput.begin(), modifiedInput.end(), input.begin()));
}

TEST_CASE("OpCodeSeven - 1st param < 2nd param, store 1 based on 3rd param", "[OpCodeProcessor]")
{
    std::vector<int> input =
    {
        7,1,2,3
    };

    OpCodeProcessor<int> opCodeProcessor;
    auto result = opCodeProcessor.ProcessInstructions(input);
    REQUIRE(result.has_value());
    auto [modifiedInput, printedOut] = result.value();
    REQUIRE(modifiedInput.size() == input.size());
    CHECK(modifiedInput[3] == 1);
}

TEST_CASE("OpCodeSeven - 1st param > 2nd param, store 0 based on 3rd param", "[OpCodeProcessor]")
{
    std::vector<int> input =
    {
        1107,2,1,3
    };

    OpCodeProcessor<int> opCodeProcessor;
    auto result = opCodeProcessor.ProcessInstructions(input);
    REQUIRE(result.has_value());
    auto [modifiedInput, printedOut] = result.value();
    REQUIRE(modifiedInput.size() == input.size());
    CHECK(modifiedInput[3] == 0);
}
