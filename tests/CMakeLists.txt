function (add_google_test testname source)
	add_executable(${testname} ${source})
	target_link_libraries(${testname} mdfds ${ROOT_LIBRARIES} ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
	target_include_directories(${testname} PUBLIC ${CMAKE_SOURCE_DIR}/src ${ROOT_INCLUDE_DIRS})
	if (EXTERNAL_GTEST)
		add_dependencies(${testname} googletest)
	endif()
	add_test(${testname} ${testname})
endfunction()

add_google_test(mdfds_test mdfds_test.cxx)
add_google_test(recordreader_test recordreader.cxx)
add_google_test(hltvertexreports_test hltvertexreports.cxx)

# copy datasets to binary dir
configure_file(${CMAKE_SOURCE_DIR}/tests/small.raw ${CMAKE_BINARY_DIR}/tests/small.raw COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/tests/2krecords.raw ${CMAKE_BINARY_DIR}/tests/2krecords.raw COPYONLY)

