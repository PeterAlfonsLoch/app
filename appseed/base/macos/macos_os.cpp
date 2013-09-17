//
//  macos_os.cpp
//  base
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//
#include "framework.h"


__thread DWORD g_dwLastError = 0;


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


CLASS_DECL_c bool _istlead(int32_t ch)
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
