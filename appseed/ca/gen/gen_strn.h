#pragma once


namespace gen
{


   namespace strn
   {


      CLASS_DECL_ca  bool           to_int(const char * psz, int iLen, int & i);
      CLASS_DECL_ca  bool           to_int(const char * psz, int iLen, int64_t & i);
      CLASS_DECL_ca  bool           to_int(const char * psz, int iLen, int & i, int iBase);
      CLASS_DECL_ca  bool           to_int(const char * psz, int iLen, int64_t & i, int iBase);


   } // namespace strn


} // namespace gen




