// vmsse.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f vmsseps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "vmsse.h"
#include "VmsseApp.h"
#include "VmsseThread.h"

#include "..\vmsgui\VmsGuiDll.h"



#include "vmsse_i.c"
#include "AlbumSongList.h"

#include "rpcdce.h"
#include "AlbumSongFolder.h"
#include "AlbumSongView.h"

#include "DataCentral.h"
#include "AlbumSongs.h"

#include "vmsseDLL.h"


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_AlbumSongFolder, CAlbumSongFolder)
OBJECT_ENTRY(CLSID_AlbumSongView, CAlbumSongView)
END_OBJECT_MAP()

BEGIN_MESSAGE_MAP(CVmsseApp, CWinApp)
	//{{AFX_MSG_MAP(CVmsseApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CVmsseApp theApp;

CVmsseApp::CVmsseApp()
{
    m_pthread = NULL;
}

BOOL CVmsseApp::InitInstance()
{
    _Module.Init(ObjectMap, m_hInstance, &LIBID_VMSSELib);
    return CWinApp::InitInstance();
}

int CVmsseApp::ExitInstance()
{

	if(m_pthread != NULL)
	{
		m_pthread->PostThreadMessage(WM_QUIT, 0, 0);
	}
    _Module.Term();
    return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    return (AfxDllCanUnloadNow()==S_OK && _Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    ((CVmsseApp *) AfxGetApp())->StartMainThread();
    return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
    // registers object, typelib and all interfaces in typelib
    HRESULT hr;
    if(FAILED(hr = _Module.RegisterServer(TRUE)))
        return hr;

    int i;
    CString strParam;
    CString strCLSID;
    CString strBase;
    CString strSystemRoot;
    CString str;
    CRegKey regKey;

    {
        UUID uuid = CLSID_AlbumSongFolder;
        unsigned char * lpstr = NULL;
    
        UuidToString(&uuid, &lpstr);

        strParam = lpstr;
        strCLSID = strParam;
    

        RpcStringFree(&lpstr);

        
    
/*        str.Format(_T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Desktop\\NameSpace\\{%s}"), strParam);

    
        if( ERROR_SUCCESS != regKey.Open(
            HKEY_LOCAL_MACHINE,
            str))
        {
            VERIFY((regKey.Create(
                HKEY_LOCAL_MACHINE,
                str,
                REG_OPTION_NON_VOLATILE) == ERROR_SUCCESS));
        }

        regKey.SetValue(_T("Meus Karaokês"));

        regKey.Close();*/



        strBase.Format(_T("CLSID\\{%s}"), strParam);
        str.Format(_T("%s\\ShellFolder"), strBase);
        HKEY hKeyShellFolder = NULL;
	    DWORD dwDisposition = 0;
	    if (ERROR_SUCCESS != regKey.Open(HKEY_CLASSES_ROOT, str))
	    {
               VERIFY((regKey.Create(
                HKEY_CLASSES_ROOT,
                str,
                REG_OPTION_NON_VOLATILE) == ERROR_SUCCESS));
        }

		DWORD dwAttr = SFGAO_HASSUBFOLDER | SFGAO_FOLDER;
        if(::RegSetValueEx(
            regKey.m_hKey,
            _T("Attributes"),
            0, REG_BINARY, 
        	(LPBYTE)&dwAttr, sizeof(dwAttr)) == ERROR_SUCCESS)
		{
			hr = S_OK;
		}
		else
		{
			hr = E_UNEXPECTED;
		}
        regKey.Close();
	}
/*        str.Format(_T("%s"), strBase);

        if( ERROR_SUCCESS != regKey.Open(
            HKEY_CLASSES_ROOT,
            str))
        {
            VERIFY((regKey.Create(
                HKEY_CLASSES_ROOT,
                str,
                REG_OPTION_NON_VOLATILE) == ERROR_SUCCESS));
        }

        str.Format("%s", _T("Meus Karaokês"));

        regKey.SetValue(str);
        regKey.Close();*/
 



  /*      str.Format(_T("%s\\DefaultIcon"), strBase);
        if( ERROR_SUCCESS != regKey.Open(
            HKEY_CLASSES_ROOT,
            str))
        {
            VERIFY((regKey.Create(
                HKEY_CLASSES_ROOT,
                str,
                REG_OPTION_NON_VOLATILE) == ERROR_SUCCESS));
        }

        TCHAR lpszModuleFilePath[MAX_PATH + 1];
	    GetModuleFileName(NULL, lpszModuleFilePath, MAX_PATH + 1);
	    
        TCHAR lpszModuleFolder[MAX_PATH + 1];
	    LPTSTR lpszModuleFileName;
	    GetFullPathName(lpszModuleFilePath, MAX_PATH + 1, lpszModuleFolder, &lpszModuleFileName);
	    
        CString strModuleFolder(lpszModuleFolder, lpszModuleFileName - lpszModuleFolder);
    #define IDR_XFPLAYER_INDEX 2
        str.Format("%svms.exe,%d", strModuleFolder, IDR_XFPLAYER_INDEX);
        //str.Format("%svms.exe,%d", strModuleFolder, 3);
        regKey.SetValue(str);
        regKey.Close();*/

/*        str.Format(_T("SOFTWARE\\Microsoft\\WindowsNT\\CurrentVersion\\ShellExtensions\\Approved\\{%s}"), strCLSID);
        if( ERROR_SUCCESS != regKey.Open(
            HKEY_LOCAL_MACHINE,
            str))
        {
            VERIFY((regKey.Create(
                HKEY_LOCAL_MACHINE,
                str,
                REG_OPTION_NON_VOLATILE) == ERROR_SUCCESS));
        }

        str.Format("Meus Karaokês", strSystemRoot);
        regKey.SetValue(str);
        regKey.Close();*/

        //HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Shell Extensions\Approved

/*        str.Format(_T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions\\Approved"));
        if( ERROR_SUCCESS != regKey.Open(
            HKEY_LOCAL_MACHINE,
            str))
        {
            VERIFY((regKey.Create(
                HKEY_LOCAL_MACHINE,
                str,
                REG_OPTION_NON_VOLATILE) == ERROR_SUCCESS));
        }

        str.Format("Meus Karaokês", strSystemRoot);
        regKey.SetValue(str, strCLSID);
        regKey.Close();
    }*/

//    UUID uuid = CLSID_AlbumSongFolder;
  //  unsigned char * lpstr = NULL;
//
  //  UuidToString(&uuid, &lpstr);

    //strParam = lpstr;
    //strCLSID = strParam;


    //RpcStringFree(&lpstr);

//    CString strBase;
    //strBase.Format(_T("CLSID\\{%s}"), strParam);
/*    str.Format(_T("%s\\Shell\\Open\\Command"), strBase);


    if( ERROR_SUCCESS != regKey.Open(
        HKEY_CLASSES_ROOT,
        str))
    {
        VERIFY((regKey.Create(
            HKEY_CLASSES_ROOT,
            str,
            REG_OPTION_NON_VOLATILE) == ERROR_SUCCESS));
    }

    str.Format("%s\\explorer.exe /root,::{%s}", strSystemRoot, strCLSID);

    regKey.SetValue(str);
    regKey.Close();*/

    /*str.Format(_T("%s\\Shell\\Explore\\Command"), strBase);
    if( ERROR_SUCCESS != regKey.Open(
        HKEY_CLASSES_ROOT,
        str))
    {
        VERIFY((regKey.Create(
            HKEY_CLASSES_ROOT,
            str,
            REG_OPTION_NON_VOLATILE) == ERROR_SUCCESS));
    }

    str.Format("%s\\explorer.exe /e,/root,::{%s}", strSystemRoot, strCLSID);
    regKey.SetValue(str);
    regKey.Close();*/

    return hr;
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
    return _Module.UnregisterServer(TRUE);
}




BOOL CVmsseApp::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWinApp::PreTranslateMessage(pMsg);
}


bool CVmsseApp::StartMainThread()
{
    if(m_pthread == NULL)
    {
        m_pthread = (CVmsseThread *) AfxBeginThread(RUNTIME_CLASS(CVmsseThread));
    }
	if(m_pthread == NULL)
		return false;
	else
		return true;

}

bool CVmsseApp::MessageWindowListener(
		UINT message,
		WPARAM wparam, 
		LPARAM lparam)
{
	return false;
}

void CVmsseApp::OnPointerClear(CVmsseThread *pthread)
{
	if(pthread == m_pthread)
	{
		m_pthread = NULL;
	}

}
