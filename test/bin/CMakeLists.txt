add_executable(unit.t unit.t.cpp)
add_test(NAME unit.t COMMAND unit.t)
target_link_libraries(unit.t ${TESTLIBNAME})
