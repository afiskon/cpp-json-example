cmake_minimum_required(VERSION 3.8)

project(cpp-json-example)

option(USE_GCOV "Create a GCov-enabled build." OFF)
option(USE_CLANG "Build project with Clang." OFF)

if (USE_GCOV)
  set(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
  set(GCC_COVERAGE_LINK_FLAGS    "-lgcov")
endif()

if (USE_CLANG)
  set(CMAKE_C_COMPILER   "/usr/bin/clang")
  set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )

include_directories(
    include
    deps/rapidjson/include
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

if(NOT WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
endif()

add_executable(json_example src/json_example.cpp)
target_link_libraries(json_example)

file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.h)
add_custom_target(format
    COMMAND clang-format --style=file -i ${ALL_SOURCE_FILES} )
