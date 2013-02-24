#pragma once


namespace ca
{


   namespace hex
   {


      CLASS_DECL_ca int64_t         to_int64(const char * lpcsz);
      CLASS_DECL_ca uint32_t    to_uint(const string & str);

      CLASS_DECL_ca int64_t         from_char(const char * pszUtf8Char);

      CLASS_DECL_ca string          hi_from(void * p, primitive::memory_size s);
      CLASS_DECL_ca string          lo_from(void * p, primitive::memory_size s);


   } // namespace hex


} // namespace ca



