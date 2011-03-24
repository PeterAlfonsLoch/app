#pragma once

// circles, chain, daisies, sunflowers
// you need to profile the top start for bergedge
// from profiler in beggining bottom for veriwellfair

namespace ca
{
   namespace profiler
   {
      extern CLASS_DECL_ca __int64 g_iFrequency;

      void initialize();

      __forceinline __int64 micros()
      {
         __int64 iCount;
         if(g_iFrequency
         && QueryPerformanceCounter((LARGE_INTEGER *) &iCount))
         {
            return iCount * 1000 * 1000 / g_iFrequency;
         }
         else
         {
            return ::GetTickCount() * 1000;
         }
      }

      __forceinline float millis()
      {
         return micros() / 1000.0f;
      }
   }
} // namespace gen