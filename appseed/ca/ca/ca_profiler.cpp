#include "framework.h"


namespace ca
{


   namespace profiler
   {


#ifdef WINDOWS
      int64_t g_iFrequency = 0;
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


