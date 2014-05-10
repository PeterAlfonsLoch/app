#pragma once


namespace core
{


   namespace strn
   {


      CLASS_DECL_CORE  bool           to(const char * psz, int32_t iLen, int32_t & i);
      CLASS_DECL_CORE  bool           to(const char * psz, int32_t iLen, int64_t & i);
      CLASS_DECL_CORE  bool           to(const char * psz, int32_t iLen, int32_t & i, int32_t iBase);
      CLASS_DECL_CORE  bool           to(const char * psz, int32_t iLen, int64_t & i, int32_t iBase);


   } // namespace strn


} // namespace core




