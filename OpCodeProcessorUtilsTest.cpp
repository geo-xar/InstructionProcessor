#include "catch2.hpp"
#include "OpCodeProcessorUtils.h"
#include <limits>

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

TEST_CASE("Get OpCode mode from number test", "[OpCodeProcessor]")
{
    uint16_t number = 1;
    OpCodeModeVector expectedModes = { OpCodeMode::Position, OpCodeMode::Position, OpCodeMode::Position };
    CHECK(ExtractParameterModesFromNumber(number) == expectedModes);

    number = 12;
    expectedModes = { OpCodeMode::Position, OpCodeMode::Position, OpCodeMode::Position };
    CHECK(ExtractParameterModesFromNumber(number) == expectedModes);

    number = 123;
    expectedModes = { OpCodeMode::Parameter, OpCodeMode::Position, OpCodeMode::Position };
    CHECK(ExtractParameterModesFromNumber(number) == expectedModes);

    number = 323;
    CHECK_THROWS_AS(ExtractParameterModesFromNumber(number), std::runtime_error);

    number = 1034;
    expectedModes = { OpCodeMode::Position, OpCodeMode::Parameter, OpCodeMode::Position };
    CHECK(ExtractParameterModesFromNumber(number) == expectedModes);

    number = 1134;
    expectedModes = { OpCodeMode::Parameter, OpCodeMode::Parameter, OpCodeMode::Position };
    CHECK(ExtractParameterModesFromNumber(number) == expectedModes);

    number = 1434;
    CHECK_THROWS_AS(ExtractParameterModesFromNumber(number), std::runtime_error);

    number = 5134;
    CHECK_THROWS_AS(ExtractParameterModesFromNumber(number), std::runtime_error);

    number = 10034;
    expectedModes = { OpCodeMode::Position, OpCodeMode::Position, OpCodeMode::Parameter };
    CHECK(ExtractParameterModesFromNumber(number) == expectedModes);

    number = 10134;
    expectedModes = { OpCodeMode::Parameter, OpCodeMode::Position, OpCodeMode::Parameter };
    CHECK(ExtractParameterModesFromNumber(number) == expectedModes);

    number = 11034;
    expectedModes = { OpCodeMode::Position, OpCodeMode::Parameter, OpCodeMode::Parameter };
    CHECK(ExtractParameterModesFromNumber(number) == expectedModes);

    number = 11134;
    expectedModes = { OpCodeMode::Parameter, OpCodeMode::Parameter, OpCodeMode::Parameter };
    CHECK(ExtractParameterModesFromNumber(number) == expectedModes);

    number = 10634;
    CHECK_THROWS_AS(ExtractParameterModesFromNumber(number), std::runtime_error);

    number = 17034;
    CHECK_THROWS_AS(ExtractParameterModesFromNumber(number), std::runtime_error);

    number = 90034;
    CHECK_THROWS_AS(ExtractParameterModesFromNumber(number), std::runtime_error);
}
