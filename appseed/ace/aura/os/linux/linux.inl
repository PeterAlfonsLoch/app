#pragma once


//inline DWORD get_tick_count()
//{
//
//   return (get_nanos() / (1000 * 1000)) % 0xffffffffu;
//
//}



inline uint64_t get_nanos()
{

   struct timespec ts;

   if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0)
   {
      //error
      return 0;
   }

   return ts.tv_sec * 1000 * 1000 * 1000 + ts.tv_nsec;

}



