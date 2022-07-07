# Copyright 2022 by Georgios Charitos.
# All rights reserved.

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(InstructionProcessor STATIC)

target_sources(InstructionProcessor
    PUBLIC
      InstructionProcessor.h
      Temp.cpp
)

target_include_directories(InstructionProcessor
    PUBLIC
      $<TARGET_PROPERTY:OpCodes,SOURCE_DIR>
)

target_link_libraries(InstructionProcessor
    PUBLIC
      OpCodes
)
