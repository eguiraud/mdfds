add_library(mdfds TBankDecoder.hxx TDummyDecoder.cxx TMDFDataSource.hxx)
target_link_libraries(mdfds ${ROOT_LIBRARIES})
target_include_directories(mdfds PUBLIC ${ROOT_INCLUDE_DIRS})
