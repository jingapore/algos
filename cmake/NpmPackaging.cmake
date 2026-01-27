include(Utils)

function(generate_npm_package TARGET_NAME)
  if(NOT TARGET ${TARGET_NAME})
    message(
      FATAL_ERROR "generate_npm_package: ${TARGET_NAME} is not a valid target.")
  endif()
  get_and_validate_target_property(MAIN_FILE ${TARGET_NAME} NPM_KEY_MAIN)
  get_and_validate_target_property(TYPES_FILE ${TARGET_NAME} NPM_KEY_TYPES)
  get_and_validate_target_property(WASM_FILE ${TARGET_NAME} NPM_KEY_WASM)

  set(QUOTED_LIST "")
  list(APPEND QUOTED_LIST ${NPM_KEY_MAIN} ${NPM_KEY_TYPES} ${NPM_KEY_WASM})
  list(TRANSFORM QUOTED_LIST PREPEND "\"")
  list(TRANSFORM QUOTED_LIST APPEND "\"")
  string(JOIN ", " PKG_JSON_FILES_LIST ${QUOTED_LIST})

  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/package.json.in"
                 "${CMAKE_CURRENT_SOURCE_DIR}/package.json" @ONLY)
endfunction()
