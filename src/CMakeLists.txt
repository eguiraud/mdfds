add_library(mdfds TRecordReader.hxx TRecordReader.cxx TBankDecoder.hxx TDummyDecoder.cxx THltVertexReports.hxx THltVertexReportsDecoder.hxx THltVertexReportsDecoder.cxx TMDFDataSource.hxx PunTo.hxx BankTypes.hxx)
target_link_libraries(mdfds ${ROOT_LIBRARIES})
target_include_directories(mdfds PUBLIC ${ROOT_INCLUDE_DIRS})

function (copy_header headername)
	configure_file("${headername}" "${CMAKE_BINARY_DIR}/include/${headername}" COPYONLY)
endfunction()

copy_header(THltVertexReports.hxx)
copy_header(THltVertexReportsDecoder.hxx)
copy_header(TMDFDataSource.hxx)
