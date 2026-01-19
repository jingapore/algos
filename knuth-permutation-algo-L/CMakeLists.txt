set(SOURCES src/permutation.cpp)
add_library(knuth_permutation_algo_l ${SOURCES})

# PUBLIC ensures that consumers of this library will also have headers in the include path
target_include_directories(knuth_permutation_algo_l PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
