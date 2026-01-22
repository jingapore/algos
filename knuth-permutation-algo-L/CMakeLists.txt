set(SOURCES src/permutation.cpp  src/trace.cpp)
set(TEST_SOURCES tests/test_permutation.cpp)
add_library(knuth_permutation_algo_l ${SOURCES})

# PUBLIC ensures that consumers of this library will also have headers in the include path
target_include_directories(knuth_permutation_algo_l PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (BUILD_TESTING)
    add_executable(knuth_permutation_algo_l_test ${TEST_SOURCES})
    target_link_libraries(knuth_permutation_algo_l_test PRIVATE GTest::gtest_main knuth_permutation_algo_l)
    target_include_directories(knuth_permutation_algo_l_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
    gtest_discover_tests(knuth_permutation_algo_l_test)
endif()
