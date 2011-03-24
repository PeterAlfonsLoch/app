// OSZipContextMenuHandler.cpp : implementation file
//

#include "stdafx.h"
#include "OSZipContextMenuHandler.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// OSZipContextMenuHandler


IMPLEMENT_DYNCREATE(OSZipContextMenuHandler, CWnd)

OSZipContextMenuHandler::OSZipContextMenuHandler()
{
	EnableAutomation();
   AfxOleLockApp();
}

OSZipContextMenuHandler::~OSZipContextMenuHandler()
{
   AfxOleUnlockApp();
}

void OSZipContextMenuHandler::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CWnd::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(OSZipContextMenuHandler, CWnd)
	//{{AFX_MSG_MAP(OSZipContextMenuHandler)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(OSZipContextMenuHandler, CWnd)
	//{{AFX_DISPATCH_MAP(OSZipContextMenuHandler)
	DISP_FUNCTION(OSZipContextMenuHandler, "teste", teste, VT_I2, VTS_I2)
	DISP_FUNCTION(OSZipContextMenuHandler, "teste2", teste2, VT_ERROR, VTS_I4 VTS_I4)
	//}}AFX_DISPATCH_MAP
   DISP_FUNCTION(OSZipContextMenuHandler, "Initialize", Initialize, VT_ERROR, VTS_I4 VTS_I4 VTS_I4)
   DISP_FUNCTION(OSZipContextMenuHandler, "QueryContextMenu", QueryContextMenu, VT_ERROR, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4)
END_DISPATCH_MAP()

//   DISP_FUNCTION(OSZipContextMenuHandler, "QueryContextMenu", QueryContextMenu, VT_I4, VT_I4 VT_I4 VT_I4 VT_I4 VT_I4)

// Note: we add support for IID_IOSZipContextMenuHandler to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.


BEGIN_INTERFACE_MAP(OSZipContextMenuHandler, CWnd)
   INTERFACE_PART(OSZipContextMenuHandler, IID_IShellExtInit, Dispatch)
	INTERFACE_PART(OSZipContextMenuHandler, IID_IContextMenu, Dispatch)
END_INTERFACE_MAP()


// {EB903F95-E909-4BA6-86CF-9BDFE4F5F9D7}
IMPLEMENT_OLECREATE(OSZipContextMenuHandler, "fontopus.OSZip.ContextMenuHandler", 0xeb903f95, 0xe909, 0x4ba6, 0x86, 0xcf, 0x9b, 0xdf, 0xe4, 0xf5, 0xf9, 0xd7)

/////////////////////////////////////////////////////////////////////////////
// OSZipContextMenuHandler message handlers


SCODE OSZipContextMenuHandler::Initialize(
    LPCITEMIDLIST pidlFolder,
    LPDATAOBJECT lpdobj,
    HKEY hkeyProgID)
{
   return S_OK;
}

#define IDM_DISPLAY 0

SCODE OSZipContextMenuHandler::QueryContextMenu(HMENU hMenu,
                                               UINT indexMenu,
                                               UINT idCmdFirst,
                                               UINT idCmdLast,
                                               UINT uFlags)
{

    if(!(CMF_DEFAULTONLY & uFlags))
    {
        InsertMenu(hMenu, 
                    indexMenu, 
                    MF_STRING | MF_BYPOSITION, 
                    idCmdFirst +IDM_DISPLAY, 
                    "&Display File Name");

//        StrCpyA(m_pszVerb, "display"); 
  //      StrCpyW(m_pwszVerb, L"display"); 

        return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(IDM_DISPLAY + 1));
    }
    else if(!(CMF_NORMAL & uFlags))
    {
        InsertMenu(hMenu, 
                    indexMenu, 
                    MF_STRING | MF_BYPOSITION, 
                    idCmdFirst +IDM_DISPLAY, 
                    "&Display File Name");

//        StrCpyA(m_pszVerb, "display"); 
  //      StrCpyW(m_pwszVerb, L"display"); 

        return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(IDM_DISPLAY + 1));
    }

    return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(0));
}

short OSZipContextMenuHandler::teste(short xxx) 
{
	// TODO: Add your dispatch handler code here

	return 0;
}

SCODE OSZipContextMenuHandler::teste2(long l1, long l2) 
{
	// TODO: Add your dispatch handler code here

	return S_OK;
}
