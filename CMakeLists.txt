cmake_minimum_required(VERSION 3.16)

project(InstructionProcessor)

set(CMAKE_CXX_STANDARD 17)

add_executable(InstructionProcessor
    catch2.hpp
    NonCopyable.h
    NonMovable.h
    Utils.h
    UtilsTest.cpp
    OpCodeProcessorUtils.h
    OpCodeProcessorUtilsTest.cpp
    OpCodeInterface.h
    OpCodeOne.h
    OpCodeOneTest.cpp
    OpCodeTwo.h
    OpCodeTwoTest.cpp
    OpCodeThree.h
    OpCodeThreeTest.cpp
    OpCodeFour.h
    OpCodeFourTest.cpp
    OpCodeFive.h
    OpCodeSix.h
    OpCodeSeven.h
    OpCodeEight.h
    OpCodeNinetyNine.h
    OpCodeProcessor.h
    OpCodeProcessorTest.cpp)
