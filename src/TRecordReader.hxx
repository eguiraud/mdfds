#ifndef TRECORDREADER
#define TRECORDREADER

#include <fstream> // std::filebuf

struct BankHeader {
   unsigned int size = 0u;    // actually 16 bits
   unsigned int type = 0u;    // actually 8 bits
   unsigned int version = 0u; // actually 8 bits
};

class TRecordReader {
public:
   using pos_type = std::filebuf::pos_type;

private:
   std::filebuf fFileBuf;         ///< Stream buffer
   pos_type fCurrentRecord = 0;   ///< Position of current record in file
   unsigned int fRecordSize = 0u; ///< Size of current record
   pos_type fCurrentBank = 0;     ///< Position of current bank in file
   BankHeader fBankHeader;        ///< Header information for the current header
   /// Get size of current record, or 0 if record is corrupted
   unsigned int EvalRecordSize();

public:
   TRecordReader(const TRecordReader &) = default;
   TRecordReader(TRecordReader &&) = default;
   TRecordReader &operator=(const TRecordReader &) = default;
   TRecordReader &operator=(TRecordReader &&) = default;
   explicit TRecordReader(const std::string &fname);
   /// Move this RecordReader to the next valid record in the file. Return false if there are no further records.
   bool NextRecord();
   /// Return position of the current record
   pos_type GetRecordPosition() { return fCurrentRecord; }
   /// Return size of current record, or 0 if no record has been read yet
   unsigned int GetRecordSize() { return fRecordSize; }
   /// Move this RecordReader to the next bank in the record. Return false if there are no further banks.
   bool NextBank();
   /// Return position of the current bank
   pos_type GetBankPosition() { return fCurrentBank; }
   /// Return header information for the current bank
   BankHeader GetBankHeader() { return fBankHeader; }


private:
   /// Extract information from the bank header
   BankHeader ReadBankHeader();
};

#endif
