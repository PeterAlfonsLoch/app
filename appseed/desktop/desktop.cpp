// vmpLight.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"

#include "gen/MessageFilterMainHook.h"

#include "MainFrm.h"
#include "IpFrame.h"
#include "vmpLightDoc.h"
#include "vmpLightViewUpdateHint.h"
#include "DesktopView.h"
#include "XfplayerOpenFileDialog.h"

#include "mixguibase/MixerVisualCentral.h"

#include "VmpHighThread.h"

#include "OptionsDialog.h"

#include "guibase/UserInterfaceImageManager.h"




#include "RecentFileList.h"

// vmsgen
#include "gen/CommandLineInfo.h"

#include "VmpLightDB.h"


#include "resource.h"
#include "DocumentManager.h"

#include "guibase/BaseWndMenu.h"
#include "guibase/BaseWndMenuButton.h"
#include "guibase/BaseWndMenuItem.h"

#include "wndfrm/FrameSchema.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



BOOL CALLBACK searcher(HWND hWnd, LPARAM lParam)
{
    DWORD result;
    LRESULT ok = ::SendMessageTimeout(hWnd,
                                      VM_SIMPLE,
                                      123, 0, 
                                      SMTO_BLOCK |
                                      SMTO_ABORTIFHUNG,
                                      200,
                                      &result);
    if(ok == 0)
       return TRUE; // ignore this and continue
    if(result == VM_SIMPLE)
    { /* found it */
        HWND * target = (HWND *)lParam;
        *target = hWnd;
        return FALSE; // stop search
    } /* found it */
    return TRUE; // continue search
} // CMyApp::searcher

/*HDDEDATA CALLBACK MyDdeCallback(          UINT uType,
    UINT uFmt,
    HCONV hconv,
    HDDEDATA hsz1,
    HDDEDATA hsz2,
    HDDEDATA hdata,
    HDDEDATA dwData1,
    HDDEDATA dwData2
);*/

TCHAR szServer[100] = TEXT("Server");


// WM_HELPPROMPTADDR is used internally to get the address of
//  m_dwPromptContext from the associated frame window. This is used
//  during message boxes to setup for F1 help while that msg box is
//  displayed. lResult is the address of m_dwPromptContext.
#define WM_HELPPROMPTADDR   0x0376

#define HID_BASE_PROMPT     0x00030000UL        // IDP

void GetModuleShortFileName(HINSTANCE hModule, String &str)
{
    TCHAR lpFilename[MAX_PATH];
    GetModuleFileName(hModule, lpFilename, MAX_PATH);
    GetShortPathName(lpFilename, lpFilename, MAX_PATH);
    str = lpFilename;
}

AFX_STATIC_DATA const TCHAR _afxShellOpenFmt[] = _T("%s\\shell\\open\\%s");
AFX_STATIC_DATA const TCHAR _afxShellPrintFmt[] = _T("%s\\shell\\print\\%s");
AFX_STATIC_DATA const TCHAR _afxShellPrintToFmt[] = _T("%s\\shell\\printto\\%s");
AFX_STATIC_DATA const TCHAR _afxDefaultIconFmt[] = _T("%s\\DefaultIcon");
AFX_STATIC_DATA const TCHAR _afxShellNewFmt[] = _T("%s\\ShellNew");

AFX_STATIC_DATA const TCHAR _afxFileSection[] = _T("Recent File List");
AFX_STATIC_DATA const TCHAR _afxFileEntry[] = _T("File%d");

#define DEFAULT_ICON_INDEX 0

AFX_STATIC_DATA const TCHAR _afxIconIndexFmt[] = _T(",%d");
AFX_STATIC_DATA const TCHAR _afxCommand[] = _T("command");
AFX_STATIC_DATA const TCHAR _afxOpenArg[] = _T(" \"%1\"");
AFX_STATIC_DATA const TCHAR _afxPrintArg[] = _T(" /p \"%1\"");
AFX_STATIC_DATA const TCHAR _afxPrintToArg[] = _T(" /pt \"%1\" \"%2\" \"%3\" \"%4\"");
AFX_STATIC_DATA const TCHAR _afxDDEArg[] = _T(" /dde");

AFX_STATIC_DATA const TCHAR _afxDDEExec[] = _T("ddeexec");
AFX_STATIC_DATA const TCHAR _afxDDEOpen[] = _T("[open(\"%1\")]");
AFX_STATIC_DATA const TCHAR _afxDDEPrint[] = _T("[print(\"%1\")]");
AFX_STATIC_DATA const TCHAR _afxDDEPrintTo[] = _T("[printto(\"%1\",\"%2\",\"%3\",\"%4\")]");

AFX_STATIC_DATA const TCHAR _afxShellNewValueName[] = _T("NullFile");
AFX_STATIC_DATA const TCHAR _afxShellNewValue[] = _T("");

AFX_STATIC BOOL AFXAPI
_AfxSetRegKey(LPCTSTR lpszKey, LPCTSTR lpszValue, LPCTSTR lpszValueName = NULL)
{
	if (lpszValueName == NULL)
	{
		if (::RegSetValue(HKEY_CLASSES_ROOT, lpszKey, REG_SZ,
			  lpszValue, lstrlen(lpszValue) * sizeof(TCHAR)) != ERROR_SUCCESS)
		{
			TRACE1("Warning: registration database update failed for key '%s'.\n",
				lpszKey);
			return FALSE;
		}
		return TRUE;
	}
	else
	{
		HKEY hKey;

		if(::RegCreateKey(HKEY_CLASSES_ROOT, lpszKey, &hKey) == ERROR_SUCCESS)
		{
			LONG lResult = ::RegSetValueEx(hKey, lpszValueName, 0, REG_SZ,
				(CONST BYTE*)lpszValue, (lstrlen(lpszValue) + 1) * sizeof(TCHAR));

			if(::RegCloseKey(hKey) == ERROR_SUCCESS && lResult == ERROR_SUCCESS)
				return TRUE;
		}
		TRACE1("Warning: registration database update failed for key '%s'.\n", lpszKey);
		return FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////
// DesktopApp

BEGIN_MESSAGE_MAP(DesktopApp, gen::App)
	//{{AFX_MSG_MAP(DesktopApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_TOOLS_OPTIONS, OnToolsOptions)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_OPTIONS, OnUpdateToolsOptions)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_OPEN_EX, OnFileOpenEx)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_VIEW_ALBUM, OnViewAlbum)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ALBUM, OnUpdateViewAlbum)
	ON_COMMAND(ID_FILE_ADD, OnFileAdd)
	ON_COMMAND_RANGE(ID_LANGUAGE_CHANGE1, ID_LANGUAGE_CHANGE12,  OnLanguageChange)
	ON_UPDATE_COMMAND_UI_RANGE(ID_LANGUAGE_CHANGE, ID_LANGUAGE_CHANGE12, OnUpdateLanguageChange)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_ENCODING, ID_VIEW_ENCODING, OnUpdateViewEncoding)
	//}}AFX_MSG_MAP
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
	ON_UPDATE_COMMAND_UI(ID_FILE_MRU_FILE, OnUpdateRecentFileMenu)
	ON_COMMAND_EX_RANGE(ID_FILE_MRU_FILE1, ID_FILE_MRU_FILE16, OnOpenRecentFile)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DesktopApp construction

DesktopApp::DesktopApp()
{
   _setmbcp(CP_UTF8);

   DWORD dw = ::_getmbcp();

   m_lpoptionsdialog = NULL;
   m_plightdb = NULL;
   m_pfileassociation = NULL;

   m_precentfilelist = NULL;

   // DDE variables
   m_hszAppName = NULL;
   m_hszSystemTopic = NULL;


}

DesktopApp::~DesktopApp()
{
   //if (m_precentfilelist != NULL)
     // delete m_precentfilelist;
}



// This identifier was generated to be statistically unique for your app.
// You may change it if you prefer to choose a specific identifier.

// {67CAD50F-D5DD-4C7E-9943-2130B9444129}
static const CLSID clsid =
{ 0x67cad50f, 0xd5dd, 0x4c7e, { 0x99, 0x43, 0x21, 0x30, 0xb9, 0x44, 0x41, 0x29 } };

//CComModule _Module;

//BEGIN_OBJECT_MAP(ObjectMap)
//OBJECT_ENTRY(CLSID_VmpLight, CVmp)
//END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DesktopApp initialization

BOOL DesktopApp::InitInstance()
{
   HWND hwndDesktop = ::GetDesktopWindow();

   HWND hwndFirst = ::GetNextWindow(hwndDesktop, GW_CHILD);

   TCHAR szModule[2048];
   TCHAR szClassName[2048];
   HWND hwnd = hwndFirst;
   int i = 1;
   String strNumber;
   WNDCLASS wndclass;
   DWORD dwThreadId;
   DWORD dwProcessId;
   String strClassName;
   HINSTANCE hinstance;
   BOOL bGetClassInfo;
   HMODULE hmodule;
   String str;
   while(hwnd != NULL)
   {
      bGetClassInfo = false;
      hmodule = NULL;
      base_wnd * pwnd = base_wnd::FromHandle(hwnd);
      pwnd->GetWindowText(str);
      if(str.Find("veriwell Desktop") >= 0)
      {
         // Confirm if it is veriwell Desktop

         int iResult = pwnd->SendMessage(WM_APP, 0, 0);
         if(iResult != 240525)
            return FALSE;
         iResult = pwnd->SendMessage(WM_APP, 0, 1);
         if(iResult != 18374345)
            return FALSE;
         iResult = pwnd->SendMessage(WM_APP, 0, 2);
         if(iResult != 23416234)
            return FALSE;
         iResult = pwnd->SendMessage(WM_APP, 0, 3);
         if(iResult != 11455)
            return FALSE;
         iResult = pwnd->SendMessage(WM_APP, 0, 4);
         if(iResult != 452345)
            return FALSE;
         ProcessCommand(pwnd);
         PostQuitMessage(1);
         return TRUE;
      }
      hwnd = ::GetNextWindow(hwnd, GW_HWNDNEXT);
   }

   m_pdocmanager = new vmplite::DocumentManager();


   AfxGetModuleState()->m_bDLL = FALSE;

   InitializeResourceId();

   SetFileApisToANSI();
   VERIFY(!_setmbcp(CP_UTF8));

   Ex1AppInitialize();


   DWORD dw = ::_getmbcp();

//   AfxDebugBreak();

   // Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
   String strKey(_T("veriwell\\Musical Player\\"));
   strKey += GetVersion();
	SetRegistryKey(strKey);

   String strPath = GetProfileString("language", "resource path", "");
   VERIFY(SetLanguageResourcePath(strPath));


   //m_hmodulePtBr = ::LoadLibrary("vmplightresptbr.dll");
   //if(m_hmodulePtBr == NULL)
      //return FALSE;

   //HMODULE hmoduleOld = AfxGetResourceHandle();
   //AfxSetResourceHandle(m_hmodulePtBr);




   // The call fails with ERROR_ACCESS_DENIED if the Mutex was 
   // created in a different users session because of passing
   // NULL for the SECURITY_ATTRIBUTES on Mutex creation);

   /*if ( AlreadyRunning )
   { /* kill this */
      //HWND hOther = NULL;
      //EnumWindows(searcher, (LPARAM)&hOther);
      
      //if ( hOther != NULL )
      //{ /* pop up */
/*         ::SetForegroundWindow( hOther );
         
         if ( IsIconic( hOther ) )
         { /* restore */
  //          ::ShowWindow( hOther, SW_RESTORE );
//         } /* restore */

        // LPWSTR lpwstr = GetCommandLineW();
        // COPYDATASTRUCT cds;
        // cds.dwData = 123;
        // cds.cbData = (lstrlenW(lpwstr) + 1) * sizeof(lpwstr[0]);
        // cds.lpData = lpwstr;

       //  DWORD result;
       //LRESULT ok = ::SendMessageTimeout(hOther,
                             //            WM_COPYDATA,
                              //           NULL, (LPARAM) &cds, 
                              //           SMTO_BLOCK |
                              //           SMTO_ABORTIFHUNG,
                              //           200,
                              //           &result);
      //} /* pop up */
      
      //return FALSE; // terminates the creation
   //} /* kill this */


   m_pdocmanager->AddDocTemplate(new SingleDocTemplate(
      IDR_MAINFRAME,
      RUNTIME_CLASS(MusicalPlayerLightDoc),
      RUNTIME_CLASS(MainFrame),
      RUNTIME_CLASS(DesktopView)));
   m_uiaPopupMenu.Add(IDR_MAINFRAME);
   m_uiaMenuInline.Add(IDR_MAINFRAME_INLINE);


   // Register your unique class name that you wish to use
   WNDCLASS wndcls;

   memset(&wndcls, 0, sizeof(WNDCLASS));   // start with NULL
                                            // defaults

   wndcls.style = CS_GLOBALCLASS | CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;

   //you can specify your own window procedure
   wndcls.lpfnWndProc = ::DefWindowProc; 
   wndcls.hInstance = AfxGetInstanceHandle();
   wndcls.hIcon = NULL; // LoadIcon(IDR_MAINFRAME); // or load a different icon
   wndcls.hCursor = NULL; //LoadCursor( IDC_ARROW );
   wndcls.hbrBackground = NULL; // (HBRUSH) (COLOR_WINDOW + 1);
   wndcls.lpszMenuName = NULL;

   // Specify your own class name for using FindWindow later
   wndcls.lpszClassName = _T("vmsbasewnd");

//   AfxDebugBreak();

   // Register the new class and exit if it fails
   if(!AfxRegisterClass(&wndcls))
   {
      TRACE("Class Registration Failed\n");
      return FALSE;
   }


   WindowsShell::Initialize();

   CImaging::SetImaging(new CImaging());
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	if (!InitATL())
		return FALSE;


	AfxEnableControlContainer();


   CCommandLineInfo cmdInfo2;
   ParseCommandLine(cmdInfo2);

   // Parse command line for standard shell commands, DDE, file open
   gen::CommandLineInfo cmdInfo;
   Ex1::GetApp()->_001ParseCommandLine(cmdInfo);

   m_pimagemanager = new CUserInterfaceImageManager();


   MessageFilterHookManager * pmfmh;
   if(MessageFilterHookManager::AppGetMessageFilterHookManager(&pmfmh))
   {
      pmfmh->MessageFilterHook();
   }


   BaseMenuCentral::SetMenuCentral(new BaseMenuCentral());
   UINT uiaMenuMap [][2] =
   {
      {ID_LANGUAGE_CHANGE           , IDI_LANGUAGE_CHANGE},
      {ID_VIEW_FULLSCREEN           , IDI_VIEW_FULLSCREEN},
      {ID_FILE_OPEN_EX              , IDI_FILE_OPEN_EX},
      {ID_FILE_OPEN                 , IDI_FILE_OPEN_EX},
      {ID_FILE_ADD                  , IDI_FILE_ADD},
      {ID_EDIT_REMOVE               , IDI_EDIT_REMOVE},
      {ID_KARAOKE_GRADUAL_FILLING   , IDI_KARAOKE_GRADUAL_FILLING},
      {ID_KARAOKE_BOUNCING_BALL     , IDI_KARAOKE_BOUNCING_BALL},
      {ID_EXECUTE_PLAY              , IDI_EXECUTE_PLAY},
      {ID_EXECUTE_STOP              , IDI_EXECUTE_STOP},
      {ID_EXECUTE_PAUSE             , IDI_EXECUTE_PAUSE},
      {ID_EXECUTE_MINUS_ONE         , IDI_EXECUTE_MINUS_ONE},
      {ID_VIEW_KARAOKE              , IDI_VIEW_KARAOKE},
      {ID_VIEW_PLAYLIST             , IDI_VIEW_PLAYLIST},
      {ID_VIEW_ALBUM                , IDI_VIEW_ALBUM},
      {ID_APP_EXIT                  , IDI_APP_EXIT},
      {-1, -1}
   };

   GetImageManager().Initialize(uiaMenuMap);
   UINT ui1;
   GetImageManager().m_rel.Lookup(ID_FILE_OPEN_EX, ui1);
   BaseMenuCentral::GetMenuCentral()->MenuV033CreateImageMap(uiaMenuMap);


   FontCentral::AppGetFontCentral()->Initialize();
   FontCentral::AppGetFontCentral()->CreateLyricViewFonts();

/*   GetMusicalPlayerCentral().m_pruntimeclassDocument = RUNTIME_CLASS(MusicalPlayerLightDoc);
   GetMusicalPlayerCentral().m_pruntimeclassFrameWnd = RUNTIME_CLASS(CMainFrame);
   GetMusicalPlayerCentral().m_pruntimeclassView = RUNTIME_CLASS(CMPLightView);
   GetMusicalPlayerCentral().m_pruntimeclassIPFrame = RUNTIME_CLASS(CInPlaceFrame);
   GetMusicalPlayerCentral().m_uiResourceId = IDR_MAINFRAME;
   GetMusicalPlayerCentral().m_uiResourceIdEmbedding = IDR_SRVR_EMBEDDED;
   GetMusicalPlayerCentral().m_uiResourceIdInPlace = IDR_SRVR_INPLACE;
   GetMusicalPlayerCentral().CreateDocTemplate();

   AddDocTemplate(GetMusicalPlayerCentral().CreateDocTemplate());*/


   m_pdocmanager->CreateTemplates();
   m_pdocmanager->UpdateRegistry();



	LoadStdProfileSettings();  // Load standard INI file options (including MRU)



	// Connect the COleTemplateServer to the document template.
	//  The COleTemplateServer creates new documents on behalf
	//  of requesting OLE containers by using information
	//  specified in the document template.
	//m_server.ConnectTemplate(clsid, pDocTemplate, TRUE);
		// Note: SDI applications register server objects only if /Embedding
		//   or /Automation is present on the command line.

	// Enable DDE Execute open

   Ex1::GetApp()->_001EnableShellOpen();
	RegisterShellFileTypes(TRUE);

   m_dwDde = 0;
   if(!DdeInitializeW(&m_dwDde,         // receives instance identifier 
      (PFNCALLBACK) DdeCallback, // pointer to callback function 
      //CBF_FAIL_EXECUTES |        // filter XTYPE_EXECUTE 
      APPCMD_FILTERINITS, // filter notifications 
      0))
   {
      m_hszAppName = DdeCreateStringHandleW(m_dwDde, L"vmpLight", 0);
      m_hszSystemTopic = DdeCreateStringHandleW(m_dwDde, L"System", 0);
      DdeNameService(m_dwDde, m_hszAppName, 0, DNS_REGISTER);
   }
   

//   AfxDebugBreak();



//   _Module.UpdateRegistryFromResource(IDR_VMSPLAYER, TRUE);
//xxx	_Module.RegisterServer(TRUE);

	// When a server application is launched stand-alone, it is a good idea
	//  to update the system registry in case it has been damaged.
   //m_docmanager.UpdateRegistry();
//	m_server.UpdateRegistry(OAT_INPLACE_SERVER);
	COleObjectFactory::UpdateRegistryAll();

	// Dispatch commands specified on the command line
	if (!m_bInline && !_001ProcessShellCommand(cmdInfo))
		return FALSE;

   if(cmdInfo.m_nShellCommand == CCommandLineInfo::FileDDE)
   {
      //_001OpenDocumentFile(NULL);
   }

   // Threads initialized here to avoid DDE missreading

   /*VERIFY(GetAudioWaveCentral().Initialize());

   base_runtime_class * pruntimeclass = RUNTIME_CLASS(CVmpHighThread);
   if(!(m_phighthread = dynamic_cast<CVmpHighThread *>(AfxBeginThread(pruntimeclass))))
   {
      return FALSE;
   }*/

	// The one and only window has been initialized, so show and update it.
//	m_pMainWnd->ShowWindow(SW_SHOW);
//	m_pMainWnd->UpdateWindow();

   AddCodePage(
      1252, // Latin1
      ID_VIEW_ENCODING_1,
      IDS_VIEW_ENCODING_LATIN1);

   AddCodePage(
      950, // BIG 5
      ID_VIEW_ENCODING_1,
      IDS_VIEW_ENCODING_BIG5);

   AddCodePage(
      51932, // Japanese (EUCJP)
      ID_VIEW_ENCODING_1,
      IDS_VIEW_ENCODING_SHIFTEUCJP);

   AddCodePage(
      50220, // Japanese (IS02022JP)
      ID_VIEW_ENCODING_1,
      IDS_VIEW_ENCODING_ISO2022JP);

   AddCodePage(
      932, // Japanese (ShiftJIS)
      ID_VIEW_ENCODING_1,
      IDS_VIEW_ENCODING_SHIFTJIS);

   AddCodePage(
      10001, // Japanese (ShiftJIS)
      ID_VIEW_ENCODING_1,
      IDS_VIEW_ENCODING_MACJP);
   
   AddCodePage(
      77777, // Auto detect
      ID_VIEW_ENCODING_1,
      IDS_VIEW_ENCODING_AUTODETECT);


	return TRUE;
}


void DesktopApp::ProcessCommand(base_wnd * pwnd)
{ 
   LPWSTR *szArglist;
   int nArgs;
   int i;

   szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
   if( NULL == szArglist )
   {
      wprintf(L"CommandLineToArgvW failed\n");
   }
   else for( i=1; i<nArgs; i++)
   {
      String strParam;
      International::UnicodeToUtf8(strParam, szArglist[i]);
      if(strParam == "--desktop=1")
      {
         pwnd->PostMessage(WM_APP, 1, 0);
         return;
      }
      else if (strParam == "--desktop=2")
      {
         pwnd->PostMessage(WM_APP, 1, 1);
         return;
      }
      else if (strParam == "--hide")
      {
         pwnd->PostMessage(WM_APP, 2, 0);
         return;
      }
      else if (strParam == "--show")
      {
         pwnd->PostMessage(WM_APP, 2, 1);
         return;
      }
   }

}


/////////////////////////////////////////////////////////////////////////////
// AboutDlg dialog used for App About

class AboutDlg : public BaseForm
{
public:
	AboutDlg();

   CBrush m_brushStatic;
   COLORREF m_crStaticBackground;
   CBitmap m_bitmapBackground;
   CDC m_dcBackground;

   void _001InitializeFormPreData();
   void _001OnDraw(CDC * pdc);

// Dialog Data
	//{{AFX_DATA(AboutDlg)
	enum { IDD = IDD_ABOUTBOX };
//	CStatic	m_stTitle;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AboutDlg)
	//}}AFX_VIRTUAL

   DECL_GEN_SIGNAL(_001OnEnable)

   void _001InstallMessageHandling(igui::win::message::Dispatch * pinterface);

// Implementation
protected:
	//{{AFX_MSG(AboutDlg)
	//afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, base_wnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

AboutDlg::AboutDlg() 
: 
   BaseForm(AboutDlg::IDD)
{
   m_crStaticBackground = RGB(64, 128, 255);
   //m_brushStatic.CreateSolidBrush(m_crStaticBackground);
   m_brushStatic.CreateStockObject(NULL_BRUSH);
	//{{AFX_DATA_INIT(AboutDlg)
	//}}AFX_DATA_INIT
}


BEGIN_MESSAGE_MAP(AboutDlg, BaseForm)
	//{{AFX_MSG_MAP(AboutDlg)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void DesktopApp::OnAppAbout()
{
	AboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// DesktopApp message handlers


   void DesktopApp::SetLanguage(enum gen::App::ELanguage)
   {
   }
   enum gen::App::ELanguage DesktopApp::GetLanguage()
   {
      return langDefault;
   }
   enum gen::App::ELanguage DesktopApp::GetDefaultLanguage()
   {
      return langDefault;
   }
   bool DesktopApp::MessageWindowListener(unsigned int,unsigned int,long)
   {
      return true;
   }

void DesktopApp::OnToolsOptions() 
{
/*	m_lpoptionsdialog = new OptionsDialog();
   m_lpoptionsdialog->Create(IDD_OPTIONS, NULL);*/
	
}

void DesktopApp::OnUpdateToolsOptions(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable();	
   pCmdUI->SetCheck(m_lpoptionsdialog != NULL ? 1 : 0);
}

void DesktopApp::OnFileOpen() 
{
   XfplayerOpenFileDialog dlgFile(IDS_XFPLAYER_OPENFILETITLE,
		OFN_HIDEREADONLY
		| OFN_FILEMUSTEXIST
		| OFN_ALLOWMULTISELECT
		| OFN_EXPLORER);

	dlgFile.DoModal();

   AStrArray & wstra = dlgFile.m_straFile;

   for(int i = 0; i < wstra.GetSize(); i++)
   {
      _001OpenDocumentFile(wstra[i]);
   }
}

void DesktopApp::OnFileOpenEx() 
{
}

void DesktopApp::OnFileAdd() 
{

	XfplayerOpenFileDialog dlgFile(IDS_XFPLAYER_OPENFILETITLE,
		OFN_HIDEREADONLY
		| OFN_FILEMUSTEXIST
		| OFN_ALLOWMULTISELECT
		| OFN_EXPLORER);

   dlgFile.DoModal();

   AStrArray & stra = dlgFile.m_straFile;

   for(int i = 0; i < stra.GetSize(); i++)
   {
      _001OpenDocumentFile(stra[i]);
   }
	
}


void DesktopApp::VmsDataOnAfterChange(gen::signal_object * pobj)
{
   VmsDataChangeHint * pch = (VmsDataChangeHint *) pobj;
   if(*pch->m_pkey == VMSDATAKEY(SongDirectorySet))
   {
      AStrArray wstra;

   }
//   switch(key.GetType())
  // {
   //case _vmsdb::DataKeyType_vmplight:
      {
	      switch(pch->m_pkey->GetValue())
	      {
      //	case _vmsdb::CConfiguration::CfgUserInterfaceLanguage:
      //		OnAfterLanguageChange(GetLanguage(), puh);
      //		break;
      //	case _vmsp::CConfiguration::CfgKaraokeEncoding:
      //		OnAfterKaraokeEncodingChange(puh);
      //		break;
         }
      }
   //default:
     // break;
	//}
}

//AFX_STATIC_DATA const TCHAR _afxFileSection[] = _T("Recent File List");
//AFX_STATIC_DATA const TCHAR _afxFileEntry[] = _T("File%d");
AFX_STATIC_DATA const TCHAR _afxPreviewSection[] = _T("Settings");
AFX_STATIC_DATA const TCHAR _afxPreviewEntry[] = _T("PreviewPages");

int DesktopApp::ExitInstance() 
{
   MessageFilterHookManager * pmfmh;
   if(MessageFilterHookManager::AppGetMessageFilterHookManager(&pmfmh))
   {
      pmfmh->MessageFilterUnhook();
   }
   
   if (m_cmdinfo.m_nShellCommand != CCommandLineInfo::AppUnregister)
	{
		if (!afxContextIsDLL)
      {
		//	SaveStdProfileSettings();
	      ASSERT_VALID(this);

	      if (m_precentfilelist != NULL)
		      m_precentfilelist->WriteList();

	      if (m_nNumPreviewPages != 0)
		      WriteProfileInt(_afxPreviewSection, _afxPreviewEntry, m_nNumPreviewPages);
      }
	}

   
   if(m_pdocmanager != NULL)
   {
      delete m_pdocmanager;
      m_pdocmanager = NULL;
   }

	
	return gen::App::ExitInstance();
}


int DesktopApp::Run()
{
   return gen::App::Run();
}



void DesktopApp::_001CloseAllDocuments(bool bEndSession)
{
   guibase::AppInterface::_001CloseAllDocuments(bEndSession);
   m_pdocmanager->CloseAllDocuments(bEndSession);
}

bool DesktopApp::InitATL()
{
	m_bATLInited = true;

//xxx	_Module.Init(ObjectMap, AfxGetInstanceHandle());

	return TRUE;
}

void DesktopApp::RegisterShellFileTypes(BOOL bCompat)
{
//	ASSERT(m_pDocManager != NULL);
//	m_pDocManager->RegisterShellFileTypes(bCompat);
//	ASSERT(!m_pDocManager->m_templateList.IsEmpty());  // must have some doc templates

	String strPathName, strTemp, strResourcePathName;
 
	GetModuleShortFileName(AfxGetInstanceHandle(), strPathName);

	AStrArray strarray;

	String str;

	str.LoadString(IDS_MID);
	strarray.Add(str);
	str.LoadString(IDS_KAR);
	strarray.Add(str);
	str.LoadString(IDS_ST3);
	strarray.Add(str);

	AStrTokenizer strTokenizer;

	strTokenizer = str;

	AStrArray strarrayDocString;


//	_vmsp::FileAssociation fileassociation;

	for (int iTemplate = 0; iTemplate < strarray.GetSize(); iTemplate++)
	{
		strarrayDocString.RemoveAll();
		strarrayDocString.AddTokens(strarray[iTemplate],"\n", true);
		
		String strOpenCommandLine = strPathName;
		String strPrintCommandLine = strPathName;
		String strPrintToCommandLine = strPathName;
		String strDefaultIconCommandLine = strPathName;
        
        int nIconIndex = 1;
		if (bCompat)
		{
			String strIconIndex;
		//	HICON hIcon = ::ExtractIcon(AfxGetInstanceHandle(), strPathName, nTemplateIndex);
            HICON hIcon = ::ExtractIcon(AfxGetInstanceHandle(), strPathName, nIconIndex);
			if (hIcon != NULL)
			{
				//strIconIndex.Format(_afxIconIndexFmt, nTemplateIndex);
                strIconIndex.Format(_afxIconIndexFmt, nIconIndex);
				DestroyIcon(hIcon);
			}
			else
			{
				strIconIndex.Format(_afxIconIndexFmt, DEFAULT_ICON_INDEX);
			}
			strDefaultIconCommandLine += strIconIndex;
		}

		String strFilterExt, strFileTypeId, strFileTypeName;
		strFileTypeId = strarrayDocString[CDocTemplate::regFileTypeId];
		if (!strFileTypeId.IsEmpty())
		{
			strFileTypeName = strarrayDocString[CDocTemplate::regFileTypeName];
			// enough info to register it
			if (strFileTypeName.IsEmpty())
				strFileTypeName = strFileTypeId;    // use id name

			ASSERT(strFileTypeId.Find(' ') == -1);  // no spaces allowed

			// first register the type ID of our server
			if (!_AfxSetRegKey(strFileTypeId, strFileTypeName))
				continue;       // just skip it

			if (bCompat)
			{
				// path\DefaultIcon = path,1
				strTemp.Format(_afxDefaultIconFmt, (LPCTSTR)strFileTypeId);
				if (!_AfxSetRegKey(strTemp, strDefaultIconCommandLine))
					continue;       // just skip it
			}

			strTemp = strarrayDocString[CDocTemplate::windowTitle];
			// If MDI Application
			if (strTemp.IsEmpty())
			{
				// path\shell\open\ddeexec = [open("%1")]
				strTemp.Format(_afxShellOpenFmt, (LPCTSTR)strFileTypeId,
					(LPCTSTR)_afxDDEExec);
				if (!_AfxSetRegKey(strTemp, _afxDDEOpen))
					continue;       // just skip it

				if (bCompat)
				{
					// path\shell\print\ddeexec = [print("%1")]
					strTemp.Format(_afxShellPrintFmt, (LPCTSTR)strFileTypeId,
						(LPCTSTR)_afxDDEExec);
					if (!_AfxSetRegKey(strTemp, _afxDDEPrint))
						continue;       // just skip it

					// path\shell\printto\ddeexec = [printto("%1","%2","%3","%4")]
					strTemp.Format(_afxShellPrintToFmt, (LPCTSTR)strFileTypeId,
						(LPCTSTR)_afxDDEExec);
					if (!_AfxSetRegKey(strTemp, _afxDDEPrintTo))
						continue;       // just skip it

					// path\shell\open\command = path /dde
					// path\shell\print\command = path /dde
					// path\shell\printto\command = path /dde
					strOpenCommandLine += _afxDDEArg;
					strPrintCommandLine += _afxDDEArg;
					strPrintToCommandLine += _afxDDEArg;
				}
				else
				{
					strOpenCommandLine += _afxOpenArg;
				}
			}
			else
			{
				// path\shell\open\command = path filename
				// path\shell\print\command = path /p filename
				// path\shell\printto\command = path /pt filename printer driver port
				strOpenCommandLine += _afxOpenArg;
				if (bCompat)
				{
					strPrintCommandLine += _afxPrintArg;
					strPrintToCommandLine += _afxPrintToArg;
				}
			}

			// path\shell\open\command = path filename
			strTemp.Format(_afxShellOpenFmt, (LPCTSTR)strFileTypeId,
				(LPCTSTR)_afxCommand);
			if (!_AfxSetRegKey(strTemp, strOpenCommandLine))
				continue;       // just skip it

			if (bCompat)
			{
				// path\shell\print\command = path /p filename
				strTemp.Format(_afxShellPrintFmt, (LPCTSTR)strFileTypeId,
					(LPCTSTR)_afxCommand);
				if (!_AfxSetRegKey(strTemp, strPrintCommandLine))
					continue;       // just skip it

				// path\shell\printto\command = path /pt filename printer driver port
				strTemp.Format(_afxShellPrintToFmt, (LPCTSTR)strFileTypeId,
					(LPCTSTR)_afxCommand);
				if (!_AfxSetRegKey(strTemp, strPrintToCommandLine))
					continue;       // just skip it
			}
			strFilterExt = strarrayDocString[CDocTemplate::filterExt];
            AStrTokenizer strtokenizer;
            strtokenizer = strFilterExt;
            while(strtokenizer.GetNextToken(strFilterExt, _T(";"), false))
            {
			    if (!strFilterExt.IsEmpty())
			    {
				    ASSERT(strFilterExt[0] == '.');

				    LONG lSize = _MAX_PATH * 2;
				    LONG lResult = ::RegQueryValue(HKEY_CLASSES_ROOT, strFilterExt,
					    strTemp.GetBuffer(lSize), &lSize);
				    strTemp.ReleaseBuffer();


				    if (lResult != ERROR_SUCCESS || strTemp.IsEmpty() ||
					    strTemp == strFileTypeId)
				    {
					    // no association for that suffix
					    if (!_AfxSetRegKey(strFilterExt, strFileTypeId))
						    continue;

					    if (bCompat)
					    {
						    strTemp.Format(_afxShellNewFmt, (LPCTSTR)strFilterExt);
						    (void)_AfxSetRegKey(strTemp, _afxShellNewValue, _afxShellNewValueName);
					    }
				    }
                    else
                    {
                    }
                }
			}
		}
//		fileassociation.UpdateServerRegistration(strarray[iTemplate]);
	}
}

BOOL DesktopApp::_001ProcessShellCommand(gen::CommandLineInfo& rCmdInfo)
{
	BOOL bResult = TRUE;
	switch (rCmdInfo.m_nShellCommand)
	{
		// If we're doing DDE, hide ourselves

	case CCommandLineInfo::FileDDE:
//		m_pCmdInfo = (CCommandLineInfo*)m_nCmdShow;
//		m_nCmdShow = SW_HIDE;
		break;
	case CCommandLineInfo::FileOpen:
		if(!m_pdocmanager->OpenDocumentFile(rCmdInfo.m_strFileName))
         bResult = FALSE;
		break;
   default:
      bResult = Ex1App::_001ProcessShellCommand(rCmdInfo);
      break;
   }
   return bResult;
}

void DesktopApp::OnEvent(_vmsdb::EDBEvent eevent, LPARAM lparam)
{
   switch(eevent)
   {
   case _vmsdb::DBEventGetDefaultImageDirectorySet:
      {
         WStrArray * pwstra = (WStrArray *) lparam;
         ASSERT_VALID(pwstra);

         WString wstr;
         String str;
         String strPath;

         simpledb::AppInterface * papp = (simpledb::AppInterface *) this;
         String strModuleFolder(m_strModuleFolder);
         // xxx str.LoadString(IDS_FOLDER_IMAGES);
         str = strModuleFolder;
         str += "Images";
         strPath += str;

         International::ACPToUnicode(wstr, strPath);
         pwstra->Add(wstr);

         TCHAR buffer[MAX_PATH * 2];
         GetWindowsDirectory(buffer, sizeof(buffer));
         String strWallpaper(buffer);
         strWallpaper += "\\Web\\Wallpaper";
         
         International::ACPToUnicode(wstr, strWallpaper);
         pwstra->Add(wstr);

      }
      break;
   }
}

BOOL DesktopApp::OnDDECommand(LPTSTR lpszCommand) 
{
	if (m_pdocmanager != NULL)
		return m_pdocmanager->OnDDECommand(lpszCommand);
	else
		return FALSE;
//	return gen::App::OnDDECommand(lpszCommand);
}

void DesktopApp::OnViewAlbum() 
{
   m_pdoctemplateAlbum->OpenDocumentFile(NULL);	
}

void DesktopApp::OnUpdateViewAlbum(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable();
}



CUserInterfaceImageManager & DesktopApp::GetImageManager()
{
   return *m_pimagemanager;
}


void AboutDlg::_001OnDraw(CDC * pdc) 
{
	CDC & dc = *pdc;

   CRect rectClient;

   _001GetClientRect(rectClient);

   if(m_dcBackground.GetSafeHdc() == NULL)
   {
      m_dcBackground.CreateCompatibleDC(&dc);
      HBITMAP hbitmap = CImaging::_w001LoadBitmap(
         "PNG",
         MAKEINTRESOURCE(IDR_PNG_VMPLITE_ABOUT));
      m_bitmapBackground.Attach(hbitmap);
      m_dcBackground.SelectObject(m_bitmapBackground);
   }

/*   TRIVERTEX        vert[2] ;
   GRADIENT_RECT    gRect;
   vert [0] .x      = rectClient.left;
   vert [0] .y      = rectClient.top;
   vert [0] .Red    = 0x0000;
   vert [0] .Green  = 0x0000;
   vert [0] .Blue   = 0x0000;
   vert [0] .Alpha  = 0x0000;

   vert [1] .x      = rectClient.right;
   vert [1] .y      = rectClient.bottom; 
   vert [1] .Red    = 0x0000;
   vert [1] .Green  = 0x0000;
   vert [1] .Blue   = 0xff00;
   vert [1] .Alpha  = 0x0000;

   gRect.UpperLeft  = 0;
   gRect.LowerRight = 1;
   GradientFill(dc,vert,2,&gRect,1,GRADIENT_FILL_RECT_H);*/

   //dc.FillSolidRect(rectClient, m_crStaticBackground);
   dc.BitBlt(
      rectClient.left,
      rectClient.top,
      rectClient.Width(),
      rectClient.Height(),
      &m_dcBackground,
      0,
      0,
      SRCCOPY);


   dc.Draw3dRect(rectClient, RGB(92, 127, 192), RGB(92, 127, 192));

   CRect rect(rectClient);
   rect.DeflateRect(1, 1, 1, 1);
   dc.Draw3dRect(rectClient, RGB(64, 92, 127), RGB(64, 92, 127));
	
}

void AboutDlg::_001InstallMessageHandling(igui::win::message::Dispatch * pinterface)
{
   BaseForm::_001InstallMessageHandling(pinterface);
	IGUI_WIN_MSG_LINK(WM_ENABLE, this, this, &AboutDlg::_001OnEnable);

}

void AboutDlg::_001OnEnable(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::enable, penable, pobj);
   BOOL bEnable = penable->get_enable();
}


BOOL AboutDlg::OnInitDialog() 
{
	BaseForm::OnInitDialog();

   String str;

   str.Format("veriwell Musical Player Lite");


   DesktopApp * papp = (DesktopApp *) AfxGetApp();

	TCHAR lpszModuleFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, lpszModuleFilePath, MAX_PATH + 1);

   DWORD dw;
   
   DWORD dwResSize = GetFileVersionInfoSize(      
      lpszModuleFilePath,
      &dw);


   if(dwResSize > 0)
   {
      LPVOID lpdata = new BYTE[dwResSize];
      if(GetFileVersionInfo(      
         lpszModuleFilePath,
         0,
         dwResSize,
         lpdata))
      {
         UINT cbTranslate;
         struct LANGANDCODEPAGE {
            WORD wLanguage;
            WORD wCodePage;
            } *lpTranslate;

         // Read the list of languages and code pages.

         VerQueryValue(lpdata, 
              TEXT("\\VarFileInfo\\Translation"),
              (LPVOID*)&lpTranslate,
              &cbTranslate);

         String strKey;
         //for( i=0; i < (cbTranslate/sizeof(struct LANGANDCODEPAGE)); i++ )
         for(int i=0; i < 1; i++ )
         {
           LPTSTR lpsz;
           UINT uiSize;

           strKey.Format(
            TEXT("\\StringFileInfo\\%04x%04x\\FileDescription"),
            lpTranslate[i].wLanguage,
            lpTranslate[i].wCodePage);

           String strValue;

           

           // Retrieve file description for language and code page "i". 
           VerQueryValue(lpdata, 
                         (LPTSTR) (LPCTSTR) strKey, 
                         (LPVOID *)&lpsz, 
                         &uiSize); 

           strValue = lpsz;

           if(uiSize > 0)
           {
               str = strValue;
           }

           strKey.Format(
            TEXT("\\StringFileInfo\\%04x%04x\\FileVersion"),
            lpTranslate[i].wLanguage,
            lpTranslate[i].wCodePage);

           // Retrieve file description for language and code page "i". 
           VerQueryValue(lpdata, 
                         (LPTSTR) (LPCTSTR) strKey, 
                         (LPVOID *)&lpsz, 
                         &uiSize); 


           String strVersion(lpsz, uiSize);

           str += " " + strVersion;
         }
      }
      delete [] (LPBYTE) lpdata;
   }


	
   GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(str);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH AboutDlg::OnCtlColor(CDC* pdc, base_wnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = BaseForm::OnCtlColor(pdc, pWnd, nCtlColor);
	
   if(nCtlColor == CTLCOLOR_STATIC)
   {
      pdc->SetBkMode(TRANSPARENT);
      //pdc->SetBkColor(m_crStaticBackground);
      return m_brushStatic;
   }
	return hbr;
}

void AboutDlg::_001InitializeFormPreData()
{
	Ex1FormInterfaceControl control;

	control.m_uiId = IDOK;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleButton);
	_001AddControl(control);

	control.m_uiId = IDC_STATIC_ICON;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleButton);
	_001AddControl(control);

	control.m_uiId = IDC_STATIC_TITLE;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleButton);
	_001AddControl(control);

	control.m_uiId = IDC_STATIC_COPYRIGHT;
	control.m_pruntimeclass = RUNTIME_CLASS(SimpleButton);
	_001AddControl(control);
}

String DesktopApp::GetVersion()
{

	TCHAR lpszModuleFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, lpszModuleFilePath, MAX_PATH + 1);

   DWORD dw;
   
   DWORD dwResSize = GetFileVersionInfoSize(      
      lpszModuleFilePath,
      &dw);


   if(dwResSize > 0)
   {
      LPVOID lpdata = new BYTE[dwResSize];
      if(GetFileVersionInfo(      
         lpszModuleFilePath,
         0,
         dwResSize,
         lpdata))
      {
         UINT cbTranslate;
         struct LANGANDCODEPAGE {
            WORD wLanguage;
            WORD wCodePage;
            } *lpTranslate;

         // Read the list of languages and code pages.

         VerQueryValue(lpdata, 
              TEXT("\\VarFileInfo\\Translation"),
              (LPVOID*)&lpTranslate,
              &cbTranslate);

         String strKey;
         //for( i=0; i < (cbTranslate/sizeof(struct LANGANDCODEPAGE)); i++ )
         for(int i=0; i < 1; i++ )
         {
           LPTSTR lpsz;
           UINT uiSize;

           strKey.Format(
            TEXT("\\StringFileInfo\\%04x%04x\\FileDescription"),
            lpTranslate[i].wLanguage,
            lpTranslate[i].wCodePage);

           


           strKey.Format(
            TEXT("\\StringFileInfo\\%04x%04x\\FileVersion"),
            lpTranslate[i].wLanguage,
            lpTranslate[i].wCodePage);

           // Retrieve file description for language and code page "i". 
           VerQueryValue(lpdata, 
                         (LPTSTR) (LPCTSTR) strKey, 
                         (LPVOID *)&lpsz, 
                         &uiSize); 


           String strVersion(lpsz, uiSize);

           return strVersion;
         }
      }
      delete [] (LPBYTE) lpdata;
   }


	return "";

}


void DesktopApp::LoadStdProfileSettings()
{
   int iMRUCount = _AFX_MRU_COUNT;

	ASSERT_VALID(this);
	ASSERT(m_precentfilelist == NULL);

   UINT nMaxMRU = 15;
	if (nMaxMRU != 0)
	{
		// create file MRU since nMaxMRU not zero
		m_precentfilelist = new RecentFileList(0, _afxFileSection, _afxFileEntry,
			nMaxMRU, VMSDATAKEY(MRUFiles));
		m_precentfilelist->ReadList();
	}
	// 0 by default means not set
	m_nNumPreviewPages = GetProfileInt(_afxPreviewSection, _afxPreviewEntry, 0);


   gen::App::LoadStdProfileSettings(iMRUCount);
}


int DesktopApp::DoMessageBox(LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt)
{
	// disable windows for modal dialog
	//xxx EnableModeless(FALSE);
	HWND hWndTop;
	HWND hWnd = base_wnd::GetSafeOwner_(NULL, &hWndTop);

	// set help context if possible
	DWORD* pdwContext = NULL;
	if (hWnd != NULL)
	{
		// use app-level context or frame level context
		LRESULT lResult = ::SendMessage(hWndTop, WM_HELPPROMPTADDR, 0, 0);
		if (lResult != 0)
			pdwContext = (DWORD*)lResult;
	}
	// for backward compatibility use app context if possible
	if (pdwContext == NULL && this != NULL)
		pdwContext = &m_dwPromptContext;

	DWORD dwOldPromptContext = 0;
	if (pdwContext != NULL)
	{
		// save old prompt context for restoration later
		dwOldPromptContext = *pdwContext;
		if (nIDPrompt != 0)
			*pdwContext = HID_BASE_PROMPT+nIDPrompt;
	}

	// determine icon based on type specified
	if ((nType & MB_ICONMASK) == 0)
	{
		switch (nType & MB_TYPEMASK)
		{
		case MB_OK:
		case MB_OKCANCEL:
			nType |= MB_ICONEXCLAMATION;
			break;

		case MB_YESNO:
		case MB_YESNOCANCEL:
			nType |= MB_ICONEXCLAMATION;
			break;

		case MB_ABORTRETRYIGNORE:
		case MB_RETRYCANCEL:
			// No default icon for these types, since they are rarely used.
			// The caller should specify the icon.
			break;
		}
	}

#ifdef _DEBUG
	if ((nType & MB_ICONMASK) == 0)
		TRACE0("Warning: no icon specified for message box.\n");
#endif

	TCHAR szAppName[_MAX_PATH];
	LPCTSTR pszAppName;
	if (this != NULL)
		pszAppName = m_pszAppName;
	else
	{
		pszAppName = szAppName;
		GetModuleFileName(NULL, szAppName, _MAX_PATH);
	}

	int nResult =
		::MessageBox(hWnd, lpszPrompt, pszAppName, nType);

	// restore prompt context if possible
	if (pdwContext != NULL)
		*pdwContext = dwOldPromptContext;

	// re-enable windows
	if (hWndTop != NULL)
		::EnableWindow(hWndTop, TRUE);
//xxx 	EnableModeless(TRUE);

	return nResult;
}

BOOL DesktopApp::OnCmdMsg(UINT nID, int nCode, void* pExtra, CAFX_CMDHANDLERINFO* pHandlerInfo) 
{
   if(guibase::AppInterface::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
      return TRUE;

/*   BOOL bResult;
   if(nCode == CN_UPDATE_COMMAND_UI)
   {
        ASSERT(nCode == CN_UPDATE_COMMAND_UI);
		ASSERT(pExtra != NULL);
		CCmdUI* pCmdUI = (CCmdUI*)pExtra;
		ASSERT(pCmdUI->m_nID == nID);           // sanity assert
		ASSERT(!pCmdUI->m_bContinueRouting);    // idle - not set
		OnUpdatePopupMenu(pCmdUI);
		bResult = !pCmdUI->m_bContinueRouting;
		//pCmdUI->m_bContinueRouting = FALSE; 
   }
   else
   {
        //ASSERT(FALSE);
        bResult = FALSE;
   }
   if(bResult)
      return bResult;*/

	return gen::App::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}




HDDEDATA CALLBACK DesktopApp::DdeCallback(
   UINT uType,
   UINT uFmt,
   HCONV hconv,
   HDDEDATA hsz1,
   HDDEDATA hsz2,
   HDDEDATA hdata,
   HDDEDATA dwData1,
   HDDEDATA dwData2
   )
{ 
   switch (uType) 
   { 
   case XTYP_REGISTER: 
   case XTYP_UNREGISTER: 
      return (HDDEDATA) NULL; 
 
   case XTYP_ADVDATA: 
      return (HDDEDATA) DDE_FACK; 
 
   case XTYP_XACT_COMPLETE: 
      return (HDDEDATA) NULL; 
      
   case XTYP_CONNECT: 
   {
      DesktopApp * papp = (DesktopApp *) AfxGetApp();
      if(!DdeCmpStringHandles((HSZ) hsz1, papp->m_hszSystemTopic))
      {
         if(!DdeCmpStringHandles((HSZ) hsz2, papp->m_hszAppName))
         {
            return (HDDEDATA) TRUE; 
         }
      }
      return (HDDEDATA) FALSE; 
   }
   
   case XTYP_DISCONNECT: 
      return (HDDEDATA) NULL; 
 
   case XTYP_EXECUTE: 
   {
      // get the command string
      DWORD dwSize = DdeGetData(
         hdata,
         NULL, 
         0, 
         0);
      
      WString wstr;
      
      dwSize = DdeGetData(
         hdata,
         (LPBYTE) wstr.GetBuffer(dwSize), 
         dwSize, 
         0);
      
      wstr.ReleaseBuffer();
      
      
      // execute the command
      if (!AfxGetApp()->OnDDECommand( (LPTSTR)(LPCWSTR)wstr))
         TRACE1("Error: failed to execute DDE command '%S'.\n", wstr);
      
      // 
      VERIFY(DdeFreeDataHandle(hdata));            
      return (HDDEDATA) NULL; 
   }

   default: 
      return (HDDEDATA) NULL; 
   } 
} 

void DesktopApp::ProcessCommandLine(LPCWSTR lpwstr)
{
   gen::CommandLineInfo rCmdInfo;

/*   int numargs;
   int numchars;
   wparse_cmdline(
      (LPWSTR) lpwstr, 
      NULL, 
      NULL,
      &numargs,
      &numchars);

   m_pszCmdLine = new WCHAR[numchars];
   m_argv = new WCHAR*[numargs];

   wparse_cmdline(
      (LPWSTR) lpwstr, 
      m_argv, 
      m_pszCmdLine,
      &numargs,
      &numchars);

   m_argc = numargs - 1;

	for (int i = 1; i < m_argc; i++)
	{
		LPCWSTR pszParam = m_argv[i];
		BOOL bFlag = FALSE;
		BOOL bLast = ((i + 1) == m_argc);
		if (pszParam[0] == '-' || pszParam[0] == '/')
		{
			// remove flag specifier
			bFlag = TRUE;
			++pszParam;
		}
		rCmdInfo.ParseParam(pszParam, bFlag, bLast);
	}

   _001ProcessShellCommand(rCmdInfo);*/
}


void DesktopApp::GetAvailableLanguages(AStrArray &wstra)
{

   String strPathName;

   GetModuleFolder(strPathName);

   AStrArray wstraFilter;

   wstraFilter.Add("*.dll");

   String wstr;
   wstr = strPathName;

   wstr += "language\\";

   AStrArray wstraBase;
   wstraBase.Add(wstr);

   Ex1FileSet fileset;

   fileset.AddSearch(wstraBase, wstraFilter);
   
   String wstrFile;
   wstra.RemoveAll();
   for(int i = 0; i < fileset.GetFileCount(); i++)
   {
      fileset.FileAt(i, wstrFile);
      wstra.Add(wstrFile);
   }
   /*WString wstr1;
   wstr1 = wstr + L"language\\vmslightptbr.dll";
   wstra.Add(wstr1);

   WString wstr2;
   wstr1 = wstr + L"language\\vmslightjp.dll";
   wstra.Add(wstr1);*/

}

void DesktopApp::OnUpdatePopupMenu(CCmdUI *pcmdui)
{
   if(pcmdui->m_nID == ID_LANGUAGE_CHANGE)
   {
//      MENUITEMINFO mii;
      
      CMenu * pmenu = pcmdui->m_pMenu;
      
      pmenu->DeleteMenu(pcmdui->m_nID, MF_BYCOMMAND);
      
      UINT uiId = ID_LANGUAGE_CHANGE1;
      pmenu->InsertMenu(pcmdui->m_nIndex++,
         MF_BYPOSITION,
         uiId,
         "English");
      uiId++;
      
      AStrArray wstra;
      GetAvailableLanguages(wstra);
      
      m_straLanguagePath.RemoveAll();

      WString wstr;
      for(int i = 0; i < wstra.GetSize(); i++, uiId++)
      {
         
         HINSTANCE hinst = win::LoadLibrary(wstra[i]);
         if(hinst == NULL)
            continue;
         if(!wstr.LoadString(hinst, IDS_VIEW_LANGUAGE))
            continue;
         
         m_straLanguagePath.Add(wstra[i]);

         ::InsertMenuW(
            pmenu->GetSafeHmenu(),
            pcmdui->m_nIndex++,
            MF_BYPOSITION,
            uiId,
            wstr);
         
      }
      pcmdui->m_nIndex--;
      
      pcmdui->m_nIndexMax = pmenu->GetMenuItemCount();

      pcmdui->m_bContinueRouting = TRUE;
      
   }
   

}

bool DesktopApp::SetLanguageResourcePath(LPCTSTR lpcsz)
{
   if(lpcsz == NULL || lstrlenA(lpcsz) <= 0)
   {
      m_strLanguagePath = "";
      AfxSetResourceHandle(m_hInstance);
   }
   else
   {
      HMODULE hmodule = ::LoadLibrary(lpcsz);
      if(hmodule == NULL)
         return false;
      m_strLanguagePath = lpcsz;
      AfxSetResourceHandle(hmodule);
   }
   WriteProfileString("language", "resource path", lpcsz);
   SendMessageToWindows(APPM_LANGUAGE, 0, 0);
   return true;
}

void DesktopApp::OnLanguageChange(UINT uiId) 
{
   int i = uiId - ID_LANGUAGE_CHANGE1;
   if(i == 0)
   {
      SetLanguageResourcePath("");
   }
   else
   {
      String str(m_straLanguagePath[i - 1]);
      SetLanguageResourcePath(str);
   }
}

void DesktopApp::OnUpdateLanguageChange(CCmdUI* pcmdui) 
{
   if(pcmdui->m_nID == ID_LANGUAGE_CHANGE)
   {
      BaseWndMenuButtonCmdUI * pcmdui1 = dynamic_cast < BaseWndMenuButtonCmdUI * > (pcmdui);
      if(pcmdui1 != NULL)
      {
         BaseWndMenuItemPtrArray * pitema = pcmdui1->m_pitema;

         
//         pmenu->DeleteMenu(pcmdui->m_nID, MF_BYCOMMAND);

         int iStartIndex = pcmdui->m_nIndex;
         
         int iIndex = iStartIndex;
         UINT uiId = ID_LANGUAGE_CHANGE1;
         BaseWndMenuItem * pitem = new BaseWndMenuItem;
         pitem->m_iId = uiId;
         pitem->m_button._001SetButtonText("English");
         pitem->m_iLevel = pitema->m_pitemContainer != NULL ? pitema->m_pitemContainer->m_iLevel + 1 : 0;
         pitema->SetAt(iIndex, pitem);
         uiId++;
         iIndex++;
         
         AStrArray wstra;
         GetAvailableLanguages(wstra);
         
         m_straLanguagePath.RemoveAll();

         String wstr;
         String str;
         for(int i = 0; i < wstra.GetSize(); i++, uiId++)
         {
            pitem = new BaseWndMenuItem;
            HINSTANCE hinst = win::LoadLibrary(wstra[i]);
            if(hinst == NULL)
               continue;
            if(!wstr.LoadString(hinst, IDS_VIEW_LANGUAGE))
               continue;
            
            m_straLanguagePath.Add(wstra[i]);

            pitem->m_iId = uiId;
            pitem->m_button._001SetButtonText("English");
            pitem->m_iLevel = pitema->m_pitemContainer != NULL ? pitema->m_pitemContainer->m_iLevel + 1 : 0;
            pitema->InsertAt(iIndex, pitem);
            iIndex++;
            
         }
         pcmdui->m_nIndex = iStartIndex;
         
         pcmdui->m_nIndexMax = pitema->GetSize();

   ////      pcmdui->m_bContinueRouting = TRUE;
   	   pcmdui->Enable(!m_strLanguagePath.IsEmpty());    // all the added items are enabled
         
      }
      else
      {

         CMenu * pmenu = pcmdui->m_pMenu;

         if(pcmdui->m_pSubMenu != NULL)
         {
            pmenu = pcmdui->m_pSubMenu;
         }
         
         pmenu->DeleteMenu(pcmdui->m_nID, MF_BYCOMMAND);

         int iStartIndex = pcmdui->m_nIndex;
         
         UINT uiId = ID_LANGUAGE_CHANGE1;
         pmenu->InsertMenu(pcmdui->m_nIndex++,
            MF_BYPOSITION,
            uiId,
            "English");
         uiId++;
         
         AStrArray wstra;
         GetAvailableLanguages(wstra);
         
         m_straLanguagePath.RemoveAll();

         String wstr;
         for(int i = 0; i < wstra.GetSize(); i++, uiId++)
         {
            
            HINSTANCE hinst = win::LoadLibrary(wstra[i]);
            if(hinst == NULL)
               continue;
            if(!wstr.LoadString(hinst, IDS_VIEW_LANGUAGE))
               continue;
            
            m_straLanguagePath.Add(wstra[i]);

            SimpleMenu::_InsertMenuItem(
               *pcmdui->m_pMenu,
               *pmenu,
               pcmdui->m_nIndex++,
               MF_BYPOSITION,
               uiId,
               wstr);
            
         }
         pcmdui->m_nIndex = iStartIndex;
         
         pcmdui->m_nIndexMax = pmenu->GetMenuItemCount();

   ////      pcmdui->m_bContinueRouting = TRUE;
   	   pcmdui->Enable(!m_strLanguagePath.IsEmpty());    // all the added items are enabled
         
      }
   }
   else
   {
      bool bCurrent;
      if(pcmdui->m_nID == ID_LANGUAGE_CHANGE1)
      {
         bCurrent = m_strLanguagePath.IsEmpty() != 0;
      }
      else
      {
         String str(m_straLanguagePath[pcmdui->m_nID - ID_LANGUAGE_CHANGE1 - 1]);
         bCurrent = m_strLanguagePath == str;
      }
      pcmdui->Enable(!bCurrent);
      pcmdui->SetCheck(bCurrent ? 1 : 0);
   }
}


bool DesktopApp::GetCodePageCommandData(EncodingMapItem & itemParam, UINT uiCommand)
{
   for(int i = 0 ; i < m_encodinga.GetSize(); i++)
   {
      EncodingMapItem & item = m_encodinga[i];
      if(item.m_uiBaseCommand + item.m_iIndex == uiCommand)
      {
         itemParam = item;
         return true;
      }
   }
   return false;
}

DWORD DesktopApp::CommandToCodePage(UINT uiId)
{
   EncodingMapItem item;
   if(GetCodePageCommandData(item, uiId))
      return item.m_dwCodePage;
   else
      return 0xffffffff;
}

void DesktopApp::AddCodePage(
   DWORD dwCodePage, 
   UINT uiBaseCommand,
   UINT uiString)
{
   int iNewIndex = 0;
   for(int i = 0 ; i < m_encodinga.GetSize(); i++)
   {
      EncodingMapItem & item = m_encodinga[i];
      if(item.m_uiBaseCommand == uiBaseCommand)
      {
         if(item.m_dwCodePage == dwCodePage)
         {
            // already added
            ASSERT(FALSE);
            return ;
         }
         iNewIndex++;
      }
   }
   EncodingMapItem item;
   item.m_dwCodePage       = dwCodePage;
   item.m_uiBaseCommand    = uiBaseCommand;
   item.m_iIndex           = iNewIndex;
   item.m_uiString         = uiString;
   m_encodinga.Add(item);
}

int DesktopApp::GetCodePageCommandCount(UINT uiBaseCommand)
{
   int iMaxIndex = -1;
   for(int i = 0 ; i < m_encodinga.GetSize(); i++)
   {
      EncodingMapItem & item = m_encodinga[i];
      if(item.m_uiBaseCommand == uiBaseCommand)
      {
         if(item.m_iIndex > iMaxIndex)
            iMaxIndex = item.m_iIndex;
      }
   }
   return iMaxIndex + 1;
}

void DesktopApp::OnUpdateViewEncoding(CCmdUI* pcmdui) 
{
   if(pcmdui->m_nID == ID_VIEW_ENCODING)
   {
      BaseWndMenuButtonCmdUI * pcmdui1 = dynamic_cast < BaseWndMenuButtonCmdUI * > (pcmdui);
      if(pcmdui1 != NULL)
      {
         BaseWndMenuItemPtrArray * pitema = pcmdui1->m_pitema;
         
         pitema->RemoveAt(pcmdui->m_nIndex);

         int iStartIndex = pcmdui->m_nIndex;
         int iIndex = iStartIndex;
         
         int iCount = GetCodePageCommandCount(ID_VIEW_ENCODING_1);

         BaseWndMenuItem menuitem;
         EncodingMapItem item;
         WString wstr;
         String str;
         for(int i = 0; i < iCount; i++)
         {
            if(GetCodePageCommandData(item, ID_VIEW_ENCODING_1 + i))
            {
               if(!str.LoadString(item.m_uiString))
                  continue;
            
               menuitem.m_iId = ID_VIEW_ENCODING_1 + i;
               menuitem.m_button._001SetButtonText(str);
               menuitem.m_iLevel = pitema->m_pitemContainer != NULL ? pitema->m_pitemContainer->m_iLevel + 1 : 0;
               pitema->InsertAt(iIndex, new BaseWndMenuItem(menuitem));
               iIndex++;
            }
         }
         pcmdui->m_nIndex = iStartIndex;
         
         pcmdui->m_nIndexMax = iIndex;

      }
      else
      {

         CMenu * pmenu = pcmdui->m_pMenu;

         if(pcmdui->m_pSubMenu != NULL)
         {
            pmenu = pcmdui->m_pSubMenu;
         }
         
         pmenu->DeleteMenu(pcmdui->m_nID, MF_BYCOMMAND);

         int iStartIndex = pcmdui->m_nIndex;
         
         int iCount = GetCodePageCommandCount(ID_VIEW_ENCODING_1);

         EncodingMapItem item;
         String wstr;
         for(int i = 0; i < iCount; i++)
         {
            if(GetCodePageCommandData(item, ID_VIEW_ENCODING_1 + i))
            {
               if(!wstr.LoadString(item.m_uiString))
                  continue;
            

               SimpleMenu::_InsertMenuItem(
                  *pcmdui->m_pMenu,
                  *pmenu,
                  pcmdui->m_nIndex++,
                  MF_BYPOSITION,
                  ID_VIEW_ENCODING_1 + i,
                  wstr);
            }
            
         }
         pcmdui->m_nIndex = iStartIndex;
         
         pcmdui->m_nIndexMax = pmenu->GetMenuItemCount();

   ////      pcmdui->m_bContinueRouting = TRUE;
   	   //pcmdui->Enable(!m_strLanguagePath.IsEmpty());    // all the added items are enabled
      }
      
   }
/*   else
   {
      bool bCurrent;
      if(pcmdui->m_nID == ID_LANGUAGE_CHANGE1)
      {
         bCurrent = m_strLanguagePath.IsEmpty();
      }
      else
      {
         String str(m_wstraLanguagePath[pcmdui->m_nID - ID_LANGUAGE_CHANGE1 - 1]);
         bCurrent = m_strLanguagePath == str;
      }
      pcmdui->Enable(!bCurrent);
      pcmdui->SetCheck(bCurrent ? 1 : 0);
   }*/
}

void DesktopApp::AddToRecentFileList(LPCTSTR lpszPathName)
{
	ASSERT_VALID(this);
	ASSERT(lpszPathName != NULL);
	ASSERT(AfxIsValidString(lpszPathName));

	if (m_precentfilelist != NULL)
		m_precentfilelist->Add(lpszPathName);
}


/////////////////////////////////////////////////////////////////////////////
// MRU file list default implementation

void DesktopApp::OnUpdateRecentFileMenu(CCmdUI* pCmdUI)
{
   
	ASSERT_VALID(this);
	if (m_precentfilelist == NULL) // no MRU files
		pCmdUI->Enable(FALSE);
	else
   {
      if(pCmdUI->m_nID == ID_FILE_MRU_FILE1)
         pCmdUI->Enable(TRUE);
      else
		   m_precentfilelist->UpdateMenu(pCmdUI);
   }
}

/////////////////////////////////////////////////////////////////////////////
// MRU file list default implementation

BOOL DesktopApp::OnOpenRecentFile(UINT nID)
{
	ASSERT_VALID(this);
	ASSERT(m_precentfilelist != NULL);

	ASSERT(nID >= ID_FILE_MRU_FILE1);
	ASSERT(nID < ID_FILE_MRU_FILE1 + (UINT)m_precentfilelist->GetSize());
	int nIndex = nID - ID_FILE_MRU_FILE1;
	ASSERT((*m_precentfilelist)[nIndex].GetLength() != 0);

	TRACE2("MRU: open file (%d) '%s'.\n", (nIndex) + 1,
			(*m_precentfilelist)[nIndex]);

	if (_001OpenDocumentFile((*m_precentfilelist)[nIndex]) == NULL)
		m_precentfilelist->Remove(nIndex);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////


CDocument* DesktopApp::OpenDocumentFile(LPCTSTR lpszFileName)
{
   return (CDocument * ) _001OpenDocumentFile(lpszFileName);
}

Ex1FactoryImpl * DesktopApp::Ex1AppGetFactoryImpl()
{
   return new WinFactoryImpl();
}


void DesktopApp::InitializeResourceId()
{
   {
      window_frame::FrameSchema::ButtonIdSpace idspace;
      SetResourceId(idspace, window_frame::FrameSchema::ButtonClose, ID_VMSGUI_CLOSE);
      SetResourceId(idspace, window_frame::FrameSchema::ButtonUp, ID_VMSGUI_WINDOW_UP);
      SetResourceId(idspace, window_frame::FrameSchema::ButtonDown, ID_VMSGUI_WINDOW_DOWN);
      SetResourceId(idspace, window_frame::FrameSchema::ButtonMinimize, ID_VMSGUI_WINDOW_MINIMIZE);
      SetResourceId(idspace, window_frame::FrameSchema::ButtonMaximize, ID_VMSGUI_WINDOW_MAXIMIZE);
      SetResourceId(idspace, window_frame::FrameSchema::ButtonRestore, ID_VMSGUI_WINDOW_RESTORE);
      SetResourceId(idspace, window_frame::FrameSchema::ButtonNotifyIcon, ID_VMSGUI_NOTIFY_ICON);
   }
   {
   }
}



void DesktopApp::OnFileNew()
{
   m_pdocmanager->OnFileNew();
}