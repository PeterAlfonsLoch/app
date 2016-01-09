#include "framework.h"
#include <sys/time.h>



inline DWORD GetTickCount()
{
   timeval ts;
   gettimeofday(&ts,0);
   return (ts.tv_sec * 1000 + (ts.tv_usec / 1000)) % 0xffffffffu;

}



DWORD get_tick_count()
{

   return (DWORD) GetTickCount();

}







