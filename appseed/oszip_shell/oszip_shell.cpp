// oszip_shell.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "oszip_shell.h"
#include <initguid.h>
#include "Oszip_shell_i.c"
#include "ContextMenuHandler.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// COszip_shellApp

BEGIN_MESSAGE_MAP(COszip_shellApp, CWinApp)
	//{{AFX_MSG_MAP(COszip_shellApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COszip_shellApp construction

COszip_shellApp::COszip_shellApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only COszip_shellApp object

COszip_shellApp theApp;

/////////////////////////////////////////////////////////////////////////////
// COszip_shellApp initialization

BOOL COszip_shellApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Register all OLE server (factories) as running.  This enables the
	//  OLE libraries to create objects from other applications.
	COleObjectFactory::RegisterAll();
	if (!InitATL())
		return FALSE;


	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// Special entry points required for inproc servers

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (SUCCEEDED(_Module.GetClassObject(rclsid, riid, ppv)))
		return S_OK;


	return AfxDllGetClassObject(rclsid, riid, ppv);
}

STDAPI DllCanUnloadNow(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return (AfxDllCanUnloadNow()==S_OK && _Module.GetLockCount()==0) ? S_OK : S_FALSE;

	return AfxDllCanUnloadNow();
}

// by exporting DllRegisterServer, you can use regsvr.exe
STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	COleObjectFactory::UpdateRegistryAll();
	return _Module.RegisterServer(TRUE);

	return S_OK;
}

	
CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_ContextMenuHandler, CContextMenuHandler)
END_OBJECT_MAP()

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return SELFREG_E_CLASS;
	_Module.UnregisterServer(TRUE); //TRUE indicates that typelib is unreg'd
	return S_OK;
}

int COszip_shellApp::ExitInstance()
{
	_Module.Term();

	return CWinApp::ExitInstance();

}

BOOL COszip_shellApp::InitATL()
{
	_Module.Init(ObjectMap, AfxGetInstanceHandle());
	return TRUE;

}
