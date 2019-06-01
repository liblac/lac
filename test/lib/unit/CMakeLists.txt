target_sources(unit.t PRIVATE ${CMAKE_CURRENT_LIST_DIR}/traits.t.cpp)
target_sources(unit.t PRIVATE ${CMAKE_CURRENT_LIST_DIR}/vector.t.cpp)
target_sources(unit.t PRIVATE ${CMAKE_CURRENT_LIST_DIR}/vector_view.t.cpp)

target_sources(${TESTLIBNAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/traits.cpp)
