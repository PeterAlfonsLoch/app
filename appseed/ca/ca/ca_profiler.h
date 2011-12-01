#pragma once

// circles, chain, daisies, sunflowers
// you need to profile the top start for bergedge
// from profiler in beggining bottom for veriwellfair

#ifdef LINUX
#include <sys/time.h>                // for gettimeofday()
#endif

namespace ca
{
   namespace profiler
   {

#ifdef WINDOWS

      extern CLASS_DECL_ca int64_t g_iFrequency;

#endif

      void initialize();

      inline int64_t micros()
      {
#ifdef WINDOWS
         int64_t iCount;
         if(g_iFrequency
         && QueryPerformanceCounter((LARGE_INTEGER *) &iCount))
         {
            return iCount * 1000 * 1000 / g_iFrequency;
         }
         else
         {
            return ::GetTickCount() * 1000;
         }
#else
         timeval t;
         gettimeofday(&t, NULL);
         return t.tv_sec * 1000 * 1000 + t.tv_usec;
#endif
      }

      inline float millis()
      {
         return micros() / 1000.0f;
      }
   }
} // namespace gen



