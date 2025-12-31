set(SOURCES src/main.cpp)
add_executable(knuth-permutation-l ${SOURCES})
#[[ target_include_directories(knuth-permutation-l INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>) ]]
