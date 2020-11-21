set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(
    InstructionProcessor
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
    OpCodeSixTest.cpp
    OpCodeSeven.h
    OpCodeEight.h
    OpCodeNinetyNine.h
    OpCodeProcessor.h
    OpCodeProcessorTest.cpp
)

target_include_directories(
    InstructionProcessor
    PRIVATE
    ${CMAKE_SOURCE_DIR}/catch
)

