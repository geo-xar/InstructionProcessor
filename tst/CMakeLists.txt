set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

find_package(Catch2 REQUIRED CONFIG)

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
      Catch2::Catch2
)
