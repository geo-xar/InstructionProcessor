cmake_minimum_required(VERSION 3.16)

project(InstructionProcessor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

IF (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")

    IF (CMAKE_BUILD_TYPE STREQUAL "Debug")

	SET(CMAKE_CXX_FLAGS "-g2 -Wall -Werror -Wextra")
	SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
        SET(GCC_COVERAGE_LINK_FLAGS "-lgcov")

    ELSE()

	SET(CMAKE_CXX_FLAGS "-O2 -Wall -Werror -Wextra")

    ENDIF()

ENDIF()

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

add_executable(InstructionProcessor
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
    OpCodeFiveTest.cpp
    OpCodeSix.h
    OpCodeSeven.h
    OpCodeEight.h
    OpCodeNinetyNine.h
    OpCodeProcessor.h
    OpCodeProcessorTest.cpp)

target_include_directories(InstructionProcessor
                           PRIVATE
                           ${CMAKE_CURRENT_DIR}/catch)

