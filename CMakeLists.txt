cmake_minimum_required(VERSION 4.0.0)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
project(algos VERSION 0.0.1 DESCRIPTION "Compendium of algos" LANGUAGES C CXX)

if (DEFINED EMSCRIPTEN)
endif()

file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" PATH_TO_CMAKELISTS_TXT)
message("project bin dir is ${PROJECT_BINARY_DIR}")
if(EXISTS "${PATH_TO_CMAKELISTS_TXT}")
        message(FATAL_ERROR "Run CMake from a build subdirectory! \"mkdir build ; cd build ; cmake ..\" \
    Some junk files were created in this folder (CMakeCache.txt, CMakeFiles); you should delete those.")
endif()

# we will enable_testing when we have a test dir, which will allow us to run ctest
#enable_testing()

add_executable(omnibus_program src/main.cpp)

# produces library that we'll consume in omnibus_program
add_subdirectory(knuth-permutation-algo-L)

target_link_libraries(omnibus_program PRIVATE knuth_permutation_algo_l)
