cmake_minimum_required(VERSION 3.12)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/module")

project(
  lac
  VERSION 0.0.0
  DESCRIPTION "lac : a linear algebra library"
  HOMEPAGE_URL "https://github.com/liblac/lac"
  LANGUAGES CXX
  )

set(CMAKE_DEBUG_POSTFIX -debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS OFF)

set(LIBNAME "${PROJECT_NAME}")
add_library(${LIBNAME})
set_target_properties(${LIBNAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

include(cmake/include/option.cmake)
include(cmake/include/configure.cmake)
include(cmake/include/debug.cmake)
if (NOT ${LAC_TEST} STREQUAL "None")
  include(cmake/include/test-configure.cmake)
  include(cmake/include/test-external.cmake)
endif()
include(cmake/include/external.cmake)
include(cmake/include/documentation.cmake)

add_subdirectory(src)
include(CTest)
if (NOT ${LAC_TEST} STREQUAL "None")
  add_subdirectory(test)
endif()

include(cmake/include/dependency.cmake)
include(cmake/include/install.cmake)

