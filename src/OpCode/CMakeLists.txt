# Copyright 2022 by Georgios Charitos.
# All rights reserved.

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(OpCode INTERFACE)

target_sources(OpCode INTERFACE
    OpCode.h
)

target_include_directories(OpCode
    INTERFACE
      $<TARGET_PROPERTY:Commands,SOURCE_DIR>
      $<TARGET_PROPERTY:Utils,SOURCE_DIR>
)
