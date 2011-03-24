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

#ifdef _MBCS    // entire file is only for DBCS enabling



AFX_STATIC BOOL PASCAL _AfxInitDBCS()
{
   CPINFO info;
   GetCPInfo(GetOEMCP(), &info);
   return info.MaxCharSize > 1;
}

const AFX_DATADEF BOOL _afxDBCS = _AfxInitDBCS();

#endif //_MBCS

/////////////////////////////////////////////////////////////////////////////
