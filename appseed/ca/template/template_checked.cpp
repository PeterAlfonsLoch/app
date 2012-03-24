#include "StdAfx.h"

#ifdef LINUX
#include <errno.h>
#endif

namespace _template
{

#ifdef _WINDOWS

   CLASS_DECL_ca int get_errno()
   {
      int nErrNo;
      C_RUNTIME_ERROR_CHECK(::_get_errno(&nErrNo));
      return nErrNo;
   }

   CLASS_DECL_ca void set_errno(int _Value)
   {
      C_RUNTIME_ERROR_CHECK(::_set_errno(_Value));
   }

#else

   CLASS_DECL_ca int get_errno()
   {
      return errno;
   }

   CLASS_DECL_ca void set_errno(int _Value)
   {
      errno = _Value;
   }

#endif

} // namespace _template

