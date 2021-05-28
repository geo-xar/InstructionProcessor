set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(InstructionProcessor INTERFACE)

target_sources(InstructionProcessor INTERFACE
    NonCopyable.h
    NonMovable.h
    Utils.h
    OpCodeInterface.h
    OpCodeOne.h
    OpCodeTwo.h
    OpCodeThree.h
    OpCodeFour.h
    OpCodeFive.h
    OpCodeSix.h
    OpCodeSeven.h
    OpCodeEight.h
    OpCodeNinetyNine.h
    OpCodeProcessor.h
    OpCodeProcessorUtils.h
)
