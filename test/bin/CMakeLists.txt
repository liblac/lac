add_executable(tools.t tools.t.cpp)
add_test(NAME tools.t COMMAND tools.t)
target_link_libraries(tools.t ${TESTLIBNAME})

add_executable(unit.t unit.t.cpp)
add_test(NAME unit.t COMMAND unit.t)
target_link_libraries(unit.t ${TESTLIBNAME})
