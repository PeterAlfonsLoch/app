// xfplayer.cpp : Defines the class behaviors for the application.
//

#include "StdAfx.h"
#include <afxpriv.h>
#include "VcdpApp.h"
#include "vmsgdiapi.h"
#include "HelpCentral.h"
//#include "hook.h"
#include "AppMessageWindow.h"
#include "..\vmp\resource.h"
#include "vmsguiresource.h"
#include "XfplayerIPFrame.h"
#include <afxadv.h>
#include "AudioSpectrumViewUpdateHint.h"
#include "MenuUtil.h"
#include "FileAssociation.h"

#include "VmspDll.h"

#include "VmpInPlaceFrame.h"

#include "Registry.h"
#include "International.h"

#include "MainFrame.h"
//#include "KaraokeMainFrame.h"
#include "CDDoc.h"
#include "CDFrame.h"
#include "CDView.h"

#include "VmsTextFrame.h"
#include "VmsTextDoc.h"
#include "VmsTextView.h"

//#include "MidiTracksEventsView.h"


#include "PlaylistDoc.h"
#include "PlaylistFrame.h"
#include "PlaylistView.h"
#include "PlaylistListView.h"

#include "VmsGuiDll.h"

#include "WaveCentral.h"

#include "MidiCentral.h"

#include "MixerCentral.h"

#include "optionsdialog.h"

//#include "splash.h"

#include "optionsimagesdialog.h"

#include "VmsGuiSingleDocTemplate.h"
#include "VmsGuiMultiDocTemplate.h"
#include "XfplayerSingleDocTemplate.h"
#include "XfplayerOpenFileDialog.h"

#include "DBSongSet.h"
#include "SongDirectory.h"
#include "DBImageFile.h"
#include "DBImageDirectory.h"
#include "DBLong.h"
#include "DBBuildAlbumThreadData.h"

#include "TaskDialog.h"

#include "WaveIn.h"
#include "XfplayerThreadV1.h"
#include "XfplayerThreadV2.h"
#include "XfplayerThreadV3.h"
#include <initguid.h>
//#include "Xfplayer_i.c"

//#include "bitmapwindow.h"

#include "SplashThread.h"
//#include "SplashWnd.h"

#include "Imaging.h"
#include "Savings.h"
#include "FontCentral.h"
#include "DataCentral.h"

#include "MenuV033.h"

//#include "WelcomeDialog.h"

#include "AlbumSongs.h"
#include "AlbumDoc.h"
#include "AlbumMainView.h"
#include "AlbumFrameWnd.h"
#include "AlbumThread.h"

#include "MenuCentral.h"
#include "MenuBarV033.h"

#include "StrTokenizer.h"


#include "rpcdce.h"

//#include "..\vmsse\vmsse.h"
//#include "..\vmsse\vmsse_i.c"
#include "Vmsp_i.c"
#include "Vmp.h"

#include "FileUtil.h"

#include "TextDocV05.h"
#include "TextFrameV014.h"
#include "TextViewV033.h"

#include "DDEFrameWnd.h"

#include "ToolsOptionsDoc.h"
#include "ToolsOptionsMDIChildWnd.h"
#include "FileAssociationsFormView.h"

//#include "D3d8.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CComModule _Module;

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

void GetModuleShortFileName(HINSTANCE hModule, CString &str)
{
    TCHAR lpFilename[MAX_PATH];
    GetModuleFileName(hModule, lpFilename, MAX_PATH);
    GetShortPathName(lpFilename, lpFilename, MAX_PATH);
    str = lpFilename;
}
int AppMsgBox
(
    HWND                    hwnd,
    UINT                    fuStyle,
    PTSTR                  pszFormat,
    ...
)
{
    va_list     va;
    TCHAR       ach[APP_MAX_STRING_ERROR_CHARS];
    int         n;

    //
    //  format and display the message..
    //
    va_start(va, pszFormat);
    wvsprintf(ach, pszFormat, va);
    va_end(va);

    n = MessageBox(hwnd, ach, _T("XF Player"), fuStyle);

    return (n);
} // AppMsgBox()

/////////////////////////////////////////////////////////////////////////////
// CVcdpApp


BEGIN_MESSAGE_MAP(CVcdpApp, CVmsGuiApp)
	//{{AFX_MSG_MAP(CVcdpApp)
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
	ON_UPDATE_COMMAND_UI(ID_FILE_MRU_FILE1, OnUpdateRecentFileMenu)
	ON_UPDATE_COMMAND_UI(ID_LANGUAGE_CHANGE, OnUpdateLanguageChangeMenu)
	ON_COMMAND(ID_LANGUAGE_ENUS, OnLanguageEnus)
	ON_UPDATE_COMMAND_UI(ID_LANGUAGE_ENUS, OnUpdateLanguageEnus)
	ON_COMMAND(ID_LANGUAGE_PTBR, OnLanguagePtbr)
	ON_UPDATE_COMMAND_UI(ID_LANGUAGE_PTBR, OnUpdateLanguagePtbr)
	ON_COMMAND(ID_LANGUAGE_DE, OnLanguageDe)
	ON_UPDATE_COMMAND_UI(ID_LANGUAGE_DE, OnUpdateLanguageDe)
	ON_COMMAND(ID_LANGUAGE_JP, OnLanguageJp)
	ON_UPDATE_COMMAND_UI(ID_LANGUAGE_JP, OnUpdateLanguageJp)
	ON_COMMAND(ID_CONTEXT_HELP, OnContextHelp)
	ON_COMMAND(ID_PLAYER, OnPlayer)
	ON_COMMAND(ID_TOOLS_OPTIONS_FILE_ASSOCIATIONS, OnToolsOptionsFileAssociations)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CVmsGuiApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CVmsGuiApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CVmsGuiApp::OnFilePrintSetup)
    ON_THREAD_MESSAGE(WM_USER, OnUserMessage)
    ON_THREAD_MESSAGE(WM_APP, OnAppMessage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVcdpApp construction

CVcdpApp::CVcdpApp()
:
m_evInitialized(FALSE, TRUE)
{
	m_pwndMessageBoxParent = NULL;
	CWStr::m_dwResourceCP = 1252;
//	m_pActiveDocument = NULL;
//	m_pPlayingDocument = NULL;
	m_pMainDocTemplate = NULL;
	m_pxfplayerdoc = NULL;
    m_pdoctemplateCD = NULL;
    m_pMidiDocTemplate = NULL;
	m_pthreadV1 = NULL;
	m_pthreadV2 = NULL;
	m_pthreadV3 = NULL;

//	m_pplayerdoctemplateOLE = NULL;

//	m_pSplashThread = NULL;
    m_pwelcomedlg = NULL; 
//	m_pdbcentral = NULL;
    
    //m_hPlayerMenuShared = NULL;
    m_hPlayerAccelTable = NULL;
    m_pmenuPlayerShared = NULL;
//    m_pilMenuV033 = new CImageList();

	m_pImaging = NULL;

    m_pAlbumThread = NULL;
    AFX_MODULE_STATE * pState = AfxGetAppModuleState();
    pState->m_pCurrentWinApp = this;
//	m_lpDirectDraw = NULL;
	m_pplaylistdoc = NULL;
	m_hmoduleResource = NULL;
	m_elanguage = langDefault;
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CVcdpApp object

//CVcdpApp theApp;

// This identifier was generated to be statistically unique for your app.
// You may change it if you prefer to choose a specific identifier.

// {F53B78E0-A6F5-41CF-B4FB-9F9FE49DD416}
static const CLSID clsidMid =
{ 0xf53b78e0, 0xa6f5, 0x41cf, { 0xb4, 0xfb, 0x9f, 0x9f, 0xe4, 0x9d, 0xd4, 0x16 } };

// {F53B78E0-A6F5-41CF-B4FB-9F9FE49DD416}
static const CLSID clsidKar =
{ 0xf53b78e0, 0xa6f5, 0x41cf, { 0xb4, 0xfb, 0x9f, 0x9f, 0xe4, 0x9d, 0xd4, 0x17 } };

// {F53B78E0-A6F5-41CF-B4FB-9F9FE49DD416}
static const CLSID clsidSt3 =
{ 0xf53b78e0, 0xa6f5, 0x41cf, { 0xb4, 0xfb, 0x9f, 0x9f, 0xe4, 0x9d, 0xd4, 0x18 } };

/////////////////////////////////////////////////////////////////////////////
// CVcdpApp initialization



BOOL CVcdpApp::InitInstance()
{
	
	//AfxMessageBox("Teste");
    if(!CVmsGuiApp::InitInstance())
        return FALSE;
	m_strHelpFilePath = m_strModuleFolder + _T("vmpen.chm");
	m_pszHelpFilePath = _tcsdup(m_strHelpFilePath);
	// Parse command line for standard shell commands, DDE, file open
    
	SetRegistryKey(_T("Veriwell"));

//	if(!SetLanguage(elanguageFinal))
//		return FALSE;
    //__asm
    //{
    //    int 3
    //}
//    AfxDebugBreak();
	TRACE(_T("CVcdpApp::InitInstance current thread %X\n"), GetCurrentThreadId());
//    AfxMessageBox(_T("1"));
	//m_pSplashThread = new CSplashThread(&m_pSplashThread);
	//m_pSplashThread->CreateThread();
    CSplashThread * pSplashThread = NULL;
    if(!m_cmdinfo.m_bRunAutomated &&
        !m_cmdinfo.m_bRunEmbedded
		&& m_cmdinfo.m_nShellCommand != CCommandLineInfo::FileDDE)
    {
        pSplashThread = (CSplashThread *) AfxBeginThread(RUNTIME_CLASS(CSplashThread));
        pSplashThread->Initialize(&pSplashThread);
        pSplashThread->m_evInitialized.Lock();
        //m_pMainWnd = pSplashThread->m_pMainWnd;
    }
    else
    {
        m_pMainWnd = NULL;
    }

	CKeeper <CWnd *> keepMessageBoxParent(
		&m_pwndMessageBoxParent,
		pSplashThread == NULL ?
			NULL
			: pSplashThread->m_pMainWnd,
		NULL,
		true);
    m_pfontcentral = CFontCentral::AppGetFontCentral();
    m_pfontcentral->Initialize();

    m_psavings = new CSavings();

	
/*    m_hhookMsgFilter = SetWindowsHookEx(
        WH_MSGFILTER,        // type of hook to install
        CMenuBarV033::MessageProc,     // address of hook procedure
        m_hInstance,    // handle to application instance
        m_nThreadID   // identity of thread to install hook for
        );*/
    CMessageFilterMainHook::AppGetMessageFilterMainHook(&m_pmfmh);
    m_pmfmh->MessageFilterHook();

/*	if(!MouseHook(m_hInstance))
	{
		AfxMessageBox(_T("Could not start application"));
		return FALSE;
	}*/

    {
        MEMORYSTATUS ms;
        GlobalMemoryStatus(&ms);
        if(ms.dwAvailPhys <  30 * 1024 * 1024)
        {
//            AfxMessageBox(_T("Operando em modo de economia de memória"));
            m_psavings->SetEconoMode(CSavings::SaveMemory);
        }
    }
//AfxMessageBox(_T("2"));
  	TRACE(_T("GdiGetBatchLimit %d"), GdiGetBatchLimit());
	GdiSetBatchLimit(50);

    m_XFToolTipV1ClassName = AfxRegisterWndClass(NULL, 0, 0, 0);

    m_strMessageWndClassName = AfxRegisterWndClass(NULL, 0, 0, 0);
    
    CMenuCentral::SetMenuCentral(new CMenuCentral());
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
        {ID_VIEW_LEVELMETER, 18},
		{ID_WINDOW_LEVELMETER, 18},
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
		{ID_VIEW_LYRICVIEW_SPECTRUM, 40},
		{ID_VIEW_PLAYERCONTROLSETV19, 41},
		{ID_WINDOW_PLAYERCONTROLSETV19, 41},
        {-1, -1}
    };

	CVmsGdiApi::Open();

    m_uiaPopupMenu.Add(IDR_XFPLAYER_MENUBAR);

    CMenuCentral::GetMenuCentral()->MenuV033CreateImageMap(uiaMenuV003Map);

    CRelationV001<UINT, UINT, UINT, UINT> * prel;
    CMenuCentral::GetMenuCentral()->MenuV033GetImageMap(&prel);
	CMenuCentral::GetMenuCentral()->MenuV033GetImageList()->Create(IDB_MENUV033, 18, 1, RGB(192, 192, 192));
	CImaging::GetImaging()->CreateGrayVRCPImageList(NULL, CMenuCentral::GetMenuCentral()->MenuV033GetImageListDisabled(), CMenuCentral::GetMenuCentral()->MenuV033GetImageList());
    m_pmenuPlayerShared = new CMenuV033(
        CMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
        CMenuCentral::GetMenuCentral()->MenuV033GetImageListDisabled(),
        prel,
        CFontCentral::AppGetFontCentral()->GetMenuFont());

    CString strModuleFolder(m_strModuleFolder);
	CString strLib;
    CString strExe;
//	strLib = ;
//    CString str;
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
    

//    NONCLIENTMETRICS ncm;
  //  ncm.cbSize = sizeof(NONCLIENTMETRICS);
    //::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0);
	//VERIFY(m_pfontStandard->CreateFontIndirect(&ncm.lfMenuFont));

//    m_pilMenuV033->Create(IDB_MENUV033, 18, 1, RGB(192, 192, 192));

    

//    InitDirectDraw();

	m_pImaging = new CImaging();
    CImaging::SetImaging(m_pImaging);

    m_pMixerCentral = new CMixerCentral();
    m_pMixerCentral->CreateEx(
        0, m_strMessageWndClassName, NULL,
        0, 0, 0, 0,
        NULL, NULL, NULL);

    CMidiCentral::SetMidiCentral(new CMidiCentral());
//    CWaveCentral::SetWaveCentral(new CWaveCentral());

	
	
	
	
	
	
	
	//VERIFY(WaveCentralInitialize());
	

	//if(!BeginVSeriesThreads())
	//	return FALSE;


	
	m_XFViewClassName = AfxRegisterWndClass(
		CS_DBLCLKS |
		CS_OWNDC,
		0, 0, 0);
    CMidiCentral::GetMidiCentral()->m_uiMidiOutDevice = MIDI_MAPPER;
    m_uiWaveInDevice = WAVE_MAPPER;

#if  (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) // DCOM
	HRESULT hRes = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
#else
	CoInitialize(NULL);
#endif
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

//	if (!InitATL())
//		return FALSE;

	if (!InitATL())
		return FALSE;

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
	
	if(!InitializeDataCentral(m_cmdinfo))
	{
		AfxMessageBox(_T("Database initialization failed"));
		return FALSE;
	}

	ELanguage elanguageFinal;
	ELanguage elanguageDefault = GetDefaultLanguage();
	ELanguage elanguageOldDefault = (ELanguage) GetProfileInt(_T("Language"), _T("Default"), langDefault);
	if(elanguageDefault != elanguageOldDefault)
		elanguageFinal = elanguageDefault;
	else
		elanguageFinal = (ELanguage) GetProfileInt(_T("Language"), _T("Current"), elanguageDefault);
	WriteProfileInt(_T("Language"), _T("Default"), elanguageDefault);
	//elanguage = GetDefaultLanguage();
	SetLanguage(elanguageFinal);

	if(pSplashThread != NULL)
	{
		pSplashThread->m_pMainWnd->SendMessage(APPM_LANGUAGE, WPARAM_LANGUAGE_UPDATE, 0);
	}

	//AfxMessageBox(_T("7.1"));
	LoadAppSettings();
    //AfxMessageBox(_T("7.2"));



	LoadStdProfileSettings(m_nMaxMRU);  // Load standard INI file options (including MRU)

//    AddToRecentFileList("c:\mid1.mid");

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
    
    //AfxMessageBox(_T("5"));

	//AfxMessageBox(_T("Enter here"));

	CSingleDocTemplate* pPlayerSingleDocTemplate;
	pPlayerSingleDocTemplate = new CSingleDocTemplate(
		IDR_CD,
		RUNTIME_CLASS(CCDDoc),
		RUNTIME_CLASS(CCDFrame),       // main SDI frame window
		RUNTIME_CLASS(CCDiew));
	m_pdoctemplateCD = (CSinngleDocTemplate*) pPlayerSingleDocTemplate;
	pPlayerSingleDocTemplate->SetServerInfo(
		IDR_XFPLAYER_SERVER_EMBEDDING, IDR_XFPLAYER_SERVER_INPLACE,
		RUNTIME_CLASS(CXfplayerIPFrame));
	AddDocTemplate(pPlayerSingleDocTemplate);

/*	pPlayerSingleDocTemplate = new CXfplayerSingleDocTemplate(
		IDR_KAR,
		RUNTIME_CLASS(CXfplayerDoc),
		RUNTIME_CLASS(CKaraokeSDIFrame),       // main SDI frame window
		RUNTIME_CLASS(CXfplayerView));
	m_pdoctemplateKar = (CXfplayerSingleDocTemplate*) pPlayerSingleDocTemplate;
	pPlayerSingleDocTemplate->SetServerInfo(
		IDR_XFPLAYER_SERVER_EMBEDDING, IDR_XFPLAYER_SERVER_INPLACE,
		RUNTIME_CLASS(CXfplayerIPFrame));
	AddDocTemplate(pPlayerSingleDocTemplate);*/

/*	pPlayerSingleDocTemplate = new CXfplayerSingleDocTemplate(
		IDR_ST3,
		RUNTIME_CLASS(CXfplayerDoc),
		RUNTIME_CLASS(CKaraokeSDIFrame),       // main SDI frame window
		RUNTIME_CLASS(CXfplayerView));
	m_pdoctemplateSt3 = (CXfplayerSingleDocTemplate*) pPlayerSingleDocTemplate;
	pPlayerSingleDocTemplate->SetServerInfo(
		IDR_XFPLAYER_SERVER_EMBEDDING, IDR_XFPLAYER_SERVER_INPLACE,
		RUNTIME_CLASS(CXfplayerIPFrame));
	AddDocTemplate(pPlayerSingleDocTemplate);*/

//	m_pplayerdoctemplateOLE = new CXfplayerSingleDocTemplate(
//		IDR_XFPLAYER,
//		RUNTIME_CLASS(CXfplayerDoc),
//		RUNTIME_CLASS(CXfplayerIPFrame),       // main SDI frame window
//		RUNTIME_CLASS(CXfplayerView));
//	m_pplayerdoctemplateOLE->SetServerInfo(
//		IDR_XFPLAYER_SERVER_EMBEDDING, IDR_XFPLAYER_SERVER_INPLACE,
//		RUNTIME_CLASS(CXfplayerIPFrame));

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


    CVmsGuiMultiDocTemplate* pPlaylistDocTemplate;
	pPlaylistDocTemplate = new CVmsGuiMultiDocTemplate(
		IDR_PLAYLIST,
		RUNTIME_CLASS(CPlaylistDoc),
		RUNTIME_CLASS(CPlaylistFrame), // custom MDI child frame
		RUNTIME_CLASS(CPlaylistListView));
//	pMSMultiDocTemplate->SetServerInfo(
//		IDR_MUSICALSTUDIO_SERVER_EMBEDDING, IDR_MUSICALSTUDIO_SERVER_INPLACE,
//		RUNTIME_CLASS(CMSInPlaceFrame));
	AddDocTemplate(pPlaylistDocTemplate);
    m_pPlaylistDocTemplate = pPlaylistDocTemplate;

    CVmsGuiMultiDocTemplate * pvmstextdoctemplate;
	pvmstextdoctemplate = new CVmsGuiMultiDocTemplate(
		IDR_VMSTEXT,
		RUNTIME_CLASS(CVmsTextDoc),
		RUNTIME_CLASS(CVmsTextFrame),
		RUNTIME_CLASS(CVmsTextView));
	AddDocTemplate(pvmstextdoctemplate);
	m_pvmstextdoctemplate = pvmstextdoctemplate;


	m_pdoctemplateFileAssociations = new
			CVmsGuiSingleDocTemplate(
			IDR_FILE_ASSOCIATIONS,
			RUNTIME_CLASS(CToolsOptionsDoc),
			RUNTIME_CLASS(CToolsOptionsMDIChildWnd),
			RUNTIME_CLASS(CFileAssociationsFormView));


    // Midi Document Template
    
//	pMSMultiDocTemplate->SetServerInfo(
//		IDR_MUSICALSTUDIO_SERVER_EMBEDDING, IDR_MUSICALSTUDIO_SERVER_INPLACE,
//		RUNTIME_CLASS(CMSInPlaceFrame));


    // Connect the COleTemplateServer to the document template.
	//  The COleTemplateServer creates new documents on behalf
	//  of requesting OLE containers by using information
	//  specified in the document template.
	m_serverMid.ConnectTemplate(clsidMid, m_pdoctemplateMid, FALSE);
	//m_serverKar.ConnectTemplate(clsidKar, m_pdoctemplateKar, FALSE);
	//m_serverSt3.ConnectTemplate(clsidSt3, m_pdoctemplateSt3, FALSE);

	// Register all OLE server factories as running.  This enables the
	//  OLE libraries to create objects from other applications.
	COleTemplateServer::RegisterAll();
	_Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, 
		REGCLS_MULTIPLEUSE);



	if(m_cmdinfo.m_nShellCommand == CCommandLineInfo::FileDDE)
	{
		m_pddeframewnd = new CDDEFrameWnd();
		if(!m_pddeframewnd->LoadFrame(IDR_DDE))
			return FALSE;
	}

		// Note: MDI applications register all server objects without regard
		//  to the /Embedding or /Automation on the command line.
//AfxMessageBox(_T("6"));
	// create main MDI Frame window
	
    //AfxMessageBox(_T("7.3"));
//	CRuntimeClass* pRuntimeClass = RUNTIME_CLASS(CKaraokeSDIFrame);
//	CObject* pObject = pRuntimeClass->CreateObject();
//	ASSERT(pObject->IsKindOf(RUNTIME_CLASS(CMainFrame)));
//	CMainFrame* pMainFrame = (CMainFrame *) pObject;
//    CKaraokeSDIFrame* pMainFrame = (CKaraokeSDIFrame *) m_pMainWnd;
    //AfxMessageBox(_T("7.4"));
//	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
//		return FALSE;
//	m_pMainWnd = pMainFrame;

    //AfxMessageBox(_T("8"));


	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Check to see if launched as OLE server
	if (m_cmdinfo.m_bRunEmbedded || m_cmdinfo.m_bRunAutomated)
	{
//        m_pSplashThread->Kill();
		// Application was run with /Embedding or /Automation.  Don't show the
		//  main window in this case.
        m_evInitialized.SetEvent();
        //__asm
        //{
        //    int 3
        //}
		if(m_cmdinfo.m_bRunEmbedded)
		{
			//AfxMessageBox(_T("Veriwell Musical Player Running Embedded"));
		}
		if(m_cmdinfo.m_bRunAutomated)
		{
			//AfxMessageBox(_T("Veriwell Musical Player Running Automated"));
		}
		
		return TRUE;
	}

	if(m_cmdinfo.m_nShellCommand != CCommandLineInfo::FileDDE)
	{
		// create main MDI Frame window
/*		CMainFrame* pMainFrame = new CMainFrame;
		if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
			return FALSE;
		m_pMainWnd = pMainFrame;

		// Enable drag/drop open
		m_pMainWnd->DragAcceptFiles();*/
	}


	// When a server application is launched stand-alone, it is a good idea
	//  to update the system registry in case it has been damaged.
	m_serverMid.UpdateRegistry(OAT_DOC_OBJECT_SERVER, IDS_MID);
	m_serverMid.UpdateRegistry(OAT_DOC_OBJECT_SERVER, IDS_KAR);
	m_serverMid.UpdateRegistry(OAT_DOC_OBJECT_SERVER, IDS_ST3);
//	m_serverKar.UpdateRegistry(OAT_DOC_OBJECT_SERVER);
//	m_serverSt3.UpdateRegistry(OAT_DOC_OBJECT_SERVER);
	COleObjectFactory::UpdateRegistryAll();

    //AfxMessageBox(_T("9"));
	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(m_cmdinfo))
		return FALSE;


	//AfxDebugBreak();

	if(m_cmdinfo.m_nShellCommand == CCommandLineInfo::FileDDE)
	{
		ASSERT_KINDOF(CDDEFrameWnd, m_pddeframewnd);
		m_pddeframewnd->ShowWindow(SW_HIDE);
		m_pddeframewnd->UpdateWindow();
	}
	else
	{
		if(m_pMainWnd == NULL)
		{
			OnFileNew();
		}
/*		if(m_pMainWnd != NULL)
		{
			CKaraokeSDIFrame* pMainFrame = (CKaraokeSDIFrame *) GetKaraokeSDIFrame();
			m_pMainWnd = pMainFrame;
			
			ASSERT_KINDOF(CKaraokeSDIFrame, pMainFrame);

			if(m_cmdinfo.m_nShellCommand != CCommandLineInfo::FileOpen)
			{
				OpenDefaultPlaylist();
			}

			if(pMainFrame != NULL)
			{
				// The main window has been initialized, so show and update it.
				pMainFrame->ShowWindow(m_nCmdShow);
				pMainFrame->UpdateWindow();
				pMainFrame->ActivateFrame();
			}
		}*/
	}



    /*
     * create the main DirectDraw object
     */

	// The one and only window has been initialized, so show and update it.


    
    // Enable drag/drop open
	if(m_pMainWnd != NULL)
	{
		m_pMainWnd->DragAcceptFiles();
	}


	if(m_pMainWnd != NULL)
	{
		// The main window has been initialized, so show and update it.
		m_pMainWnd->ShowWindow(m_nCmdShow);
		m_pMainWnd->UpdateWindow();
	}

    _Module.UpdateRegistryFromResource(IDR_VMSPLAYER, TRUE);
	_Module.RegisterServer(TRUE);



	if(m_cmdinfo.m_nShellCommand != CCommandLineInfo::FileDDE)
	{
		VerifyBrowsers();

		m_pdbcentral->SongsPostBuildAlbumMessage(
			AfxGetApp(),
			(SongsAlbum::EBuildSongsAlbumOperation)
			(SongsAlbum::eBuildSongsAlbumDeleteNotFound |
			SongsAlbum::eBuildSongsAlbumAddNew |
			SongsAlbum::eBuildSongsAlbumCreateSearchReferences),
			false);
	}




	

	if(pSplashThread != NULL)
	{
		pSplashThread->SetFocusToApp();
		pSplashThread->Kill();
		keepMessageBoxParent.KeepAway();
	}

    m_evInitialized.SetEvent();

    CWnd * pwndMain = m_pMainWnd;

	if(m_cmdinfo.m_nShellCommand != CCommandLineInfo::FileDDE)
	{
		SendMessageToWindows(WM_APP, 179, 0);
	}

	_vmsp::CFileAssociation fileassociation;

	fileassociation.CheckAssociations();

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
	afx_msg void OnToolsCompactdatabase();
	afx_msg void OnUpdateToolsCompactdatabase(CCmdUI* pCmdUI);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnButtonWwwveriwelldotcom();
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
	ON_COMMAND(ID_TOOLS_COMPACTDATABASE, OnToolsCompactdatabase)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_COMPACTDATABASE, OnUpdateToolsCompactdatabase)
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_BUTTON_WWWVERIWELLDOTCOM, OnButtonWwwveriwelldotcom)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CVcdpApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CVcdpApp message handlers





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




int CVcdpApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
//    UnhookWindowsHookEx(
  //      m_hhookMsgFilter
    //    );
    if(m_pmfmh != NULL)
    {
        m_pmfmh->MessageFilterUnhook();
//        delete m_pmfmh;
        m_pmfmh = NULL;
    }
    //MessageFilterUnhook();

	MouseUnhook();
 
    m_pdbcentral->SetBuildAlbumThreadsCancelFlag();

	SetThreadPriority(THREAD_PRIORITY_HIGHEST);
    
//    if(m_pdbcentral != NULL)
  //  {
    //    m_pdbcentral->Close();
	  //  delete m_pdbcentral;
//        CDataCentral::SetDBCentral(NULL);
    //}

	VERIFY(WaveCentralFinalize());
    if(m_pMixerCentral != NULL)
    {
        m_pMixerCentral->SendMessage(WM_CLOSE);
        delete m_pMixerCentral;
        m_pMixerCentral = NULL;
    }

    if(m_pfontcentral != NULL)
    {
//        delete m_pfontcentral;
        m_pfontcentral = NULL;
    }
	
	if(m_pthreadV1 != NULL)
	{
		m_pthreadV1->SetThreadPriority(THREAD_PRIORITY_NORMAL);
		m_pthreadV1->PostThreadMessage(WM_QUIT, 0, 0);
	}


	if(m_pthreadV2 != NULL)
	{
		m_pthreadV2->SetThreadPriority(THREAD_PRIORITY_NORMAL);
		m_pthreadV2->PostThreadMessage(WM_QUIT, 0, 0);
	}
	
	if(m_pthreadV3 != NULL)
	{
		m_pthreadV3->SetThreadPriority(THREAD_PRIORITY_NORMAL);
		m_pthreadV3->PostThreadMessage(WM_QUIT, 0, 0);
	}

    if(m_pImaging != NULL)
        delete m_pImaging;

    if(m_pmenuPlayerShared != NULL)
        delete m_pmenuPlayerShared;

//    if(m_pilMenuV033 != NULL)
  //      delete m_pilMenuV033;


	CVmsGdiApi::Close();


	if (m_bATLInited)
	{
		_Module.RevokeClassObjects();
		_Module.Term();
	
	}
    /*if(g_vmshookpaint_hhk != NULL)
    {
        UnhookWindowsHookEx(
            g_vmshookpaint_hhk);
    }*/

	if(m_hmoduleResource != NULL)
	{
		FreeLibrary(m_hmoduleResource);
	}

	return CVmsGuiApp::ExitInstance();

}





void AddStringLines(LPCTSTR lpStr, CStringArray *pArray)
{
	CString str(lpStr);
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

void CVcdpApp::Exit()
{

    ASSERT(m_pMainWnd != NULL);
    m_pMainWnd->SendMessage(WM_CLOSE);

}

void CVcdpApp::OnFileOpen() 
{
	// TODO: Add your command handler code here
//	CVmsGuiApp::OnFileOpen();
//	return;
	CXfplayerOpenFileDialog dlgFile;

	
	dlgFile.DoPrompt(IDS_XFPLAYER_OPENFILETITLE,
		OFN_HIDEREADONLY
		| OFN_FILEMUSTEXIST
		| OFN_ALLOWMULTISELECT
		| OFN_EXPLORER);

	CStrArray & straFile = dlgFile.m_straFile;

	CDocument * pdoc;
	bool bFirst = true;
    for(int i = 0; i < straFile.GetSize(); i++)
	{
		if(m_pdoctemplateKar->MatchDocType(straFile[i], pdoc) == CXfplayerSingleDocTemplate::yesAttemptNative)
		{
			m_pdoctemplateKar->ReserveSong(straFile[i], bFirst, true);
			bFirst = false;
		}
		else if(m_pdoctemplateMid->MatchDocType(straFile[i], pdoc) == CXfplayerSingleDocTemplate::yesAttemptNative)
		{
			m_pdoctemplateMid->ReserveSong(straFile[i], bFirst, true);
			bFirst = false;
		}
		else if(m_pdoctemplateSt3->MatchDocType(straFile[i], pdoc) == CXfplayerSingleDocTemplate::yesAttemptNative)
		{
			m_pdoctemplateSt3->ReserveSong(straFile[i], bFirst, true);
			bFirst = false;
		}
		else
		{
			CVmsGuiApp::OpenDocumentFile(straFile[i]);
		}
	}


}

void CVcdpApp::OnFileNew() 
{
	// TODO: Add your command handler code here
	//CVmsGuiApp::OnFileNew();
	m_pdoctemplateMid->OpenDocumentFile(NULL);
}


//CWaveIn * CVcdpApp::GetWaveIn()
//{

	//return m_pWaveIn;
//}

//LPDIRECTDRAW CVcdpApp::GetDirectDraw()
//{
//	return m_lpDirectDraw;
//}


/*CTypedPtrArray <CPtrArray, CXfplayerFont *> *
	CVcdpApp::GetLyricViewFonts()
{
	return m_pLyricViewFonts;
}

CTypedPtrArray <CPtrArray, CXfplayerFont *> *
	CVcdpApp::GetTitleFonts()
{
	return m_pTitleFonts;
}

CTypedPtrArray <CPtrArray, CXfplayerFont *> *
	CVcdpApp::GetSubTitleFonts()
{
	return m_pSubTitleFonts;
}

/*CFont * CVcdpApp::GetMenuFont()
{
    return m_pfontMenu;
}*/

/*void CVcdpApp::CreateLyricViewFonts()
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


//BOOL CVcdpApp::InitATL()
//{
//	m_bATLInited = TRUE;
//
//	_Module.Init(ObjectMap, AfxGetInstanceHandle());
//	_Module.dwThreadID = GetCurrentThreadId();
//
//	return TRUE;
//
//}

BOOL CVcdpApp::PreTranslateMessage(MSG* pMsg) 
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
                    CDWArray * pdwa = (CDWArray *) pMsg->lParam;
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
	else if(pMsg->message == VMSM_EXCEPTION)
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
	}
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
                if(pDataCentral->IsBuildingSongsAlbum())
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
                }
            }
            else if(pMsg->wParam == NOTIFY_BUILDALBUMDELETE)
            {
                CDBCentral* pDataCentral = GetDBCentral();
                pDataCentral->DeleteBuildAlbumThreadData((CDBBuildAlbumThreadData *) pMsg->lParam);
            }
            else if(pMsg->wParam == NOTIFY_BUILDALBUMFINISHED)
            {
                CDBCentral* pDataCentral = GetDBCentral();
                pDataCentral->OnFinishedBuildAlbum((CDBBuildAlbumThreadData *) pMsg->lParam);
            }
            return TRUE;
        }
    }
	return CVmsGuiApp::PreTranslateMessage(pMsg);
}

CSplashThread * CVcdpApp::GetSplashThread_()
{
	//return m_pSplashThread;
    return NULL;
}


void CVcdpApp::LoadAppSettings()
{
//		if(!m_pdbcentral->IsWorking())
//		return;

	CDBLongSet * pLongsSet = m_pdbcentral->GetDBLongSet();
//	if(pLongsSet->m_spRowset != NULL)
//	{
		if(!pLongsSet->Load(_T("MRU"), _T("Count"), (int *) &m_nMaxMRU))
			m_nMaxMRU = _AFX_MRU_COUNT;

        int iEnable;
        if(!pLongsSet->Load(_T("MRU"), _T("Enable"), &iEnable))
			m_nMaxMRU = _AFX_MRU_COUNT;
        if(!iEnable)
            m_nMaxMRU = 0;

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
		CString strModuleFolder(m_strModuleFolder);
		CString strPath;
        CString str;
        str.LoadString(IDS_FOLDER_IMAGES);
		strPath += str;
		CDBImageDirectorySet * pImagesDirsSet = m_pdbcentral->GetImageDirSet();
        bAdd = true;
		if(pImagesDirsSet->m_spRowsetChange == NULL)
        {
            m_pdbcentral->OpenImagesDirsSet();
            if(pImagesDirsSet->m_spRowsetChange == NULL)
            {
//                AfxMessageBox(_T("CVcdpApp::LoadAppSettings() Fail 1000"));
  //              bAdd = false;
            }

        }
        if(bAdd)
        {
            TCHAR buffer[MAX_PATH * 2];
            GetWindowsDirectory(buffer, sizeof(buffer));
            CString strWallpaper(buffer);
            strWallpaper += "\\Web\\Wallpaper";
		    pImagesDirsSet->Add(strPath);
            pImagesDirsSet->Add(strWallpaper);
            pImagesDirsSet->Add(buffer);
            pImagesDirsSet->Close();
            m_pdbcentral->OpenImagesDirsSet();
        }
		
		GetDefaultSongFolderPath(strPath);
		CDBSongDirectorySet * pSongsDirsSet = m_pdbcentral->GetSongsDirsSet();
        bAdd = true;
		if(pSongsDirsSet->m_spRowsetChange == NULL)
        {
            m_pdbcentral->OpenSongsDirsSet();
            if(pSongsDirsSet->m_spRowsetChange == NULL)
            {
    //            AfxMessageBox(_T("CVcdpApp::LoadAppSettings() Fail 2000"));
      //          bAdd = false;
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
    CMidiCentral::GetMidiCentral()->m_uiMidiOutDevice = uiDev;
    
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

}


void CVcdpApp::OnHelp() 
{
	// TODO: Add your command handler code here
	CVmsGuiApp::OnHelp();
}

void CVcdpApp::RegisterShellFileTypes(BOOL bCompat)
{
	ASSERT(m_pDocManager != NULL);
//	m_pDocManager->RegisterShellFileTypes(bCompat);
//	ASSERT(!m_pDocManager->m_templateList.IsEmpty());  // must have some doc templates

	CString strPathName, strTemp, strResourcePathName;
 
	GetModuleShortFileName(AfxGetInstanceHandle(), strPathName);

	CStrArray strarray;

	CString str;

	str.LoadString(IDS_MID);
	strarray.Add(str);
	str.LoadString(IDS_KAR);
	strarray.Add(str);
	str.LoadString(IDS_ST3);
	strarray.Add(str);

	CStrTokenizer strTokenizer;

	strTokenizer = str;

	CStrArray strarrayDocString;


	_vmsp::CFileAssociation fileassociation;

	for (int iTemplate = 0; iTemplate < strarray.GetSize(); iTemplate++)
	{
		strarrayDocString.RemoveAll();
		strarrayDocString.AddTokens(strarray[iTemplate],"\n", true);
		
		CString strOpenCommandLine = strPathName;
		CString strPrintCommandLine = strPathName;
		CString strPrintToCommandLine = strPathName;
		CString strDefaultIconCommandLine = strPathName;
        
        int nIconIndex = 1;
		if (bCompat)
		{
			CString strIconIndex;
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

		CString strFilterExt, strFileTypeId, strFileTypeName;
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
            CStrTokenizer strtokenizer;
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
		fileassociation.UpdateServerRegistration(strarray[iTemplate]);
	}
}

//bool CVcdpApp::InitDirectDraw()
//{
//    HANDLE hLibrary = LoadLibrary(_T("d3d8.dll"));
//    if(hLibrary == NULL)
//        return false;
//    m_spDirectDraw = Direct3DCreate8(D3D_SDK_VERSION);
//    return true;
//}

void CVcdpApp::OnHelpFinder() 
{
	// TODO: Add your command handler code here
 //   CVmsGuiApp::OnHelpFinder();
	if(m_elanguage == langPtBr)
	{
		HtmlHelp(NULL, "vmpptbr.chm", HH_DISPLAY_TOPIC, 0);
	}
	else
	{
		HtmlHelp(NULL, "vmpen.chm", HH_DISPLAY_TOPIC, 0);
	}


}

BOOL CVcdpApp::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CVmsGuiApp::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

/*CXfplayerDoc	*CVcdpApp::GetPlayerDocument()
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

void CAboutDlg::OnToolsCompactdatabase() 
{
	// TODO: Add your command handler code here
    
}

void CAboutDlg::OnUpdateToolsCompactdatabase(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CVcdpApp::OnFileNewFromplayerview() 
{
	// TODO: Add your command handler code here
//    CXfplayerDoc * pDoc = (CXfplayerDoc *) GetPlayerDocTemplate()->GetOnlyDoc();
  //  m_pMainDocTemplate->OpenDocumentFile(pDoc->GetPathName());
	
}

void CVcdpApp::OnUpdateFileNewFromplayerview(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
//    CXfplayerDoc * pDoc = (CXfplayerDoc *) GetPlayerDocTemplate()->GetOnlyDoc();
  //  pCmdUI->Enable(pDoc->GetMidiPlayer() &&
    //   pDoc->GetMidiSequence()->GetState() != CMidiSequence::StatusNoFile);
}

CXfplayerSingleDocTemplate * CVcdpApp::GetPlayerDocTemplate()
{
    return m_pdoctemplateMid;
}

/*void CVcdpApp::SetPlayerDocument(CXfplayerDoc *lpDoc)
{
    m_pPlayerDoc = lpDoc;
}*/

/*CXfplayerFont * CVcdpApp::GetTitleFont()
{
    return NULL;
}

CXfplayerFont * CVcdpApp::GetSongLabelFont()
{
    return m_lpSongLabelFont;
}

CXfplayerFont * CVcdpApp::GetSongListFont()
{
    return m_lpSongListFont;
}*/

CMultiDocTemplate * CVcdpApp::GetPlaylistDocTemplate()
{
    return m_pPlaylistDocTemplate;
}

CImaging * CVcdpApp::GetImaging()
{
	return m_pImaging;
}

int CVcdpApp::GetEconoMode_()
{
    ASSERT(FALSE);
    return -1;
    //return m_iEconoMode;
}

void CVcdpApp::OnChangeEconoMode()
{
    if(CDataCentral::GetDB())
        if(CDataCentral::GetDB()->GetDBLongSet())
            CDataCentral::GetDB()->GetDBLongSet()->Save(_T("EconoMode"), _T("Value"), m_psavings->GetEconoMode());
    if(m_pMainWnd != NULL)
        m_pMainWnd->SendMessage(VMSM_ECONOMODECHANGE, m_psavings->GetEconoMode());
}

/*void CVcdpApp::SetEconoMode(int iNewEconoMode)
{
    
    if(m_iEconoMode != iNewEconoMode)
    {
        m_iEconoMode = iNewEconoMode;
        OnChangeEconoMode();
        m_pdbcentral->GetDBLongSet()->Save(_T("EconoMode"), _T("Value"), m_iEconoMode);
    }
    
}*/


CKaraokeSDIFrame * CVcdpApp::GetKarWnd()
{
    CXfplayerDoc * pdoc;
    if(CXfplayerSingleDocTemplate::AppGetPlayerDocTemplate())
    {
        if(pdoc = (CXfplayerDoc *) CXfplayerSingleDocTemplate::AppGetPlayerDocTemplate()->GetOnlyDoc())
        {
            if(pdoc->GetLyricView())
            {
                return (CKaraokeSDIFrame *) pdoc->GetLyricView()->GetParentFrame();
            }
        }
    }
    return NULL;
}

void CVcdpApp::OnToolsAlbum() 
{
	// TODO: Add your command handler code here
    ViewToolsAlbum();
	
}

void CVcdpApp::OnUpdateToolsAlbum(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

VMSRESULT CVcdpApp::OpenToolsAlbum()
{
	if(DB()->IsWorking())
	{
		CWaitCursor cwc;



		if(m_pAlbumThread == NULL)
		{
			CreateAlbumThread();
		}
		if(m_pAlbumThread != NULL)
		{
			m_pAlbumThread->PostMessageViewAlbum(false);
		}
		else
		{
		}
	}
	else
	{
		AfxMessageBox(IDS_NODATABASESUPPORTERROR_RESOURCEUNAVAILABLE, MB_ICONINFORMATION);
	}
//    if(m_pAlbumThread == NULL)
  //  {
    //    m_pAlbumThread = (CAlbumThread *) AfxBeginThread(
      //      RUNTIME_CLASS(CAlbumThread));

//    }
  //  else
    //{
      //  m_pAlbumThread->ViewToolsAlbum();
    //}
//        CVcdpApp * pApp = (CVcdpApp *)AfxGetApp();
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
	        //CObject* pObject = pRuntimeClass->CreateObject();
	        //ASSERT(pObject->IsKindOf(RUNTIME_CLASS(CAlbumFrameWnd)));
	        //CAlbumFrameWnd * pAlbumFrameWnd = (CAlbumFrameWnd *) pObject;
            //CCreateContext cc;
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
                    &CWnd::wndTop,
			        0, 0,
			        0, 0,
			        SWP_NOMOVE |
			        SWP_NOSIZE); //|
			        //SWP_SHOWWINDOW);*/
               //m_pAlbumFrameWnd->InitialUpdateFrame(NULL, true);
                //m_pAlbumFrameWnd->ActivateFrame();
            /*}
	    }
	    
//	    CWnd * pParent = GetParent();
    }
    else
    {
        AfxMessageBox(
            IDS_NODATABASESUPPORTERROR_RESOURCEUNAVAILABLE,
            MB_OK |
            MB_ICONINFORMATION);

    }*/

    /*CVcdpApp * pApp = (CVcdpApp *)AfxGetApp();
    if(pApp->GetDBCentral()->IsWorking())
    {
	    if(m_pAlbumFrameWnd == NULL)
	    {
            CRuntimeClass* pRuntimeClass = RUNTIME_CLASS(CAlbumFrameWnd);
	        CObject* pObject = pRuntimeClass->CreateObject();
	        ASSERT(pObject->IsKindOf(RUNTIME_CLASS(CAlbumFrameWnd)));
	        CAlbumFrameWnd * pAlbumFrameWnd = (CAlbumFrameWnd *) pObject;
            CCreateContext cc;
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
                    &CWnd::wndTop,
			        0, 0,
			        0, 0,
			        SWP_NOMOVE |
			        SWP_NOSIZE); //|
			        //SWP_SHOWWINDOW);*/
               //m_pAlbumFrameWnd->InitialUpdateFrame(NULL, true);
                //m_pAlbumFrameWnd->ActivateFrame();
  //          }
//	    }
	    
//	    CWnd * pParent = GetParent();
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

VMSRESULT CVcdpApp::ViewToolsAlbum()
{
    return OpenToolsAlbum();
}

/*CSingleDocTemplate * CVcdpApp::GetAlbumDocTemplate()
{
    return m_pAlbumDocTemplate;
}*/

CAlbumThread * CVcdpApp::GetAlbumThread()
{
    if(m_pAlbumThread == NULL)
    {
        CreateAlbumThread();
    }
    return m_pAlbumThread;
}

CMultiDocTemplate * CVcdpApp::GetMidiDocTemplate()
{
    return m_pMidiDocTemplate;
}

/*CFont * CVcdpApp::GetStandartFont()
{
    return m_pfontMenu;
}*/

/*VMSRESULT CVcdpApp::ReserveSong_(int iCode)
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
                CMultiDocTemplate * pPlaylistDocTemplate = GetPlaylistDocTemplate();
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

VMSRESULT CVcdpApp::SetAlbumThread(CAlbumThread *pAlbumThread)
{
    m_pAlbumThread = pAlbumThread;
    return VMSR_SUCCESS;
}

CString CVcdpApp::GetAppFolder()
{
    TCHAR lpszModuleFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, lpszModuleFilePath, MAX_PATH + 1);
	TCHAR lpszModuleFolder[MAX_PATH + 1];
	LPTSTR lpszModuleFileName;
	GetFullPathName(lpszModuleFilePath, MAX_PATH + 1, lpszModuleFolder, &lpszModuleFileName);
	CString strModuleFolder(lpszModuleFolder, lpszModuleFileName - lpszModuleFolder);
    return strModuleFolder;
}

VMSRESULT CVcdpApp::CreateAlbumThread()
{
    m_pAlbumThread = (CAlbumThread *) AfxBeginThread(
        RUNTIME_CLASS(CAlbumThread)); 
    if(m_pAlbumThread != NULL)
    {
        return VMSR_SUCCESS;
    }
    else
    {
        return VMSR_E_FAIL;
    }

}

/*VMSRESULT CVcdpApp::ReserveSong(LPCTSTR lpcszPath, bool bDoPlay)
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
                CMultiDocTemplate * pPlaylistDocTemplate = GetPlaylistDocTemplate();
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


VMSRESULT CVcdpApp::ReserveSongs(LPINT lpiaSongs, int iSongCount)
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
                CMultiDocTemplate * pPlaylistDocTemplate = GetPlaylistDocTemplate();
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

void CAboutDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}


CMessageFilterMainHook * CVcdpApp::GetMessageFilterMainHook()
{
    return m_pmfmh;
}

void CVcdpApp::OnToolsOptions() 
{
	// TODO: Add your command handler code here
	
    COptionsDialog optionsDialog;
	optionsDialog.DoModal();

}

void CVcdpApp::OnUpdateToolsOptions(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    pCmdUI->Enable();	
}


CDocument* CVcdpApp::OpenDocumentFile(LPCTSTR lpszFileName) 
{
	// TODO: Add your specialized code here and/or call the base class
	//ReserveSong(lpszFileName, true);
	return CVmsGuiApp::OpenDocumentFile(lpszFileName);
}

CSavings * CVcdpApp::GetSavings()
{
    return m_psavings;

}


CFontCentral * CVcdpApp::GetFontCentral()
{
    return m_pfontcentral;
}

afx_msg void CVcdpApp::OnAppMessage(WPARAM wParam, LPARAM lParam )
{
	switch(wParam)
	{
    case 534231:
        {
            GetKarWnd()->SendMessageToDescendants(WM_APP, 534231);
        }
	case 178:
		{
	        LPSCOREUPDATEMESSAGE lpsum = (LPSCOREUPDATEMESSAGE) lParam ;
			if(lpsum == NULL)
				return;
			CXfplayerDoc * pdoc = (CXfplayerDoc *) CXfplayerSingleDocTemplate::AppGetPlayerDocTemplate()->GetOnlyDoc();
			if(pdoc == NULL)
			{
				delete lpsum;
				return;
			}
			CAudioSpectrumViewUpdateHint uh;
			uh.m_lpwaveformatex = WaveCentralGetWaveIn()->GetFormatEx();			
			uh.m_dDeltaScore = lpsum->dDeltaScore;
			uh.m_dScoreAddUp = lpsum->dScoreAddUp;
			delete lpsum;
			lpsum = NULL;
			CDocument * pdoctarget = (CDocument *) pdoc->GetAudioSpectrumDoc();
			pdoctarget->UpdateAllViews(NULL, 0, &uh);
		}
		break;
	default:
		break;
	}
}


afx_msg void CVcdpApp::OnUserMessage(WPARAM wParam, LPARAM lParam )
{
    switch(wParam)
    {
    case 21:
//                    ASSERT(FALSE);
//                  //ReserveSong_(pMsg->lParam);
        GetPlayerDocTemplate()->ReserveSong(lParam, false, true);
        break;
    case 22:
        {
            CDWArray * pdwa = (CDWArray *) lParam;
            GetPlayerDocTemplate()->ReserveSong((LPINT) &pdwa->GetData()[1], pdwa->GetAt(0), false, true);
            delete pdwa;
        }
        break;
    case 23:
        {
            CStrArray * pstra = (CStrArray *) lParam;
            GetPlayerDocTemplate()->ReserveSong(pstra, false, true);
            delete pstra;
        }
        break;
    }
      if(wParam == 1)
    {
        if(lParam == 1)
        {
            m_pdbcentral->OnSongsUpdated();
        }
        else if(lParam == 3)
        {
            m_pdbcentral->OnSongsInfoV001Updated();
        }
    }

    switch(wParam)
    {
    case 131415:
        ViewToolsAlbum();
        break;
    case 454647:
        {
            CXfplayerSingleDocTemplate * pDocTemplate = GetPlayerDocTemplate();
            if(pDocTemplate != NULL)
            {
	            CXfplayerDoc * pDoc = (CXfplayerDoc *) pDocTemplate->GetOnlyDoc();
	            if(pDoc != NULL)
                {
	                CXfplayerView * pView = (CXfplayerView *) pDoc->GetLyricView();
	                if(pView != NULL)
                    {
                        //pView->PostMessage(WM_USER, 17, CXfplayerView::BkImageChangeEventLoadNow);
                        pView->_ImageChangePostEvent(pView->BkImageEventLoadNow);
                        TRACE(_T("CDataCentral::OnImagesDirsModified Out"));
                    }
                }
            }
        }
        break;
    case 565758:
        {
            CDBBuildAlbumThreadData * lpdata = 
                (CDBBuildAlbumThreadData *)lParam;
            CSingleDocTemplate * pAlbumDocTemplate = NULL;
            if(GetAlbumThread())
            {
                pAlbumDocTemplate = GetAlbumThread()->GetAlbumDocTemplate();
            }
            bool bVisible = false;
            if(pAlbumDocTemplate != NULL)
            {
                bVisible = pAlbumDocTemplate->GetFirstDocPosition() != NULL;

                // avoid thread quit on close all documents
                GetAlbumThread()->m_pMainWnd = NULL;

                GetAlbumThread()->PostThreadMessage(VMSIM_ALBUMTHREAD,67985, FALSE);
            }
            //CAlbumFrameWnd * pAlbum = GetAlbumDocTemplate();
            //bool bVisible;
            //if(pAlbum != NULL)
            //{
              //  bVisible = (pAlbum->GetStyle() & WS_VISIBLE) != 0;
                //if(bVisible)
                  //  pAlbum->ShowWindow(SW_HIDE);
            //}
            lpdata->bVisible = bVisible;
        }
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
            CDBBuildAlbumThreadData * lpdata = 
                (CDBBuildAlbumThreadData *)lParam;
            if(m_pAlbumDocTemplate != NULL)
            {
                if(lpdata->bVisible)
                {
                    lpdata->lpDataCentral->m_csBuildAlbumThreadData.Lock();
                    lpdata->m_evStarted.Lock();
                    //lpdata->m_ptaskdlg->m_pCloseWindow = pAlbum;
        //            lpdata->m_ptaskdlg->m_lparamClose = 10;
                    lpdata->lpDataCentral->m_csBuildAlbumThreadData.Unlock();
                }
            }
        }
        break;
    case 12342345:
        {
            if(m_pMainWnd == NULL)
            {
                return;
            }
            else if(!m_pMainWnd->IsKindOf(RUNTIME_CLASS(CKaraokeSDIFrame)))
            {
                return;
            }
            //CMainFrame * pFrame = (CMainFrame *) pApp->m_pMainWnd;
            //if(pFrame->m_pAlbumDialog == NULL)
        //    CAlbumFrameWnd * pAlbum = pApp->GetAlbumFrameWnd();
          //  if(pAlbum == NULL)
            //{
              //  return;
            //}
            //pAlbum->GetAlbumView()->OnSongsUpdated();
            CSingleDocTemplate * pTempl = GetAlbumThread()->GetAlbumDocTemplate();
            POSITION pos = pTempl->GetFirstDocPosition();
            while(pos != NULL)
            {
                CDocument * pDoc = pTempl->GetNextDoc(pos);
                if(pDoc != NULL)
                {
                    pDoc->UpdateAllViews(NULL, 13);
                }
            }
        }
        break;
    case 23453456:
        {
            if(m_pMainWnd == NULL)
            {
                return;
            }
            else if(!m_pMainWnd->IsKindOf(RUNTIME_CLASS(CKaraokeSDIFrame)))
            {
                return;
            }
        //    CMainFrame * pFrame = (CMainFrame *) pApp->m_pMainWnd;
          //  if(pFrame->m_pAlbumDialog == NULL)
            CSingleDocTemplate * pTempl = GetAlbumThread()->GetAlbumDocTemplate();
            POSITION pos = pTempl->GetFirstDocPosition();
            while(pos != NULL)
            {
                CDocument * pDoc = pTempl->GetNextDoc(pos);
                if(pDoc != NULL)
                {
                    pDoc->UpdateAllViews(NULL, 4);
                }
            }

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
    
            CAlbumThread::CBuildRequest * lpbr = new CAlbumThread::CBuildRequest();

            lpbr->m_pdc = GetDBCentral();
            lpbr->m_eop = (SongsAlbum::EBuildSongsAlbumOperation) eop;
            lpbr->m_bfb = bFullBuild;

            pThread->PostThreadMessage(VMSIM_ALBUMTHREAD, 20191817, (LPARAM) lpbr);


        }
        break;
    case 321432:
        {
            // On Task Dialog Stop
            ASSERT(m_pdbcentral != NULL);
            m_pdbcentral->SetBuildAlbumThreadsCancelFlag();
        }
        break;
    case 3214:
        {
            OnChangeEconoMode();

        }
        break;
    case 534231:
        {
			ASSERT(FALSE);
            //GetKarWnd()->SendMessageToDescendants(WM_USER, 534231);
        }
        break;
    default:;
        break;
    }
}

void CVcdpApp::RegisterShellExtension(bool bRegister)
{
    TCHAR lpszModuleFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, lpszModuleFilePath, MAX_PATH + 1);
	
    TCHAR lpszModuleFolder[MAX_PATH + 1];
	LPTSTR lpszModuleFileName;
	GetFullPathName(lpszModuleFilePath, MAX_PATH + 1, lpszModuleFolder, &lpszModuleFileName);
	
    CString strModuleFolder(lpszModuleFolder, lpszModuleFileName - lpszModuleFolder);
    CString str(_T("vmsse.dll"));
    CString strFormat;
	if(bRegister)
	{
		strFormat.Format(_T(" /s %s%s"),strModuleFolder,str);
	}
	else
	{
		strFormat.Format(_T(" /u /s %s%s"),strModuleFolder,str);
	}
    ShellExecute(m_pMainWnd->GetSafeHwnd(), _T("open"), _T("regsvr32.exe"), strFormat, strModuleFolder,SW_SHOW); 

/*    CRegKey regKey;

    UUID uuida[2];
    uuida[0] = CLSID_AlbumSongFolder;
    uuida[1] = CLSID_AlbumSongView;
    

    int i;
    CString strParam;
    CString strCLSID;
    CString strBase;
    CString strSystemRoot;
    CString str;

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
	    
        CString strModuleFolder(lpszModuleFolder, lpszModuleFileName - lpszModuleFolder);
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

//    CString strBase;
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

CDBCentral * CVcdpApp::GetDBCentral()
{
    return m_pdbcentral;
}

	
extern CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_VmsPlayer, CVmp)
END_OBJECT_MAP()

/*LONG CVmsModule::Unlock()
{
	AfxOleUnlockApp();
	return 0;
}

LONG CVmsModule::Lock()
{
	AfxOleLockApp();
	return 1;
}*/


BOOL CVcdpApp::InitATL()
{
	m_bATLInited = TRUE;

	_Module.Init(ObjectMap, AfxGetInstanceHandle());
//	_Module.dwThreadID = GetCurrentThreadId();

	return TRUE;

}

CWelcomeDialog * CVcdpApp::GetWelcomeDialog()
{
    return m_pwelcomedlg;
}

void CVcdpApp::SetWelcomeDialog(CWelcomeDialog *pdlg)
{
    m_pwelcomedlg = NULL;
}


void CVcdpApp::OnUpdateRecentFileMenu(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    TRACE(_T("CVcdpApp::OnUpdateRecentFileMenu"));
    if(m_pRecentFileList == NULL)
    {
        pCmdUI->Enable(FALSE);
        CString str;
        str.LoadString(IDS_RECENT_FILE);
        pCmdUI->SetText(str);
    	for (int iMRU = 1; iMRU < 10; iMRU++)
	    	pCmdUI->m_pMenu->DeleteMenu(pCmdUI->m_nID + iMRU, MF_BYCOMMAND);
        return;
    }
		ASSERT(m_pRecentFileList->m_arrNames != NULL);

	CMenu* pMenu = pCmdUI->m_pMenu;
	if (m_pRecentFileList->m_strOriginal.IsEmpty() && pMenu != NULL)
		pMenu->GetMenuString(pCmdUI->m_nID, m_pRecentFileList->m_strOriginal, MF_BYCOMMAND);

	if (m_pRecentFileList->m_arrNames[0].IsEmpty())
	{
		// no MRU files
		if (!m_pRecentFileList->m_strOriginal.IsEmpty())
			pCmdUI->SetText(m_pRecentFileList->m_strOriginal);
		pCmdUI->Enable(FALSE);
		return;
	}

	if (pCmdUI->m_pMenu == NULL)
		return;

    CMenu * pmenu = CMenuUtil::FindPopupMenuFromID(pCmdUI->m_pMenu, pCmdUI->m_nID);
    
    if(pmenu == NULL)
    {
        pmenu = pCmdUI->m_pMenu;
    }

    bool bCmdUIMenu = pmenu == pCmdUI->m_pMenu;

	for (int iMRU = 0; iMRU < m_pRecentFileList->m_nSize; iMRU++)
		pCmdUI->m_pMenu->DeleteMenu(pCmdUI->m_nID + iMRU, MF_BYCOMMAND);

    int nIndex = pCmdUI->m_nIndex;
    int nID = pCmdUI->m_nID;

	TCHAR szCurDir[_MAX_PATH];
	GetCurrentDirectory(_MAX_PATH, szCurDir);
	int nCurDir = lstrlen(szCurDir);
	ASSERT(nCurDir >= 0);
	szCurDir[nCurDir] = '\\';
	szCurDir[++nCurDir] = '\0';

	CString strName;
	CString strTemp;
	for (iMRU = 0; iMRU < m_pRecentFileList->m_nSize; iMRU++)
	{
		if (!m_pRecentFileList->GetDisplayName(strName, iMRU, szCurDir, nCurDir))
			break;

		// double up any '&' characters so they are not underlined
		LPCTSTR lpszSrc = strName;
		LPTSTR lpszDest = strTemp.GetBuffer(strName.GetLength()*2);
		while (*lpszSrc != 0)
		{
			if (*lpszSrc == '&')
				*lpszDest++ = '&';
			if (_istlead(*lpszSrc))
				*lpszDest++ = *lpszSrc++;
			*lpszDest++ = *lpszSrc++;
		}
		*lpszDest = 0;
		strTemp.ReleaseBuffer();

		// insert mnemonic + the file name
		TCHAR buf[10];
		wsprintf(buf, _T("&%d "), (iMRU+1+m_pRecentFileList->m_nStart) % 10);
        
//		pCmdUI->m_pMenu->InsertMenu(pCmdUI->m_nIndex++,
//			MF_STRING | MF_BYPOSITION, pCmdUI->m_nID++,
//			CString(buf) + strTemp);
		pmenu->InsertMenu(nIndex,
			MF_STRING | MF_BYPOSITION, nID,
			CString(buf) + strTemp);
        nIndex++;
        nID++;
        if(bCmdUIMenu)
        {
            pCmdUI->m_nIndex = nIndex;
            pCmdUI->m_nID = nID;
        }
	}

	// update end menu count
    if(bCmdUIMenu)
    {
	    pCmdUI->m_nIndex--; // point to last menu added
	    pCmdUI->m_nIndexMax = pCmdUI->m_pMenu->GetMenuItemCount();
    }

	pCmdUI->m_bEnableChanged = TRUE;    // all the added items are enabled

}

LRESULT CVcdpApp::GetPaintMsgProc(int nCode, WPARAM wParam, LPARAM lParam)
{
//    for(int i = 0; i < m_pha.GetSize(); i++)
  //  {
    //    m_pha.ElementAt(i)->PaintHookGetPaintMsgProc(nCode, wParam, lParam);
    //}
    return 0;
}

void CVcdpApp::UpdateMRU(BOOL bEnable, int iCount)
{
    if(m_pRecentFileList != NULL)
    {
        CRecentFileList * plist = m_pRecentFileList;
        m_pRecentFileList = NULL;
        delete plist;
    }
    if(bEnable)
    {
		m_pRecentFileList = new CRecentFileList(0, _afxFileSection, _afxFileEntry,
			iCount);
	    m_pRecentFileList->ReadList();
    }

}

void CAboutDlg::OnButtonWwwveriwelldotcom() 
{
	::ShellExecute(m_hWnd, _T("open"), _T("http://www.veriwell.com"), NULL, NULL, SW_RESTORE );
}

CString CVcdpApp::GetModuleFolder()
{
	TCHAR lpszModuleFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, lpszModuleFilePath, MAX_PATH + 1);
	
    TCHAR lpszModuleFolder[MAX_PATH + 1];
	LPTSTR lpszModuleFileName;
	GetFullPathName(lpszModuleFilePath, MAX_PATH + 1, lpszModuleFolder, &lpszModuleFileName);
	
    CString strModuleFolder(lpszModuleFolder, lpszModuleFileName - lpszModuleFolder);

	return strModuleFolder;
}


CString CVcdpApp::GetLanguageDllPath(ELanguage language)
{
	CString str;
	str = GetModuleFolder();
	switch(language)
	{
	case langDefault:
		str += "vmsp.dll";
		break;
	case langEnUs:
		str += "vmpresenus.dll";
		break;
	case langPtBr:
		str += "vmpresptbr.dll";
		break;
	case langDe:
		str += "vmpresde.dll";
		break;
	case langJp:
		str += "vmpresjp.dll";
		break;
	default:
		str += "vmpresenus.dll";
	}
	return str;
}

void CVcdpApp::OnUpdateLanguageChangeMenu(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    TRACE(_T("CVcdpApp::OnUpdateLanguageChangeMenu"));

	CMenu* pMenu = pCmdUI->m_pMenu;

	if (pCmdUI->m_pMenu == NULL)
		return;

    CMenuV033 * pmenu = (CMenuV033 *) CMenuUtil::FindPopupMenuFromID(pCmdUI->m_pMenu, pCmdUI->m_nID);
    
    if(pmenu == NULL)
    {
        pmenu = (CMenuV033 *) pCmdUI->m_pMenu;
    }

    bool bCmdUIMenu = pmenu == pCmdUI->m_pMenu;

	const iSize = 4;

	pCmdUI->m_pMenu->DeleteMenu(ID_LANGUAGE_CHANGE, MF_BYCOMMAND);
	pCmdUI->m_pMenu->DeleteMenu(ID_LANGUAGE_ENUS, MF_BYCOMMAND);
	pCmdUI->m_pMenu->DeleteMenu(ID_LANGUAGE_DE, MF_BYCOMMAND);
	pCmdUI->m_pMenu->DeleteMenu(ID_LANGUAGE_JP, MF_BYCOMMAND);
	pCmdUI->m_pMenu->DeleteMenu(ID_LANGUAGE_PTBR, MF_BYCOMMAND);

    int nIndex = pCmdUI->m_nIndex;


	pmenu->InsertWMenu(
			nIndex,
			MF_STRING | MF_BYPOSITION,
			ID_LANGUAGE_ENUS,
			L"English (U.S:)");
	nIndex++;
	pmenu->InsertWMenu(
			nIndex,
			MF_STRING | MF_BYPOSITION,
			ID_LANGUAGE_DE,
			L"Deutsch\tGerman");
	nIndex++;
	pmenu->InsertWMenu(
			nIndex,
			MF_STRING | MF_BYPOSITION,
			ID_LANGUAGE_JP,
			L"\x65e5\x672c\x8a9e\tJapanese");
	nIndex++;
	pmenu->InsertWMenu(
			nIndex,
			MF_STRING | MF_BYPOSITION,
			ID_LANGUAGE_PTBR,
			L"Portugu7x00eas (Brasil)\tPortuguese (Brazil)");
	        nIndex++;


	if(bCmdUIMenu)
	{
        pCmdUI->m_nIndex = nIndex;
        pCmdUI->m_nID = ID_LANGUAGE_PTBR;
	}

	pCmdUI->m_bEnableChanged = TRUE;    // all the added items are enabled

}


void CVcdpApp::OnLanguageEnus() 
{
	SetLanguage(langEnUs);
}

void CVcdpApp::OnUpdateLanguageEnus(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(GetLanguage() != langEnUs);
	pCmdUI->SetCheck(GetLanguage() == langEnUs);
}

void CVcdpApp::OnLanguagePtbr() 
{
	SetLanguage(langPtBr);
}

void CVcdpApp::OnUpdateLanguagePtbr(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetLanguage() != langPtBr);
	pCmdUI->SetCheck(GetLanguage() == langPtBr);
	
}

void CVcdpApp::OnLanguageDe() 
{
	SetLanguage(langDe);
}

void CVcdpApp::OnUpdateLanguageDe(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetLanguage() != langDe);
	pCmdUI->SetCheck(GetLanguage() == langDe);
}

void CVcdpApp::OnLanguageJp() 
{
	SetLanguage(langJp);
}

void CVcdpApp::OnUpdateLanguageJp(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetLanguage() != langJp);
	pCmdUI->SetCheck(GetLanguage() == langJp);
}

/*bool CVcdpApp::InitializeDataCentral(CCommandLineInfo & cmdinfo)
{
//	CDBCentral * pdbcentral = new CDBCentral();
//	if(pdbcentral == NULL)
//	{
//		AfxMessageBox("No memory");
//		return false;
//	}
  //  CDataCentral::SetDBCentral(pdbcentral);
    m_pdbcentral = GetDB();

    CString strCompactDatabase = GetProfileString(_T("Database"), _T("Compact"));
    if(!strCompactDatabase.IsEmpty())
    {
        m_pdbcentral->CompactDatabase(strCompactDatabase);
        WriteProfileString(_T("Database"), _T("Compact"), _T(""));
    }

	HRESULT hr;
	if(FAILED(hr = m_pdbcentral->Initialize(m_hInstance)))
	{
		if(!m_pdbcentral->IsWorking())
		{
			if(!cmdinfo.m_bRunEmbedded &&
				!cmdinfo.m_bRunAutomated)
			{
				//AfxMessageBox(
				//	IDS_NODATABASESUPPORTERROR,
				//	MB_OK | MB_ICONEXCLAMATION);
			}
		}

	}
	m_presourcecentral->Initialize(m_hInstance);
	return true;
}*/



bool CVcdpApp::RestoreEnhMetaFiles()
{
	CreateFileFromRawResource(
		IDR_EMF_VMP447CV,
		_T("EMF"),
		m_strModuleFolder + "vmp447cv.emf");
	CreateFileFromRawResource(
		IDR_EMF_VMPCOOLGRAY,
		_T("EMF"),
		m_strModuleFolder + "vmpcoolgray.emf");
	CreateFileFromRawResource(
		IDR_EMF_VMP,
		_T("EMF"),
		m_strModuleFolder + "vmp.emf");
	
	return true;
}

CVcdpApp::ELanguage CVcdpApp::GetDefaultLanguage()
{
	UINT uiCP = ::GetOEMCP();
	LCID lcid = ::GetUserDefaultLCID();
	TCHAR lpsz[1024];
	GetLocaleInfo(
  lcid,      // locale identifier
  LOCALE_SABBREVLANGNAME,    // type of information
  lpsz,  // address of buffer for information
  sizeof(lpsz)       // size of buffer
	);

	CString str(lpsz);
	if(str == "JPN")
	{
		return langJp;
	}
	else if(str == "DEU")
	{
		return langDe;
	}
	else if(str == "PTB")
	{
		return langPtBr;
	}
	else if(str == "ENU")
	{
		return langPtBr;
	}

	return langDefault;
}
CPlaylistDoc * CVcdpApp::GetDefaultPlaylist()
{
	if(m_pplaylistdoc != NULL)
		return m_pplaylistdoc;
	return OpenDefaultPlaylist();
}

CPlaylistDoc * CVcdpApp::OpenDefaultPlaylist()
{
	if(m_pplaylistdoc != NULL)
		return m_pplaylistdoc;
	CString strFile;
	GetDefaultPlaylistPathName(strFile);
	CPlaylistDoc * pdoc = NULL;
	if(::GetFileAttributes(strFile) == 0xFFFFFFFF)
	{
		pdoc = (CPlaylistDoc *) m_pPlaylistDocTemplate->OpenDocumentFile(NULL);
	}
	else
	{
		pdoc = (CPlaylistDoc *) m_pPlaylistDocTemplate->OpenDocumentFile(strFile);
	}
	if(pdoc == NULL)
		return NULL;
	pdoc->SetPathName(strFile);
	CString str;
	str.LoadString(IDS_DEFAULT_PLAYLIST_TITLE);
	pdoc->SetTitle(str);
	m_pplaylistdoc = pdoc;
	return pdoc;
}

void CVcdpApp::GetDefaultPlaylistPathName(CString &str)
{
	str = GetModuleFolder() + "default.vmspl";
}

void CVcdpApp::AddToRecentFileList(LPCTSTR lpszPathName) 
{
	CString str;
	GetDefaultPlaylistPathName(str);
	if(File::IsEqualFilePath(str, lpszPathName))
		return;
	CVmsGuiApp::AddToRecentFileList(lpszPathName);
	
}

CVmsTextDoc * CVcdpApp::OpenTextFile(LPCTSTR lpcsz)
{
	return (CVmsTextDoc *) m_pvmstextdoctemplate->OpenDocumentFile(lpcsz);
}

void CVcdpApp::OnCloseDefaultPlaylist()
{
	m_pplaylistdoc = NULL;
}


void CVcdpApp::OnContextHelp() 
{
	// TODO: Add your command handler code here
	CVmsGuiApp::OnContextHelp();
}



CXfplayerDoc * CVcdpApp::GetXfplayerDoc()
{
	return m_pxfplayerdoc;
}

void CVcdpApp::SetXfplayerDoc(CXfplayerDoc *pdoc)
{
	m_pxfplayerdoc = pdoc;
}

BOOL CVcdpApp::ProcessShellCommand(CCommandLineInfo& rCmdInfo)
{
	BOOL bResult = TRUE;
	switch (rCmdInfo.m_nShellCommand)
	{
	case CCommandLineInfo::FileNew:
		if (!AfxGetApp()->OnCmdMsg(ID_FILE_NEW, 0, NULL, NULL))
			OnFileNew();
		if (m_pMainWnd == NULL)
			bResult = FALSE;
		break;

		// If we've been asked to open a file, call OpenDocumentFile()

	case CCommandLineInfo::FileOpen:
		if (!OpenDocumentFile(rCmdInfo.m_strFileName))
			bResult = FALSE;
		break;

		// If the user wanted to print, hide our main window and
		// fire a message to ourselves to start the printing

	case CCommandLineInfo::FilePrintTo:
	case CCommandLineInfo::FilePrint:
		m_nCmdShow = SW_HIDE;
		ASSERT(m_pCmdInfo == NULL);
		OpenDocumentFile(rCmdInfo.m_strFileName);
		m_pCmdInfo = &rCmdInfo;
		m_pMainWnd->SendMessage(WM_COMMAND, ID_FILE_PRINT_DIRECT);
		m_pCmdInfo = NULL;
		bResult = FALSE;
		break;

		// If we're doing DDE, hide ourselves

	case CCommandLineInfo::FileDDE:
//		m_pCmdInfo = (CCommandLineInfo *) SW_SHOW;
		m_nDDECmdShow = SW_SHOW;
		m_pCmdInfo = &m_cmdinfo;
		m_nCmdShow = SW_HIDE;
		break;

	// If we've been asked to unregister, unregister and then terminate
	case CCommandLineInfo::AppUnregister:
		{
			UnregisterShellFileTypes();
			BOOL bUnregistered = Unregister();

			// if you specify /EMBEDDED, we won't make an success/failure box
			// this use of /EMBEDDED is not related to OLE

			if (!rCmdInfo.m_bRunEmbedded)
			{
				if (bUnregistered)
					AfxMessageBox(AFX_IDP_UNREG_DONE);
				else
					AfxMessageBox(AFX_IDP_UNREG_FAILURE);
			}
			bResult = FALSE;    // that's all we do

			// If nobody is using it already, we can use it.
			// We'll flag that we're unregistering and not save our state
			// on the way out. This new object gets deleted by the
			// app object destructor.

			if (m_pCmdInfo == NULL)
			{
				m_pCmdInfo = new CCommandLineInfo;
				m_pCmdInfo->m_nShellCommand = CCommandLineInfo::AppUnregister;
			}
		}
		break;
	}
	return bResult;
}



bool CVcdpApp::MessageWindowListener(
	UINT message,
	WPARAM wparam,
	LPARAM lparam)
{
	if(CVmsGuiApp::MessageWindowListener(
		message, wparam, lparam))
		return true;
	switch(message)
	{
	case WM_APP:
		switch(wparam)
		{
		case 178:
			{
				LPSCOREUPDATEMESSAGE lpsum = (LPSCOREUPDATEMESSAGE) lparam ;
				CXfplayerDoc * pdoc = (CXfplayerDoc *) CXfplayerSingleDocTemplate::AppGetPlayerDocTemplate()->GetOnlyDoc();
				if(pdoc == NULL)
				{
					delete lpsum;
					return TRUE;
				}
				CAudioSpectrumViewUpdateHint uh;
				uh.m_lpwaveformatex = WaveCentralGetWaveIn()->GetFormatEx();			
				uh.m_dDeltaScore = lpsum->dDeltaScore;
				uh.m_dScoreAddUp = lpsum->dScoreAddUp;
				delete lpsum;
				lpsum = NULL;
				CDocument * pdoctarget = (CDocument *) pdoc->GetAudioSpectrumDoc();
				if(pdoctarget != NULL)
					pdoctarget->UpdateAllViews(NULL, 0, &uh);
				return TRUE;
			}
		default:
			break;
		}
	default:
		break;
	}

	return FALSE;
}

CKaraokeSDIFrame * CVcdpApp::GetKaraokeSDIFrame()
{
	CBaseArray < CWnd *, CWnd * > & wndpa = GetWndArray();
    for(int i = 0; i < wndpa.GetSize(); i++)
	{
        CWnd * pwnd = wndpa[i];
        if(pwnd != NULL
			&& pwnd->IsKindOf(RUNTIME_CLASS(CKaraokeSDIFrame)))
        {
			return (CKaraokeSDIFrame *) pwnd;
        }
    }
	return NULL;
}

void CVcdpApp::GetDefaultSongFolderPath(CString &strPath)
{
	CString str;
    str.LoadString(IDS_FOLDER_SONGS);

	strPath = m_strModuleFolder;
	strPath += str;

}

void CVcdpApp::OnPlayer() 
{
	CKaraokeSDIFrame * pframe = GetKaraokeSDIFrame();
	if(pframe == NULL)
	{
		m_pdoctemplateMid->OpenDocumentFile(NULL);
	}
	else
	{
		pframe->ShowWindow(SW_SHOWNORMAL);
	}
	
}

int CVcdpApp::DoMessageBox(LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt) 
{
	if(m_cmdinfo.m_nShellCommand != CCommandLineInfo::FileDDE)
	{
				// disable windows for modal dialog
		EnableModeless(FALSE);
		HWND hWndTop;
		HWND hWnd = CWnd::GetSafeOwner_(NULL, &hWndTop);

		bool bToolWindow = false;
		if(m_pwndMessageBoxParent != NULL
			&& ::IsWindow(m_pwndMessageBoxParent->GetSafeHwnd()))
		{
			hWnd = m_pwndMessageBoxParent->GetSafeHwnd();
			hWndTop = m_pwndMessageBoxParent->GetSafeHwnd();
		}
		if(::GetWindowLong(hWnd, GWL_EXSTYLE) & WS_EX_TOOLWINDOW)
		{
			bToolWindow = true;
			::SetWindowLong(hWnd, GWL_EXSTYLE, ::GetWindowLong(hWnd, GWL_EXSTYLE) & ~WS_EX_TOOLWINDOW);
			if(::IsWindowVisible(hWnd))
			{
				::SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOZORDER | SWP_NOSIZE);
				::ShowWindow(hWnd, SW_SHOW);
			}
		}

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
		EnableModeless(TRUE);

		if(bToolWindow)
		{
			::SetWindowLong(hWnd, GWL_EXSTYLE, ::GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_TOOLWINDOW);
			::SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOZORDER | SWP_NOSIZE);
		}
		return nResult;

	}
	return -1;
}

BOOL CVcdpApp::OnDDECommand(LPTSTR lpszCommand) 
{
	CString strCommand = lpszCommand;
	CDocument* pDoc = NULL;

	// open format is "[open("%s")]" - no whitespace allowed, one per line
	// print format is "[print("%s")]" - no whitespace allowed, one per line
	// print to format is "[printto("%s","%s","%s","%s")]" - no whitespace allowed, one per line
	//CCommandLineInfo cmdInfo;
	m_cmdinfo.m_nShellCommand = CCommandLineInfo::FileDDE;

	if (strCommand.Left(7) == _T("[open(\""))
	{
		m_cmdinfo.m_nShellCommand = CCommandLineInfo::FileOpen;
		strCommand = strCommand.Right(strCommand.GetLength() - 7);
	}
	else if (strCommand.Left(8) == _T("[print(\""))
	{
		m_cmdinfo.m_nShellCommand = CCommandLineInfo::FilePrint;
		strCommand = strCommand.Right(strCommand.GetLength() - 8);
	}
	else if (strCommand.Left(10) == _T("[printto(\""))
	{
		m_cmdinfo.m_nShellCommand = CCommandLineInfo::FilePrintTo;\
		strCommand = strCommand.Right(strCommand.GetLength() - 10);
	}
	else
		return FALSE; // not a command we handle

	int i = strCommand.Find('"');
	if (i == -1)
		return FALSE; // illegally terminated

	m_cmdinfo.m_strFileName = strCommand.Left(i);
	strCommand = strCommand.Right(strCommand.GetLength() - i);

	CCommandLineInfo* pOldInfo = NULL;
	BOOL bRetVal = TRUE;

	// If we were started up for DDE retrieve the Show state
	if (m_pCmdInfo != NULL)
	{
		m_nCmdShow = m_nDDECmdShow;
		//m_pm_cmdinfo = &m_cmdinfo;
	}
	else
		pOldInfo = m_pCmdInfo;

	if (m_cmdinfo.m_nShellCommand == CCommandLineInfo::FileOpen)
	{

		// then open the document
		OpenDocumentFile(m_cmdinfo.m_strFileName);

		// show the application window
		CWnd* pMainWnd = m_pMainWnd;
		int nCmdShow = m_nCmdShow;
		if (nCmdShow == -1 || nCmdShow == SW_SHOWNORMAL)
		{
			if (pMainWnd->IsIconic())
				nCmdShow = SW_RESTORE;
			else
				nCmdShow = SW_SHOW;
		}
		pMainWnd->ShowWindow(nCmdShow);
		if (nCmdShow != SW_MINIMIZE)
			pMainWnd->SetForegroundWindow();

		// user is now "in control" of the application
		if (!AfxOleGetUserCtrl())
			AfxOleSetUserCtrl(TRUE);

		// next time, show the window as default
		m_nCmdShow = -1;
		goto RestoreAndReturn;
	}

	if (m_cmdinfo.m_nShellCommand == CCommandLineInfo::FilePrintTo)
	{
		if (strCommand.Left(3) != _T("\",\""))
		{
			bRetVal = FALSE;
			goto RestoreAndReturn;
		}
		else
		{
			strCommand = strCommand.Right(strCommand.GetLength() - 3);
			i = strCommand.Find('"');
			if (i == -1)
			{
				bRetVal = FALSE;
				goto RestoreAndReturn;
			}
			else
			{
				m_cmdinfo.m_strPrinterName = strCommand.Left(i);
				strCommand = strCommand.Right(strCommand.GetLength() - i);
			}
		}

		if (strCommand.Left(3) != _T("\",\""))
		{
			bRetVal = FALSE;
			goto RestoreAndReturn;
		}
		else
		{
			strCommand = strCommand.Right(strCommand.GetLength() - 3);
			i = strCommand.Find('"');
			if (i == -1)
			{
				bRetVal = FALSE;
				goto RestoreAndReturn;
			}
			else
			{
				m_cmdinfo.m_strDriverName = strCommand.Left(i);
				strCommand = strCommand.Right(strCommand.GetLength() - i);
			}
		}

		if (strCommand.Left(3) != _T("\",\""))
		{
			bRetVal = FALSE;
			goto RestoreAndReturn;
		}
		else
		{
			strCommand = strCommand.Right(strCommand.GetLength() - 3);
			i = strCommand.Find('"');
			if (i == -1)
			{
				bRetVal = FALSE;
				goto RestoreAndReturn;
			}
			else
			{
				m_cmdinfo.m_strPortName = strCommand.Left(i);
				strCommand = strCommand.Right(strCommand.GetLength() - i);
			}
		}
	}

	// get document count before opening it
	int nOldCount; nOldCount = GetDocumentCount();

	// open the document, then print it.
	pDoc = OpenDocumentFile(m_cmdinfo.m_strFileName);
	m_pCmdInfo = &m_cmdinfo;
	m_pMainWnd->SendMessage(WM_COMMAND, ID_FILE_PRINT_DIRECT);
	m_pCmdInfo = NULL;

	// close the document if it wasn't open previously (based on doc count)
	if (GetDocumentCount() > nOldCount)
	pDoc->OnCloseDocument();

	 // if the app was only started to process this command then close
	 if (!AfxOleGetUserCtrl())
		m_pMainWnd->PostMessage(WM_CLOSE);

RestoreAndReturn:
	m_pCmdInfo = pOldInfo;
	return bRetVal;

}

bool CVcdpApp::BeginVSeriesThreads()
{
	{
        
        
        CRuntimeClass * pruntimeclass = RUNTIME_CLASS(CXfplayerThreadV1);
		if(!(m_pthreadV1 = dynamic_cast<CXfplayerThreadV1 *>(AfxBeginThread(pruntimeclass))))
		{
			return FALSE;
		}

		pruntimeclass = RUNTIME_CLASS(CXfplayerThreadV2);
		if(!(m_pthreadV2 = dynamic_cast<CXfplayerThreadV2 *>(AfxBeginThread(pruntimeclass))))
		{
			return FALSE;
		}

		if(m_pwavein != NULL)
		{
			m_pwavein->SetCallbackThread(m_pthreadV2);
		}

		pruntimeclass = RUNTIME_CLASS(CXfplayerThreadV3);
		if(!(m_pthreadV3 = dynamic_cast<CXfplayerThreadV3 *>(AfxBeginThread(pruntimeclass))))
		{
			return FALSE;
		}

		m_pthreadV3->SetThreadV1(m_pthreadV1);
	}

	return true;
}

CXfplayerThreadV1 * CVcdpApp::GetThreadV1()
{
	if(m_pthreadV1 == NULL)
	{
		CRuntimeClass * pruntimeclass = RUNTIME_CLASS(CXfplayerThreadV1);
		if(!(m_pthreadV1 = dynamic_cast<CXfplayerThreadV1 *>(AfxBeginThread(pruntimeclass))))
		{
			AfxPostQuitMessage(0);
		}
	}
	return m_pthreadV1;
}

CXfplayerThreadV2 * CVcdpApp::GetThreadV2()
{
	if(m_pthreadV2 == NULL)
	{
		CRuntimeClass * pruntimeclass = RUNTIME_CLASS(CXfplayerThreadV2);
		if(!(m_pthreadV2 = dynamic_cast<CXfplayerThreadV2 *>(AfxBeginThread(pruntimeclass))))
		{
			AfxPostQuitMessage(0);
		}
	}

	if(m_pwavein != NULL)
	{
		m_pwavein->SetCallbackThread(m_pthreadV2);
	}

	return m_pthreadV2;
}

CXfplayerThreadV3 * CVcdpApp::GetThreadV3()
{
	if(m_pthreadV3 == NULL)
	{
		CRuntimeClass * pruntimeclass = RUNTIME_CLASS(CXfplayerThreadV3);
		if(!(m_pthreadV3 = dynamic_cast<CXfplayerThreadV3 *>(AfxBeginThread(pruntimeclass))))
		{
			AfxPostQuitMessage(0);
		}
		else
		{
			m_pthreadV3->SetThreadV1(GetThreadV1());
		}
	}

	return m_pthreadV3;
}


int CVcdpApp::GetDocumentCount()
{
	// count all documents
	int nCount = 0;
	POSITION pos = m_pDocManager->GetFirstDocTemplatePosition();
	while (pos != NULL)
	{
		CDocTemplate* pTemplate = m_pDocManager->GetNextDocTemplate(pos);
		POSITION pos2 = pTemplate->GetFirstDocPosition();
		while (pos2 != NULL)
		{
			pTemplate->GetNextDoc(pos2);
			++nCount;
		}
	}
	return nCount;
}

void CVcdpApp::VerifyBrowsers()
{
	CFileFind filefind;
	CString str;
	CString strDestination;
	CString strSource;
	CString strVersion;
	CString strFormat;
	strSource = m_strModuleFolder + "npvmp.dll";
	CRegistry reg;
	{
	HKEY hkeyMozilla = NULL;
	HKEY hkeyMozilla10 = NULL;
	HKEY hkeyMozilla11 = NULL;
	HKEY hkeyExtensions = NULL;
	if(ERROR_SUCCESS ==
		RegOpenKey(
			HKEY_LOCAL_MACHINE,
			"Software\\Mozilla",
			&hkeyMozilla))
	{
		if(ERROR_SUCCESS ==
			RegOpenKey(
				hkeyMozilla,
				"Mozilla 1.0",
				&hkeyMozilla10))
		{
			if(ERROR_SUCCESS ==
				RegOpenKey(
					hkeyMozilla10,
					"Extensions",
					&hkeyExtensions))
			{
				if(reg.RegQueryValue(
					hkeyExtensions,
					"Plugins",
					str))
				{
					strDestination = str + "\\npvmp.dll";
					if(!filefind.FindFile(strDestination))
					{
						if(IDYES == AfxMessageBox("Mozilla 1.0 seems to be installed. Do you wish to install Veriwell Musical Player Plugin for Mozilla 1.0?", MB_ICONQUESTION | MB_YESNO))
						{
							if(CopyFile(strSource, strDestination, false))
							{
								AfxMessageBox("You will need to restart Mozilla 1.0 for changes to take effect.", MB_ICONINFORMATION);
							}
							else
							{
								AfxMessageBox("Could not instal the plugin.", MB_ICONINFORMATION);
							}
						}
					}
				}
			
				RegCloseKey(hkeyExtensions);
			}
			RegCloseKey(hkeyMozilla10);
		}

		if(ERROR_SUCCESS ==
			RegOpenKey(
				hkeyMozilla,
				"Mozilla 1.1",
				&hkeyMozilla11))
		{
			if(ERROR_SUCCESS ==
				RegOpenKey(
					hkeyMozilla11,
					"Extensions",
					&hkeyExtensions))
			{
				if(reg.RegQueryValue(
					hkeyExtensions,
					"Plugins",
					str))
				{
							strDestination = str + "\\npvmp.dll";
							if(!filefind.FindFile(strDestination))
							{
								if(IDYES == AfxMessageBox("Mozilla 1.1 seems to be installed. Do you wish to install Veriwell Musical Player Plugin for Mozilla 1.1?", MB_ICONQUESTION | MB_YESNO))
								{
									if(CopyFile(strSource, strDestination, false))
									{
										AfxMessageBox("You will need to restart Mozilla 1.1 for changes to take effect.", MB_ICONINFORMATION);
									}
									else
									{
										AfxMessageBox("Could not instal the plugin.", MB_ICONINFORMATION);
									}
								}
							}
				}
			
				RegCloseKey(hkeyExtensions);
			}
			RegCloseKey(hkeyMozilla10);
		}
		RegCloseKey(hkeyMozilla);
	}	

	}





	// NETSCAPE
	{
	HKEY hkeyNetscape = NULL;
	HKEY hkeyNetscapeNavigator = NULL;
	HKEY hkeyNetscapeCurrent = NULL;
	HKEY hkeyNetscapeMain = NULL;

	if(ERROR_SUCCESS ==
		RegOpenKey(
			HKEY_LOCAL_MACHINE,
			"Software\\Netscape",
			&hkeyNetscape))
	{
		if(ERROR_SUCCESS ==
			RegOpenKey(
				hkeyNetscape,
				"Netscape Navigator",
				&hkeyNetscapeNavigator))
		{
			if(reg.RegQueryValue(
				hkeyNetscapeNavigator,
				"CurrentVersion",
				strVersion))
			{

				if(ERROR_SUCCESS ==
					RegOpenKey(
						hkeyNetscapeNavigator,
						strVersion,
						&hkeyNetscapeCurrent))
				{
					if(ERROR_SUCCESS ==
						RegOpenKey(
							hkeyNetscapeCurrent,
							_T("Main"),
							&hkeyNetscapeMain))
					{
						if(reg.RegQueryValue(
							hkeyNetscapeMain,
							"Install Directory",
							str))
						{
							strDestination = str + "\\Program\\Plugins\\npvmp.dll";
							if(!filefind.FindFile(strDestination))
							{
								strFormat.Format("Netscape Navigator %s seems to be installed in your computer. Do you wish to install Veriwell Musical Player Plugin for Netscape Navigator %s?", strVersion, strVersion);

								if(IDYES == AfxMessageBox(strFormat, MB_ICONQUESTION | MB_YESNO))
								{
									if(CopyFile(strSource, strDestination, false))
									{
										strFormat.Format("You will need to restart Netscape Navigator %s for changes to take effect.", strVersion);
										AfxMessageBox(strFormat, MB_ICONINFORMATION);
									}
									else
									{
										AfxMessageBox("Could not instal the plugin.", MB_ICONINFORMATION);
									}
								}
							}
						}
						
						RegCloseKey(hkeyNetscapeMain);
					}
					RegCloseKey(hkeyNetscapeCurrent);
				}
				RegCloseKey(hkeyNetscapeNavigator);
			}
			RegCloseKey(hkeyNetscape);
		}	
	
	}
	}
}

void CVcdpApp::VmsDataOnAfterChange(int iConfigurationId, int iLine, int iColumn)
{
	CVmsGuiApp::VmsDataOnAfterChange(iConfigurationId, iLine, iColumn);
	if(iConfigurationId == CfgUserInterfaceLanguage)
	{
		OnAfterLanguageChange(GetLanguage());
	}
	else if(iConfigurationId == CfgKaraokeEncoding)
	{
		OnAfterKaraokeEncodingChange();
	}
}

void CVcdpApp::OnAfterLanguageChange(ELanguage elanguage)
{
/*	if(elanguage == langDefault)
	{
		AfxSetResourceHandle(m_hInstance);
		m_elanguage = elanguage;
		CWStr::m_dwResourceCP = 1252;
		PostThreadMessage(APPM_LANGUAGE, WPARAM_LANGUAGE_UPDATE, 0);
		
	}
	else*/
	{
		if(m_hmoduleResource != NULL)
		{
			FreeLibrary(m_hmoduleResource);
		}
		CString strPath;
		strPath = GetLanguageDllPath(elanguage);
		m_hmoduleResource = LoadLibrary(strPath);
		if(m_hmoduleResource == NULL)
		{
			strPath = GetLanguageDllPath(langEnUs);
			m_hmoduleResource = LoadLibrary(strPath);
		}
		if(m_hmoduleResource == NULL)
		{
			AfxMessageBox(_T("The requested language library is not available."), MB_ICONINFORMATION);
			SetLanguage(langDefault);
			return;
		}
		AfxSetResourceHandle(m_hmoduleResource);
		switch(elanguage)
		{
		case langEnUs:
	//		str += "vmpresenus.dll";
			CWStr::m_dwResourceCP = 1252;
			break;
		case langPtBr:
	//		str += "vmpresptbr.dll";
			CWStr::m_dwResourceCP = 1252;
			break;
		case langDe:
	//		str += "vmpresde.dll";
			CWStr::m_dwResourceCP = 1252;
			break;
		case langJp:
	//		str += "vmpresjp.dll";
			CWStr::m_dwResourceCP = 932;
			break;
		default:
	//		str += "vmpresenus.dll";
			CWStr::m_dwResourceCP = 1252;
		}
		{
			WriteProfileInt(_T("Language"), _T("Current"), elanguage);
			m_elanguage = elanguage;
			PostThreadMessage(APPM_LANGUAGE, WPARAM_LANGUAGE_UPDATE, 0);

		}
	}

}

void CVcdpApp::SetKaraokeEnconding(DWORD dwCodePage)
{

	CVmsDataServerInterface & db = GetVmsDataServerInterface();

	COleVariant var;

	var.vt = VT_I4;
	var.intVal = dwCodePage;

	db.SetData(CfgKaraokeEncoding, m_elanguage, 0, var);

}

void CVcdpApp::OnAfterKaraokeEncodingChange()
{
	CVmsDataServerInterface & db = GetVmsDataServerInterface();

	COleVariant var;
	DWORD dwCodePage;

	if(db.GetData(CfgKaraokeEncoding, m_elanguage, 0, var))
	{
		ASSERT(var.vt == VT_I4);
		dwCodePage = var.intVal;
		CXfplayerDoc * pdoc = (CXfplayerDoc *) GetPlayerDocTemplate()->GetOnlyDoc();

		pdoc->SetCodePage(dwCodePage);

	}

}

DWORD CVcdpApp::GetKaraokeEncoding()
{

	CVmsDataServerInterface & db = GetVmsDataServerInterface();

	COleVariant var;
	DWORD dwCodePage;

	if(db.GetData(CfgKaraokeEncoding, m_elanguage, 0, var))
	{
		ASSERT(var.vt == VT_I4);
		dwCodePage = var.intVal;
		return dwCodePage;
	}
	else
		return CP_OEMCP;

}

void CVcdpApp::OnToolsOptionsFileAssociations() 
{
	m_pdoctemplateFileAssociations->OpenDocumentFile(NULL);
}
