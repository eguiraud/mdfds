#include "TRecordReader.hxx"
#include <array>
#include <iostream>

RecordReader::RecordReader(const std::string &fname)
{
   fFileBuf.open(fname, std::ios_base::in); // TODO check file was opened correctly
   fRecordSize = GetRecordSize();
}

bool RecordReader::NextRecord()
{
   fCurrentRecord = fFileBuf.pubseekpos(fCurrentRecord + std::streamoff(fRecordSize));
   if (fFileBuf.sgetc() == decltype(fFileBuf)::traits_type::eof())
      return false;
   return true;
}

unsigned int RecordReader::GetRecordSize()
{
   // TODO also check checksum
   fFileBuf.pubseekpos(fCurrentRecord);
   std::array<unsigned int, 3> recordSizes;
   for (auto i = 0u; i < 3; ++i) {
      fFileBuf.sgetn(reinterpret_cast<char *>(&recordSizes[i]), 32);
      std::cerr << "record size: " << recordSizes[i] << "\n"; // TODO make this a debug print
   }
   if (recordSizes[2] == recordSizes[0] || recordSizes[2] == recordSizes[1])
      return recordSizes[2];
   else if (recordSizes[0] == recordSizes[1])
      return recordSizes[0];
   else
      return 0u;
}

RecordReader::pos_type RecordReader::GetRecordPosition()
{
   return fCurrentRecord;
}
