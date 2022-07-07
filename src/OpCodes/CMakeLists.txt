# Copyright 2022 by Georgios Charitos.
# All rights reserved.

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(OpCodes STATIC)

target_sources(OpCodes
    PUBLIC
      OpCodeOne.cpp
      OpCodeOne.h
      OpCodeTwo.cpp
      OpCodeTwo.h
      OpCodeThree.cpp
      OpCodeThree.h
      OpCodeFour.cpp
      OpCodeFour.h
      OpCodeFive.cpp
      OpCodeFive.h
      OpCodeSix.cpp
      OpCodeSix.h
      OpCodeSeven.cpp
      OpCodeSeven.h
      OpCodeEight.cpp
      OpCodeEight.h
      OpCodeNine.cpp
      OpCodeNine.h
      OpCodeNinetyNine.h
)

target_include_directories(OpCodes
    PUBLIC
      $<TARGET_PROPERTY:OpCodeInterface,SOURCE_DIR>
      $<TARGET_PROPERTY:Utils,SOURCE_DIR>
)

target_link_libraries(OpCodes
    PUBLIC
      OpCodeInterface
      Utils
)
