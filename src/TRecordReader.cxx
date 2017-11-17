#include "TRecordReader.hxx"
#include "PunTo.hxx"
#include <algorithm> // max
#include <array>
#include <iostream>

TRecordReader::TRecordReader(const std::string &fname)
{
   fFileStream.open(fname, std::ios_base::binary);
   if (!fFileStream.good())
      throw std::runtime_error("could not open file " + fname);
}

bool TRecordReader::NextRecord()
{
   fBankHeader = BankHeader(); // invalidate current bank header information
   constexpr auto headerSize = 20u;
   const auto canReadHeader = (fRecordPos + fRecordSize + headerSize <= fBlobSize);
   if (!canReadHeader) {
      if (fFileStream.eof())
         return false;
      const auto nextRecordPos = GetRecordPosition() + std::streamoff(fRecordSize);
      const auto nBytes = std::max(fBlobSize, 100ul * 1024 * 1024); // by default, read 100MB at a time
      LoadBlob(nextRecordPos, nBytes);
      fRecordPos = 0u;
   } else {
      fRecordPos += fRecordSize;
   }

   fRecordSize = EvalRecordSize();
   if (fRecordSize == 0u) {
      std::cerr << "warning: corrupted record encountered at position " << GetRecordPosition() << ", aborting.\n";
      return false;
   }

   const auto canReadRecord = (fRecordPos + fRecordSize <= fBlobSize);
   if (!canReadRecord) {
      const auto bytesToRead = std::max(fBlobSize, fRecordSize);
      LoadBlob(GetRecordPosition(), bytesToRead);
      fRecordPos = 0u;
   }

   return true;
}

bool TRecordReader::SeekRecordAt(pos_type pos)
{
   fBankHeader = BankHeader();
   fRecordPos = 0u;
   fBankPos = 0u;
   fFileStream.clear();

   const auto nBytes = std::max(fBlobSize, 100ul * 1024 * 1024); // by default, read 100MB at a time
   LoadBlob(pos, nBytes);

   fRecordSize = EvalRecordSize();
   if (fRecordSize == 0u) {
      std::cerr << "warning: corrupted record encountered at position " << GetRecordPosition() << ", aborting.\n";
      return false;
   }

   if (fRecordSize > fBlobSize)
      LoadBlob(GetRecordPosition(), fRecordSize);

   return true;
}

TRecordReader::pos_type TRecordReader::GetRecordPosition()
{
   return fLastReadPosition + std::streamoff(fRecordPos);
}

bool TRecordReader::NextBank()
{
   if (fBankHeader.size == 0u) { // first time we read banks in this record: load record in memory
      // find first bank, i.e. first occurrence of the magic number
      fBankPos = fRecordPos + 20u; // skip the generic record header (20 bytes)
      auto magic = pun_to<unsigned short>(fBlob[fBankPos]);
      while (magic != 0xcbcb && fBankPos < fRecordPos + fRecordSize) {
         fBankPos += 4;
         magic = pun_to<unsigned short>(fBlob[fBankPos]);
      }
      if (magic != 0xcbcb) // no bank found
         return false;
   } else {
      // jump to next bank
      const auto bankSize = fBankHeader.size;
      const auto paddingBytes = (4 - (bankSize % 4)) % 4; // bytes required to make the next bank 32-bit aligned
      fBankPos += bankSize + paddingBytes;
      if (fBankPos >= fRecordPos + fRecordSize)
         return false;
   }
   fBankHeader = ReadBankHeader();
   if (fBankHeader.size == 0u) {
      std::cerr << "warning: could not read bank header at position " << GetBankPosition()
                << ". skipping further banks in this record\n";
      return false;
   }
   return true;
}

TRecordReader::pos_type TRecordReader::GetBankPosition()
{
   return fLastReadPosition + std::streamoff(fBankPos);
}

BankHeader TRecordReader::ReadBankHeader()
{
   auto &magic = pun_to<unsigned short>(fBlob[fBankPos]);
   if (magic != 0xcbcb) {
      return BankHeader();
   }
   BankHeader h;
   h.size = static_cast<int>(pun_to<unsigned short>(fBlob[fBankPos + 2]));
   h.type = static_cast<EBankType>(fBlob[fBankPos + 4]);
   h.version = static_cast<int>(fBlob[fBankPos + 5]);
   return h;
}

void TRecordReader::LoadBlob(pos_type from, std::streamsize nBytes)
{
   fBlob.reserve(nBytes);
   fFileStream.seekg(from);
   fLastReadPosition = fFileStream.tellg();
   fFileStream.read(fBlob.data(), nBytes);
   fBlobSize = fFileStream.gcount();
}

unsigned int TRecordReader::EvalRecordSize()
{
   // TODO also check checksum
   auto recordSizes = reinterpret_cast<unsigned int *>(&fBlob[fRecordPos]);

   if (recordSizes[2] == recordSizes[0] || recordSizes[2] == recordSizes[1])
      return recordSizes[2];
   else if (recordSizes[0] == recordSizes[1])
      return recordSizes[0];
   else
      return 0u;
}

std::array_view<char> TRecordReader::GetBankBody()
{
   const auto bankSize = fBankHeader.size;
   if (bankSize == 0u) {
      std::cerr << "warning: bank body requested, but no bank has been read for this record yet. Please call "
                   "`NextBank()` first.\n";
      return {};
   }

   return std::array_view<char>(&fBlob[fBankPos + 8], bankSize);
}
