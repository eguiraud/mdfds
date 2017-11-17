REFLEX_GENERATE_DICTIONARY(mdfds classes_def.h SELECTION selection.xml)
add_library(mdfdsDict SHARED
	TRecordReader.hxx TRecordReader.cxx
	TBankDecoder.hxx TDummyDecoder.cxx
	THltVertexReports.hxx
	THltVertexReportsDecoder.hxx THltVertexReportsDecoder.cxx
	TMDFDataSource.hxx
	PunTo.hxx
	BankTypes.hxx
	mdfds.cxx)
target_link_libraries(mdfdsDict ${ROOT_LIBRARIES})
target_include_directories(mdfdsDict PUBLIC ${ROOT_INCLUDE_DIRS})