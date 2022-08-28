# Copyright 2022 by Georgios Charitos.
# All rights reserved.

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(Commands INTERFACE)

target_sources(Commands
    PUBLIC
      AddCmd.h
      AdjustRelBaseCmd.h
      Cmd.h
      ExitCmd.h
      FirstParamEqToSecondCmd.h
      FirstParamLessThanSecondCmd.h
      MultiplyCmd.h
      NonZeroParamCmd.h
      StoreInputCmd.h
      StoreOutputCmd.h
      ZeroParamCmd.h
)
