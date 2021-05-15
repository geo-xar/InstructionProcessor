set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(
    InstructionProcessorTest
    OpCodeEightTest.cpp
    OpCodeFiveTest.cpp
    OpCodeOneTest.cpp
    OpCodeProcessorTest.cpp
    OpCodeProcessorUtilsTest.cpp
    OpCodeSevenTest.cpp
    OpCodeSixTest.cpp
    OpCodeThreeTest.cpp
    OpCodeTwoTest.cpp
    UtilsTest.cpp
    OpCodeFourTest.cpp
)

target_include_directories(
    InstructionProcessorTest
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/catch
)

target_link_libraries(
    InstructionProcessorTest
    PRIVATE
        InstructionProcessor
)

