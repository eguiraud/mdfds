# copy dataset to binary dir
configure_file(${CMAKE_SOURCE_DIR}/tests/small.raw ${CMAKE_BINARY_DIR}/tests/small.raw COPYONLY)

# MDFDS tests
add_executable(mdfds_test mdfds_test.cxx)
target_link_libraries(mdfds_test mdfds ${ROOT_LIBRARIES} ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(mdfds_test PUBLIC ${CMAKE_SOURCE_DIR}/src ${ROOT_INCLUDE_DIRS})
add_test(mdfds mdfds_test)

# TRecordReader tests
add_executable(recordreader_test recordreader.cxx)
target_link_libraries(recordreader_test mdfds ${ROOT_LIBRARIES} ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(recordreader_test PUBLIC ${CMAKE_SOURCE_DIR}/src ${ROOT_INCLUDE_DIRS})
add_test(recordreader recordreader_test)
