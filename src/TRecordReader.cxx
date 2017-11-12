#include "TRecordReader.hxx"
#include <array>
#include <iostream>

TRecordReader::TRecordReader(const std::string &fname)
{
   const auto okay = fFileBuf.open(fname, std::ios_base::in);
}

bool TRecordReader::NextRecord()
{
   fCurrentRecord = fFileBuf.pubseekpos(fCurrentRecord + std::streamoff(fRecordSize));
   if (fFileBuf.sgetc() == decltype(fFileBuf)::traits_type::eof())
      return false;
   fRecordSize = EvalRecordSize();
   if (fRecordSize == 0u)
      throw std::runtime_error("invalid record at position " + std::to_string(fCurrentRecord));
   return true;
}

unsigned int TRecordReader::EvalRecordSize()
{
   // TODO also check checksum
   fFileBuf.pubseekpos(fCurrentRecord);
   std::array<unsigned int, 3> recordSizes;
   for (auto i = 0u; i < 3; ++i)
      fFileBuf.sgetn(reinterpret_cast<char *>(&recordSizes[i]), 4);

   if (recordSizes[2] == recordSizes[0] || recordSizes[2] == recordSizes[1])
      return recordSizes[2];
   else if (recordSizes[0] == recordSizes[1])
      return recordSizes[0];
   else
      return 0u;
}
