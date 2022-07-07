# Copyright 2022 by Georgios Charitos.
# All rights reserved.

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(OpCodeInterface INTERFACE)

target_sources(OpCodeInterface INTERFACE
    OpCodeInterface.h
)
