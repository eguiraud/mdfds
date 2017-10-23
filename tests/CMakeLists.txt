add_executable(mdfds_test mdfds_test.cxx)
target_link_libraries(mdfds_test ${ROOT_LIBRARIES} ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
add_dependencies(mdfds_test googletest)
add_test(AllTests mdfds_test)

