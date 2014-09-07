#include "framework.h"
#include <sys/time.h>


namespace core
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


      CLASS_DECL_CORE int64_t micros()
      {
#ifdef WINDOWSEX
         int64_t iCount;
         if(g_iFrequency
         && QueryPerformanceCounter((LARGE_INTEGER *) &iCount))
         {
            return iCount * 1000 * 1000 / g_iFrequency;
         }
         else
         {
            return ::get_tick_count() * 1000;
         }
#elif defined(METROWIN)
         int64_t iCount;
         if(g_iFrequency
         && QueryPerformanceCounter((LARGE_INTEGER *) &iCount))
         {
            return iCount * 1000 * 1000 / g_iFrequency;
         }
         else
         {
            return ::GetTickCount64() * 1000;
         }
#else
         timeval t;
         gettimeofday(&t, NULL);
         return t.tv_sec * 1000 * 1000 + t.tv_usec;
#endif


      }


   } // namespace profiler


} // namespace core




