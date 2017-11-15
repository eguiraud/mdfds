add_library(mdfds TRecordReader.hxx TRecordReader.cxx TBankDecoder.hxx TDummyDecoder.cxx THltVertexReportsDecoder.hxx THltVertexReportsDecoder.cxx TMDFDataSource.hxx PunTo.hxx BankTypes.h)
target_link_libraries(mdfds ${ROOT_LIBRARIES})
target_include_directories(mdfds PUBLIC ${ROOT_INCLUDE_DIRS})
