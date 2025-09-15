cmake_minimum_required(VERSION 4.0.0)
# project(knuth LANGUAGES CXX)
#
# add_subdirectory(permutation-l)


file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" PATH_TO_CMAKELISTS_TXT)
message("project bin dir is ${PROJECT_BINARY_DIR}")
if(EXISTS "${PATH_TO_CMAKELISTS_TXT}")
        message(FATAL_ERROR "Run CMake from a build subdirectory! \"mkdir build ; cd build ; cmake ..\" \
    Some junk files were created in this folder (CMakeCache.txt, CMakeFiles); you should delete those.")
endif()
# cmake_path(CONVERT "${PROJECT_BINARY_DIR}/CMakeLists.txt" TO_CMAKE_PATH_LIST PATH_TO_CMAKE_LIST)
# message("${PATH_TO_CMAKE_LIST}")
