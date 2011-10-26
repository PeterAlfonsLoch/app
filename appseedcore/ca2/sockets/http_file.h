#pragma once

namespace http
{

   class CLASS_DECL_ca file : 
      virtual public ::ex1::file
   {
   public:
      bool read_string(string & str);
      inline file & operator << (const char * lpcsz)
      {
         write(lpcsz, strlen(lpcsz));
         return *this;
      }
      inline file & operator << (const string & str)
      {
         write((const char *) str, str.get_length());
         return *this;
      }
      inline file & operator << (gen::memory_file & memfile)
      {
         write(memfile.get_data(), (::primitive::memory_size) memfile.get_length());
         return *this;
      }
      inline file & operator << (ex1::file & file);
      inline void to_string(string & str)
      {
         read(str.GetBufferSetLength((int)get_length()), (int)(get_length()));
         str.ReleaseBuffer();
      }
   };

} // namespace http