// This is ca2 API library.
// 
// 
//
// 
// 
// 
// 
// 

#include "StdAfx.h"
#include <stdarg.h>

#ifdef _DEBUG   // entire file



/////////////////////////////////////////////////////////////////////////////
// Helper routines that can be called from debugger

void Afxdump(const ::radix::object* pOb)
{
   afxdump << pOb;
}

/////////////////////////////////////////////////////////////////////////////
// Diagnostic Trace

void AFX_CDECL AfxTrace(const char * lpszFormat, ...)
{
   va_list args;
   va_start(args, lpszFormat);

   int nBuf;
   char szBuffer[512];

   nBuf = _vstprintf_s(szBuffer, _countof(szBuffer), lpszFormat, args); 

   // was there an error? was the expanded string too long?
   ASSERT(nBuf >= 0);

   afxdump << szBuffer;

   va_end(args);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
