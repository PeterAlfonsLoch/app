#include "framework.h"


BEGIN_EXTERN_C


CLASS_DECL_BASE int32_t mkint32(uint32_t ui)
{
   if (ui >= 0x7fffffff)
      throw_cast_overflow();
   return (int32_t)ui;
}

CLASS_DECL_BASE  int64_t mkint64(uint64_t ull)
{
   if (ull >= 0x7fffffffffffffffull)
      throw_cast_overflow();
   return (int64_t)ull;
}


CLASS_DECL_BASE uint32_t natural32(int32_t i)
{
   if (i < 0)
      return 0;
   return (uint32_t)i;
}

CLASS_DECL_BASE  uint64_t natural64(int64_t ll)
{
   if (ll < 0)
      return 0;
   return (uint64_t)ll;
}


END_EXTERN_C


