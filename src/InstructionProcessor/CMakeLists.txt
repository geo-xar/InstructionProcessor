set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(InstructionProcessor INTERFACE)

target_sources(InstructionProcessor
    PUBLIC
      InstructionProcessor.h
)

target_include_directories(InstructionProcessor
    INTERFACE
      $<TARGET_PROPERTY:Commands,SOURCE_DIR>
      $<TARGET_PROPERTY:OpCodes,SOURCE_DIR>
      $<TARGET_PROPERTY:Utils,SOURCE_DIR>
)
