#ifndef TRECORDREADER
#define TRECORDREADER

#include "BankTypes.h"

#include <ROOT/RArrayView.hxx>

#include <fstream> // std::filebuf
#include <vector>

struct BankHeader {
   unsigned int size = 0u;               // actually 16 bits
   EBankType type = EBankType::LastType; // actually 8 bits
   unsigned int version = 0u;            // actually 8 bits
};

class TRecordReader {
public:
   using pos_type = std::filebuf::pos_type;

private:
   std::filebuf fFileBuf;         ///< Stream buffer
   pos_type fCurrentRecord = 0;   ///< Position of current record in file
   unsigned int fRecordSize = 0u; ///< Size of current record in bytes
   BankHeader fBankHeader;        ///< Header information for the current header
   std::vector<char> fRecordBody; ///< Content of last record read
   std::size_t fCurrentBank = 0;  ///< Position of current bank in fRecordBody

public:
   TRecordReader(const TRecordReader &) = delete; // std::filebuf is not copy-constructible
   TRecordReader(TRecordReader &&) = default;
   TRecordReader &operator=(const TRecordReader &) = delete; // std::filebuf is not copy-assignable
   TRecordReader &operator=(TRecordReader &&) = default;
   explicit TRecordReader(const std::string &fname);
   /// Move this RecordReader to the next valid record in the file. Return false if there are no further records.
   bool NextRecord();
   /// Move this RecordReader to the record at position pos.
   /// Return false if the contents at this position do not look like a record header (prone to rare false negatives).
   bool SeekRecordAt(pos_type pos);
   /// Return position of the current record
   pos_type GetRecordPosition() const { return fCurrentRecord; }
   /// Return size of current record, or 0 if no record has been read yet
   unsigned int GetRecordSize() const { return fRecordSize; }
   /// Move this RecordReader to the next bank in the record. Return false if there are no further banks.
   /// After NextBank returns false, NextRecord must be called before calling NextBank again.
   bool NextBank();
   /// Return position of the current bank
   pos_type GetBankPosition() const { return fCurrentBank; }
   /// Return header information for the current bank
   BankHeader GetBankHeader() const { return fBankHeader; }
   /// Return a vector of bytes whose `data` contains the current bank's body
   std::array_view<char> GetBankBody();

private:
   /// Get size of current record, or 0 if record is corrupted
   unsigned int EvalRecordSize();
   /// Extract information from the bank header
   BankHeader ReadBankHeader();
};

#endif
