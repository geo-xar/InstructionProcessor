cmake_minimum_required(VERSION 3.15.3)

project(InstructionProcessor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

IF (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")

    IF (CMAKE_BUILD_TYPE STREQUAL "Debug")

        SET(CMAKE_CXX_FLAGS "-g2 -Wall -Werror -Wextra")

        IF (CODE_COVERAGE)

            SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
            SET(GCC_COVERAGE_LINK_FLAGS "-lgcov")

        ENDIF()

    ELSE()

        SET(CMAKE_CXX_FLAGS "-O2 -Wall -Werror -Wextra")

    ENDIF()

ENDIF()

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
message("CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

add_subdirectory(src)
add_subdirectory(tst)
