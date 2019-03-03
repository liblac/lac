set(TESTLIBNAME "libtest${PROJECT_NAME}")
add_library(${TESTLIBNAME})
set_target_properties(${TESTLIBNAME} PROPERTIES OUTPUT_NAME "test${PROJECT_NAME}")
target_link_libraries(${TESTLIBNAME} PUBLIC ${LIBNAME})

target_include_directories(
  ${TESTLIBNAME} PUBLIC
  ${PROJECT_SOURCE_DIR}/test/include
  )

target_include_directories(
  ${TESTLIBNAME} PUBLIC
  ${PROJECT_BINARY_DIR}/gen/test/include/
  )

add_subdirectory(bin)

# Add library directory
add_subdirectory(lib)

# Dependencies of Tests
include(${PROJECT_SOURCE_DIR}/cmake/include/test-dependency.cmake)
