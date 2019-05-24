option(BUILD_TESTING "Build Testing" OFF)
option(BUILD_DOC "Build Documentation" OFF)

set(LAC_TEST "None" CACHE STRING "Selection of Tests")
set_property(CACHE LAC_TEST PROPERTY STRINGS None Code)

set(LAC_TESTOUTPUT_PATH "" CACHE PATH "Path to Store Test Output")
set(LAC_TESTDATA_PATH "" CACHE PATH "Path to Test Data")

# Option Logic Code
if (
    BUILD_TESTING
    AND (${PROJECT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    AND (${LAC_TEST} STREQUAL "None")
    )
  message("-- BUILD_TESTING is On but LAC_TEST is set to None.")
  message("-- Setting LAC_TEST to Code")
  set(LAC_TEST "Code")
endif()

if (NOT (${LAC_TEST} STREQUAL "None"))
  # Check that LAC_TESTDATA_PATH is not empty
  if (LAC_TESTDATA_PATH STREQUAL "")
    message(FATAL_ERROR "LAC_TESTDATA_PATH is required to be specified")
  endif()

  # Check that LAC_TESTOUTPUT_PATH is not empty
  if (LAC_TESTOUTPUT_PATH STREQUAL "")
    message(FATAL_ERROR "LAC_TESTDATA_PATH is required to be specified")
  endif()

  get_filename_component(
    LAC_TESTDATA_ABSPATH
    ${LAC_TESTDATA_PATH}
    ABSOLUTE
    )
  get_filename_component(
    LAC_TESTOUTPUT_ABSPATH
    ${LAC_TESTOUTPUT_PATH}
    ABSOLUTE
    )
endif()

