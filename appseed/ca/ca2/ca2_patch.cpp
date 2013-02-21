#include "framework.h"


namespace ca4
{
   int32_t patch::bsdiff(const char * old, const char * newfile, const char * patch)
   {
      try
      {
         return ::bsdiff(old, newfile, patch);
      }
      catch(...)
      {
         return -1;
      }
   }

   int32_t patch::bspatch(const char * old, const char * newfile, const char * patch)
   {
      try
      {
         return ::bspatch(old, newfile, patch);
      }
      catch(...)
      {
         return -1;
      }
   }
} // namespace ca4