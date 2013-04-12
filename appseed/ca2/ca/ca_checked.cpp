#include "framework.h"


namespace ca
{


#ifdef WINDOWS


   CLASS_DECL_ca2 int32_t get_errno()
   {
      int32_t nErrNo;
      C_RUNTIME_ERROR_CHECK(::_get_errno(&nErrNo));
      return nErrNo;
   }

   CLASS_DECL_ca2 void set_errno(int32_t _Value)
   {
      C_RUNTIME_ERROR_CHECK(::_set_errno(_Value));
   }


#else


   CLASS_DECL_ca2 int32_t get_errno()
   {
      return errno;
   }

   CLASS_DECL_ca2 void set_errno(int32_t _Value)
   {
      errno = _Value;
   }


#endif


} // namespace ca




