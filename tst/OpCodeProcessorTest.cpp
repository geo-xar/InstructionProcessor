#include "catch2/catch.hpp"
#include "OpCodeProcessor.h"

using namespace InstructionProcessor;

TEST_CASE("Process instructions - empty input", "[OpCodeProcessor]")
{
    std::vector<uint8_t> input;

    OpCodeProcessor<uint8_t> opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input);
    CHECK(modifiedInput.empty());
    CHECK(printedOut.empty());
}

TEST_CASE("Process instructions - invalid OpCode", "[OpCodeProcessor]")
{
    std::vector<uint16_t> input =
    {
        98
    };

    OpCodeProcessor<uint16_t> opCodeProcessor;
    CHECK_THROWS_AS(opCodeProcessor.ProcessInstructions(input), std::runtime_error);
}

TEST_CASE("Process instructions - 1st part - 2nd day - 1st sample", "[OpCodeProcessor]")
{
    std::vector<uint16_t> input =
    {
        1,9,10,3,2,3,11,0,99,30,40,50
    };

    OpCodeProcessor<uint16_t> opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input);
    REQUIRE(modifiedInput.size());
    CHECK(modifiedInput[0] == 3500);
}

TEST_CASE("Process instructions - 1st part - 2nd day", "[OpCodeProcessor]")
{
    std::vector<uint32_t> input =
    {
        1,12,2,3,1,1,2,3,1,3,4,3,1,5,0,3,2,1,10,19,1,19,6,23,2,23,13,27,1,27,5,31,2,31,10,35,1,9,35,39,1,39,9,43,2,9,43,47,1,5,47,51,2,13,51,55,1,55,9,59,2,6,59,63,1,63,5,67,1,10,67,71,1,71,10,75,2,75,13,79,2,79,13,83,1,5,83,87,1,87,6,91,2,91,13,95,1,5,95,99,1,99,2,103,1,103,6,0,99,2,14,0,0
    };

    OpCodeProcessor<uint32_t> opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input);
    REQUIRE(modifiedInput.size());
    CHECK(modifiedInput[0] == 3790645);
}

TEST_CASE("Process instructions - 1st part - 5th day- 1st sample", "[OpCodeProcessor]")
{
    std::vector<uint16_t> input =
    {
        3,0,4,0,99
    };

    OpCodeProcessor<uint16_t> opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input, 1989);
    REQUIRE(printedOut.size() == 1);
    CHECK(printedOut[0] == 1989);
}

TEST_CASE("Process instructions - 1st part - 5th day - 2nd sample", "[OpCodeProcessor]")
{
    std::vector<uint16_t> input =
    {
        1002,4,3,4,33
    };

    OpCodeProcessor<uint16_t> opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input);
    REQUIRE(modifiedInput.size());
    CHECK(modifiedInput[4] == 99);
}

TEST_CASE("Process instructions - 1st part - 5th day - 3rd sample", "[OpCodeProcessor]")
{
    std::vector<int32_t> input =
    {
        1101,100,-1,4,0
    };

    OpCodeProcessor<int32_t> opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input);
    REQUIRE(modifiedInput.size());
    CHECK(modifiedInput[4] == 99);
}

TEST_CASE("Process instructions - 1st part - 5th day", "[OpCodeProcessor]")
{
    std::vector<int32_t> input =
    {
        3,225,1,225,6,6,1100,1,238,225,104,0,1101,9,90,224,1001,224,-99,224,4,224,102,8,223,223,1001,224,6,224,1,223,224,223,1102,26,62,225,1101,11,75,225,1101,90,43,225,2,70,35,224,101,-1716,224,224,4,224,1002,223,8,223,101,4,224,224,1,223,224,223,1101,94,66,225,1102,65,89,225,101,53,144,224,101,-134,224,224,4,224,1002,223,8,223,1001,224,5,224,1,224,223,223,1102,16,32,224,101,-512,224,224,4,224,102,8,223,223,101,5,224,224,1,224,223,223,1001,43,57,224,101,-147,224,224,4,224,102,8,223,223,101,4,224,224,1,223,224,223,1101,36,81,225,1002,39,9,224,1001,224,-99,224,4,224,1002,223,8,223,101,2,224,224,1,223,224,223,1,213,218,224,1001,224,-98,224,4,224,102,8,223,223,101,2,224,224,1,224,223,223,102,21,74,224,101,-1869,224,224,4,224,102,8,223,223,1001,224,7,224,1,224,223,223,1101,25,15,225,1101,64,73,225,4,223,99,0,0,0,677,0,0,0,0,0,0,0,0,0,0,0,1105,0,99999,1105,227,247,1105,1,99999,1005,227,99999,1005,0,256,1105,1,99999,1106,227,99999,1106,0,265,1105,1,99999,1006,0,99999,1006,227,274,1105,1,99999,1105,1,280,1105,1,99999,1,225,225,225,1101,294,0,0,105,1,0,1105,1,99999,1106,0,300,1105,1,99999,1,225,225,225,1101,314,0,0,106,0,0,1105,1,99999,1008,226,677,224,1002,223,2,223,1005,224,329,1001,223,1,223,1007,677,677,224,102,2,223,223,1005,224,344,101,1,223,223,108,226,677,224,102,2,223,223,1006,224,359,101,1,223,223,108,226,226,224,1002,223,2,223,1005,224,374,1001,223,1,223,7,226,226,224,1002,223,2,223,1006,224,389,1001,223,1,223,8,226,677,224,1002,223,2,223,1006,224,404,1001,223,1,223,107,677,677,224,1002,223,2,223,1006,224,419,101,1,223,223,1008,677,677,224,102,2,223,223,1006,224,434,101,1,223,223,1107,226,677,224,102,2,223,223,1005,224,449,1001,223,1,223,107,226,226,224,102,2,223,223,1006,224,464,101,1,223,223,107,226,677,224,102,2,223,223,1005,224,479,1001,223,1,223,8,677,226,224,102,2,223,223,1005,224,494,1001,223,1,223,1108,226,677,224,102,2,223,223,1006,224,509,101,1,223,223,1107,677,226,224,1002,223,2,223,1005,224,524,101,1,223,223,1008,226,226,224,1002,223,2,223,1005,224,539,101,1,223,223,7,226,677,224,1002,223,2,223,1005,224,554,101,1,223,223,1107,677,677,224,1002,223,2,223,1006,224,569,1001,223,1,223,8,226,226,224,1002,223,2,223,1006,224,584,101,1,223,223,1108,677,677,224,102,2,223,223,1005,224,599,101,1,223,223,108,677,677,224,1002,223,2,223,1006,224,614,101,1,223,223,1007,226,226,224,102,2,223,223,1005,224,629,1001,223,1,223,7,677,226,224,1002,223,2,223,1005,224,644,101,1,223,223,1007,226,677,224,102,2,223,223,1005,224,659,1001,223,1,223,1108,677,226,224,102,2,223,223,1006,224,674,101,1,223,223,4,223,99,226
    };

    OpCodeProcessor<int32_t> opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input, 1);
    REQUIRE(printedOut.size());
    CHECK(*(printedOut.end() - 1) == 13818007);
}

TEST_CASE("Input not equal to 8 - position mode - 2nd part - 5th day", "[OpCodeProcessor]")
{
    std::vector<int32_t> input =
    {
        3,9,8,9,10,9,4,9,99,-1,8
    };

    OpCodeProcessor<int32_t> opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input, 1);
    REQUIRE(printedOut.size() == 1);
    CHECK(printedOut[0] == 0);
}

TEST_CASE("Input equal to 8 - position mode - 2nd part - 5th day", "[OpCodeProcessor]")
{
    std::vector<int32_t> input =
    {
        3,9,8,9,10,9,4,9,99,-1,8
    };

    OpCodeProcessor<int32_t> opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input, 8);
    REQUIRE(printedOut.size() == 1);
    CHECK(printedOut[0] == 1);
}

TEST_CASE("Input less than 8 - position mode - 2nd part - 5th day", "[OpCodeProcessor]")
{
    std::vector<int32_t> input =
    {
        3,9,7,9,10,9,4,9,99,-1,8
    };

    OpCodeProcessor<int32_t> opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input, 2);
    REQUIRE(printedOut.size() == 1);
    CHECK(printedOut[0] == 1);
}

TEST_CASE("Input greater than 8 - position mode - 2nd part - 5th day", "[OpCodeProcessor]")
{
    std::vector<int32_t> input =
    {
        3,9,7,9,10,9,4,9,99,-1,8
    };

    OpCodeProcessor<int32_t> opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input, 9);
    REQUIRE(printedOut.size() == 1);
    CHECK(printedOut[0] == 0);
}

TEST_CASE("Input not equal to 8 - immediate mode - 2nd part - 5th day", "[OpCodeProcessor]")
{
    std::vector<int32_t> input =
    {
        3,3,1108,-1,8,3,4,3,99
    };

    OpCodeProcessor<int32_t> opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input, 10);
    REQUIRE(printedOut.size() == 1);
    CHECK(printedOut[0] == 0);
}

TEST_CASE("Input equal to 8 - immediate mode - 2nd part - 5th day", "[OpCodeProcessor]")
{
    std::vector<int32_t> input =
    {
        3,3,1108,-1,8,3,4,3,99
    };

    OpCodeProcessor<int32_t> opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input, 8);
    REQUIRE(printedOut.size() == 1);
    CHECK(printedOut[0] == 1);
}

TEST_CASE("Input less than 8 - immediate mode - 2nd part - 5th day", "[OpCodeProcessor]")
{
    std::vector<int32_t> input =
    {
        3,3,1107,-1,8,3,4,3,99
    };

    OpCodeProcessor<int32_t> opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input, 7);
    REQUIRE(printedOut.size() == 1);
    CHECK(printedOut[0] == 1);
}

TEST_CASE("Input greater than 8 - immediate mode - 2nd part - 5th day", "[OpCodeProcessor]")
{
    std::vector<int32_t> input =
    {
        3,3,1107,-1,8,3,4,3,99
    };

    OpCodeProcessor<int32_t> opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input, 9);
    REQUIRE(printedOut.size() == 1);
    CHECK(printedOut[0] == 0);
}

TEST_CASE("Input equal to 0 - position mode - 2nd part - 5th day", "[OpCodeProcessor]")
{
    std::vector<int32_t> input =
    {
        3,12,6,12,15,1,13,14,13,4,13,99,-1,0,1,9
    };

    OpCodeProcessor<int32_t> opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input, 0);
    REQUIRE(printedOut.size() == 1);
    CHECK(printedOut[0] == 0);
}

TEST_CASE("Input not equal to 0 - position mode - 2nd part - 5th day", "[OpCodeProcessor]")
{
    std::vector<int32_t> input =
    {
        3,12,6,12,15,1,13,14,13,4,13,99,-1,0,1,9
    };

    OpCodeProcessor<int32_t> opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input, -5);
    REQUIRE(printedOut.size() == 1);
    CHECK(printedOut[0] == 1);
}

TEST_CASE("Input equal to 0 - immediate mode - 2nd part - 5th day", "[OpCodeProcessor]")
{
    std::vector<int32_t> input =
    {
        3,3,1105,-1,9,1101,0,0,12,4,12,99,1
    };

    OpCodeProcessor<int32_t> opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input, 0);
    REQUIRE(printedOut.size() == 1);
    CHECK(printedOut[0] == 0);
}

TEST_CASE("Input not equal to 0 - immediate mode - 2nd part - 5th day", "[OpCodeProcessor]")
{
    std::vector<int32_t> input =
    {
        3,3,1105,-1,9,1101,0,0,12,4,12,99,1
    };

    OpCodeProcessor<int32_t> opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input, 250);
    REQUIRE(printedOut.size() == 1);
    CHECK(printedOut[0] == 1);
}

TEST_CASE("Input less than 8 - 2nd part - 5th day", "[OpCodeProcessor]")
{
    std::vector<uint32_t> input =
    {
        3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99
    };

    OpCodeProcessor<uint32_t> opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input, 7);
    REQUIRE(printedOut.size() == 1);
    CHECK(printedOut[0] == 999);
}

TEST_CASE("Input equal to 8 - 2nd part - 5th day", "[OpCodeProcessor]")
{
    std::vector<uint32_t> input =
    {
        3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99
    };

    OpCodeProcessor<uint32_t> opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input, 8);
    REQUIRE(printedOut.size() == 1);
    CHECK(printedOut[0] == 1000);
}

TEST_CASE("Input greater than 8 - 2nd part - 5th day", "[OpCodeProcessor]")
{
    std::vector<uint32_t> input =
    {
        3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99
    };

    OpCodeProcessor<uint32_t> opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input, 9);
    REQUIRE(printedOut.size() == 1);
    CHECK(printedOut[0] == 1001);
}

TEST_CASE("Process instructions - 2nd part - 5th day", "[OpCodeProcessor]")
{
    std::vector<int32_t> input =
    {
        3,225,1,225,6,6,1100,1,238,225,104,0,1101,9,90,224,1001,224,-99,224,4,224,102,8,223,223,1001,224,6,224,1,223,224,223,1102,26,62,225,1101,11,75,225,1101,90,43,225,2,70,35,224,101,-1716,224,224,4,224,1002,223,8,223,101,4,224,224,1,223,224,223,1101,94,66,225,1102,65,89,225,101,53,144,224,101,-134,224,224,4,224,1002,223,8,223,1001,224,5,224,1,224,223,223,1102,16,32,224,101,-512,224,224,4,224,102,8,223,223,101,5,224,224,1,224,223,223,1001,43,57,224,101,-147,224,224,4,224,102,8,223,223,101,4,224,224,1,223,224,223,1101,36,81,225,1002,39,9,224,1001,224,-99,224,4,224,1002,223,8,223,101,2,224,224,1,223,224,223,1,213,218,224,1001,224,-98,224,4,224,102,8,223,223,101,2,224,224,1,224,223,223,102,21,74,224,101,-1869,224,224,4,224,102,8,223,223,1001,224,7,224,1,224,223,223,1101,25,15,225,1101,64,73,225,4,223,99,0,0,0,677,0,0,0,0,0,0,0,0,0,0,0,1105,0,99999,1105,227,247,1105,1,99999,1005,227,99999,1005,0,256,1105,1,99999,1106,227,99999,1106,0,265,1105,1,99999,1006,0,99999,1006,227,274,1105,1,99999,1105,1,280,1105,1,99999,1,225,225,225,1101,294,0,0,105,1,0,1105,1,99999,1106,0,300,1105,1,99999,1,225,225,225,1101,314,0,0,106,0,0,1105,1,99999,1008,226,677,224,1002,223,2,223,1005,224,329,1001,223,1,223,1007,677,677,224,102,2,223,223,1005,224,344,101,1,223,223,108,226,677,224,102,2,223,223,1006,224,359,101,1,223,223,108,226,226,224,1002,223,2,223,1005,224,374,1001,223,1,223,7,226,226,224,1002,223,2,223,1006,224,389,1001,223,1,223,8,226,677,224,1002,223,2,223,1006,224,404,1001,223,1,223,107,677,677,224,1002,223,2,223,1006,224,419,101,1,223,223,1008,677,677,224,102,2,223,223,1006,224,434,101,1,223,223,1107,226,677,224,102,2,223,223,1005,224,449,1001,223,1,223,107,226,226,224,102,2,223,223,1006,224,464,101,1,223,223,107,226,677,224,102,2,223,223,1005,224,479,1001,223,1,223,8,677,226,224,102,2,223,223,1005,224,494,1001,223,1,223,1108,226,677,224,102,2,223,223,1006,224,509,101,1,223,223,1107,677,226,224,1002,223,2,223,1005,224,524,101,1,223,223,1008,226,226,224,1002,223,2,223,1005,224,539,101,1,223,223,7,226,677,224,1002,223,2,223,1005,224,554,101,1,223,223,1107,677,677,224,1002,223,2,223,1006,224,569,1001,223,1,223,8,226,226,224,1002,223,2,223,1006,224,584,101,1,223,223,1108,677,677,224,102,2,223,223,1005,224,599,101,1,223,223,108,677,677,224,1002,223,2,223,1006,224,614,101,1,223,223,1007,226,226,224,102,2,223,223,1005,224,629,1001,223,1,223,7,677,226,224,1002,223,2,223,1005,224,644,101,1,223,223,1007,226,677,224,102,2,223,223,1005,224,659,1001,223,1,223,1108,677,226,224,102,2,223,223,1006,224,674,101,1,223,223,4,223,99,226
    };

    OpCodeProcessor<int32_t> opCodeProcessor;
    auto [modifiedInput, printedOut] = opCodeProcessor.ProcessInstructions(input, 5);
    REQUIRE(printedOut.size() == 1);
    CHECK(printedOut[0] == 3176266);
}
