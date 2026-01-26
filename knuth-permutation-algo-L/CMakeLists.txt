set(SOURCES src/trace.cpp)
set(TEST_SOURCES tests/test_permutation.cpp)

add_library(knuth_permutation_algo_lib STATIC ${SOURCES})
# PUBLIC ensures that consumers of this library will also have headers in the
# include path
target_include_directories(knuth_permutation_algo_lib
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(EMSCRIPTEN)
  message("Building with EMSCRIPTEN for wasm")
  add_executable(knuth_permutation_algo_wasm ${SOURCES} src/wasm_api.cpp)
  target_include_directories(knuth_permutation_algo_wasm
                             PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
  set_target_properties(
    knuth_permutation_algo_wasm
    PROPERTIES OUTPUT_NAME "knuth_permutation_algo"
               SUFFIX ".mjs"
               RUNTIME_OUTPUT_DIRECTORY "${DIST_DIR}")
  set(DIST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dist")
  file(MAKE_DIRECTORY "${DIST_DIR}")
  target_link_options(
    knuth_permutation_algo_wasm
    PRIVATE
    "-sMODULARIZE=1"
    "-sEXPORT_ES6=1"
    "--bind"
    "-sEXPORTED_FUNCTIONS=['_malloc', '_free']"
    "--emit-tsd=${DIST_DIR}/index.d.ts")
endif()

if(BUILD_TESTING)
  add_executable(knuth_permutation_algo_l_test ${TEST_SOURCES})
  target_link_libraries(knuth_permutation_algo_l_test
                        PRIVATE GTest::gtest_main knuth_permutation_algo_lib)
  target_include_directories(knuth_permutation_algo_l_test
                             PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
  gtest_discover_tests(knuth_permutation_algo_l_test)
endif()
