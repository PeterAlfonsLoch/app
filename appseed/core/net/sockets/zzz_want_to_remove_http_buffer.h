#pragma once

/*
namespace file
{


   class CLASS_DECL_ca2 http_buffer :
      virtual public ::file::buffer
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


      inline file & operator << (::file::memory_buffer & memfile)
      {

         write(memfile.get_data(), (::primitive::memory_size) memfile.get_length());

         return *this;

      }


      file & operator << (::file::binary_buffer & file);


      inline file & operator << (::file::binary_buffer_sp & binary_buffer_sp) { return operator << ((::file::binary_buffer &) *binary_buffer_sp.m_p); }


      inline void to_string(string & str)
      {

         read(str.GetBufferSetLength((int32_t)get_length()), (int32_t)(get_length()));

         str.ReleaseBuffer();

      }


   };

} // namespace http
*/