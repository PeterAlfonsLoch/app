#pragma once


namespace ca2
{


   namespace hex
   {


      CLASS_DECL_ca2 int64_t         to_int64(const char * lpcsz);
      CLASS_DECL_ca2 uint32_t    to_uint(const string & str);

      CLASS_DECL_ca2 int64_t         from_char(const char * pszUtf8Char);

      CLASS_DECL_ca2 string          hi_from(void * p, primitive::memory_size s);
      CLASS_DECL_ca2 string          lo_from(void * p, primitive::memory_size s);


   } // namespace hex


} // namespace ca2



