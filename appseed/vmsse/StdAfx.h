// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__5403BFC3_BD61_4B63_A8EA_D332790DE8F5__INCLUDED_)
#define AFX_STDAFX_H__5403BFC3_BD61_4B63_A8EA_D332790DE8F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#define _ATL_APARTMENT_THREADED

#include <afxwin.h>
#include <afxdisp.h>

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

#include <atldbcli.h>

#include <afxmt.h>
#include <afxole.h>
#include <afxext.h>
#include <afxcmn.h>
#include <afxtempl.h>

#include <comdef.h>
#include <oledberr.h>

#include <mmsystem.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__5403BFC3_BD61_4B63_A8EA_D332790DE8F5__INCLUDED)
