#include "StdAfx.h"

namespace ca
{
   namespace profiler
   {
      __int64 g_iFrequency = 0;

      void initialize()
      {
         if(!QueryPerformanceFrequency((LARGE_INTEGER *) &g_iFrequency))
         {
            g_iFrequency = 0;
         }
      }
   } // namespace profiler
} // namespace gen