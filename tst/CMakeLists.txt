# Copyright 2022 by Georgios Charitos.
# All rights reserved.

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(InstructionProcessorTest
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

target_include_directories(InstructionProcessorTest
    PRIVATE
      $<TARGET_PROPERTY:InstructionProcessor,SOURCE_DIR>
      $<TARGET_PROPERTY:Utils,SOURCE_DIR>
      $<TARGET_PROPERTY:OpCodes,SOURCE_DIR>
      $<TARGET_PROPERTY:Commands,SOURCE_DIR>
)

target_link_libraries(InstructionProcessorTest
    PRIVATE
      InstructionProcessor
      ${CONAN_LIBS}
)
