#ifndef TRECORDREADER
#define TRECORDREADER

#include <fstream> // std::filebuf

class TRecordReader {
public:
   using pos_type = std::filebuf::pos_type;

private:
   std::filebuf fFileBuf;         ///< stream buffer
   pos_type fCurrentRecord = 0;   ///< position of current record in file
   unsigned int fRecordSize = 0u; ///< size of current record
   /// Get size of current record, return 0 if record is corrupted
   unsigned int EvalRecordSize();

public:
   TRecordReader(const TRecordReader &) = default;
   TRecordReader(TRecordReader &&) = default;
   TRecordReader &operator=(const TRecordReader &) = default;
   TRecordReader &operator=(TRecordReader &&) = default;
   TRecordReader(const std::string &fname);
   /// Move this RecordReader to the next valid record in the file. Return false if there are no further records.
   bool NextRecord();
   /// Return position of the current record
   pos_type GetRecordPosition() { return fCurrentRecord; }
   unsigned int GetRecordSize() { return fRecordSize; }

private:
};

#endif
