#include "framework.h"


namespace ca
{


   namespace profiler
   {


#ifdef WINDOWS
      __int64 g_iFrequency = 0;
#endif


      void initialize()
      {


#ifdef WINDOWS
         if(!QueryPerformanceFrequency((LARGE_INTEGER *) &g_iFrequency))
         {
            g_iFrequency = 0;
         }
#endif


      }


   } // namespace profiler


} // namespace gen


