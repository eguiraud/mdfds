add_library(mdfds TRecordReader.hxx TRecordReader.cxx TBankDecoder.hxx TDummyDecoder.cxx THltVertexReportsDecoder.cxx TMDFDataSource.hxx)
target_link_libraries(mdfds ${ROOT_LIBRARIES})
target_include_directories(mdfds PUBLIC ${ROOT_INCLUDE_DIRS})
