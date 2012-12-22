#pragma once


namespace gen
{


   namespace hex
   {


      CLASS_DECL_ca int64_t         to_int64(const char * lpcsz);
      CLASS_DECL_ca unsigned int    to_uint(const string & str);

      CLASS_DECL_ca int64_t         from_char(const char * pszUtf8Char);
      CLASS_DECL_ca string          from(void * p, primitive::memory_size s);


   } // namespace hex


} // namespace gen



