#pragma once

class CLASS_DECL_ca Ex17MemoryFile : public MemoryFile
{
public:
   Ex17MemoryFile(bergedge_application * papp)
      : MemoryFile(papp)
   {
   }
   inline Ex17MemoryFile & operator << (LPCTSTR lpcsz)
   {
      write(lpcsz, strlen(lpcsz));
      return *this;
   }
   inline Ex17MemoryFile & operator << (const string & str)
   {
      write((LPCTSTR) str, str.get_length());
      return *this;
   }
   inline Ex17MemoryFile & operator << (MemoryFile & memfile)
   {
      write(memfile.GetAllocation(), memfile.get_length());
      return *this;
   }
   inline Ex17MemoryFile & operator << (gen::filesp & file)
   {
      int32_t nRead;
      char buf[1024];
      while(nRead = spfile->read(buf, sizeof(buf)))
      {
         write(buf, sizeof(buf));
      }
      return *this;
   }
};
