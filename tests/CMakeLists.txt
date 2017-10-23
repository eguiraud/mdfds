add_executable(mdfds_test mdfds_test.cxx)
target_link_libraries(mdfds_test ${ROOT_LIBRARIES} ${GTEST_BOTH_LIBRARIES})
add_test(AllTests mdfds_test)

