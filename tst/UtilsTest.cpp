#include "catch2/catch.hpp"
#include "Utils.h"

using namespace InstructionProcessor;

TEST_CASE("Build number from digits test", "[OpCodeProcessor]")
{
    std::vector<uint16_t> digits{1, 9, 8, 9};
    CHECK(BuildNumberFromDigits<uint16_t>(digits) == 1989);

    digits = {};
    CHECK(!BuildNumberFromDigits<uint16_t>(digits).has_value());

    std::vector<int> negativeDigits{-1, -9, 8, -9};
    CHECK(BuildNumberFromDigits<int>(negativeDigits) == 1989);
}

TEST_CASE("Get digits from number test", "[OpCodeProcessor]")
{
    std::vector<uint8_t> expectedDigits{1, 9, 8, 9};
    auto digits = GetDigitsFromNumber(1989);
    CHECK(std::equal(digits.begin(), digits.end(), expectedDigits.begin()));

    expectedDigits = {0};
    digits = GetDigitsFromNumber(0);
    CHECK(std::equal(digits.begin(), digits.end(), expectedDigits.begin()));

    expectedDigits = {1, 2, 5};
    digits = GetDigitsFromNumber(-125);
    CHECK(std::equal(digits.begin(), digits.end(), expectedDigits.begin()));

    expectedDigits = {1, 0, 0};
    digits = GetDigitsFromNumber(100);
    CHECK(std::equal(digits.begin(), digits.end(), expectedDigits.begin()));
}
