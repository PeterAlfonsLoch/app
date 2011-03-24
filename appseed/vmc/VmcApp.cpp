// vmc.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "VmcApp.h"
#include "../vmsp/resource.h"

//#include "MainFrm.h"
#include "ChildFrame.h"
//#include "IpFrame.h"
#include "vmcDoc.h"
#include "vmcView.h"

#include "MainFrame.h"

#include "MidiTracksEventsView.h"

#include "MSDoc.h"
#include "MSStaffView.h"
#include "MSFrame.h"
#include "MSMultiDocTemplate.h"
#include "XfplayerOpenFileDialog.h"

#include "bitmapwindow.h"

/*
BEGIN_MESSAGE_MAP(CVmcApp, ca77::application)
	//{{AFX_MSG_MAP(CVmcApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_HELP, OnHelp)
	ON_COMMAND(ID_HELP_FINDER, OnHelpFinder)
	ON_COMMAND(ID_FILE_NEW_FROMPLAYERVIEW, OnFileNewFromplayerview)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW_FROMPLAYERVIEW, OnUpdateFileNewFromplayerview)
	ON_COMMAND(ID_TOOLS_ALBUM, OnToolsAlbum)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_ALBUM, OnUpdateToolsAlbum)
	ON_COMMAND(ID_TOOLS_OPTIONS, OnToolsOptions)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_OPTIONS, OnUpdateToolsOptions)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, ca77::application::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, ca77::application::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, ca77::application::OnFilePrintSetup)
    ON_THREAD_MESSAGE(WM_USER, OnUserMessage)
END_MESSAGE_MAP()
*/

/////////////////////////////////////////////////////////////////////////////
// CVmcApp construction

/////////////////////////////////////////////////////////////////////////////
// The one and only CVmcApp object

CVmcApp theApp;

// This identifier was generated to be statistically unique for your app.
// You may change it if you prefer to choose a specific identifier.

// {5EE6AF21-73F4-4734-BB93-FB5AC7DAE2FF}
static const CLSID clsid =
{ 0x5ee6af21, 0x73f4, 0x4734, { 0xbb, 0x93, 0xfb, 0x5a, 0xc7, 0xda, 0xe2, 0xff } };

/////////////////////////////////////////////////////////////////////////////
// CVmcApp initialization

bool CVmcApp::InitInstance()
{
   set_locale("pt-br");
   set_style("pt-br");
    if(!ca77::application::InitInstance())
       return false;

    TRACE(_T("CVmcApp::InitInstance current thread %X\n"), GetCurrentThreadId());
//    AfxMessageBox(_T("1"));
	//m_pSplashThread = new CSplashThread(&m_pSplashThread);
	//m_pSplashThread->CreateThread();
    /*m_pSplashThread = (CSplashThread *) AfxBeginThread(RUNTIME_CLASS(CSplashThread));
    m_pSplashThread->Initialize(&m_pSplashThread);
    m_pSplashThread->m_evInitialized.Lock();
    m_pMainWnd = m_pSplashThread->m_pMainWnd;*/


	/*if(!InitializeDataCentral())
		return FALSE;*/


	
/*    m_hhookMsgFilter = SetWindowsHookEx(
        WH_MSGFILTER,        // type of hook to install
        CMenuBarV033::MessageProc,     // address of hook procedure
        m_hInstance,    // handle to application instance
        m_nThreadID   // identity of thread to install hook for
        );*/
/*    CMessageFilterMainHook::AppGetMessageFilterMainHook(&m_pmfmh);
    m_pmfmh->MessageFilterHook();*/

    {
        MEMORYSTATUS ms;
        GlobalMemoryStatus(&ms);
        if(ms.dwAvailPhys <  30 * 1024 * 1024)
        {
            AfxMessageBox(_T("Operando em modo de economia de memória"));
//            m_psavings->SetEconoMode(CSavings::SaveMemory);
        }
    }
//AfxMessageBox(_T("2"));
  	TRACE(_T("GdiGetBatchLimit %d"), GdiGetBatchLimit());
	GdiSetBatchLimit(50);

    m_XFToolTipV1ClassName = AfxRegisterWndClass(NULL, 0, 0, 0);

    m_strMessageWndClassName = AfxRegisterWndClass(NULL, 0, 0, 0);
    
//    MenuV033CreateImageMap();

  //  CRelationV001<UINT, UINT, UINT, UINT> * prel;
    //MenuV033GetImageMap(&prel);
//    m_pmenuPlayerShared = new CMenuV033(
  //      MenuV033GetImageList(),
	//	NULL,
      //  prel,
        //CFontCentral::AppGetFontCentral()->GetMenuFont());

    TCHAR lpszModuleFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, lpszModuleFilePath, MAX_PATH + 1);
	TCHAR lpszModuleFolder[MAX_PATH + 1];
	LPTSTR lpszModuleFileName;
	GetFullPathName(lpszModuleFilePath, MAX_PATH + 1, lpszModuleFolder, &lpszModuleFileName);
	string strModuleFolder(lpszModuleFolder, lpszModuleFileName - lpszModuleFolder);
	string strLib;
    string strExe;
//	strLib = ;
//    string str;
  //  str = _T("VMSIdle.tlb");
	strLib += strModuleFolder + _T("VMSIdle.tlb");
    strExe += strModuleFolder + _T("VMSIdle.exe");


    BSTR bstrLib = NULL;
    strLib.SetSysString(&bstrLib);
    BSTR bstrExe = NULL;
    strExe.SetSysString(&bstrExe);

    CComPtr<ITypeLib> spIdle;
    HRESULT hr = LoadTypeLib(bstrLib, &spIdle);
    if(SUCCEEDED(hr))
    {
        HRESULT hr = RegisterTypeLib(spIdle,bstrExe, NULL);
    }
    
/*    CMenuCentral::SetMenuCentral(new CMenuCentral());
    UINT uiaMenuV003Map [][2] =
    {
        {ID_FILE_NEW, 0},
        {ID_FILE_OPEN, 1},
        {ID_FILE_SAVE, 2},
        {ID_VIEW_FULL_SCREEN, 7},
        {ID_TOOLS_ALBUM, 8},
        {ID_VIEW_PLAYLIST, 9},
        {ID_VIEW_LYRICS, 10},
        {ID_TOOLS_MIXER, 11},
        {ID_PLAY, 12},
        {ID_STOP, 13},
        {ID_PAUSE, 14},
        {ID_NEXTSONG, 15},
        {ID_VIEW_LYRICVIEW_SPECTRUM, 18},
        {ID_PLAYER, 19},
        {ID_ALBUM_NAVIGATOR, 20},
        {ID_ALBUM_FULLLIST, 21},
        {ID_ALBUM_TREELIST, 22},
        {ID_ALBUM_SEARCHLIST, 23},
        {ID_ALBUM_RESERVESONG, 24},
        {-1, 25}, //ID_CHECK
        {ID_SCORING_ENABLE, 26},
        {ID_ALBUM_DUPLICATESLIST, 27},
        {ID_VIEW_BOUNCINGBALL, 28},
        {ID_VIEW_GRADUALFILLING, 29},
        {ID_VIEW_BOUNCE_BALL1, 30},
        {ID_VIEW_BOUNCE_BALL2, 31},
        {ID_APP_EXIT, 32},
        {ID_REMOVE_SONG, 33},
        {ID_VMSGUI_CLOSE, 32},
        {ID_VIEW_IMAGE_ZOOMALL, 34},
        {ID_VIEW_IMAGE_TILE, 35},
        {ID_VIEW_IMAGE_STRETCH, 36},
        {ID_VIEW_IMAGE_ZOOMEXTEND, 37},
        {ID_VIEW_COMPACT_SIZE, 38},
        {ID_VMSGUI_WINDOW_MINIMIZE, 39},
        {-1, -1}
    };

	CVmsGdiApi::Open();

//    m_uiaPopupMenu.Add(IDR_XFPLAYER_MENUBAR);

    CMenuCentral::GetMenuCentral()->MenuV033CreateImageMap(uiaMenuV003Map);

    CRelationV001<UINT, UINT, UINT, UINT> * prel;
    CMenuCentral::GetMenuCentral()->MenuV033GetImageMap(&prel);
	CMenuCentral::GetMenuCentral()->MenuV033GetImageList()->Create(IDB_MENUV033, 18, 1, RGB(192, 192, 192));
	CImaging::GetImaging()->CreateGrayV001ImageList(NULL, CMenuCentral::GetMenuCentral()->MenuV033GetImageListDisabled(), CMenuCentral::GetMenuCentral()->MenuV033GetImageList());
    m_pmenuPlayerShared = new CMenuV033(
        CMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
        CMenuCentral::GetMenuCentral()->MenuV033GetImageListDisabled(),
        prel,
        CFontCentral::AppGetFontCentral()->GetMenuFont());
*/

//    NONCLIENTMETRICS ncm;
  //  ncm.cbSize = sizeof(NONCLIENTMETRICS);
    //::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0);
	//VERIFY(m_pfontStandard->CreateFontIndirect(&ncm.lfMenuFont));

//    m_pilMenuV033->Create(IDB_MENUV033, 18, 1, RGB(192, 192, 192));

//    CVmsGuiDll::AppGetDll()->MenuV033GetImageList()->Create(IDB_MENUV033, 18, 1, RGB(192, 192, 192));

//    InitDirectDraw();

/*	m_pImaging = new CImaging();*/

/*
    m_pMixerCentral = new CMixerCentral();
    m_pMixerCentral->CreateEx(
        0, m_strMessageWndClassName, NULL,
        0, 0, 0, 0,
        NULL, NULL, NULL);*/

//	m_pWaveIn = new CWaveIn();

/*	{
		CRuntimeClass* pRuntimeClass = RUNTIME_CLASS(CXfplayerThreadV1);
//		base_object* pObject = pRuntimeClass->CreateObject();
//		ASSERT(pObject->IsKindOf(RUNTIME_CLASS(CXfplayerThreadV1)));
//		m_pThreadV1 = (CXfplayerThreadV1 *) pObject;
		if(!(m_pThreadV1 = (CXfplayerThreadV1 *) AfxBeginThread(pRuntimeClass)))
		{
			return FALSE;
		}

		pRuntimeClass = RUNTIME_CLASS(CXfplayerThreadV2);
//		pObject = pRuntimeClass->CreateObject();
//		ASSERT(pObject->IsKindOf(RUNTIME_CLASS(CXfplayerThreadV2)));
//		m_pThreadV2 = (CXfplayerThreadV2 *) pObject;
//		if(!m_pThreadV2->CreateThread())
//		{
//			return FALSE;
//		}
		if(!( m_pThreadV2 = (CXfplayerThreadV2 *) AfxBeginThread(pRuntimeClass)))
		{
			return FALSE;
		}

		pRuntimeClass = RUNTIME_CLASS(CXfplayerThreadV3);
//		pObject = pRuntimeClass->CreateObject();
//		ASSERT(pObject->IsKindOf(RUNTIME_CLASS(CXfplayerThreadV3)));
//		m_pThreadV3 = (CXfplayerThreadV3 *) pObject;
//		m_pThreadV3->SetThreadV1(m_pThreadV1);
//		if(!m_pThreadV3->CreateThread())
//		{
//			return FALSE;
//		}
		if(!( m_pThreadV3 = (CXfplayerThreadV3 *) AfxBeginThread(pRuntimeClass)))
		{
			return FALSE;
		}
        m_pThreadV3->SetThreadV1(m_pThreadV1);
	}

//AfxMessageBox(_T("3"));
//	m_pThreadV2->SetThreadPriority(THREAD_PRIORITY_ABOVE_NORMAL);

	//SetThreadPriority(THREAD_PRIORITY_HIGHEST);
//	SetThreadPriority(THREAD_PRIORITY_ABOVE_NORMAL);
//	SetThreadPriority(THREAD_PRIORITY_TIME_CRITICAL);
	//m_pThreadV1->PostThreadMessage(WM_USER + 1, 0, 0);
    //AfxMessageBox(_T("4"));
//	{
//		TCHAR pModuleName[MAX_PATH];
//		GetModuleFileName(NULL, pModuleName, MAX_PATH);
//		string strA(pModuleName);
//		string &strB = strA.Left(strA.ReverseFind('\\') + 1);
//		strB += "ImageLoader.exe";
//		_tcsncpy(pModuleName, strB, MAX_PATH);
//		STARTUPINFO si;
//		memset(&si, 0, sizeof(si));
//		if(!CreateProcess(
//			pModuleName,
//			NULL,
//			NULL,
//			NULL,
//			TRUE,
//			//REALTIME_PRIORITY_CLASS,
///			IDLE_PRIORITY_CLASS,
//			NULL,
//			NULL,
///			&si,
//			&m_piImageLoader))
//		{
//			DWORD dw = GetLastError();
//			return FALSE;
//		}
//	}


*/

//	HRESULT  ddrval = DirectDrawCreate( NULL, &m_lpDirectDraw, NULL );
  //  if( ddrval != DD_OK )
//    {
//		TRACE(_T("Failed to init directdraw"));
//		return FALSE;
  //  }

	
	m_XFViewClassName = AfxRegisterWndClass(
		CS_DBLCLKS |
		CS_OWNDC,
		0, 0, 0);
	m_uiMidiOutDevice = MIDI_MAPPER;
    m_uiWaveInDevice = WAVE_MAPPER;
//	m_hHeap = HeapCreate(0, 1, 0);
//	if(!m_hHeap)
//	{
//		AfxMessageBox(_T("Out Of Memory"), MB_OK, 0);
//		return FALSE;
//	}

	SetRegistryKey(_T("Veriwell"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

//	MultipleDocumentTemplate* pDocTemplate;
//	pDocTemplate = new MultipleDocumentTemplate(
//		IDR_VMCTYPE,
//		RUNTIME_CLASS(CVmcDoc),
//		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
//		RUNTIME_CLASS(CVmcView));
//	pDocTemplate->SetContainerInfo(IDR_VMCTYPE_CNTR_IP);
//	pDocTemplate->SetServerInfo(
//		IDR_VMCTYPE_SRVR_EMB, IDR_VMCTYPE_SRVR_IP,
//		RUNTIME_CLASS(CVmcInPlaceFrame));
//	AddDocTemplate(pDocTemplate);

   CMSMultiDocTemplate* pMSMultiDocTemplate;
   pMSMultiDocTemplate = new CMSMultiDocTemplate(
      this,
      IDR_MUSICALSTUDIO,
      &typeid(CMSDoc),
      &typeid(CMSFrame), // custom MDI child frame
      &typeid(CMSStaffView));
   AddDocTemplate(pMSMultiDocTemplate);
   m_pMainDocTemplate = pMSMultiDocTemplate;

//    MultipleDocumentTemplate* pMidiDocTemplate;
//	pMidiDocTemplate = new MultipleDocumentTemplate(
//		IDR_MIDIEVENTS,
//		RUNTIME_CLASS(CMidiDoc),
//		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
//		RUNTIME_CLASS(CMidiTracksEventsView));
//	pMSMultiDocTemplate->SetServerInfo(
//		IDR_MUSICALSTUDIO_SERVER_EMBEDDING, IDR_MUSICALSTUDIO_SERVER_INPLACE,
//		RUNTIME_CLASS(CMSInPlaceFrame));
//	AddDocTemplate(pMidiDocTemplate);
//    m_pMidiDocTemplate = pMidiDocTemplate;
	m_pMidiDocTemplate = NULL;

	// Connect the COleTemplateServer to the document template.
	//  The COleTemplateServer creates new documents on behalf
	//  of requesting OLE containers by using information
	//  specified in the document template.
//	m_server.ConnectTemplate(clsid, pDocTemplate, FALSE);
	m_server.ConnectTemplate(clsid, pMSMultiDocTemplate, FALSE);

	// Register all OLE server factories as running.  This enables the
	//  OLE libraries to create objects from other applications.
	COleTemplateServer::RegisterAll();
		// Note: MDI applications register all server objects without regard
		//  to the /Embedding or /Automation on the command line.

   CMainFrame * pMainFrame = new CMainFrame(this);
   pMainFrame->LoadFrame(IDR_MAINFRAME);

	// create main MDI Frame window
	pMSMultiDocTemplate->OpenDocumentFile(NULL, FALSE, pMainFrame);

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Check to see if launched as OLE server
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Application was run with /Embedding or /Automation.  Don't show the
		//  main window in this case.
/*    m_pSplashThread->Kill();*/
		// Application was run with /Embedding or /Automation.  Don't show the
		//  main window in this case.
        m_evInitialized.SetEvent();
        //__asm
        //{
        //    int 3
        //}
			return TRUE;
	}

	// When a server application is launched stand-alone, it is a good idea
	//  to update the system registry in case it has been damaged.
	m_server.UpdateRegistry(OAT_DOC_OBJECT_SERVER);
	COleObjectFactory::UpdateRegistryAll();

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
   if(m_nCmdShow == -1)
   {
	   pMainFrame->ShowWindow(5);
   }
   else
   {
      pMainFrame->ShowWindow(m_nCmdShow);
   }
	pMainFrame->UpdateWindow();
//	m_pSplashThread->Kill();
	//m_pThreadV1->PostThreadMessage(WM_USER + 2, 0, 0);
//    {
//		CRuntimeClass* pRuntimeClass = RUNTIME_CLASS(CMainFrame);
//		base_object* pObject = pRuntimeClass->CreateObject();
//		//ASSERT(pObject->IsKindOf(RUNTIME_CLASS(CXfplayerThreadV1)));
//		//m_pThreadV1 = (CXfplayerThreadV1 *) pObject;
//	    CMainFrame * pOtherFrame = (CMainFrame *) pObject;
  //      pOtherFrame->LoadFrame(IDR_MAINFRAME);
    //    pOtherFrame->ShowWindow(SW_SHOWNORMAL);
    //}
//	Sleep(1000);
//	m_pMainWnd->ShowWindow(SW_SHOWNORMAL);
    RegisterShellExtension();
//    m_pwelcomedlg = new CWelcomeDialog();
  //  m_pwelcomedlg->Create(IDD_WELCOME);
//    m_pwelcomedlg->ShowWindow(SW_SHOWNORMAL);
    m_evInitialized.SetEvent();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CVmcApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CVmcApp message handlers


AFX_STATIC_DATA const TCHAR _afxShellOpenFmt[] = _T("%s\\shell\\open\\%s");
AFX_STATIC_DATA const TCHAR _afxShellPrintFmt[] = _T("%s\\shell\\print\\%s");
AFX_STATIC_DATA const TCHAR _afxShellPrintToFmt[] = _T("%s\\shell\\printto\\%s");
AFX_STATIC_DATA const TCHAR _afxDefaultIconFmt[] = _T("%s\\DefaultIcon");
AFX_STATIC_DATA const TCHAR _afxShellNewFmt[] = _T("%s\\ShellNew");

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

// recursively remove a registry key if and only if it has no subkeys

BOOL AFXAPI _AfxDeleteRegKey(LPCTSTR lpszKey)
{
	// copy the string
	LPTSTR lpszKeyCopy = _tcsdup(lpszKey);
	LPTSTR lpszLast = lpszKeyCopy + lstrlen(lpszKeyCopy);

	// work until the end of the string
	while (lpszLast != NULL)
	{
		*lpszLast = '\0';
		lpszLast = _tcsdec(lpszKeyCopy, lpszLast);

		// try to open that key
		HKEY hKey;
		if (::RegOpenKey(HKEY_CLASSES_ROOT, lpszKeyCopy, &hKey) != ERROR_SUCCESS)
			break;

		// enumerate the keys underneath
		TCHAR szScrap[_MAX_PATH+1];
		DWORD dwLen = _tcslen(szScrap);
		BOOL bItExists = FALSE;

		if (::RegEnumKey(hKey, 0, szScrap, dwLen) == ERROR_SUCCESS)
			bItExists = TRUE;
		::RegCloseKey(hKey);

		// found one?  quit looping
		if (bItExists)
			break;

		// otherwise, delete and find the previous backwhack
		::RegDeleteKey(HKEY_CLASSES_ROOT, lpszKeyCopy);
		lpszLast = _tcsrchr(lpszKeyCopy, '\\');
	}

	// release the string and return
	free(lpszKeyCopy);
	return TRUE;
}


CVmcApp::CVmcApp():
   m_evInitialized(FALSE, TRUE)
{
   m_signalAllocation.connect(this, &CVmcApp::_001Alloc);
//	m_pActiveDocument = NULL;
//	m_pPlayingDocument = NULL;
	m_pMainDocTemplate = NULL;
//    m_pPlayerDocTemplate = NULL;
    m_pMidiDocTemplate = NULL;
	m_pThreadV1 = NULL;
	m_pThreadV2 = NULL;
	m_pThreadV3 = NULL;

	m_pSplashThread = NULL;
    m_pwelcomedlg = NULL; 
//	m_pdbcentral = NULL;
    
    //m_hPlayerMenuShared = NULL;
    m_hPlayerAccelTable = NULL;
    m_pmenuPlayerShared = NULL;
//    m_pilMenuV033 = new CImageList();

	m_pImaging = NULL;

//    m_pAlbumThread = NULL;
//	m_lpDirectDraw = NULL;
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CVmcApp object


// This identifier was generated to be statistically unique for your app.
// You may change it if you prefer to choose a specific identifier.

// {F53B78E0-A6F5-41CF-B4FB-9F9FE49DD416}
//static const CLSID clsid =
//{ 0xf53b78e0, 0xa6f5, 0x41cf, { 0xb4, 0xfb, 0x9f, 0x9f, 0xe4, 0x9d, 0xd4, 0x16 } };

/////////////////////////////////////////////////////////////////////////////
// CVmcApp initialization

/*BOOL CVmcApp::InitInstance()
{
    //__asm
    //{
    //    int 3
    //}
//    AfxDebugBreak();


//	if (!InitATL())
//		return FALSE;


	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Veriwell"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)


	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
    
    //AfxMessageBox(_T("5"));

	CXfplayerSingleDocTemplate* pPlayerSingleDocTemplate;
	pPlayerSingleDocTemplate = new CXfplayerSingleDocTemplate(
		IDR_XFPLAYER,
		RUNTIME_CLASS(CXfplayerDoc),
		RUNTIME_CLASS(CKaraokeSDIFrame),       // main SDI frame window
		RUNTIME_CLASS(CXfplayerView));
	m_pPlayerDocTemplate = (CXfplayerSingleDocTemplate*) pPlayerSingleDocTemplate;
	pPlayerSingleDocTemplate->SetServerInfo(
		IDR_XFPLAYER_SERVER_EMBEDDING, IDR_XFPLAYER_SERVER_INPLACE,
		RUNTIME_CLASS(CInPlaceFrame));
	AddDocTemplate(pPlayerSingleDocTemplate);

//    pPlayerSingleDocTemplate = new CXfplayerSingleDocTemplate(
//		IDR_SOFTKARAOKE,
//		RUNTIME_CLASS(CXfplayerDoc),
//		RUNTIME_CLASS(CKaraokeSDIFrame),       // main SDI frame window
//		RUNTIME_CLASS(CXfplayerView));
//	m_pPlayerDocTemplate = (CXfplayerSingleDocTemplate*) pPlayerSingleDocTemplate;
//	pPlayerSingleDocTemplate->SetServerInfo(
//		IDR_XFPLAYER_SERVER_EMBEDDING, IDR_XFPLAYER_SERVER_INPLACE,
//		RUNTIME_CLASS(CInPlaceFrame));
//	AddDocTemplate(pPlayerSingleDocTemplate);


    MultipleDocumentTemplate* pPlaylistDocTemplate;
	pPlaylistDocTemplate = new MultipleDocumentTemplate(
		IDR_PLAYLIST,
		RUNTIME_CLASS(CPlaylistDoc),
		RUNTIME_CLASS(CPlaylistFrame), // custom MDI child frame
		RUNTIME_CLASS(CPlaylistView));
//	pMSMultiDocTemplate->SetServerInfo(
//		IDR_MUSICALSTUDIO_SERVER_EMBEDDING, IDR_MUSICALSTUDIO_SERVER_INPLACE,
//		RUNTIME_CLASS(CMSInPlaceFrame));
	AddDocTemplate(pPlaylistDocTemplate);
    m_pPlaylistDocTemplate = pPlaylistDocTemplate;

    // Midi Document Template
    


    // Connect the COleTemplateServer to the document template.
	//  The COleTemplateServer creates new documents on behalf
	//  of requesting OLE containers by using information
	//  specified in the document template.
	m_server.ConnectTemplate(clsid, pMSMultiDocTemplate, FALSE);

	// Register all OLE server factories as running.  This enables the
	//  OLE libraries to create objects from other applications.
	COleTemplateServer::RegisterAll();
	_Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, 
		REGCLS_MULTIPLEUSE);

		// Note: MDI applications register all server objects without regard
		//  to the /Embedding or /Automation on the command line.
//AfxMessageBox(_T("6"));
	// create main MDI Frame window
    CDataCentral::m_pdbcentral = new CDBCentral();
    m_pdbcentral = CDataCentral::AppGetDBCentral();

    string strCompactDatabase = GetProfileString(_T("Database"), _T("Compact"));
    if(!strCompactDatabase.is_empty())
    {
        m_pdbcentral->CompactDatabase(strCompactDatabase);
        WriteProfileString(_T("Database"), _T("Compact"), _T(""));
    }

    //AfxMessageBox(_T("7"));
	m_pdbcentral->Initialize(m_hInstance);
	//AfxMessageBox(_T("7.1"));
	LoadAppSettings();
    //AfxMessageBox(_T("7.2"));
	
    //AfxMessageBox(_T("7.3"));
	CRuntimeClass* pRuntimeClass = RUNTIME_CLASS(CMainFrame);
	base_object* pObject = pRuntimeClass->CreateObject();
	ASSERT(pObject->IsKindOf(RUNTIME_CLASS(CMainFrame)));
	CMainFrame* pMainFrame = (CMainFrame *) pObject;
    //AfxMessageBox(_T("7.4"));
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

    //AfxMessageBox(_T("8"));
	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

    _Module.UpdateRegistryFromResource(IDR_VMS, TRUE);
	_Module.RegisterServer(TRUE);


	// Check to see if launched as OLE server
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
        m_pSplashThread->Kill();
		// Application was run with /Embedding or /Automation.  Don't show the
		//  main window in this case.
        m_evInitialized.SetEvent();
        //__asm
        //{
        //    int 3
        //}
		return TRUE;
	}
	m_pdbcentral->SongsPostBuildAlbumMessage(
        AfxGetApp(),
        (SongsAlbum::EBuildSongsAlbumOperation)
        (SongsAlbum::eBuildSongsAlbumDeleteNotFound |
        SongsAlbum::eBuildSongsAlbumAddNew |
        SongsAlbum::eBuildSongsAlbumCreateSearchReferences),
        false);

	// When a server application is launched stand-alone, it is a good idea
	//  to update the system registry in case it has been damaged.
	m_server.UpdateRegistry(OAT_DOC_OBJECT_SERVER);
	COleObjectFactory::UpdateRegistryAll();

    //AfxMessageBox(_T("9"));
	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();
    pMainFrame->ActivateFrame();
//    m_pPlayerDocTemplate->OpenDocumentFile(NULL);
	// Connect the COleTemplateServer to the document template.
	//  The COleTemplateServer creates new documents on behalf
	//  of requesting OLE containers by using information
	//  specified in the document template.
//	m_server.ConnectTemplate(clsid, pDocTemplate, TRUE);
		// Note: SDI applications register server objects only if /Embedding
		//   or /Automation is present on the command line.

	// Enable DDE Execute open
//	EnableShellOpen();
//	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
//	CCommandLineInfo cmdInfo;
//	ParseCommandLine(cmdInfo);

    _Module.UpdateRegistryFromResource(IDR_XFPLAYER, TRUE);
//	_Module.RegisterServer(TRUE);


	// Check to see if launched as OLE server
//	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
//	{
//		// Register all OLE server (factories) as running.  This enables the
		//  OLE libraries to create objects from other applications.
//		COleTemplateServer::RegisterAll();
//	_Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, 
//		REGCLS_MULTIPLEUSE);


		// Application was run with /Embedding or /Automation.  Don't show the
		//  main window in this case.
//		return TRUE;
//	}

	// When a server application is launched stand-alone, it is a good idea
	//  to update the system registry in case it has been damaged.
//	m_server.UpdateRegistry(OAT_DISPATCH_OBJECT);
//	COleObjectFactory::UpdateRegistryAll();

	// Dispatch commands specified on the command line
//	if (!ProcessShellCommand(cmdInfo))
//		return FALSE;
	

    /*
     * create the main DirectDraw object
     */

	// The one and only window has been initialized, so show and update it.

//	m_pMainWnd->ShowWindow(SW_SHOWNORMAL);
//	m_pMainWnd->UpdateWindow();
	// Enable drag/drop open
/*	m_pMainWnd->DragAcceptFiles();
//



	
		// Create CFont used to test the view.

//	LOGFONT                 lf;
//    HFONT                   hFont;
//    HFONT                   h;
//    LONG                    FormatWidth;
//    LONG                    ScaledClientWidth;
//    LONG                    ScaledClientHeight;
//    LONG                    AspectN;
//    LONG                    AspectD;
//    int                     nPosX;
//    UINT                    cb;
//    UINT                    ii;
//    UINT                    jj;
//    SIZE                    size;

//    ScaledClientHeight =  ((lpRect->bottom - lpRect->top)) * 3 / 4;
//    ScaledClientWidth  =  ((lpRect->right  - lpRect->left)) * 3 / 4;
    
	return TRUE;
}*/



/////////////////////////////////////////////////////////////////////////////
// CVmcApp message handlers





int CALLBACK BrowseCallbackProc(
    HWND hwnd, 
    UINT uMsg, 
    LPARAM lParam, 
    LPARAM lpData
    )
{
	if(lParam == 1) // COptionsImageDirectory 
	{

	}
	return 0;
}




int CVmcApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
//    UnhookWindowsHookEx(
  //      m_hhookMsgFilter
    //    );
    if(m_pmfmh != NULL)
    {
//        m_pmfmh->MessageFilterUnhook();
//        delete m_pmfmh;
        m_pmfmh = NULL;
    }
    //MessageFilterUnhook();
 
//    m_pdbcentral->SetBuildAlbumThreadsCancelFlag();

	SetThreadPriority(THREAD_PRIORITY_HIGHEST);
    
  /*  if(m_pdbcentral != NULL)
    {
        m_pdbcentral->Close();
	    delete m_pdbcentral;
//        CDataCentral::m_pdbcentral = NULL;
    }*/

/*    if(m_pWaveIn != NULL)
    {
	    delete m_pWaveIn;
    }
    if(m_pMixerCentral != NULL)
    {
        m_pMixerCentral->SendMessage(WM_CLOSE);
        delete m_pMixerCentral;
        m_pMixerCentral = NULL;
    }
*/
    if(m_pfontcentral != NULL)
    {
//        delete m_pfontcentral;
        m_pfontcentral = NULL;
    }
/*	m_pThreadV1->SetThreadPriority(THREAD_PRIORITY_NORMAL);
	m_pThreadV1->PostThreadMessage(WM_QUIT, 0, 0);

	m_pThreadV2->SetThreadPriority(THREAD_PRIORITY_NORMAL);
	m_pThreadV2->PostThreadMessage(WM_QUIT, 0, 0);
	
	m_pThreadV3->SetThreadPriority(THREAD_PRIORITY_NORMAL);
	m_pThreadV3->PostThreadMessage(WM_QUIT, 0, 0);

    if(m_pImaging != NULL)
        delete m_pImaging;

    if(m_pmenuPlayerShared != NULL)
        delete m_pmenuPlayerShared;*/

//    if(m_pilMenuV033 != NULL)
  //      delete m_pilMenuV033;





	return ca77::application::ExitInstance();

}





void AddStringLines(LPCTSTR lpStr, AStrArray *pArray)
{
	string str(lpStr);
	int nIndex, nLastIndex;
	nLastIndex = 0;
	while((nIndex = str.Find(_T("\n"), nLastIndex)) >= 0)
	{
		pArray->Add(str.Mid(nLastIndex, nIndex - nLastIndex));
		nLastIndex = nIndex + 1;
	}
	if(nLastIndex < str.GetLength())
	{
		pArray->Add(str.Mid(nLastIndex));
	}
}

void CVmcApp::Exit()
{

    ASSERT(m_pMainWnd != NULL);
    m_pMainWnd->SendMessage(WM_CLOSE);

}

void CVmcApp::OnFileOpen() 
{
	// TODO: Add your command handler code here
//	ca77::application::OnFileOpen();
//	return;
	CXfplayerOpenFileDialog dlgFile;

	string fileName;
	if(!dlgFile.DoPromptFileName(fileName, IDS_XFPLAYER_OPENFILETITLE, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST))
		return;

    
	ca77::application::OpenDocumentFile(fileName);


}

void CVmcApp::OnFileNew() 
{
	// TODO: Add your command handler code here
	//ca77::application::OnFileNew();
	m_pMainDocTemplate->OpenDocumentFile(NULL);
}


CWaveIn * CVmcApp::GetWaveIn()
{
	return m_pWaveIn;
}

//LPDIRECTDRAW CVmcApp::GetDirectDraw()
//{
//	return m_lpDirectDraw;
//}


/*CTypedPtrArray <CPtrArray, CXfplayerFont *> *
	CVmcApp::GetLyricViewFonts()
{
	return m_pLyricViewFonts;
}

CTypedPtrArray <CPtrArray, CXfplayerFont *> *
	CVmcApp::GetTitleFonts()
{
	return m_pTitleFonts;
}

CTypedPtrArray <CPtrArray, CXfplayerFont *> *
	CVmcApp::GetSubTitleFonts()
{
	return m_pSubTitleFonts;
}

/*CFont * CVmcApp::GetMenuFont()
{
    return m_pfontMenu;
}*/

/*void CVmcApp::CreateLyricViewFonts()
{

		LOGFONT                 lf;
    
    memset(&lf, 0, sizeof(lf));
//	CDC *pDC = GetDC();
//	pDC->SetMapMode(MM_TEXT);
//	RECT rect;
//	GetClientRect(&rect);
	CDC dc;
	dc.CreateCompatibleDC(NULL);
    lf.lfHeight         = (int)-MulDiv(36, dc.GetDeviceCaps(LOGPIXELSY), 72);
	lf.lfWeight         = FW_BOLD;
    lf.lfCharSet        = ANSI_CHARSET;
    lf.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
    lf.lfQuality        = PROOF_QUALITY;
    lf.lfPitchAndFamily = FF_ROMAN|DEFAULT_PITCH;
    lstrcpy(lf.lfFaceName, _T("Tahoma"));

	CFont font;
	font.CreateFontIndirect(&lf);
	CFont *pFontOld = dc.SelectObject(&font);
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
	
	lf.lfWidth = tm.tmAveCharWidth;
	CFont * pFont = new CFont;
	pFont->CreateFontIndirect(&lf);
	CXfplayerFont * pPlayerFont = new CXfplayerFont();
	pPlayerFont->SetFont(pFont);
	m_pLyricViewFonts->Add(pPlayerFont);
	
	lf.lfWidth = (long) (tm.tmAveCharWidth * 0.90);
	pFont = new CFont;
	pFont->CreateFontIndirect(&lf);
	pPlayerFont = new CXfplayerFont();
	pPlayerFont->SetFont(pFont);
	m_pLyricViewFonts->Add(pPlayerFont);

	lf.lfWidth = (long) (tm.tmAveCharWidth * 0.80);
	pFont = new CFont;
	pFont->CreateFontIndirect(&lf);
	pPlayerFont = new CXfplayerFont();
	pPlayerFont->SetFont(pFont);
	m_pLyricViewFonts->Add(pPlayerFont);

	lf.lfWidth = (long) (tm.tmAveCharWidth * 0.70);
	pFont = new CFont;
	pFont->CreateFontIndirect(&lf);
	pPlayerFont = new CXfplayerFont();
	pPlayerFont->SetFont(pFont);
	m_pLyricViewFonts->Add(pPlayerFont);

	lf.lfWidth = (long) (tm.tmAveCharWidth * 0.60);
	pFont = new CFont;
	pFont->CreateFontIndirect(&lf);
	pPlayerFont = new CXfplayerFont();
	pPlayerFont->SetFont(pFont);
	m_pLyricViewFonts->Add(pPlayerFont);
	
   memset(&lf, 0, sizeof(lf));
//	CDC *pDC = GetDC();
//	pDC->SetMapMode(MM_TEXT);
//	RECT rect;
//	GetClientRect(&rect);

	lf.lfHeight         = (int)-MulDiv(28, dc.GetDeviceCaps(LOGPIXELSY), 72);
	lf.lfWidth			= 0;
	lf.lfWeight         = FW_BOLD;
    lf.lfCharSet        = ANSI_CHARSET;
    lf.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
    lf.lfQuality        = PROOF_QUALITY;
    lf.lfPitchAndFamily = FF_ROMAN|DEFAULT_PITCH;
    lstrcpy(lf.lfFaceName, _T("Tahoma"));

	font.DeleteObject();
	font.CreateFontIndirect(&lf);
	dc.SelectObject(&font);
	dc.GetTextMetrics(&tm);
	
	lf.lfWidth = tm.tmAveCharWidth;
	pFont = new CFont;
	pFont->CreateFontIndirect(&lf);
	pPlayerFont = new CXfplayerFont();
	pPlayerFont->SetFont(pFont);
	m_pTitleFonts->Add(pPlayerFont);
	
	lf.lfWidth = (long) (tm.tmAveCharWidth * 0.90);
	pFont = new CFont;
	pFont->CreateFontIndirect(&lf);
	pPlayerFont = new CXfplayerFont();
	pPlayerFont->SetFont(pFont);
	m_pTitleFonts->Add(pPlayerFont);

	lf.lfWidth = long (tm.tmAveCharWidth * 0.80);
	pFont = new CFont;
	pFont->CreateFontIndirect(&lf);
	pPlayerFont = new CXfplayerFont();
	pPlayerFont->SetFont(pFont);
	m_pTitleFonts->Add(pPlayerFont);

	lf.lfWidth = long (tm.tmAveCharWidth * 0.70);
	pFont = new CFont;
	pFont->CreateFontIndirect(&lf);
	pPlayerFont = new CXfplayerFont();
	pPlayerFont->SetFont(pFont);
	m_pTitleFonts->Add(pPlayerFont);

	lf.lfWidth = long (tm.tmAveCharWidth * 0.60);
	pFont = new CFont;
	pFont->CreateFontIndirect(&lf);
	pPlayerFont = new CXfplayerFont();
	pPlayerFont->SetFont(pFont);
	m_pTitleFonts->Add(pPlayerFont);

	   memset(&lf, 0, sizeof(lf));
//	CDC *pDC = GetDC();
//	pDC->SetMapMode(MM_TEXT);
//	RECT rect;
//	GetClientRect(&rect);
    lf.lfHeight         = (int)-MulDiv(21, dc.GetDeviceCaps(LOGPIXELSY), 72);
	lf.lfWidth			= 0;
	lf.lfWeight         = FW_NORMAL;
    lf.lfCharSet        = ANSI_CHARSET;
    lf.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
    lf.lfQuality        = PROOF_QUALITY;
    lf.lfPitchAndFamily = FF_ROMAN|DEFAULT_PITCH;
    lstrcpy(lf.lfFaceName, _T("Tahoma"));

	font.DeleteObject();	
	font.CreateFontIndirect(&lf);
	dc.SelectObject(&font);
	dc.GetTextMetrics(&tm);
	
	lf.lfWidth = tm.tmAveCharWidth;
	pFont = new CFont;
	pFont->CreateFontIndirect(&lf);
	pPlayerFont = new CXfplayerFont();
	pPlayerFont->SetFont(pFont);
	m_pSubTitleFonts->Add(pPlayerFont);
	
	lf.lfWidth = long (tm.tmAveCharWidth * 0.90);
	pFont = new CFont;
	pFont->CreateFontIndirect(&lf);
	pPlayerFont = new CXfplayerFont();
	pPlayerFont->SetFont(pFont);
	m_pSubTitleFonts->Add(pPlayerFont);

	lf.lfWidth = long (tm.tmAveCharWidth * 0.80);
	pFont = new CFont;
	pFont->CreateFontIndirect(&lf);
	pPlayerFont = new CXfplayerFont();
	pPlayerFont->SetFont(pFont);
	m_pSubTitleFonts->Add(pPlayerFont);

	lf.lfWidth = long (tm.tmAveCharWidth * 0.70);
	pFont = new CFont;
	pFont->CreateFontIndirect(&lf);
	pPlayerFont = new CXfplayerFont();
	pPlayerFont->SetFont(pFont);
	m_pSubTitleFonts->Add(pPlayerFont);

	lf.lfWidth = long (tm.tmAveCharWidth * 0.60);
	pFont = new CFont;
	pFont->CreateFontIndirect(&lf);
	pPlayerFont = new CXfplayerFont();
	pPlayerFont->SetFont(pFont);
	m_pSubTitleFonts->Add(pPlayerFont);
	
    lf.lfHeight         = (int)-MulDiv(12, dc.GetDeviceCaps(LOGPIXELSY), 72);
	lf.lfWeight         = FW_BOLD;
    lf.lfCharSet        = ANSI_CHARSET;
    lf.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
    lf.lfQuality        = PROOF_QUALITY;
    lf.lfPitchAndFamily = FF_ROMAN|DEFAULT_PITCH;
    lstrcpy(lf.lfFaceName, _T("Tahoma"));

    font.DeleteObject();	
	font.CreateFontIndirect(&lf);
	dc.SelectObject(&font);
	dc.GetTextMetrics(&tm);

    lf.lfWidth = long (tm.tmAveCharWidth);
	pFont = new CFont;
	pFont->CreateFontIndirect(&lf);
	pPlayerFont = new CXfplayerFont();
	pPlayerFont->SetFont(pFont);
    m_lpSongLabelFont = pPlayerFont;
    
    lf.lfWidth = long (tm.tmAveCharWidth);
	pFont = new CFont;
	pFont->CreateFontIndirect(&lf);
	pPlayerFont = new CXfplayerFont();
	pPlayerFont->SetFont(pFont);
    m_lpSongListFont = pPlayerFont;


	dc.SelectObject(pFontOld);
	font.DeleteObject();
	dc.DeleteDC();

}*/

	
//CXfplayerModule _Module;
//CComModule _Module;

//BEGIN_OBJECT_MAP(ObjectMap)
//END_OBJECT_MAP()

//LONG CXfplayerModule::Unlock()
//{
//	AfxOleUnlockApp();
//	return 0;
//}

//LONG CXfplayerModule::Lock()
//{
//	AfxOleLockApp();
//	return 1;
//}


//BOOL CVmcApp::InitATL()
//{
//	m_bATLInited = TRUE;
//
//	_Module.Init(ObjectMap, AfxGetInstanceHandle());
//	_Module.dwThreadID = GetCurrentThreadId();
//
//	return TRUE;
//
//}

BOOL CVmcApp::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
    if(pMsg->hwnd == NULL)
    {
	    switch(pMsg->message)
		{
		case WM_DISPLAYCHANGE:
			int i;
			i = 2;
			break;
        case VMSM_ECONOMODECHANGE:
            OnChangeEconoMode();
            return TRUE;
        //case WM_USER:
/*            {
                switch(pMsg->wParam)
                {
                case 21:
//                    ASSERT(FALSE);
  //                  //ReserveSong_(pMsg->lParam);
                    GetPlayerDocTemplate()->ReserveSong(pMsg->lParam, false, true);
                    break;
                case 22:
                    BaseDWORDArray * pdwa = (BaseDWORDArray *) pMsg->lParam;
                    GetPlayerDocTemplate()->ReserveSong((LPINT) &pdwa->GetData()[1], pdwa->GetAt(0), false, true);
                    delete pdwa;
                    break;
                }
                  if(pMsg->wParam == 1)
                {
                    if(pMsg->lParam == 1)
                    {
                        m_pdbcentral->OnSongsUpdated();
                    }
                    else if(pMsg->lParam == 3)
                    {
                        m_pdbcentral->OnSongsInfoV001Updated();
                    }
                }
                  }
            break;*/
        case WM_USER + 113:
            //ASSERT(FALSE);
            ViewToolsAlbum();
            //m_pAlbumDocTemplate->OpenDocumentFile(NULL);
            return TRUE;
		default:
			break;
		}
    }
    if(pMsg->message == WM_USER + 1)
	{
//		m_pMainWnd->SetForegroundWindow();
//		m_pMainWnd->SetActiveWindow();
//		m_pMainWnd->BringWindowToTop();
		return TRUE;
	}
/*    else if(pMsg->message == WM_USER)
	{
        if(pMsg->wParam == 1)
        {
            if(pMsg->lParam == 1)
            {
                m_pdbcentral->OnSongsUpdated();
            }
            else if(pMsg->lParam == 3)
            {
                m_pdbcentral->OnSongsInfoV001Updated();
            }
        }
    }*/
/*	else if(pMsg->message == VMSM_EXCEPTION)
	{
		if(pMsg->wParam == EXCEPTION_OLEDB)
		{
			COLEDBException * pE = (COLEDBException * ) pMsg->lParam;
		    CDBErrorDialog dlg;
		    dlg.Init(pE->m_spUnk, pE->m_iid);
		    dlg.DoModal();
		    pE->Delete();
			return TRUE;
		}
	}*/
    else if(pMsg->message == VMSM_V001)
    {
        if(pMsg->hwnd == NULL)
        {
            if(pMsg->wParam == NOTIFY_BUILDALBUMPROGRESSUPDATE ||
                pMsg->wParam == NOTIFY_BUILDALBUMSTATUSUPDATE ||
                pMsg->wParam == NOTIFY_BUILDALBUMTASKSUPDATE)
            {
                ASSERT(FALSE);
                CDBCentral* pDataCentral = GetDBCentral();
/*                if(pDataCentral->IsBuildingSongsAlbum())
                {
                    CCriticalSection *pcs;
                    CDBBuildAlbumThreadData * lpdata =
                        pDataCentral->GetActiveBuildAlbumThreadData(&pcs);
                    if(lpdata != NULL)
                    {
                        lpdata->m_ptaskdlg->PostMessage(VMSM_V001, pMsg->wParam, 0);
                    }
                    pcs->Unlock();
                }
                else
                {
                //    ASSERT(FALSE);
                }*/
            }
            else if(pMsg->wParam == NOTIFY_BUILDALBUMDELETE)
            {
/*                CDBCentral* pDataCentral = GetDBCentral();
                pDataCentral->DeleteBuildAlbumThreadData((CDBBuildAlbumThreadData *) pMsg->lParam);*/
            }
            else if(pMsg->wParam == NOTIFY_BUILDALBUMFINISHED)
            {
                /*CDBCentral* pDataCentral = GetDBCentral();
                pDataCentral->OnFinishedBuildAlbum((CDBBuildAlbumThreadData *) pMsg->lParam);*/
            }
            return TRUE;
        }
    }
	return ca77::application::PreTranslateMessage(pMsg);
}

CSplashThread * CVmcApp::GetSplashThread()
{
	return m_pSplashThread;
}


void CVmcApp::LoadAppSettings()
{
//	if(!m_pdbcentral->IsWorking())
//		return;
/*	CDBLongSet * pLongsSet = m_pdbcentral->GetDBLongSet();
//	if(pLongsSet->m_spRowset != NULL)
//	{
		if(!pLongsSet->Load(_T("Images"), _T("ChangeTime"), &m_iBackgroundUpdateMillis))
			m_iBackgroundUpdateMillis =  BACKGROUND_IMAGE_CHANGE_DEFAULT_SECONDS * 1000;
		else
			m_iBackgroundUpdateMillis *= 1000;
//	}
//	else
//	{
//		m_iBackgroundUpdateMillis = BACKGROUND_IMAGE_CHANGE_DEFAULT_SECONDS * 1000;
//	}

	if(m_iBackgroundUpdateMillis < (BACKGROUND_IMAGE_CHANGE_MIN_SECONDS * 1000))
	{
		m_iBackgroundUpdateMillis = BACKGROUND_IMAGE_CHANGE_MIN_SECONDS * 1000;
	}

	//int iValue = GetProfileInt(_T("Initialization"), _T("Initialized"), -1);
	//if(iValue == -1)
	//{
		// if GetProfileInt returned -1, it means that the entry was not
		// found
	//	WriteProfileInt(_T("Initialization"), _T("Initialized"), 1);
	int iInitialized;
	if(!pLongsSet->Load(_T("Initialization"), _T("Initialized"), &iInitialized))
	{
        bool bAdd;
		pLongsSet->Save(_T("Initialization"), _T("Initialized"), 1);
		TCHAR lpszModuleFilePath[MAX_PATH + 1];
		GetModuleFileName(NULL, lpszModuleFilePath, MAX_PATH + 1);
		TCHAR lpszModuleFolder[MAX_PATH + 1];
		LPTSTR lpszModuleFileName;
		GetFullPathName(lpszModuleFilePath, MAX_PATH + 1, lpszModuleFolder, &lpszModuleFileName);
		string strModuleFolder(lpszModuleFolder, lpszModuleFileName - lpszModuleFolder);
		string strPath;
		strPath = strModuleFolder;
        string str;
        str.LoadString(IDS_FOLDER_IMAGES);
		strPath += str;
		CDBImageDirectorySet * pImagesDirsSet = m_pdbcentral->GetImageDirSet();
        bAdd = true;
		if(pImagesDirsSet->m_spRowsetChange == NULL)
        {
            m_pdbcentral->OpenImagesDirsSet();
            if(pImagesDirsSet->m_spRowsetChange == NULL)
            {
                AfxMessageBox(_T("CVmcApp::LoadAppSettings() Fail 1000"));
                bAdd = false;
            }

        }
        if(bAdd)
        {
            TCHAR buffer[MAX_PATH * 2];
            GetWindowsDirectory(buffer, sizeof(buffer));
            string strWallpaper(buffer);
            strWallpaper += "\\Web\\Wallpaper";
		    pImagesDirsSet->Add(strPath);
            pImagesDirsSet->Add(strWallpaper);
            pImagesDirsSet->Add(buffer);
            pImagesDirsSet->Close();
            m_pdbcentral->OpenImagesDirsSet();
        }
		strPath = strModuleFolder;
        str.LoadString(IDS_FOLDER_SONGS);
		strPath += str;
		CDBSongDirectorySet * pSongsDirsSet = m_pdbcentral->GetSongsDirsSet();
        bAdd = true;
		if(pSongsDirsSet->m_spRowsetChange == NULL)
        {
            m_pdbcentral->OpenSongsDirsSet();
            if(pSongsDirsSet->m_spRowsetChange == NULL)
            {
                AfxMessageBox(_T("CVmcApp::LoadAppSettings() Fail 2000"));
                bAdd = false;
            }

        }
        if(bAdd)
        {
		    pSongsDirsSet->Add(strPath);
            pSongsDirsSet->Close();
            m_pdbcentral->OpenSongsDirsSet();
        }
    }

    UINT uiDev;
	if(!pLongsSet->Load(_T("Audio Devices"), _T("Midi Playback"),(long*)&uiDev))
		uiDev = MIDI_MAPPER;
    m_uiMidiOutDevice = uiDev;
    
	if(!pLongsSet->Load(_T("Audio Devices"), _T("Sound Recording"), (long*) &uiDev))
		uiDev = WAVE_MAPPER;
    m_uiWaveInDevice = uiDev;

    int iEconoMode;
    if(!pLongsSet->Load(_T("EconoMode"), _T("Value"), &iEconoMode))
    {
        iEconoMode = CSavings::SaveNoSave;
    }
    if(!(CSavings::AppGetEconoMode() & CSavings::SaveMemory))
	{
		CSavings::AppSetEconoMode(CSavings::AppGetEconoMode() & CSavings::SaveMemory);
	}
	if(!(CSavings::AppGetEconoMode() & CSavings::SaveProcessing))
	{
		CSavings::AppSetEconoMode(CSavings::AppGetEconoMode() & CSavings::SaveProcessing);
	}
*/
}


void CVmcApp::OnHelp() 
{
	// TODO: Add your command handler code here
	ca77::application::OnHelp();
}

void CVmcApp::RegisterShellFileTypes(BOOL bCompat)
{
//	ASSERT(m_pDocManager != NULL);
//	m_pDocManager->RegisterShellFileTypes(bCompat);
//	ASSERT(!m_pDocManager->m_templateList.is_empty());  // must have some doc templates

	string strPathName, strTemp;
 
//	GetModuleShortFileName(AfxGetInstanceHandle(), strPathName);

/*    POSITION pos = m_pDocManager->GetFirstDocTemplatePosition();
	for (int nTemplateIndex = 1; pos != NULL; nTemplateIndex++)
	{
		DocumentTemplate* pTemplate = (DocumentTemplate*)m_pDocManager->GetNextDocTemplate(pos);

		string strOpenCommandLine = strPathName;
		string strPrintCommandLine = strPathName;
		string strPrintToCommandLine = strPathName;
		string strDefaultIconCommandLine = strPathName;
        
        int nIconIndex = 1;
		if (bCompat)
		{
			string strIconIndex;
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

		string strFilterExt, strFileTypeId, strFileTypeName;
		if (pTemplate->GetDocString(strFileTypeId,
		   DocumentTemplate::regFileTypeId) && !strFileTypeId.is_empty())
		{
			// enough info to register it
			if (!pTemplate->GetDocString(strFileTypeName,
			   DocumentTemplate::regFileTypeName))
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

			// If MDI Application
			if (!pTemplate->GetDocString(strTemp, DocumentTemplate::windowTitle) ||
				strTemp.is_empty())
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

			pTemplate->GetDocString(strFilterExt, DocumentTemplate::filterExt);
            CStrTokenizer strtokenizer;
            strtokenizer = strFilterExt;
            while(strtokenizer.GetNextToken(strFilterExt, _T(";"), false))
            {
			    if (!strFilterExt.is_empty())
			    {
				    ASSERT(strFilterExt[0] == '.');

				    LONG lSize = _MAX_PATH * 2;
				    LONG lResult = ::RegQueryValue(HKEY_CLASSES_ROOT, strFilterExt,
					    strTemp.GetBuffer(lSize), &lSize);
				    strTemp.ReleaseBuffer();

				    if (lResult != ERROR_SUCCESS || strTemp.is_empty() ||
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
	}*/
}

//bool CVmcApp::InitDirectDraw()
//{
//    HANDLE hLibrary = LoadLibrary(_T("d3d8.dll"));
//    if(hLibrary == NULL)
//        return false;
//    m_spDirectDraw = Direct3DCreate8(D3D_SDK_VERSION);
//    return true;
//}

void CVmcApp::OnHelpFinder() 
{
	// TODO: Add your command handler code here
    ca77::application::OnHelpFinder();
}

BOOL CVmcApp::OnCmdMsg(UINT nID, int nCode, void* pExtra, CAFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return ca77::application::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

/*CXfplayerDoc	*CVmcApp::GetPlayerDocument()
{
    POSITION pos = m_pPlayerDocTemplate->GetFirstDocPosition();
    if(pos == NULL)
    {
        return NULL;
    }
    else
    {
    	return (CXfplayerDoc *) m_pPlayerDocTemplate->GetNextDoc(pos);
    }
};*/


void CVmcApp::OnFileNewFromplayerview() 
{
	// TODO: Add your command handler code here
//    CXfplayerDoc * pDoc = (CXfplayerDoc *) GetPlayerDocTemplate()->GetOnlyDoc();
  //  m_pMainDocTemplate->OpenDocumentFile(pDoc->GetPathName());
	
}

void CVmcApp::OnUpdateFileNewFromplayerview(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
//    CXfplayerDoc * pDoc = (CXfplayerDoc *) GetPlayerDocTemplate()->GetOnlyDoc();
  
	//pCmdUI->Enable(pDoc->GetMidiPlayer() &&
      //  &pDoc->HelperGetMidiSequence()->GetState() != MidiSequence::StatusNoFile);
}

//CXfplayerSingleDocTemplate * CVmcApp::GetPlayerDocTemplate()
//{
    //return m_pPlayerDocTemplate;
//}

/*void CVmcApp::SetPlayerDocument(CXfplayerDoc *lpDoc)
{
    m_pPlayerDoc = lpDoc;
}*/

/*CXfplayerFont * CVmcApp::GetTitleFont()
{
    return NULL;
}

CXfplayerFont * CVmcApp::GetSongLabelFont()
{
    return m_lpSongLabelFont;
}

CXfplayerFont * CVmcApp::GetSongListFont()
{
    return m_lpSongListFont;
}*/

MultipleDocumentTemplate * CVmcApp::GetPlaylistDocTemplate()
{
    return m_pPlaylistDocTemplate;
}

CImaging * CVmcApp::GetImaging()
{
	return m_pImaging;
}

int CVmcApp::GetEconoMode_()
{
    ASSERT(FALSE);
    return -1;
    //return m_iEconoMode;
}

void CVmcApp::OnChangeEconoMode()
{
/*    if(DB())
        if(DB()->GetDBLongSet())
            DB()->GetDBLongSet()->Save(_T("EconoMode"), _T("Value"), m_psavings->GetEconoMode());*/

//    m_pMainWnd->SendMessage(VMSM_ECONOMODECHANGE, m_psavings->GetEconoMode());
}

/*void CVmcApp::SetEconoMode(int iNewEconoMode)
{
    
    if(m_iEconoMode != iNewEconoMode)
    {
        m_iEconoMode = iNewEconoMode;
        OnChangeEconoMode();
        m_pdbcentral->GetDBLongSet()->Save(_T("EconoMode"), _T("Value"), m_iEconoMode);
    }
    
}*/

/*VMSRESULT CVmcApp::MenuV033CreateImageMap()
{
    UINT uiaMenuV003Map [][2] =
    {
        {ID_FILE_NEW, 0},
        {ID_FILE_OPEN, 1},
        {ID_FILE_SAVE, 2},
        {ID_VIEW_FULL_SCREEN, 7},
        {ID_TOOLS_ALBUM, 8},
        {ID_VIEW_PLAYLIST, 9},
        {ID_VIEW_LYRICS, 10},
        {ID_TOOLS_MIXER, 11},
        {ID_PLAY, 12},
        {ID_STOP, 13},
        {ID_PAUSE, 14},
        {ID_NEXTSONG, 15},
        {ID_VIEW_LYRICVIEW_SPECTRUM, 18},
        {ID_PLAYER, 19},
        {ID_ALBUM_NAVIGATOR, 20},
        {ID_ALBUM_FULLLIST, 21},
        {ID_ALBUM_TREELIST, 22},
        {ID_ALBUM_SEARCHLIST, 23},
        {ID_ALBUM_RESERVESONG, 24},
        {-1, 25}, //ID_CHECK
        {ID_SCORING_ENABLE, 26},
        {ID_ALBUM_DUPLICATESLIST, 27},
        {ID_VIEW_BOUNCINGBALL, 28},
        {ID_VIEW_GRADUALFILLING, 29}
    };
    CRelationV001<UINT, UINT, UINT, UINT> * prel;
//    CVmsGuiDll::AppGetDll()->MenuV033GetImageMap(&prel);
  //  UINT uiSize = sizeof(uiaMenuV003Map) / (sizeof(UINT) * 2);
    //for(UINT ui = 0; ui < uiSize; ui++)
//    {
  //      prel->Add(uiaMenuV003Map[ui][0], uiaMenuV003Map[ui][1]);
    //}
    return VMSR_SUCCESS;
}*/

/*VMSRESULT CVmcApp::MenuV033GetImageMap(CRelationV001<UINT, UINT, UINT, UINT> ** pprel)
{
//    *pprel = &m_relMenuV033ImageMap;
//    return CVmsGuiDll::AppGetDll()->MenuV033GetImageMap(pprel);
    return VMSR_SUCCESS;
}*/

/*CImageList * CVmcApp::MenuV033GetImageList()
{
    //return m_pilMenuV033;
    return CVmsGuiDll::AppGetDll()->MenuV033GetImageList();
}*/

CKaraokeSDIFrame * CVmcApp::GetKarWnd()
{
//    CXfplayerDoc * pdoc;
//    if(CXfplayerSingleDocTemplate::AppGetPlayerDocTemplate())
  //  {
    //    if(pdoc = (CXfplayerDoc *) CXfplayerSingleDocTemplate::AppGetPlayerDocTemplate()->GetOnlyDoc())
      //  {
        //    if(pdoc->GetLyricView())
          //  {
            //    return (CKaraokeSDIFrame *) pdoc->GetLyricView()->GetParentFrame();
//            }
  //      }
    //}
    return NULL;
}

void CVmcApp::OnToolsAlbum() 
{
	// TODO: Add your command handler code here
    ViewToolsAlbum();
	
}

void CVmcApp::OnUpdateToolsAlbum(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

VMSRESULT CVmcApp::OpenToolsAlbum()
{
    CWaitCursor cwc;

  //  if(m_pAlbumThread == NULL)
    //{
      //  CreateAlbumThread();
    //}
    //if(m_pAlbumThread != NULL)
    //{
//        m_pAlbumThread->PostMessageViewAlbum(false);
    //}
    //else
    //{
    //}
//    if(m_pAlbumThread == NULL)
  //  {
    //    m_pAlbumThread = (CAlbumThread *) AfxBeginThread(
      //      RUNTIME_CLASS(CAlbumThread));

//    }
  //  else
    //{
      //  m_pAlbumThread->ViewToolsAlbum();
    //}
//        CVmcApp * pApp = (CVmcApp *)AfxGetApp();
/*    if(GetDBCentral()->IsWorking())
    {
	    if(m_pAlbumDocTemplate == NULL)
	    {
            m_pAlbumDocTemplate = new CSingleDocTemplate(
                IDR_ALBUM,
                RUNTIME_CLASS(CAlbumDoc),
                RUNTIME_CLASS(CAlbumFrameWnd),
                RUNTIME_CLASS(CAlbumFormView));
            AddDocTemplate(m_pAlbumDocTemplate);
            //m_pAlbumDocTemplate->
            //CRuntimeClass* pRuntimeClass = RUNTIME_CLASS(CAlbumFrameWnd);
	        //base_object* pObject = pRuntimeClass->CreateObject();
	        //ASSERT(pObject->IsKindOf(RUNTIME_CLASS(CAlbumFrameWnd)));
	        //CAlbumFrameWnd * pAlbumFrameWnd = (CAlbumFrameWnd *) pObject;
            //CreateContext cc;
            //cc.m_pCurrentDoc = NULL;
            //cc.m_pCurrentFrame = pAlbumFrameWnd;
            //cc.m_pLastView = NULL;
            //cc.m_pNewDocTemplate = NULL;
            //cc.m_pNewViewClass = RUNTIME_CLASS(CAlbumFormView);
            //AfxMessageBox(_T("7.4"));
	        //if (!pAlbumFrameWnd->LoadFrame(IDR_ALBUM,
            //    WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,
            //    NULL, &cc))

//            {
//			    delete m_pAlbumFrameWnd;
//			    m_pAlbumDocTemplate = NULL;
            //}
            //m_pAlbumFrameWnd = pAlbumFrameWnd;
	    }
	    //dlg.DoModal();
	    if(m_pAlbumDocTemplate != NULL)
	    {
            if(GetDBCentral()->IsBuildingSongsAlbum())
            {
                CCriticalSection *pcs;
                CDBBuildAlbumThreadData * lpData =
                    GetDBCentral()->GetActiveBuildAlbumThreadData(&pcs);
                if(lpData != NULL)
                {
                    //lpdata->m_ptaskdlg->m_pCloseWindow = m_pAlbumFrameWnd;
					lpdata->m_ptaskdlg->SetPendingShowCommandFlag(true);
                }
                pcs->Unlock();
            }
            else
            {
//                m_pAlbumDialog->Update(); // retirar se possível
		        //m_pAlbumFrameWnd->ShowWindow(SW_SHOWNORMAL);
		        /*m_pAlbumDialog->SetWindowPos(
                    &base_wnd::wndTop,
			        0, 0,
			        0, 0,
			        SWP_NOMOVE |
			        SWP_NOSIZE); //|
			        //SWP_SHOWWINDOW);*/
               //m_pAlbumFrameWnd->InitialUpdateFrame(NULL, true);
                //m_pAlbumFrameWnd->ActivateFrame();
            /*}
	    }
	    
//	    base_wnd * pParent = GetParent();
    }
    else
    {
        AfxMessageBox(
            IDS_NODATABASESUPPORTERROR_RESOURCEUNAVAILABLE,
            MB_OK |
            MB_ICONINFORMATION);

    }*/

    /*CVmcApp * pApp = (CVmcApp *)AfxGetApp();
    if(pApp->GetDBCentral()->IsWorking())
    {
	    if(m_pAlbumFrameWnd == NULL)
	    {
            CRuntimeClass* pRuntimeClass = RUNTIME_CLASS(CAlbumFrameWnd);
	        base_object* pObject = pRuntimeClass->CreateObject();
	        ASSERT(pObject->IsKindOf(RUNTIME_CLASS(CAlbumFrameWnd)));
	        CAlbumFrameWnd * pAlbumFrameWnd = (CAlbumFrameWnd *) pObject;
            CreateContext cc;
            cc.m_pCurrentDoc = NULL;
            cc.m_pCurrentFrame = pAlbumFrameWnd;
            cc.m_pLastView = NULL;
            cc.m_pNewDocTemplate = NULL;
            cc.m_pNewViewClass = RUNTIME_CLASS(CAlbumFormView);
            //AfxMessageBox(_T("7.4"));
	        if (!pAlbumFrameWnd->LoadFrame(IDR_ALBUM,
                WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,
                NULL, &cc))

            {
//			    delete m_pAlbumFrameWnd;
			    m_pAlbumFrameWnd = NULL;
            }
            m_pAlbumFrameWnd = pAlbumFrameWnd;
	    }
	    //dlg.DoModal();
	    if(m_pAlbumFrameWnd != NULL)
	    {
            if(pApp->GetDBCentral()->IsBuildingSongsAlbum())
            {
                CCriticalSection *pcs;
                CDBBuildAlbumThreadData * lpData =
                    pApp->GetDBCentral()->GetActiveBuildAlbumThreadData(&pcs);
                if(lpData != NULL)
                {
                    lpdata->m_ptaskdlg->m_pCloseWindow = m_pAlbumFrameWnd;
					lpdata->m_ptaskdlg->SetPendingShowCommandFlag(true);
                }
                pcs->Unlock();
            }
            else
            {
//                m_pAlbumDialog->Update(); // retirar se possível
		        //m_pAlbumFrameWnd->ShowWindow(SW_SHOWNORMAL);
		        /*m_pAlbumDialog->SetWindowPos(
                    &base_wnd::wndTop,
			        0, 0,
			        0, 0,
			        SWP_NOMOVE |
			        SWP_NOSIZE); //|
			        //SWP_SHOWWINDOW);*/
               //m_pAlbumFrameWnd->InitialUpdateFrame(NULL, true);
                //m_pAlbumFrameWnd->ActivateFrame();
  //          }
//	    }
	    
//	    base_wnd * pParent = GetParent();
    /*}
    else
    {
        AfxMessageBox(
            IDS_NODATABASESUPPORTERROR_RESOURCEUNAVAILABLE,
            MB_OK |
            MB_ICONINFORMATION);

    }*/
    return VMSR_SUCCESS;

}

VMSRESULT CVmcApp::ViewToolsAlbum()
{
    return OpenToolsAlbum();
}

/*CSingleDocTemplate * CVmcApp::GetAlbumDocTemplate()
{
    return m_pAlbumDocTemplate;
}*/

CAlbumThread * CVmcApp::GetAlbumThread()
{
//    if(m_pAlbumThread == NULL)
  //  {
    //    CreateAlbumThread();
    //}
    //return m_pAlbumThread;
	return NULL;
}

MultipleDocumentTemplate * CVmcApp::GetMidiDocTemplate()
{
    return m_pMidiDocTemplate;
}

/*CFont * CVmcApp::GetStandartFont()
{
    return m_pfontMenu;
}*/

/*VMSRESULT CVmcApp::ReserveSong_(int iCode)
{
    CXfplayerDoc * pPlayerDoc  = GetPlayerDocument();

    if(pPlayerDoc == NULL)
    {
        pPlayerDoc = (CXfplayerDoc *) GetPlayerDocTemplate()->OpenDocumentFile(NULL);
    }

    if(pPlayerDoc != NULL)
    {
        CXfplayerView * pLyricView = pPlayerDoc->GetLyricView();
        if(pLyricView != NULL)
        {
            //CPlaylistView * pPlaylistView = pLyricView->GetPlaylistView();
            CPlaylistDoc * pPlaylistDoc = pLyricView->GetPlaylistDoc();
            //if(pPlaylistView == NULL)
            if(pPlaylistDoc == NULL)
            {
                MultipleDocumentTemplate * pPlaylistDocTemplate = GetPlaylistDocTemplate();
                pPlaylistDoc
                 = (CPlaylistDoc *) pPlaylistDocTemplate->OpenDocumentFile(NULL);
                pLyricView->AttachPlaylistDoc(pPlaylistDoc);
//                pPlaylistView = pPlaylistDoc->GetPlaylistView();
            }
//            else
  //          {
    //            pPlaylistDoc = pPlaylistView->GetDocument();
      //      }
            if(pPlaylistDoc != NULL)
            {
                pPlaylistDoc->AddSong_(iCode);
            }
//            }

//          	CMainFrame *pFrame = (CMainFrame *) pApp->m_pMainWnd;
  //      	pFrame->UpdateReserveList();
        }
    }
    return VMSR_SUCCESS;
}*/

VMSRESULT CVmcApp::SetAlbumThread(CAlbumThread *pAlbumThread)
{
//    m_pAlbumThread = pAlbumThread;
    return VMSR_SUCCESS;
}

string CVmcApp::GetAppFolder()
{
    TCHAR lpszModuleFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, lpszModuleFilePath, MAX_PATH + 1);
	TCHAR lpszModuleFolder[MAX_PATH + 1];
	LPTSTR lpszModuleFileName;
	GetFullPathName(lpszModuleFilePath, MAX_PATH + 1, lpszModuleFolder, &lpszModuleFileName);
	string strModuleFolder(lpszModuleFolder, lpszModuleFileName - lpszModuleFolder);
    return strModuleFolder;
}

VMSRESULT CVmcApp::CreateAlbumThread()
{
//    m_pAlbumThread = (CAlbumThread *) AfxBeginThread(
  //      RUNTIME_CLASS(CAlbumThread)); 
    //if(m_pAlbumThread != NULL)
    //{
      //  return VMSR_SUCCESS;
    //}
    //else
    //{
        return VMSR_E_FAIL;
    //}

}

/*VMSRESULT CVmcApp::ReserveSong(LPCTSTR lpcszPath, bool bDoPlay)
{
    ASSERT(FALSE);
    return VMSR_E_FAIL;
    CXfplayerDoc * pPlayerDoc  = (CXfplayerDoc *) GetPlayerDocTemplate()->GetOnlyDoc();

    if(pPlayerDoc == NULL)
    {
        pPlayerDoc = (CXfplayerDoc *) GetPlayerDocTemplate()->OpenDocumentFile(NULL);
    }

    if(pPlayerDoc != NULL)
    {
        CXfplayerView * pLyricView = pPlayerDoc->GetLyricView();
        if(pLyricView != NULL)
        {
            //CPlaylistView * pPlaylistView = pLyricView->GetPlaylistView();
            CPlaylistDoc * pPlaylistDoc = pLyricView->GetPlaylistDoc();
            //if(pPlaylistView == NULL)
            if(pPlaylistDoc == NULL)
            {
                MultipleDocumentTemplate * pPlaylistDocTemplate = GetPlaylistDocTemplate();
                pPlaylistDoc
                 = (CPlaylistDoc *) pPlaylistDocTemplate->OpenDocumentFile(NULL);
                pLyricView->AttachPlaylistDoc(pPlaylistDoc);
//                pPlaylistView = pPlaylistDoc->GetPlaylistView();
            }
//            else
  //          {
    //            pPlaylistDoc = pPlaylistView->GetDocument();
      //      }
            if(pPlaylistDoc != NULL)
            {
                pPlaylistDoc->AddSong(lpcszPath, bDoPlay);
            }
//            }

//          	CMainFrame *pFrame = (CMainFrame *) pApp->m_pMainWnd;
  //      	pFrame->UpdateReserveList();
        }
    }
    return VMSR_SUCCESS;
}


VMSRESULT CVmcApp::ReserveSongs(LPINT lpiaSongs, int iSongCount)
{
    CXfplayerDoc * pPlayerDoc  = (CXfplayerDoc *) GetPlayerDocTemplate()->GetOnlyDoc();

    if(pPlayerDoc == NULL)
    {
        pPlayerDoc = (CXfplayerDoc *) GetPlayerDocTemplate()->OpenDocumentFile(NULL);
    }

    if(pPlayerDoc != NULL)
    {
        CXfplayerView * pLyricView = pPlayerDoc->GetLyricView();
        if(pLyricView != NULL)
        {
            //CPlaylistView * pPlaylistView = pLyricView->GetPlaylistView();
            CPlaylistDoc * pPlaylistDoc = pLyricView->GetPlaylistDoc();
            //if(pPlaylistView == NULL)
            if(pPlaylistDoc == NULL)
            {
                MultipleDocumentTemplate * pPlaylistDocTemplate = GetPlaylistDocTemplate();
                pPlaylistDoc
                 = (CPlaylistDoc *) pPlaylistDocTemplate->OpenDocumentFile(NULL);
                pLyricView->AttachPlaylistDoc(pPlaylistDoc);
//                pPlaylistView = pPlaylistDoc->GetPlaylistView();
            }
//            else
  //          {
    //            pPlaylistDoc = pPlaylistView->GetDocument();
      //      }
            if(pPlaylistDoc != NULL)
            {
                pPlaylistDoc->AddSong(lpiaSongs, iSongCount);
            }
//            }

//          	CMainFrame *pFrame = (CMainFrame *) pApp->m_pMainWnd;
  //      	pFrame->UpdateReserveList();
        }
    }
    return VMSR_SUCCESS;
}*/



CMessageFilterMainHook * CVmcApp::GetMessageFilterMainHook()
{
    return m_pmfmh;
}

void CVmcApp::OnToolsOptions() 
{
	// TODO: Add your command handler code here
	
/*    COptionsDialog optionsDialog;
	optionsDialog.DoModal();*/

}

void CVmcApp::OnUpdateToolsOptions(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    pCmdUI->Enable();	
}


Document* CVmcApp::OpenDocumentFile(LPCTSTR lpszFileName) 
{
	// TODO: Add your specialized code here and/or call the base class
	//ReserveSong(lpszFileName, true);
	return ca77::application::OpenDocumentFile(lpszFileName);
}

CSavings * CVmcApp::GetSavings()
{
    return m_psavings;

}


CFontCentral * CVmcApp::GetFontCentral()
{
    return m_pfontcentral;
}

afx_msg void CVmcApp::OnUserMessage(WPARAM wParam, LPARAM lParam )
{
    switch(wParam)
    {
    case 21:
//                    ASSERT(FALSE);
//                  //ReserveSong_(pMsg->lParam);
//        GetPlayerDocTemplate()->ReserveSong(lParam, false, true);
        break;
    case 22:
        {
            BaseDWORDArray * pdwa = (BaseDWORDArray *) lParam;
  //          GetPlayerDocTemplate()->ReserveSong((LPINT) &pdwa->GetData()[1], pdwa->GetAt(0), false, true);
            delete pdwa;
        }
        break;
    case 23:
        {
            AStrArray * pstra = (AStrArray *) lParam;
    //        GetPlayerDocTemplate()->ReserveSong(pstra, false, true);
            delete pstra;
        }
        break;
    }
      if(wParam == 1)
    {
        if(lParam == 1)
        {
            //m_pdbcentral->OnSongsUpdated();
        }
        else if(lParam == 3)
        {
            //m_pdbcentral->OnSongsInfoV001Updated();
        }
    }

    switch(wParam)
    {
    case 131415:
        ViewToolsAlbum();
        break;
    case 454647:
        {
//            CXfplayerSingleDocTemplate * pDocTemplate = GetPlayerDocTemplate();
  //          if(pDocTemplate != NULL)
    //        {

				//CXfplayerDoc * pDoc = (CXfplayerDoc *) pDocTemplate->GetOnlyDoc();
//	            if(pDoc != NULL)
  //              {
	//                CXfplayerView * pView = (CXfplayerView *) pDoc->GetLyricView();
	  //              if(pView != NULL)
        //            {
                        //pView->PostMessage(WM_USER, 17, CXfplayerView::BkImageChangeEventLoadNow);
//        //                pView->BackgroundImageChangeStateMachine(pView->BkImageChangeEventLoadNow);
            //            TRACE(_T("CDataCentral::OnImagesDirsModified Out"));
              //      }
                
			//}
      //      }
        }
        break;
    case 565758:
        //{
/*            CDBBuildAlbumThreadData * lpdata = 
                (CDBBuildAlbumThreadData *)lParam;
            CSingleDocTemplate * pAlbumDocTemplate = NULL;
            if(GetAlbumThread())
            {
//                pAlbumDocTemplate = GetAlbumThread()->GetAlbumDocTemplate();
            }
            bool bVisible = false;
  //          if(pAlbumDocTemplate != NULL)
    //        {
      //          bVisible = pAlbumDocTemplate->GetFirstDocPosition() != NULL;

                // avoid thread quit on close all documents
        //        GetAlbumThread()->m_pMainWnd = NULL;

          //      GetAlbumThread()->GetAlbumDocTemplate()->CloseAllDocuments(false);
            //}
            //CAlbumFrameWnd * pAlbum = GetAlbumDocTemplate();
            //bool bVisible;
            //if(pAlbum != NULL)
            //{
              //  bVisible = (pAlbum->GetStyle() & WS_VISIBLE) != 0;
                //if(bVisible)
                  //  pAlbum->ShowWindow(SW_HIDE);
            //}
            lpdata->bVisible = bVisible;
        }*/
        break;
    case 676869:
        {
            ASSERT(FALSE);
/*            CDBBuildAlbumThreadData * lpdata = 
                (CDBBuildAlbumThreadData *)lParam;
            if(!lpdata->m_ptaskdlg->Create(IDD_TASK))
            {
                AfxMessageBox(_T("Could not create task dialog"));
                return;
            }
    
            GetAlbumThread()->m_pMainWnd = lpdata->m_ptaskdlg;
        */
        }
    case 787970:
        {
//            CDBBuildAlbumThreadData * lpdata = 
  //              (CDBBuildAlbumThreadData *)lParam;
//            if(m_pAlbumDocTemplate != NULL)
  //          {
    //            if(lpdata->bVisible)
      //          {
        //            lpdata->lpDataCentral->m_csBuildAlbumThreadData.Lock();
          //          lpdata->m_evStarted.Lock();
                    //lpdata->m_ptaskdlg->m_pCloseWindow = pAlbum;
        //            lpdata->m_ptaskdlg->m_lparamClose = 10;
            //        lpdata->lpDataCentral->m_csBuildAlbumThreadData.Unlock();
              //  }
            //}
        }
        break;
    case 12342345:
        {
            if(m_pMainWnd == NULL)
            {
                return;
            }
//            else if(!m_pMainWnd->IsKindOf(RUNTIME_CLASS(CMainFrame)))
  //          {
    //            return;
      //      }
            //CMainFrame * pFrame = (CMainFrame *) pApp->m_pMainWnd;
            //if(pFrame->m_pAlbumDialog == NULL)
        //    CAlbumFrameWnd * pAlbum = pApp->GetAlbumFrameWnd();
          //  if(pAlbum == NULL)
            //{
              //  return;
            //}
            //pAlbum->GetAlbumView()->OnSongsUpdated();
//            CSingleDocTemplate * pTempl = GetAlbumThread()->GetAlbumDocTemplate();
  //          POSITION pos = pTempl->GetFirstDocPosition();
    //        while(pos != NULL)
      //      {
        //        Document * pDoc = pTempl->GetNextDoc(pos);
          //      if(pDoc != NULL)
            //    {
              //      pDoc->UpdateAllViews(NULL, 13);
                //}
            //}
        }
        break;
    case 23453456:
        {
            if(m_pMainWnd == NULL)
            {
                return;
            }
//            else if(!m_pMainWnd->IsKindOf(RUNTIME_CLASS(CMainFrame)))
  //          {
    //            return;
      //      }
        //    CMainFrame * pFrame = (CMainFrame *) pApp->m_pMainWnd;
          //  if(pFrame->m_pAlbumDialog == NULL)
//            CSingleDocTemplate * pTempl = GetAlbumThread()->GetAlbumDocTemplate();
  //          POSITION pos = pTempl->GetFirstDocPosition();
    //        while(pos != NULL)
      //      {
        //        Document * pDoc = pTempl->GetNextDoc(pos);
          //      if(pDoc != NULL)
            //    {
              //      pDoc->UpdateAllViews(NULL, 4);
                //}
            //}

        //    CAlbumFrameWnd * pAlbum = pApp->GetAlbumFrameWnd();
          //  if(pAlbum == NULL)
            //{
              //  return;
            //}
            //pAlbum->GetAlbumView()->OnSongsInfoV001Updated();

        }
        break;
    case 345456:
        {
            bool bFullBuild = (lParam & 0x80000000) != 0;
            int eop = lParam & 0x7fffffff;
            CAlbumThread * pThread = GetAlbumThread();
            if(pThread == NULL)
                return;
    
//            CAlbumThread::CBuildRequest * lpbr = new CAlbumThread::CBuildRequest();

  //          lpbr->m_pdc = GetDBCentral();
    //        lpbr->m_eop = (SongsAlbum::EBuildSongsAlbumOperation) eop;
      //      lpbr->m_bfb = bFullBuild;

        //    pThread->PostThreadMessage(VMSIM_ALBUMTHREAD, 20191817, (LPARAM) lpbr);


        }
        break;
    case 321432:
        {
            // On Task Dialog Stop
            ASSERT(m_pdbcentral != NULL);
//            m_pdbcentral->SetBuildAlbumThreadsCancelFlag();
        }
        break;
    case 3214:
        {
            OnChangeEconoMode();

        }
        break;
    case 534231:
        {
//            GetKarWnd()->SendMessageToDescendants(WM_USER, 534231);
        }
        break;
    default:;
        break;
    }
}

void CVmcApp::RegisterShellExtension()
{
    TCHAR lpszModuleFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, lpszModuleFilePath, MAX_PATH + 1);
	
    TCHAR lpszModuleFolder[MAX_PATH + 1];
	LPTSTR lpszModuleFileName;
	GetFullPathName(lpszModuleFilePath, MAX_PATH + 1, lpszModuleFolder, &lpszModuleFileName);
	
    string strModuleFolder(lpszModuleFolder, lpszModuleFileName - lpszModuleFolder);
    string str(_T("vmsse.dll"));
    string strFormat;
    strFormat.Format(_T("/s %s\\%s"),strModuleFolder,str);
    ShellExecute(m_pMainWnd->GetSafeHwnd(), "open", "regsvr32.exe", strFormat, strModuleFolder,SW_HIDE); 

/*    CRegKey regKey;

    UUID uuida[2];
    uuida[0] = CLSID_AlbumSongFolder;
    uuida[1] = CLSID_AlbumSongView;
    

    int i;
    string strParam;
    string strCLSID;
    string strBase;
    string strSystemRoot;
    string str;

    {
        TCHAR lpBuffer[MAX_PATH];
        GetWindowsDirectory(
            lpBuffer,  // address of buffer for system directory
            MAX_PATH);        // size of directory buffer);
        strSystemRoot = lpBuffer;
    }

    for(i = 0; i < 2; i++)
    {
        UUID uuid = uuida[i];
        unsigned char * lpstr = NULL;
    
        UuidToString(&uuid, &lpstr);

        strParam = lpstr;
        strCLSID = strParam;
    

        RpcStringFree(&lpstr);

        
    
        str.Format(_T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Desktop\\NameSpace\\{%s}"), strParam);

    
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

        regKey.Close();



        strBase.Format(_T("CLSID\\{%s}"), strParam);
        str.Format(_T("%s"), strBase);

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
        regKey.Close();
 



        str.Format(_T("%s\\DefaultIcon"), strBase);
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
	    
        string strModuleFolder(lpszModuleFolder, lpszModuleFileName - lpszModuleFolder);
    #define IDR_XFPLAYER_INDEX 2
        str.Format("%svms.exe,%d", strModuleFolder, IDR_XFPLAYER_INDEX);
        //str.Format("%svms.exe,%d", strModuleFolder, 3);
        regKey.SetValue(str);
        regKey.Close();

        str.Format(_T("SOFTWARE\\Microsoft\\WindowsNT\\CurrentVersion\\ShellExtensions\\Approved\\{%s}"), strCLSID);
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
        regKey.Close();

        //HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Shell Extensions\Approved

        str.Format(_T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions\\Approved"));
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
    }

    UUID uuid = CLSID_AlbumSongFolder;
    unsigned char * lpstr = NULL;

    UuidToString(&uuid, &lpstr);

    strParam = lpstr;
    strCLSID = strParam;


    RpcStringFree(&lpstr);

//    string strBase;
    strBase.Format(_T("CLSID\\{%s}"), strParam);
    str.Format(_T("%s\\Shell\\Open\\Command"), strBase);


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
    regKey.Close();

    str.Format(_T("%s\\Shell\\Explore\\Command"), strBase);
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


}

CDBCentral * CVmcApp::GetDBCentral()
{
    return m_pdbcentral;
}

	
extern CComModule _Module;

/*BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_VmsComposer, CVmc)
END_OBJECT_MAP()*/

/*LONG CVmsModule::Unlock()
{
	AfxOleUnlockApp();
	return 0;
}

LONG CVmsModule::Lock()
{
	AfxOleLockApp();
	return 1;
}
*/

/*
BOOL CVmcApp::InitATL()
{
	m_bATLInited = TRUE;

	_Module.Init(ObjectMap, AfxGetInstanceHandle());
//	_Module.dwThreadID = GetCurrentThreadId();

	return TRUE;

}
*/
CWelcomeDialog * CVmcApp::GetWelcomeDialog()
{
    return m_pwelcomedlg;
}

void CVmcApp::SetWelcomeDialog(CWelcomeDialog *pdlg)
{
    m_pwelcomedlg = NULL;
}

bool CVmcApp::MessageWindowListener(
	UINT message,
	WPARAM wparam,
	LPARAM lparam)
{
	return false;
}

void CVmcApp::_001Alloc(gen::signal_object * pobj)
{
   SCAST_REF(gen::message::alloc, alloc, pobj);
   if(alloc == typeid(CMSDoc))
   {
      alloc = new CMSDoc(get_app());
   }
   else if(alloc == typeid(CMSFrame))
   {
      alloc = new CMSFrame(get_app());
   }
   else if(alloc == typeid(CMSStaffView))
   {
      alloc = new CMSStaffView(get_app());
   }

}