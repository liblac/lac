if(BUILD_DOC)
  set(DOXYGEN_ALL_TARGET ALL)
  if(DOXYGEN_FOUND)
    set(DOXYGEN_IN ${PROJECT_SOURCE_DIR}/cmake/configure/doxyfile.in)
    set(DOXYGEN_OUT ${PROJECT_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("-- Configuring Doxygen documentation generator")

    file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/doc/doxygen)

    # note the option ALL which allows to build the docs together with the application
    add_custom_target(doxygen ${DOXYGEN_ALL_TARGET}
      COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
      WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/doc/doxygen
      COMMENT "Generating API documentation with doxygen"
      VERBATIM
      )
  else ()
    message(FATAL_ERROR "-- BUILD_DOC is explicitly set to On, but cannot find doxygen.")
  endif()
else()
  message("-- Documentation Generation Disabled")
endif()




