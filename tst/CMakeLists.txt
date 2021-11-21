set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        de6fe184a9ac1a06895cdd1c9b437f0a0bdf14ad # v2.13.4
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
