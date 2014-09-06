#include "framework.h"
#include <stdarg.h>

#ifdef DEBUG   // entire file



/////////////////////////////////////////////////////////////////////////////
// Helper routines that can be called from debugger

void __dump(const object* pOb)
{
   g_dumpcontext << pOb;
}

/////////////////////////////////////////////////////////////////////////////
// Diagnostic Trace

void c_cdecl __trace(const char * lpszFormat, ...)
{
   va_list args;
   va_start(args, lpszFormat);

   int32_t nBuf;
   char szBuffer[512];

#ifdef WINDOWSEX
   nBuf = _vstprintf_s(szBuffer, _countof(szBuffer), lpszFormat, args);
#else
   nBuf = vsprintf(szBuffer, lpszFormat, args);
#endif

   // was there an error? was the expanded string too long?
   ASSERT(nBuf >= 0);

   g_dumpcontext << szBuffer;

   va_end(args);
}
#endif //DEBUG

/////////////////////////////////////////////////////////////////////////////
