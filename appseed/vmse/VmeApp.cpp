// vme.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "VmeApp.h"

#include "MainFrame.h"
#include "VmeFrame.h"
#include "IpFrame.h"
#include "vmeDoc.h"
#include "VmeTreeView.h"

#include "SplashThread.h"

#include "MidiCentral.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVmeApp

BEGIN_MESSAGE_MAP(CVmeApp, CWinApp)
	//{{AFX_MSG_MAP(CVmeApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVmeApp construction

CVmeApp::CVmeApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CVmeApp object

// This identifier was generated to be statistically unique for your app.
// You may change it if you prefer to choose a specific identifier.

// {23E5FDD5-0BC6-4D80-8809-92959E434616}
static const CLSID clsid =
{ 0x23e5fdd5, 0xbc6, 0x4d80, { 0x88, 0x9, 0x92, 0x95, 0x9e, 0x43, 0x46, 0x16 } };

/////////////////////////////////////////////////////////////////////////////
// CVmeApp initialization

BOOL CVmeApp::InitInstance()
{
    if(!CBaseApp::InitInstance())
        return FALSE;

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
    
    AfxSetResourceHandle(GetModuleHandle("vmse.dll"));
    HINSTANCE hInst = AfxGetInstanceHandle();
    //__asm
    //{
    //    int 3
    //}
//    AfxDebugBreak();
	TRACE(_T("CVmpApp::InitInstance current thread %X\n"), GetCurrentThreadId());
//    AfxMessageBox(_T("1"));
	//m_pSplashThread = new CSplashThread(&m_pSplashThread);
	//m_pSplashThread->CreateThread();
    CSplashThread * pSplashThread = NULL;
    if(!cmdInfo.m_bRunAutomated &&
        !cmdInfo.m_bRunEmbedded)
    {
        pSplashThread = (CSplashThread *) AfxBeginThread(RUNTIME_CLASS(CSplashThread));
        pSplashThread->Initialize(&pSplashThread);
        pSplashThread->m_evInitialized.Lock();
        m_pMainWnd = pSplashThread->m_pMainWnd;
    }
    else
    {
        m_pMainWnd = NULL;
    }

	CoInitialize(NULL);
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

    CMidiCentral::SetMidiCentral(new CMidiCentral());

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_VMETYPE,
		RUNTIME_CLASS(CVmeDoc),
		RUNTIME_CLASS(CVmeFrame), // custom MDI child frame
		RUNTIME_CLASS(CVmeTreeView));
	pDocTemplate->SetContainerInfo(IDR_VMETYPE_CNTR_IP);
	pDocTemplate->SetServerInfo(
		IDR_VMETYPE_SRVR_EMB, IDR_VMETYPE_SRVR_IP,
		RUNTIME_CLASS(CInPlaceFrame));
	AddDocTemplate(pDocTemplate);

	// Connect the COleTemplateServer to the document template.
	//  The COleTemplateServer creates new documents on behalf
	//  of requesting OLE containers by using information
	//  specified in the document template.
	m_server.ConnectTemplate(clsid, pDocTemplate, FALSE);

	// Register all OLE server factories as running.  This enables the
	//  OLE libraries to create objects from other applications.
	COleTemplateServer::RegisterAll();
		// Note: MDI applications register all server objects without regard
		//  to the /Embedding or /Automation on the command line.

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

//	// Parse command line for standard shell commands, DDE, file open
//	CCommandLineInfo cmdInfo;
//	ParseCommandLine(cmdInfo);

	// Check to see if launched as OLE server
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Application was run with /Embedding or /Automation.  Don't show the
		//  main window in this case.
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
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

    pSplashThread->Kill();
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
void CVmeApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CVmeApp message handlers

