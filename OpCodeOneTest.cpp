#include "catch2.hpp"
#include "OpCodeProcessor.h"

TEST_CASE("OpCodeOne - Single element, collection shall not be processed", "[OpCodeProcessor]")
{
    std::vector<uint8_t> input =
    {
        1
    };

    OpCodeProcessor opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions<uint8_t>(input);
    CHECK(modifiedInput == input);
}

TEST_CASE("OpCodeOne - Two elements, collection shall not be processed", "[OpCodeProcessor]")
{
    std::vector<uint8_t> input =
    {
        1,2
    };

    OpCodeProcessor opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions<uint8_t>(input);
    CHECK(modifiedInput == input);
}

TEST_CASE("OpCodeOne - Three elements, collection shall not be processed", "[OpCodeProcessor]")
{
    std::vector<uint8_t> input =
    {
        1,2,3
    };

    OpCodeProcessor opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions<uint8_t>(input);
    CHECK(modifiedInput == input);
}

TEST_CASE("OpCodeOne - Four elements - parameter modes: Position-Position", "[OpCodeProcessor]")
{
    std::vector<uint8_t> input =
    {
        1,1,2,0
    };

    OpCodeProcessor opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions<uint8_t>(input);
    REQUIRE(modifiedInput.size());
    CHECK(modifiedInput[0] == 3);
}

TEST_CASE("OpCodeOne - Four elements - parameter modes: Position-Parameter", "[OpCodeProcessor]")
{
    std::vector<int> input =
    {
        1001,1,-2,2
    };

    OpCodeProcessor opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions<int>(input);
    REQUIRE(modifiedInput.size() >= 3);
    CHECK(modifiedInput[2] == -1);
}

TEST_CASE("OpCodeOne - Four elements - parameter modes: Parameter-Position", "[OpCodeProcessor]")
{
    std::vector<int> input =
    {
        101,-1,2,2
    };

    OpCodeProcessor opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions<int>(input);
    REQUIRE(modifiedInput.size() >= 3);
    CHECK(modifiedInput[2] == 1);
}

TEST_CASE("OpCodeOne - Four elements - parameter modes: Parameter-Parameter", "[OpCodeProcessor]")
{
    std::vector<int> input =
    {
        1101,-1,-2,3
    };

    OpCodeProcessor opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions<int>(input);
    REQUIRE(modifiedInput.size() == 4);
    CHECK(modifiedInput[3] == -3);
}
