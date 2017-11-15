#include "TRecordReader.hxx"
#include "PunTo.hxx"
#include <array>
#include <iostream>

TRecordReader::TRecordReader(const std::string &fname)
{
   const auto okay = fFileBuf.open(fname, std::ios_base::in);
   if (!okay)
      throw std::runtime_error("could not open file " + fname);
}

bool TRecordReader::NextRecord()
{
   fBankHeader = BankHeader(); // reset current bank header information
   fCurrentRecord = fFileBuf.pubseekpos(fCurrentRecord + std::streamoff(fRecordSize));
   if (fFileBuf.sgetc() == decltype(fFileBuf)::traits_type::eof())
      return false;
   fRecordSize = EvalRecordSize();
   if (fRecordSize == 0u) {
      std::cerr << "warning: corrupted record encountered at position " << fCurrentRecord << ", aborting.\n";
      return false;
   }
   return true;
}

bool TRecordReader::SeekRecordAt(pos_type pos)
{
   fBankHeader = BankHeader();
   fCurrentRecord = fFileBuf.pubseekpos(pos);
   if (fCurrentRecord < 0) {
      std::cerr << "warning: invalid position passed to SeekRecordAt, aborting.\n";
      return false;
   }
   fRecordSize = EvalRecordSize();
   if (fRecordSize == 0u) {
      std::cerr << "warning: corrupted record encountered at position " << fCurrentRecord << ", aborting.\n";
      return false;
   }
   return true;
}

bool TRecordReader::NextBank()
{
   // the body size we load is the record size except the first three words, which have been read by EvalRecordSize
   const auto bodySize = fRecordSize - 12;
   if (fBankHeader.size == 0u) { // first time we read banks in this record: load record in memory
      fRecordBody.clear();
      // N.B. this does not change the size of the vector, but we ignore that value, we just need enough storage
      fRecordBody.reserve(bodySize);
      fFileBuf.sgetn(fRecordBody.data(), bodySize);
      // find first bank, i.e. first occurrence of the magic number
      fCurrentBank = 8u; // skip the general record header (20 bytes long)
      auto magic = pun_to<unsigned short>(fRecordBody[fCurrentBank]);
      while (magic != 0xcbcb && fCurrentBank < bodySize) {
         fCurrentBank += 2;
         magic = pun_to<unsigned short>(fRecordBody[fCurrentBank]);
      }
      if (magic != 0xcbcb) // no bank found
         return false;
   } else {
      // jump to next bank
      const auto bankSize = fBankHeader.size;
      const auto paddingBytes = (4 - (bankSize % 4)) % 4; // bytes required to make the next bank 32-bit aligned
      fCurrentBank += bankSize + paddingBytes;
      if (fCurrentBank >= bodySize)
         return false;
   }
   fBankHeader = ReadBankHeader();
   if (fBankHeader.size == 0u) {
      std::cerr << "warning: could not read bank header. skipping further banks in record at position "
                << fCurrentRecord << '\n';
      return false;
   }
   return true;
}

BankHeader TRecordReader::ReadBankHeader()
{
   auto &magic = pun_to<unsigned short>(fRecordBody[fCurrentBank]);
   if (magic != 0xcbcb) {
      return BankHeader();
   }
   BankHeader h;
   h.size = static_cast<int>(pun_to<unsigned short>(fRecordBody[fCurrentBank + 2]));
   h.type = static_cast<EBankType>(fRecordBody[fCurrentBank + 4]);
   h.version = static_cast<int>(fRecordBody[fCurrentBank + 5]);
   return h;
}

unsigned int TRecordReader::EvalRecordSize()
{
   // TODO also check checksum
   std::array<unsigned int, 3> recordSizes;
   fFileBuf.sgetn(reinterpret_cast<char *>(&recordSizes[0]), 12);

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

   return std::array_view<char>(&fRecordBody[fCurrentBank + 8], bankSize);
}
