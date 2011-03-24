// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__57E4320D_B6B2_43B7_B9A1_3C5D85F76767__INCLUDED_)
#define AFX_STDAFX_H__57E4320D_B6B2_43B7_B9A1_3C5D85F76767__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WINVER 0x0501


#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#define _AFXDLL
#include "cafx/cafxwin.h"         // MFC core and standard components
#include "cafx/cafxext.h"         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include "cafx/cafxole.h"         // MFC OLE classes
#include "cafx/cafxodlgs.h"       // MFC OLE dialog classes
#include "cafx/cafxdisp.h"        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT


#include "cafx/cafxdtctl.h"		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include "cafx/cafxcmn.h"			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "caatl/atlbase.h"
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
#include "caatl/atlcom.h"


#include "cafx/cafxtempl.h"
#include "cafx/cafxctl.h"

#include <comdef.h>

#include "npapi.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__57E4320D_B6B2_43B7_B9A1_3C5D85F76767__INCLUDED_)
