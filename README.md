[![Build Status](https://travis-ci.org/bluehood/mdfds.svg?branch=master)](https://travis-ci.org/bluehood/mdfds)

A TDataSource implementation that reads MDF files.<br>
Reference docs can be found [here](https://bluehood.github.io/mdfds/).

### Quick introduction
This small library provides a TDataSource for MDF files, i.e. a way to allow ROOT's [TDataFrame](https://root.cern/doc/v610/classROOT_1_1Experimental_1_1TDataFrame.html)
to read the MDF binary format directly. This lets users access the high-level declarative syntax of TDataFrame (including
lazy evaluation and multi-thread execution of the analysis) with minimal effort.

A small example usage:
```c++
// Build a TDataFrame that reads an MDF file -- a list of multiple files is also supported
// As this TDF has a THltVertexReportsDecoder, it will provide a "HltVertexReports" column/MDF bank
// Obviously more decoders could be added in case more types of banks/column need to be read
auto tdf = MakeMDFDataFrame<THltVertexReportsDecoder>({"file.mdf"});

// Define a column "z" that extracts the "z" position of vertices from the "HltVertexReports" column
auto getZ = [](THltVertexReports &vr) { return std::move(vr.z); };
auto tdfWithZ = tdf.Define("z", getZ, {"HltVertexReports"});

// Book the filling of a histogram
auto zHisto = tdf.Histo1D("z");

// Also save z in a TTree
tdf.Snapshot("tree", "output.root", {"z"});

// Draw histogram
zHisto->DrawClone();
```
