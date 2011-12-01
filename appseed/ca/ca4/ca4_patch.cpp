#include "StdAfx.h"


namespace ca4
{
   int patch::bsdiff(const char * old, const char * newfile, const char * patch)
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

   int patch::bspatch(const char * old, const char * newfile, const char * patch)
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