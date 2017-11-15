# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public template<typename T,typename U>`  `const T & `[`pun_to`](#TBankDecoder_8hxx_1a3d2b8b16c61ab912f35b40c3999a8144)`(const U & x)`            | General utility to reinterpret the memory associated to a certain value pun_to allows to reinterpret the memory associated to a variable without copies.
`public template<typename... Decoders>`  `ROOT::Experimental::TDataFrame `[`MakeMDFDataFrame`](#TMDFDataSource_8hxx_1a471dd72b9110dbecd7d04880d3e542b5)`(const std::vector< std::string > & fileNames)`            | 
`class `[`TBankDecoder`](#classTBankDecoder) | Abstract implementation of an MDF bank decoder. [TMDFDataSource](#classTMDFDataSource) uses concrete [TBankDecoder](#classTBankDecoder) implementations to read banks.
`class `[`TDummyDecoder`](#classTDummyDecoder) | 
`class `[`THltVertexReportsDecoder`](#classTHltVertexReportsDecoder) | Implements the decoding of the HltVertexReports bank With this class, all the useful information from the HltVertexReports bank is extracted.
`class `[`TMDFDataSource`](#classTMDFDataSource) | A concrete TDataSource implementation that reads MDF files.
`class `[`TRecordReader`](#classTRecordReader) | 
`struct `[`BankHeader`](#structBankHeader) | 
`struct `[`THltVertexReports`](#structTHltVertexReports) | The C++ representation of the HltVertexReports bank This struct is a SOA which represents the primary vertices of an event.
`struct `[`TPVInfo`](#structTPVInfo) | 

## Members

#### `public template<typename T,typename U>`  `const T & `[`pun_to`](#TBankDecoder_8hxx_1a3d2b8b16c61ab912f35b40c3999a8144)`(const U & x)` {#TBankDecoder_8hxx_1a3d2b8b16c61ab912f35b40c3999a8144}

General utility to reinterpret the memory associated to a certain value pun_to allows to reinterpret the memory associated to a variable without copies.

#### `public template<typename... Decoders>`  `ROOT::Experimental::TDataFrame `[`MakeMDFDataFrame`](#TMDFDataSource_8hxx_1a471dd72b9110dbecd7d04880d3e542b5)`(const std::vector< std::string > & fileNames)` {#TMDFDataSource_8hxx_1a471dd72b9110dbecd7d04880d3e542b5}

# class TBankDecoder {#classTBankDecoder}

Abstract implementation of an MDF bank decoder. [TMDFDataSource](#classTMDFDataSource) uses concrete [TBankDecoder](#classTBankDecoder) implementations to read banks.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline virtual  `[`~TBankDecoder`](#classTBankDecoder_1a27b4cefbd6e814f7765a447782dc173a)`()` | 
`public std::string `[`GetName`](#classTBankDecoder_1a713cbba8f396c64336aeab2e769d3f3e)`() const` | Retrieve bank name. Corresponds to the column name used in TDataFrame to refer to this bank.
`public std::string `[`GetTypeName`](#classTBankDecoder_1a7d6137a27a5a42ad15824382a1af4332)`() const` | Retrieve the type name of this bank as a string.
`public const std::type_info & `[`GetTypeInfo`](#classTBankDecoder_1a6a242950032ea29bd6ffa224435abea4)`() const` | Retrieve the type info of this bank.
`public EBankType `[`GetID`](#classTBankDecoder_1a29427e9a87c162f7634057cc911c7d08)`() const` | Retrieve bank ID.
`public void `[`Decode`](#classTBankDecoder_1ac3f3480ff9c98b4c9333994eb3f7b89d)`(const std::vector< char > & bank,void * destination) const` | Take a bank body as raw bytes, put the encoding in the area of memory pointed by destination.
`public void * `[`Allocate`](#classTBankDecoder_1a282bb5e06f06cfbf7033bd31f09fec2c)`() const` | Allocate N objects of the correct type, after checking that we expect the right type.
`public void `[`Deallocate`](#classTBankDecoder_1a1c548c221c32cb114653e8ecc45c1fdb)`(void * obj) const` | Deallocate objects by calling the destructor for the appropriate type.

## Members

#### `public inline virtual  `[`~TBankDecoder`](#classTBankDecoder_1a27b4cefbd6e814f7765a447782dc173a)`()` {#classTBankDecoder_1a27b4cefbd6e814f7765a447782dc173a}

#### `public std::string `[`GetName`](#classTBankDecoder_1a713cbba8f396c64336aeab2e769d3f3e)`() const` {#classTBankDecoder_1a713cbba8f396c64336aeab2e769d3f3e}

Retrieve bank name. Corresponds to the column name used in TDataFrame to refer to this bank.

#### `public std::string `[`GetTypeName`](#classTBankDecoder_1a7d6137a27a5a42ad15824382a1af4332)`() const` {#classTBankDecoder_1a7d6137a27a5a42ad15824382a1af4332}

Retrieve the type name of this bank as a string.

#### `public const std::type_info & `[`GetTypeInfo`](#classTBankDecoder_1a6a242950032ea29bd6ffa224435abea4)`() const` {#classTBankDecoder_1a6a242950032ea29bd6ffa224435abea4}

Retrieve the type info of this bank.

#### `public EBankType `[`GetID`](#classTBankDecoder_1a29427e9a87c162f7634057cc911c7d08)`() const` {#classTBankDecoder_1a29427e9a87c162f7634057cc911c7d08}

Retrieve bank ID.

#### `public void `[`Decode`](#classTBankDecoder_1ac3f3480ff9c98b4c9333994eb3f7b89d)`(const std::vector< char > & bank,void * destination) const` {#classTBankDecoder_1ac3f3480ff9c98b4c9333994eb3f7b89d}

Take a bank body as raw bytes, put the encoding in the area of memory pointed by destination.

#### `public void * `[`Allocate`](#classTBankDecoder_1a282bb5e06f06cfbf7033bd31f09fec2c)`() const` {#classTBankDecoder_1a282bb5e06f06cfbf7033bd31f09fec2c}

Allocate N objects of the correct type, after checking that we expect the right type.

#### `public void `[`Deallocate`](#classTBankDecoder_1a1c548c221c32cb114653e8ecc45c1fdb)`(void * obj) const` {#classTBankDecoder_1a1c548c221c32cb114653e8ecc45c1fdb}

Deallocate objects by calling the destructor for the appropriate type.

# class TDummyDecoder {#classTDummyDecoder}

```
class TDummyDecoder
  : public TBankDecoder
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline virtual std::string `[`GetName`](#classTDummyDecoder_1aa9ef52b96b8992dd45bdd53bdc238d98)`() const` | Retrieve bank name. Corresponds to the column name used in TDataFrame to refer to this bank.
`public inline virtual std::string `[`GetTypeName`](#classTDummyDecoder_1a3a43c1b526e231b1212d57f070ba0018)`() const` | Retrieve the type name of this bank as a string.
`public inline virtual const std::type_info & `[`GetTypeInfo`](#classTDummyDecoder_1a968f8b90d43cae89e1e6597e521f0279)`() const` | Retrieve the type info of this bank.
`public inline virtual EBankType `[`GetID`](#classTDummyDecoder_1a6eaef7037807675b5addd3cdb197d56a)`() const` | Retrieve bank ID.
`public inline virtual void `[`Decode`](#classTDummyDecoder_1a651cc70be066cba919fe3db1025a5e4a)`(const std::vector< char > & bank,void * destination) const` | Take a bank body as raw bytes, put the encoding in the area of memory pointed by destination.
`public virtual void * `[`Allocate`](#classTDummyDecoder_1a076b39435656d17574811d4e65ffa024)`() const` | Allocate N objects of the correct type, after checking that we expect the right type.
`public virtual void `[`Deallocate`](#classTDummyDecoder_1af4da42503ae45788b559c3a453602b2f)`(void * obj) const` | Deallocate objects by calling the destructor for the appropriate type.

## Members

#### `public inline virtual std::string `[`GetName`](#classTDummyDecoder_1aa9ef52b96b8992dd45bdd53bdc238d98)`() const` {#classTDummyDecoder_1aa9ef52b96b8992dd45bdd53bdc238d98}

Retrieve bank name. Corresponds to the column name used in TDataFrame to refer to this bank.

#### `public inline virtual std::string `[`GetTypeName`](#classTDummyDecoder_1a3a43c1b526e231b1212d57f070ba0018)`() const` {#classTDummyDecoder_1a3a43c1b526e231b1212d57f070ba0018}

Retrieve the type name of this bank as a string.

#### `public inline virtual const std::type_info & `[`GetTypeInfo`](#classTDummyDecoder_1a968f8b90d43cae89e1e6597e521f0279)`() const` {#classTDummyDecoder_1a968f8b90d43cae89e1e6597e521f0279}

Retrieve the type info of this bank.

#### `public inline virtual EBankType `[`GetID`](#classTDummyDecoder_1a6eaef7037807675b5addd3cdb197d56a)`() const` {#classTDummyDecoder_1a6eaef7037807675b5addd3cdb197d56a}

Retrieve bank ID.

#### `public inline virtual void `[`Decode`](#classTDummyDecoder_1a651cc70be066cba919fe3db1025a5e4a)`(const std::vector< char > & bank,void * destination) const` {#classTDummyDecoder_1a651cc70be066cba919fe3db1025a5e4a}

Take a bank body as raw bytes, put the encoding in the area of memory pointed by destination.

#### `public virtual void * `[`Allocate`](#classTDummyDecoder_1a076b39435656d17574811d4e65ffa024)`() const` {#classTDummyDecoder_1a076b39435656d17574811d4e65ffa024}

Allocate N objects of the correct type, after checking that we expect the right type.

#### `public virtual void `[`Deallocate`](#classTDummyDecoder_1af4da42503ae45788b559c3a453602b2f)`(void * obj) const` {#classTDummyDecoder_1af4da42503ae45788b559c3a453602b2f}

Deallocate objects by calling the destructor for the appropriate type.

# class THltVertexReportsDecoder {#classTHltVertexReportsDecoder}

```
class THltVertexReportsDecoder
  : public TBankDecoder
```  

Implements the decoding of the HltVertexReports bank With this class, all the useful information from the HltVertexReports bank is extracted.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`~THltVertexReportsDecoder`](#classTHltVertexReportsDecoder_1aca7a4365746d4596c15754517d6ac351)`()` | 
`public inline virtual std::string `[`GetName`](#classTHltVertexReportsDecoder_1a1e6bc6af69af9dd90e0c92ccb4aa4133)`() const` | Retrieve bank name. Corresponds to the column name used in TDataFrame to refer to this bank.
`public inline virtual std::string `[`GetTypeName`](#classTHltVertexReportsDecoder_1a8748b607edfdecef6737ec7a43e56fd6)`() const` | Retrieve the type name of this bank as a string.
`public virtual const std::type_info & `[`GetTypeInfo`](#classTHltVertexReportsDecoder_1afd2f882b9a1319f23ffb7edda9f1e4ba)`() const` | Retrieve the type info of this bank.
`public virtual EBankType `[`GetID`](#classTHltVertexReportsDecoder_1ad428c3f6ee8e37600c10b4a28da3e755)`() const` | Retrieve bank ID.
`public virtual void `[`Decode`](#classTHltVertexReportsDecoder_1a8aed65af74d6aa7725ab9632558e6b29)`(const std::vector< char > & bank,void * destination) const` | Take a bank body as raw bytes, put the encoding in the area of memory pointed by destination.
`public virtual void * `[`Allocate`](#classTHltVertexReportsDecoder_1ad0f80c5f5a05a990cf8d485a979904e4)`() const` | Allocate N objects of the correct type, after checking that we expect the right type.
`public virtual void `[`Deallocate`](#classTHltVertexReportsDecoder_1a57f31eca68df79efa2365aaf75f42099)`(void * obj) const` | Deallocate objects by calling the destructor for the appropriate type.

## Members

#### `public inline  `[`~THltVertexReportsDecoder`](#classTHltVertexReportsDecoder_1aca7a4365746d4596c15754517d6ac351)`()` {#classTHltVertexReportsDecoder_1aca7a4365746d4596c15754517d6ac351}

#### `public inline virtual std::string `[`GetName`](#classTHltVertexReportsDecoder_1a1e6bc6af69af9dd90e0c92ccb4aa4133)`() const` {#classTHltVertexReportsDecoder_1a1e6bc6af69af9dd90e0c92ccb4aa4133}

Retrieve bank name. Corresponds to the column name used in TDataFrame to refer to this bank.

#### `public inline virtual std::string `[`GetTypeName`](#classTHltVertexReportsDecoder_1a8748b607edfdecef6737ec7a43e56fd6)`() const` {#classTHltVertexReportsDecoder_1a8748b607edfdecef6737ec7a43e56fd6}

Retrieve the type name of this bank as a string.

#### `public virtual const std::type_info & `[`GetTypeInfo`](#classTHltVertexReportsDecoder_1afd2f882b9a1319f23ffb7edda9f1e4ba)`() const` {#classTHltVertexReportsDecoder_1afd2f882b9a1319f23ffb7edda9f1e4ba}

Retrieve the type info of this bank.

#### `public virtual EBankType `[`GetID`](#classTHltVertexReportsDecoder_1ad428c3f6ee8e37600c10b4a28da3e755)`() const` {#classTHltVertexReportsDecoder_1ad428c3f6ee8e37600c10b4a28da3e755}

Retrieve bank ID.

#### `public virtual void `[`Decode`](#classTHltVertexReportsDecoder_1a8aed65af74d6aa7725ab9632558e6b29)`(const std::vector< char > & bank,void * destination) const` {#classTHltVertexReportsDecoder_1a8aed65af74d6aa7725ab9632558e6b29}

Take a bank body as raw bytes, put the encoding in the area of memory pointed by destination.

#### `public virtual void * `[`Allocate`](#classTHltVertexReportsDecoder_1ad0f80c5f5a05a990cf8d485a979904e4)`() const` {#classTHltVertexReportsDecoder_1ad0f80c5f5a05a990cf8d485a979904e4}

Allocate N objects of the correct type, after checking that we expect the right type.

#### `public virtual void `[`Deallocate`](#classTHltVertexReportsDecoder_1a57f31eca68df79efa2365aaf75f42099)`(void * obj) const` {#classTHltVertexReportsDecoder_1a57f31eca68df79efa2365aaf75f42099}

Deallocate objects by calling the destructor for the appropriate type.

# class TMDFDataSource {#classTMDFDataSource}

```
class TMDFDataSource
  : public TDataSource
```  

A concrete TDataSource implementation that reads MDF files.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  explicit `[`TMDFDataSource`](#classTMDFDataSource_1a4fcc5cfded0d8543ff959ddfb2844ddc)`(const std::vector< std::string > & fileNames)` | 
`public inline void `[`SetNSlots`](#classTMDFDataSource_1a7cabef4edda1665cb903402c4a1d762f)`(unsigned int nSlots)` | 
`public inline const std::vector< std::string > & `[`GetColumnNames`](#classTMDFDataSource_1ae3d841832c0696c3c00b9021d071394c)`() const` | 
`public inline bool `[`HasColumn`](#classTMDFDataSource_1ac86d906ab78b0e05f24b8646a6ed19c8)`(std::string_view col) const` | 
`public inline std::string `[`GetTypeName`](#classTMDFDataSource_1aa2dd04f9508f6b3da617dc974a7b2096)`(std::string_view col) const` | 
`public inline std::vector< std::pair< ULong64_t, ULong64_t > > `[`GetEntryRanges`](#classTMDFDataSource_1a71697a9a5017b63ee8925ab41e5b04c1)`()` | 
`public inline std::vector< std::pair< ULong64_t, ULong64_t > > `[`GetEntryRanges`](#classTMDFDataSource_1ab6162599fcb412ce782550ed22e97239)`(TRecordReader::pos_type minRangeSize)` | 
`public inline void `[`SetEntry`](#classTMDFDataSource_1a24e1f0d2dd3e80650d42a6874b621869)`(unsigned int slot,ULong64_t entry)` | 

## Members

#### `public inline  explicit `[`TMDFDataSource`](#classTMDFDataSource_1a4fcc5cfded0d8543ff959ddfb2844ddc)`(const std::vector< std::string > & fileNames)` {#classTMDFDataSource_1a4fcc5cfded0d8543ff959ddfb2844ddc}

#### `public inline void `[`SetNSlots`](#classTMDFDataSource_1a7cabef4edda1665cb903402c4a1d762f)`(unsigned int nSlots)` {#classTMDFDataSource_1a7cabef4edda1665cb903402c4a1d762f}

#### `public inline const std::vector< std::string > & `[`GetColumnNames`](#classTMDFDataSource_1ae3d841832c0696c3c00b9021d071394c)`() const` {#classTMDFDataSource_1ae3d841832c0696c3c00b9021d071394c}

#### `public inline bool `[`HasColumn`](#classTMDFDataSource_1ac86d906ab78b0e05f24b8646a6ed19c8)`(std::string_view col) const` {#classTMDFDataSource_1ac86d906ab78b0e05f24b8646a6ed19c8}

#### `public inline std::string `[`GetTypeName`](#classTMDFDataSource_1aa2dd04f9508f6b3da617dc974a7b2096)`(std::string_view col) const` {#classTMDFDataSource_1aa2dd04f9508f6b3da617dc974a7b2096}

#### `public inline std::vector< std::pair< ULong64_t, ULong64_t > > `[`GetEntryRanges`](#classTMDFDataSource_1a71697a9a5017b63ee8925ab41e5b04c1)`()` {#classTMDFDataSource_1a71697a9a5017b63ee8925ab41e5b04c1}

#### `public inline std::vector< std::pair< ULong64_t, ULong64_t > > `[`GetEntryRanges`](#classTMDFDataSource_1ab6162599fcb412ce782550ed22e97239)`(TRecordReader::pos_type minRangeSize)` {#classTMDFDataSource_1ab6162599fcb412ce782550ed22e97239}

#### `public inline void `[`SetEntry`](#classTMDFDataSource_1a24e1f0d2dd3e80650d42a6874b621869)`(unsigned int slot,ULong64_t entry)` {#classTMDFDataSource_1a24e1f0d2dd3e80650d42a6874b621869}

# class TRecordReader {#classTRecordReader}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`TRecordReader`](#classTRecordReader_1aa38b9403160b4fc869e60f7bceafe8f7)`(const `[`TRecordReader`](#classTRecordReader)` &) = delete` | 
`public  `[`TRecordReader`](#classTRecordReader_1a02d0a1eed10b2e9c0c453bf321ccca91)`(`[`TRecordReader`](#classTRecordReader)` &&) = default` | 
`public `[`TRecordReader`](#classTRecordReader)` & `[`operator=`](#classTRecordReader_1ae552673f22013c9e6e82b193cd138846)`(const `[`TRecordReader`](#classTRecordReader)` &) = delete` | 
`public `[`TRecordReader`](#classTRecordReader)` & `[`operator=`](#classTRecordReader_1a9a5c2410f538ad7b0083c3f131fa4d03)`(`[`TRecordReader`](#classTRecordReader)` &&) = default` | 
`public  explicit `[`TRecordReader`](#classTRecordReader_1a02d2f7538a880c0462c802ef6384cfaf)`(const std::string & fname)` | 
`public bool `[`NextRecord`](#classTRecordReader_1a37c4340128c182f24f38178c7775df96)`()` | Move this RecordReader to the next valid record in the file. Return false if there are no further records.
`public bool `[`SeekRecordAt`](#classTRecordReader_1ae20b41dfbe046e30418627a726e83486)`(pos_type pos)` | Move this RecordReader to the record at position pos. Return false if the contents at this position do not look like a record header (prone to rare false negatives).
`public inline pos_type `[`GetRecordPosition`](#classTRecordReader_1a6ad9d33d62537c26c80d413250332ca1)`() const` | Return position of the current record.
`public inline unsigned int `[`GetRecordSize`](#classTRecordReader_1abddc2d2e17bd287605b231907be629fc)`() const` | Return size of current record, or 0 if no record has been read yet.
`public bool `[`NextBank`](#classTRecordReader_1a2a33326abf992e8b7220c261c192f378)`()` | Move this RecordReader to the next bank in the record. Return false if there are no further banks.
`public inline pos_type `[`GetBankPosition`](#classTRecordReader_1a7b9dfab4636f04b902236913605561bb)`() const` | Return position of the current bank.
`public inline `[`BankHeader`](#structBankHeader)` `[`GetBankHeader`](#classTRecordReader_1a8dc808d86001c6ba1a9e9118c6606ae6)`() const` | Return header information for the current bank.
`public std::vector< char > `[`GetBankBody`](#classTRecordReader_1aa41cbce6002b11635ebdc8b7232bfe06)`()` | Return a vector of bytes whose `data` contains the current bank's body.

## Members

#### `public  `[`TRecordReader`](#classTRecordReader_1aa38b9403160b4fc869e60f7bceafe8f7)`(const `[`TRecordReader`](#classTRecordReader)` &) = delete` {#classTRecordReader_1aa38b9403160b4fc869e60f7bceafe8f7}

#### `public  `[`TRecordReader`](#classTRecordReader_1a02d0a1eed10b2e9c0c453bf321ccca91)`(`[`TRecordReader`](#classTRecordReader)` &&) = default` {#classTRecordReader_1a02d0a1eed10b2e9c0c453bf321ccca91}

#### `public `[`TRecordReader`](#classTRecordReader)` & `[`operator=`](#classTRecordReader_1ae552673f22013c9e6e82b193cd138846)`(const `[`TRecordReader`](#classTRecordReader)` &) = delete` {#classTRecordReader_1ae552673f22013c9e6e82b193cd138846}

#### `public `[`TRecordReader`](#classTRecordReader)` & `[`operator=`](#classTRecordReader_1a9a5c2410f538ad7b0083c3f131fa4d03)`(`[`TRecordReader`](#classTRecordReader)` &&) = default` {#classTRecordReader_1a9a5c2410f538ad7b0083c3f131fa4d03}

#### `public  explicit `[`TRecordReader`](#classTRecordReader_1a02d2f7538a880c0462c802ef6384cfaf)`(const std::string & fname)` {#classTRecordReader_1a02d2f7538a880c0462c802ef6384cfaf}

#### `public bool `[`NextRecord`](#classTRecordReader_1a37c4340128c182f24f38178c7775df96)`()` {#classTRecordReader_1a37c4340128c182f24f38178c7775df96}

Move this RecordReader to the next valid record in the file. Return false if there are no further records.

#### `public bool `[`SeekRecordAt`](#classTRecordReader_1ae20b41dfbe046e30418627a726e83486)`(pos_type pos)` {#classTRecordReader_1ae20b41dfbe046e30418627a726e83486}

Move this RecordReader to the record at position pos. Return false if the contents at this position do not look like a record header (prone to rare false negatives).

#### `public inline pos_type `[`GetRecordPosition`](#classTRecordReader_1a6ad9d33d62537c26c80d413250332ca1)`() const` {#classTRecordReader_1a6ad9d33d62537c26c80d413250332ca1}

Return position of the current record.

#### `public inline unsigned int `[`GetRecordSize`](#classTRecordReader_1abddc2d2e17bd287605b231907be629fc)`() const` {#classTRecordReader_1abddc2d2e17bd287605b231907be629fc}

Return size of current record, or 0 if no record has been read yet.

#### `public bool `[`NextBank`](#classTRecordReader_1a2a33326abf992e8b7220c261c192f378)`()` {#classTRecordReader_1a2a33326abf992e8b7220c261c192f378}

Move this RecordReader to the next bank in the record. Return false if there are no further banks.

#### `public inline pos_type `[`GetBankPosition`](#classTRecordReader_1a7b9dfab4636f04b902236913605561bb)`() const` {#classTRecordReader_1a7b9dfab4636f04b902236913605561bb}

Return position of the current bank.

#### `public inline `[`BankHeader`](#structBankHeader)` `[`GetBankHeader`](#classTRecordReader_1a8dc808d86001c6ba1a9e9118c6606ae6)`() const` {#classTRecordReader_1a8dc808d86001c6ba1a9e9118c6606ae6}

Return header information for the current bank.

#### `public std::vector< char > `[`GetBankBody`](#classTRecordReader_1aa41cbce6002b11635ebdc8b7232bfe06)`()` {#classTRecordReader_1aa41cbce6002b11635ebdc8b7232bfe06}

Return a vector of bytes whose `data` contains the current bank's body.

# struct `BankHeader` {#structBankHeader}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public unsigned int `[`size`](#structBankHeader_1a16d8833886143b44bf4cd71ddec36b81) | 
`public EBankType `[`type`](#structBankHeader_1a44030c862119db9a750100d529126d29) | 
`public unsigned int `[`version`](#structBankHeader_1ac4bfd736bd0dce625aed0409036651f6) | 

## Members

#### `public unsigned int `[`size`](#structBankHeader_1a16d8833886143b44bf4cd71ddec36b81) {#structBankHeader_1a16d8833886143b44bf4cd71ddec36b81}

#### `public EBankType `[`type`](#structBankHeader_1a44030c862119db9a750100d529126d29) {#structBankHeader_1a44030c862119db9a750100d529126d29}

#### `public unsigned int `[`version`](#structBankHeader_1ac4bfd736bd0dce625aed0409036651f6) {#structBankHeader_1ac4bfd736bd0dce625aed0409036651f6}

# struct `THltVertexReports` {#structTHltVertexReports}

The C++ representation of the HltVertexReports bank This struct is a SOA which represents the primary vertices of an event.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public std::vector< float > `[`x`](#structTHltVertexReports_1a822249b0a9883870b7debba712fc26f2) | 
`public std::vector< float > `[`y`](#structTHltVertexReports_1a8c316bd3def295a67d267e2d6cc9c350) | 
`public std::vector< float > `[`z`](#structTHltVertexReports_1afc4ab30cd4d2c416f12855feb67d5846) | 
`public std::vector< float > `[`chi2`](#structTHltVertexReports_1aac9b559bd931579e0f7cd809f8da476c) | 
`public std::vector< unsigned int > `[`ndof`](#structTHltVertexReports_1a06b7b376985484ba49b2e588abf59b69) | 
`public std::vector< float > `[`cov_00`](#structTHltVertexReports_1aecd87a1a77c8f22961e84ce991947483) | 
`public std::vector< float > `[`cov_11`](#structTHltVertexReports_1a7d8d45d1663c4782c1be50dc6d9dbce1) | 
`public std::vector< float > `[`cov_22`](#structTHltVertexReports_1a4c7ab40fac2fee402c8e8c5b6839cd38) | 
`public std::vector< float > `[`cov_01`](#structTHltVertexReports_1abf108621ecafe609c2f69b37a77473ef) | 
`public std::vector< float > `[`cov_02`](#structTHltVertexReports_1a777b78e5a29865ee19a448b7a014d18e) | 
`public std::vector< float > `[`cov_12`](#structTHltVertexReports_1a7fcb6f67e9553c58c9c979c860220c7f) | 

## Members

#### `public std::vector< float > `[`x`](#structTHltVertexReports_1a822249b0a9883870b7debba712fc26f2) {#structTHltVertexReports_1a822249b0a9883870b7debba712fc26f2}

#### `public std::vector< float > `[`y`](#structTHltVertexReports_1a8c316bd3def295a67d267e2d6cc9c350) {#structTHltVertexReports_1a8c316bd3def295a67d267e2d6cc9c350}

#### `public std::vector< float > `[`z`](#structTHltVertexReports_1afc4ab30cd4d2c416f12855feb67d5846) {#structTHltVertexReports_1afc4ab30cd4d2c416f12855feb67d5846}

#### `public std::vector< float > `[`chi2`](#structTHltVertexReports_1aac9b559bd931579e0f7cd809f8da476c) {#structTHltVertexReports_1aac9b559bd931579e0f7cd809f8da476c}

#### `public std::vector< unsigned int > `[`ndof`](#structTHltVertexReports_1a06b7b376985484ba49b2e588abf59b69) {#structTHltVertexReports_1a06b7b376985484ba49b2e588abf59b69}

#### `public std::vector< float > `[`cov_00`](#structTHltVertexReports_1aecd87a1a77c8f22961e84ce991947483) {#structTHltVertexReports_1aecd87a1a77c8f22961e84ce991947483}

#### `public std::vector< float > `[`cov_11`](#structTHltVertexReports_1a7d8d45d1663c4782c1be50dc6d9dbce1) {#structTHltVertexReports_1a7d8d45d1663c4782c1be50dc6d9dbce1}

#### `public std::vector< float > `[`cov_22`](#structTHltVertexReports_1a4c7ab40fac2fee402c8e8c5b6839cd38) {#structTHltVertexReports_1a4c7ab40fac2fee402c8e8c5b6839cd38}

#### `public std::vector< float > `[`cov_01`](#structTHltVertexReports_1abf108621ecafe609c2f69b37a77473ef) {#structTHltVertexReports_1abf108621ecafe609c2f69b37a77473ef}

#### `public std::vector< float > `[`cov_02`](#structTHltVertexReports_1a777b78e5a29865ee19a448b7a014d18e) {#structTHltVertexReports_1a777b78e5a29865ee19a448b7a014d18e}

#### `public std::vector< float > `[`cov_12`](#structTHltVertexReports_1a7fcb6f67e9553c58c9c979c860220c7f) {#structTHltVertexReports_1a7fcb6f67e9553c58c9c979c860220c7f}

# struct `TPVInfo` {#structTPVInfo}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public float `[`x`](#structTPVInfo_1a3279fe04ba506e0c5a42cbb292f65a8c) | 
`public float `[`y`](#structTPVInfo_1aee0fcd7e541a565e605d8d8e1c593931) | 
`public float `[`z`](#structTPVInfo_1ae565ea43daa8e73751aebee3aa813a00) | 
`public float `[`chi2`](#structTPVInfo_1a90dcb41890494885b5617239892677d1) | 
`public unsigned int `[`ndof`](#structTPVInfo_1a2e38fd404acccb0e5cadbe74b12e2396) | 
`public float `[`cov_00`](#structTPVInfo_1ae4285097e4b5c3313f8d1ea296f8bb42) | 
`public float `[`cov_11`](#structTPVInfo_1a65b430bbbf525b336fb318deb7047e51) | 
`public float `[`cov_22`](#structTPVInfo_1adf8aea19a719abe86f8cb6ad8c3dba37) | 
`public float `[`cov_01`](#structTPVInfo_1a374e676e304d8bedc35c9ec8ce0a5c4d) | 
`public float `[`cov_02`](#structTPVInfo_1a0cdd56aabcbf765fd049f2310eb144b7) | 
`public float `[`cov_12`](#structTPVInfo_1aef68b37402ac98b5357d7d3d86ac5f08) | 

## Members

#### `public float `[`x`](#structTPVInfo_1a3279fe04ba506e0c5a42cbb292f65a8c) {#structTPVInfo_1a3279fe04ba506e0c5a42cbb292f65a8c}

#### `public float `[`y`](#structTPVInfo_1aee0fcd7e541a565e605d8d8e1c593931) {#structTPVInfo_1aee0fcd7e541a565e605d8d8e1c593931}

#### `public float `[`z`](#structTPVInfo_1ae565ea43daa8e73751aebee3aa813a00) {#structTPVInfo_1ae565ea43daa8e73751aebee3aa813a00}

#### `public float `[`chi2`](#structTPVInfo_1a90dcb41890494885b5617239892677d1) {#structTPVInfo_1a90dcb41890494885b5617239892677d1}

#### `public unsigned int `[`ndof`](#structTPVInfo_1a2e38fd404acccb0e5cadbe74b12e2396) {#structTPVInfo_1a2e38fd404acccb0e5cadbe74b12e2396}

#### `public float `[`cov_00`](#structTPVInfo_1ae4285097e4b5c3313f8d1ea296f8bb42) {#structTPVInfo_1ae4285097e4b5c3313f8d1ea296f8bb42}

#### `public float `[`cov_11`](#structTPVInfo_1a65b430bbbf525b336fb318deb7047e51) {#structTPVInfo_1a65b430bbbf525b336fb318deb7047e51}

#### `public float `[`cov_22`](#structTPVInfo_1adf8aea19a719abe86f8cb6ad8c3dba37) {#structTPVInfo_1adf8aea19a719abe86f8cb6ad8c3dba37}

#### `public float `[`cov_01`](#structTPVInfo_1a374e676e304d8bedc35c9ec8ce0a5c4d) {#structTPVInfo_1a374e676e304d8bedc35c9ec8ce0a5c4d}

#### `public float `[`cov_02`](#structTPVInfo_1a0cdd56aabcbf765fd049f2310eb144b7) {#structTPVInfo_1a0cdd56aabcbf765fd049f2310eb144b7}

#### `public float `[`cov_12`](#structTPVInfo_1aef68b37402ac98b5357d7d3d86ac5f08) {#structTPVInfo_1aef68b37402ac98b5357d7d3d86ac5f08}

Generated by [Moxygen](https://sourcey.com/moxygen)
