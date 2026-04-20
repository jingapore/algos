cmake_minimum_required(VERSION 4.0.0)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(
  algos
  VERSION 0.0.1
  DESCRIPTION "Compendium of algos"
  LANGUAGES C CXX)

if(DEFINED EMSCRIPTEN)
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
endif()

file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt"
     PATH_TO_CMAKELISTS_TXT)
message("project bin dir is ${PROJECT_BINARY_DIR}")
if(EXISTS "${PATH_TO_CMAKELISTS_TXT}")
  message(
    FATAL_ERROR
      "Run CMake from a build subdirectory! \"mkdir build ; cd build ; cmake ..\" \
    Some junk files were created in this folder (CMakeCache.txt, CMakeFiles); you should delete those."
  )
endif()

# include CTest outside of if(BUILD_TESTING) check cos CTest defines option for
# BUILD_TESTING
include(CTest)
if(BUILD_TESTING)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  )
  FetchContent_MakeAvailable(googletest)
  include(GoogleTest)
endif()

if(EMSCRIPTEN)
  add_subdirectory(knuth-permutation-algo-L)
else()
  add_executable(omnibus_program src/main.cpp)
  add_subdirectory(knuth-permutation-algo-L)
  target_link_libraries(omnibus_program PRIVATE knuth_permutation_algo_lib)
endif()

