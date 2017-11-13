#include "TRecordReader.hxx"
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

bool TRecordReader::NextBank()
{
   const auto recordEnd = fCurrentRecord + std::streamoff(fRecordSize);
   if (fBankHeader.size == 0u) {
      // jump to the end of the general record header (20 bytes long)
      auto pos = fFileBuf.pubseekpos(fCurrentRecord + std::streamoff(20));
      // find first bank, i.e. first occurrence of the magic number
      unsigned int magic = 0u;
      fFileBuf.sgetn(reinterpret_cast<char *>(&magic), 2);
      while (magic != 0xcbcb && pos < recordEnd) {
         pos = fFileBuf.pubseekoff(2, std::ios_base::cur);
         fFileBuf.sgetn(reinterpret_cast<char *>(&magic), 2);
      }
      if (magic != 0xcbcb) // no bank found
         return false;
      fCurrentBank = pos;
   } else {
      // jump to next bank
      const auto bankSize = fBankHeader.size;
      const auto paddingBytes = (4 - (bankSize % 4)) % 4; // bytes required to make the next bank 32-bit aligned
      fCurrentBank =
         fFileBuf.pubseekpos(fCurrentBank + std::streamoff(fBankHeader.size) + std::streamoff(paddingBytes));
      if (fCurrentBank >= recordEnd)
         return false;
   }
   fBankHeader = ReadBankHeader();
   return true;
}

BankHeader TRecordReader::ReadBankHeader()
{
   BankHeader h;
   fFileBuf.pubseekpos(fCurrentBank);
   unsigned int magic = 0u;
   fFileBuf.sgetn(reinterpret_cast<char *>(&magic), 2);
   if (magic != 0xcbcb)
      throw std::runtime_error("bank header does not start with magic pattern");
   fFileBuf.sgetn(reinterpret_cast<char *>(&h.size), 2);
   fFileBuf.sgetn(reinterpret_cast<char *>(&h.type), 1);
   fFileBuf.sgetn(reinterpret_cast<char *>(&h.version), 1);
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

std::vector<char> TRecordReader::GetBankBody() {
   const auto bankSize = fBankHeader.size;
   if (bankSize == 0u) {
      std::cerr << "warning: bank body requested, but no bank has been read for this record yet. Please call "
                   "`NextBank()` first.\n";
      return {};
   }

   fFileBuf.pubseekpos(fCurrentBank + std::streamoff(8)); // skip bank header
   const auto bodySize = bankSize - 8;
   std::vector<char> body(bodySize, 0);
   fFileBuf.sgetn(reinterpret_cast<char *>(body.data()), body.size());
   return body;
}
