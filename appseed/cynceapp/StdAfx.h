// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__32BEB260_E7BC_45BC_AC10_0088BED6D799__INCLUDED_)
#define AFX_STDAFX_H__32BEB260_E7BC_45BC_AC10_0088BED6D799__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WINVER 0x0501

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxole.h>         // MFC OLE classes
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxsock.h>		// MFC socket extensions
#include <afxtempl.h>	// MFC templates
#include <afxmt.h>   // MFC templates

#include <comdef.h>

#include <afxpriv.h>
#include <afximpl.h>

#include <afxinet.h>

#include <oleimpl2.h> 




//#include <gl\gl.h>			// Header File For The OpenGL32 Library
//#include <gl\glu.h>			// Header File For The GLu32 Library
//#include <gl\glaux.h>		// Header File For The Glaux Library

#include "idb/idb.h"
#include "filemanager/filemanager.h"
#include "gcom/gcom.h"
#include "gdi/gdi.h"
#include "guibase/guibase.h"
#include "igui/igui.h"
#include "img/img.h"
#include "kar/kar.h"
#include "ikar/ikar.h"
#include "mediamanager/mediamanager.h"
#include "imediamanager/imediamanager.h"
#include "mediaplay/mediaplay.h"
#include "msole/msole.h"
#include "mix/mix.h"
#include "mixguibase/mixguibase.h"
#include "mus/mus.h"
#include "musctrl/musctrl.h"
#include "mediapl/mediapl.h"
#include "simpledb/simpledb.h"
#include "vmssqlite/_vmssqlite.h"
#include "win/win.h"
#include "xml/xml.h"

#include "gen/DDX.h"
#include "gen/Sort.h"

#include "win/WindowsShell.h"

#include "VmpLight.h"
#include "_vmplightConfiguration.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__32BEB260_E7BC_45BC_AC10_0088BED6D799__INCLUDED_)
