#include "framework.h"



int32_t ___()
{

   MessageBox(NULL, "___ library of ca", "___ library of ca", MB_ICONINFORMATION | MB_OK);

   return 0;

}


DWORD GetTickCount()
{
   timeval ts;
   gettimeofday(&ts,0);
   return (ts.tv_sec * 1000 + (ts.tv_usec / 1000)) % 0xffffffffu;

}



dword get_tick_count()
{

#ifdef METROWIN

   return (dword) (GetTickCount64() % 0x100000000ULL);

#else

   return (dword) GetTickCount();

#endif

}







