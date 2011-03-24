// OSZipShell.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "OSZipShell.h"
#include "shlwapi.h"

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
// COSZipShellApp

BEGIN_MESSAGE_MAP(COSZipShellApp, CWinApp)
	//{{AFX_MSG_MAP(COSZipShellApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COSZipShellApp construction

COSZipShellApp::COSZipShellApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only COSZipShellApp object

COSZipShellApp theApp;

/////////////////////////////////////////////////////////////////////////////
// COSZipShellApp initialization

BOOL COSZipShellApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Register all OLE server (factories) as running.  This enables the
	//  OLE libraries to create objects from other applications.
	COleObjectFactory::RegisterAll();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// Special entry points required for inproc servers

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return AfxDllGetClassObject(rclsid, riid, ppv);
}

STDAPI DllCanUnloadNow(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return AfxDllCanUnloadNow();
}

// by exporting DllRegisterServer, you can use regsvr.exe
STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	COleObjectFactory::UpdateRegistryAll();

   CString strName;
   strName = "Apartment";
   ::SHSetValue(HKEY_CLASSES_ROOT, "CLSID\\{D8A11407-DA73-47B3-B09D-60A99D688BC4}\\InProcServer32",
      "ThreadingModel", REG_SZ, strName, strName.GetLength());


   strName = "fontopus veriwell OSZipShell";
   ::SHSetValue(HKEY_CLASSES_ROOT, "Folder\\shellex\\ContextMenuHandlers\\{D8A11407-DA73-47B3-B09D-60A99D688BC4}",
      "", REG_SZ, strName, strName.GetLength());
   ::SHSetValue(HKEY_CLASSES_ROOT, "*\\shellex\\ContextMenuHandlers\\{D8A11407-DA73-47B3-B09D-60A99D688BC4}",
      "", REG_SZ, strName, strName.GetLength());
   //   strName = "fontopus veriwell OSZipShell";
//      ::SHSetValue(HKEY_CLASSES_ROOT, "*\\shellex\\ContextMenuHandlers\\{D8A11407-DA73-47B3-B09D-60A99D688BC4}",
  //    "Server Name", REG_SZ, strName, strName.GetLength());


   //strName = "";

   //::SHSetValue(HKEY_CLASSES_ROOT, "CLSID\\{D8A11407-DA73-47B3-B09D-60A99D688BC4}\\shellex\\MayChangeDefaultMenu",
     // "", REG_SZ, strName, strName.GetLength());

   ::SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST , 0, 0);

   /*HKEY hkey;
   ::RegCreateKeyEx(HKEY_CLASSES_ROOT, "*\\shellex\\ContextMenuHandlers\\{D8A11407-DA73-47B3-B09D-60A99D688BC4}", 
      0, NULL, 0, KEY_CREATE_SUB_KEY | KEY_SET_VALUE, NULL, &hkey, NULL);

   CString strName;
   strName = "fontopus veriwell OSZipShell";

   ::RegSetValueEx(hkey, "", 0, REG_SZ, (const BYTE *) (LPCTSTR) strName, strName.GetLength() + 1);

   ::RegCloseKey(hkey);
     //WriteRegStr HKEY_CLASSES_ROOT  "" "OSZipShell"*/

	return S_OK;
}

// by exporting DllRegisterServer, you can use regsvr.exe
STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	COleObjectFactory::UpdateRegistryAll(FALSE);

   ::RegDeleteKey(HKEY_CLASSES_ROOT, "*\\shellex\\ContextMenuHandlers\\{D8A11407-DA73-47B3-B09D-60A99D688BC4}");
   ::RegDeleteKey(HKEY_CLASSES_ROOT, "Folder\\shellex\\ContextMenuHandlers\\{D8A11407-DA73-47B3-B09D-60A99D688BC4}");
   ::SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST , 0, 0);
   
	return S_OK;
}
