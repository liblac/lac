# Adding Include Folder
target_include_directories(
  ${LIBNAME}
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
  $<INSTALL_INTERFACE:include>
  )

# Add Library Directory
add_subdirectory(lib)

