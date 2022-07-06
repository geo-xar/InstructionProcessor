# Copyright 2022 by Georgios Charitos.
# All rights reserved.

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(InstructionProcessor STATIC)

target_sources(InstructionProcessor PUBLIC
    NonCopyable.h
    NonMovable.h
    Utils.h
    OpCodeInterface.h
    OpCodeOne.cpp
    OpCodeOne.h
    OpCodeTwo.cpp
    OpCodeTwo.h
    OpCodeThree.cpp
    OpCodeThree.h
    OpCodeFour.h
    OpCodeFive.h
    OpCodeSix.h
    OpCodeSeven.h
    OpCodeEight.h
    OpCodeNine.h
    OpCodeNinetyNine.h
    OpCodeProcessor.h
    OpCodeProcessorUtils.h
)
