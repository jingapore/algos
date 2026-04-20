set(SOURCES src/trace.cpp)
set(TEST_SOURCES tests/test_permutation.cpp)

add_library(knuth_permutation_algo_lib STATIC ${SOURCES})
# PUBLIC ensures that consumers of this library will also have headers in the
# include path
target_include_directories(knuth_permutation_algo_lib
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(WASM_OUTPUT_NAME "knuth_permutation")

if(EMSCRIPTEN)

  include(NpmPackaging)

  set(DIST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dist")
  file(MAKE_DIRECTORY "${DIST_DIR}")

  message(
    STATUS
      "Building with EMSCRIPTEN for wasm with artifacts saved in ${DIST_DIR}")

  add_executable(knuth_permutation_algo_wasm ${SOURCES} src/wasm_api.cpp)
  # TODO: see if we can have target_include_directories just use lib instead of
  # specifying our dirs again
  target_include_directories(knuth_permutation_algo_wasm
                             PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
  # these properties are used in util function to generate npm package.json
  set_target_properties(
    knuth_permutation_algo_wasm
    PROPERTIES NPM_KEY_MAIN "dist/${WASM_OUTPUT_NAME}.mjs"
               NPM_KEY_TYPES "dist/${WASM_OUTPUT_NAME}.d.ts"
               NPM_KEY_WASM "dist/${WASM_OUTPUT_NAME}.wasm")

  set_target_properties(
    knuth_permutation_algo_wasm
    PROPERTIES OUTPUT_NAME "${WASM_OUTPUT_NAME}"
               SUFFIX ".mjs"
               RUNTIME_OUTPUT_DIRECTORY "${DIST_DIR}")

  generate_npm_package(knuth_permutation_algo_wasm)

  target_link_options(
    knuth_permutation_algo_wasm
    PRIVATE
    "-sMODULARIZE=1"
    "-sEXPORT_ES6=1"
    "--bind"
    "-sEXPORTED_FUNCTIONS=['_malloc', '_free']"
    "--emit-tsd=${DIST_DIR}/${WASM_OUTPUT_NAME}.d.ts"
    "-sENVIRONMENT=web,node"
    "-sWASM_ASYNC_COMPILATION=1")

endif()
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(DEBUG_TARGET "${WASM_OUTPUT_NAME}_debug")
  message(STATUS "Debug Build detected: Creating '${DEBUG_TARGET}' target.")
  add_executable(${DEBUG_TARGET} src/wasm_api.cpp ${SOURCES})
  target_compile_definitions(${DEBUG_TARGET} PRIVATE IS_DEBUG=1)
  # skip bindings so that the binary won't attempt to link in emscripten stuff
  # as we don't need that for debugging
  target_compile_definitions(${DEBUG_TARGET} PRIVATE NO_BINDINGS=1)
  target_include_directories(${DEBUG_TARGET}
                             PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
endif()

if(BUILD_TESTING)
  add_executable(knuth_permutation_algo_l_test ${TEST_SOURCES})
  target_link_libraries(knuth_permutation_algo_l_test
                        PRIVATE GTest::gtest_main knuth_permutation_algo_lib)
  target_include_directories(knuth_permutation_algo_l_test
                             PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
  gtest_discover_tests(knuth_permutation_algo_l_test)
endif()
