#pragma once


inline dword get_tick_count()
{

   struct timespec ts;

   if(clock_gettime(CLOCK_MONOTONIC,&ts) != 0)
   {
      //error
      return 0;
   }

   return (ts.tv_sec * 1000 + (ts.tv_nsec / (1000 * 1000))) % 0xffffffffu;

}





