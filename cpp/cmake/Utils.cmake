# we follow the sequence of params for get_target_property to make it easier for users
function(get_and_validate_target_property RESULT_VAR TARGET_NAME PROPERTY_NAME)
  get_target_property(PROP_VAL ${TARGET_NAME} ${PROPERTY_NAME})
  if(NOT PROP_VAL)
    message(
      FATAL_ERROR
        "Required property ${PROPERTY_NAME} is not set on target: ${TARGET_NAME}"
    )
  endif()
  set(${RESULT_VAR}
      "${PROP_VAL}"
      PARENT_SCOPE)
endfunction()
