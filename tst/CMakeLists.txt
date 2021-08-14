set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.0-preview3
)

FetchContent_MakeAvailable(Catch2)

add_executable(
    InstructionProcessorTest
    OpCodeOneTest.cpp
    OpCodeTwoTest.cpp
    OpCodeThreeTest.cpp
    OpCodeFourTest.cpp
    OpCodeFiveTest.cpp
    OpCodeSixTest.cpp
    OpCodeSevenTest.cpp
    OpCodeEightTest.cpp
    OpCodeProcessorTest.cpp
    OpCodeProcessorUtilsTest.cpp
    UtilsTest.cpp
)

target_include_directories(
    InstructionProcessorTest
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(
    InstructionProcessorTest
    PRIVATE
        InstructionProcessor
        Catch2::Catch2WithMain
)

#list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)

#include(CTest)
#include(Catch)
#catch_discover_tests(InstructionProcessorTest)
