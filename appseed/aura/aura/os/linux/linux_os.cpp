#include "framework.h"




__thread DWORD g_dwLastError = 0;

CLASS_DECL_AXIS DWORD GetLastError()
{

   return g_dwLastError;

}

CLASS_DECL_AXIS DWORD SetLastError(DWORD dw)
{

   DWORD dwLastError = g_dwLastError;

   g_dwLastError = dw;

   return dwLastError;

}


CLASS_DECL_AXIS bool _istlead(int32_t ch)
{

   return false;

}


void Sleep(DWORD dwMillis)
{
   timespec t;
   t.tv_sec = dwMillis / 1000;
   t.tv_nsec = (dwMillis % 1000) * 1000 * 1000;
   nanosleep(&t, NULL);
}







void output_debug_string(const char * psz)
{

   OutputDebugString(psz);

}

