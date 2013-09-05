#pragma once


namespace http
{


   class CLASS_DECL_ca2 file :
      virtual public ::file::file
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


      inline file & operator << (::primitive::memory_file & memfile)
      {

         write(memfile.get_data(), (::primitive::memory_size) memfile.get_length());

         return *this;

      }


      file & operator << (::file::file & file);


      inline file & operator << (::file::filesp & filesp) { return operator << ((::file::file &) *filesp.m_p); }


      inline void to_string(string & str)
      {

         read(str.GetBufferSetLength((int32_t)get_length()), (int32_t)(get_length()));

         str.ReleaseBuffer();

      }


   };

} // namespace http
