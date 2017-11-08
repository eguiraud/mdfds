add_executable(mdfds_test mdfds_test.cxx)
target_link_libraries(mdfds_test mdfds ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(mdfds_test PUBLIC ${CMAKE_SOURCE_DIR}/src ${ROOT_INCLUDE_DIRS})
add_dependencies(mdfds_test googletest)
add_test(AllTests mdfds_test)

