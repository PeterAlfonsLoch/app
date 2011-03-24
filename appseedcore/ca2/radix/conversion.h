// This is ca2 API library.
// 
// 
//
// 
// 
// 
// 
// 

#ifndef __AFXCONV_H__
#define __AFXCONV_H__

#ifndef _OBJBASE_H_
#include <objbase.h>
#endif

#pragma once

/////////////////////////////////////////////////////////////////////////////
// Global UNICODE<>ANSI translation helpers

#ifdef _WINGDI_
LPDEVMODEW AfxDevModeA2W(LPDEVMODEW lpDevModeW, LPDEVMODEA lpDevModeA);
LPDEVMODEA AfxDevModeW2A(LPDEVMODEA lpDevModeA, LPDEVMODEW lpDevModeW);
LPTEXTMETRICW AfxTextMetricA2W(LPTEXTMETRICW lptmW, LPTEXTMETRICA lptmA);
LPTEXTMETRICA AfxTextMetricW2A(LPTEXTMETRICA lptmA, LPTEXTMETRICW lptmW);

#ifndef ATLDEVMODEA2W
#define ATLDEVMODEA2W AfxDevModeA2W
#define ATLDEVMODEW2A AfxDevModeW2A
#define ATLTEXTMETRICA2W AfxTextMetricA2W
#define ATLTEXTMETRICW2A AfxTextMetricW2A
#endif

#endif //_WINGDI

wchar_t * AfxA2WHelper(wchar_t * lpw, const char * lpa, int nChars);
char * AfxW2AHelper(char * lpa, const wchar_t * lpw, int nChars);

#ifndef ATLA2WHELPER
#define ATLA2WHELPER AfxA2WHelper
#define ATLW2AHELPER AfxW2AHelper
#endif

#define OLESTDDELIMOLE OLESTR("\\")

#if defined(_UNICODE)
// in these cases the default (char) is the same as OLECHAR
   inline LPOLESTR TASKSTRINGT2OLE(LPOLESTR lp) { return lp; }
   inline LPTSTR TASKSTRINGOLE2T(LPOLESTR lp) { return lp; }
   inline BSTR BSTR2TBSTR(BSTR bstr) { return bstr;}
#else
   #define TASKSTRINGT2OLE(lpa)    AfxTaskStringA2W(lpa)
   #define TASKSTRINGOLE2T(lpo) AfxTaskStringW2A(lpo)
   #define BSTR2TBSTR(bstr) AfxBSTR2ABSTR(bstr)
#endif


#endif //__AFXCONV_H__
