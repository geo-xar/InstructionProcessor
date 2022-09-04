# Copyright 2022 by Georgios Charitos.
# All rights reserved.

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(OpCodes INTERFACE)

target_sources(OpCodes
    PUBLIC
      OpCodeOne.h
      OpCodeTwo.h
      OpCodeThree.h
      OpCodeFour.h
      OpCodeFive.h
      OpCodeSix.h
      OpCodeSeven.h
      OpCodeEight.h
      OpCodeNine.h
      OpCodeNinetyNine.h
)
