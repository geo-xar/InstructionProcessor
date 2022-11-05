# Copyright 2022 by Georgios Charitos.
# All rights reserved.

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(Utils INTERFACE)

target_sources(Utils
    PUBLIC
      InputContainer.h
      InstructionProcessorUtils.h
      NonCopyable.h
      NonMovable.h
      Utils.h
)
