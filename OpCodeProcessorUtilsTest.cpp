#include "catch/catch2.hpp"
#include "OpCodeProcessorUtils.h"

TEST_CASE("Get OpCode from number test", "[OpCodeProcessor]")
{
    uint16_t number = 1;
    uint16_t expectedOpCode = 1;
    CHECK(ExtractOpCodeFromNumber(number) == expectedOpCode);

    number = 12399;
    expectedOpCode = 99;
    CHECK(ExtractOpCodeFromNumber(number) == expectedOpCode);

    number = 302;
    expectedOpCode = 2;
    CHECK(ExtractOpCodeFromNumber(number) == expectedOpCode);

    int negativeNumber = -4003;
    expectedOpCode = 3;
    CHECK(ExtractOpCodeFromNumber(negativeNumber) == expectedOpCode);
}

TEST_CASE("Get parameter modes from number test", "[OpCodeProcessor]")
{
    uint32_t number = 1;
    ParameterModeVector expectedModes = { ParameterMode::Position, ParameterMode::Position, ParameterMode::Position };
    CHECK(ExtractParameterModesFromNumber(number) == expectedModes);

    number = 12;
    expectedModes = { ParameterMode::Position, ParameterMode::Position, ParameterMode::Position };
    CHECK(ExtractParameterModesFromNumber(number) == expectedModes);

    number = 123;
    expectedModes = { ParameterMode::Immediate, ParameterMode::Position, ParameterMode::Position };
    CHECK(ExtractParameterModesFromNumber(number) == expectedModes);

    number = 323;
    CHECK_THROWS_AS(ExtractParameterModesFromNumber(number), std::runtime_error);

    number = 1034;
    expectedModes = { ParameterMode::Position, ParameterMode::Immediate, ParameterMode::Position };
    CHECK(ExtractParameterModesFromNumber(number) == expectedModes);

    number = 1134;
    expectedModes = { ParameterMode::Immediate, ParameterMode::Immediate, ParameterMode::Position };
    CHECK(ExtractParameterModesFromNumber(number) == expectedModes);

    number = 1434;
    CHECK_THROWS_AS(ExtractParameterModesFromNumber(number), std::runtime_error);

    number = 5134;
    CHECK_THROWS_AS(ExtractParameterModesFromNumber(number), std::runtime_error);

    number = 10034;
    expectedModes = { ParameterMode::Position, ParameterMode::Position, ParameterMode::Immediate };
    CHECK(ExtractParameterModesFromNumber(number) == expectedModes);

    number = 10134;
    expectedModes = { ParameterMode::Immediate, ParameterMode::Position, ParameterMode::Immediate };
    CHECK(ExtractParameterModesFromNumber(number) == expectedModes);

    number = 11034;
    expectedModes = { ParameterMode::Position, ParameterMode::Immediate, ParameterMode::Immediate };
    CHECK(ExtractParameterModesFromNumber(number) == expectedModes);

    number = 11134;
    expectedModes = { ParameterMode::Immediate, ParameterMode::Immediate, ParameterMode::Immediate };
    CHECK(ExtractParameterModesFromNumber(number) == expectedModes);

    number = 10634;
    CHECK_THROWS_AS(ExtractParameterModesFromNumber(number), std::runtime_error);

    number = 17034;
    CHECK_THROWS_AS(ExtractParameterModesFromNumber(number), std::runtime_error);

    number = 90034;
    CHECK_THROWS_AS(ExtractParameterModesFromNumber(number), std::runtime_error);
}
