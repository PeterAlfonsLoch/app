#include "framework.h"


DWORD GetTickCount()
{
   timeval ts;
   gettimeofday(&ts,0);
   return (ts.tv_sec * 1000 + (ts.tv_usec / 1000)) % 0xffffffffu;

}

static DWORD g_dwLastError = 0;

CLASS_DECL_c DWORD GetLastError()
{

   return g_dwLastError;

}

CLASS_DECL_c DWORD SetLastError(DWORD dw)
{

   DWORD dwLastError = g_dwLastError;

   g_dwLastError = dw;

   return dwLastError;

}
