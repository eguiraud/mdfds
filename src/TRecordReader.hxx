#ifndef TRECORDREADER
#define TRECORDREADER

#include "BankTypes.h"

#include <ROOT/RArrayView.hxx>

#include <fstream> // std::ifstream
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
   std::ifstream fFileStream;       ///< Stream buffer
   pos_type fLastReadPosition = 0u; ///< Position of the seek pointer at the last call of LoadBlob
   std::vector<char> fBlob;         ///< Pointer to the part of the file currently loaded into memory
   std::size_t fBlobSize = 0u;      ///< Size of fBlob. Could be smaller than capacity for the last chunk of data.
   std::size_t fRecordPos = 0u;     ///< Position of current record in fBlob
   std::size_t fRecordSize = 0u;    ///< Size of current record in bytes
   BankHeader fBankHeader;          ///< Header information for the current header
   std::size_t fBankPos = 0u;       ///< Position of current bank in fBlob

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
   /// Return position of the current record in the input file
   pos_type GetRecordPosition();
   /// Return size of current record, or 0 if no record has been read yet
   std::size_t GetRecordSize() const { return fRecordSize; }
   /// Move this RecordReader to the next bank in the record. Return false if there are no further banks.
   /// After NextBank returns false, NextRecord must be called before calling NextBank again.
   bool NextBank();
   /// Return position of the current bank
   pos_type GetBankPosition();
   /// Return header information for the current bank
   BankHeader GetBankHeader() const { return fBankHeader; }
   /// Return a vector of bytes whose `data` contains the current bank's body
   std::array_view<char> GetBankBody();

private:
   /// Load nBytes from file to memory, taking care of starting at a record boundary
   void LoadBlob(pos_type from, std::streamsize nBytes);
   /// Get size of current record, or 0 if record is corrupted
   unsigned int EvalRecordSize();
   /// Extract information from the bank header
   BankHeader ReadBankHeader();
};

#endif
