set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Conan integration.
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

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
        ${CONAN_LIBS}
)
