// vrec.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "vrec.h"

#include "MainFrm.h"
#include "vrecDoc.h"
#include "vrecView.h"

// vmsgen
#include "vmsgen/_vmsgenCommandLineInfo.h"

// vmswin
#include "vmswin/WindowsShell.h"

#include "vmsguibase/DocManager.h"

#include "notsad/Factory.h"
#include "notsad_win/Factory.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// VRecApplication

BEGIN_MESSAGE_MAP(VRecApplication, CWinApp)
	//{{AFX_MSG_MAP(VRecApplication)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// VRecApplication construction

VRecApplication::VRecApplication()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only VRecApplication object

VRecApplication theApp;

/////////////////////////////////////////////////////////////////////////////
// VRecApplication initialization

BOOL VRecApplication::InitInstance()
{
   notsad::g_pfactory->SetFactoryImpl(new notsad_win::Factory());

   Ex1AppInitialize();


	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

   WindowsShell::Initialize();

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

   m_pdoctemplate = new guibase::SingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(VRecDocument),
		RUNTIME_CLASS(MainFrame),       // main SDI frame window
		RUNTIME_CLASS(VRecView));
	guibase::AppInterface::AddDocTemplate(m_pdoctemplate);

	// Parse command line for standard shell commands, DDE, file open
   // Parse command line for standard shell commands, DDE, file open
   _vmsgen::CommandLineInfo cmdInfo;
   Ex1::GetApp()->_001ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!_001ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();



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
void VRecApplication::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// VRecApplication message handlers


Ex1FactoryImpl * VRecApplication::Ex1AppGetFactoryImpl()
{
   return new WinFactoryImpl();
}


void VRecApplication::OnFileNew() 
{
   m_pdoctemplate->OpenDocumentFile(NULL);	
}


void VRecApplication::SetLanguage(enum gen::App::ELanguage)
{
}
enum gen::App::ELanguage VRecApplication::GetLanguage()
{
   return langDefault;
}
enum gen::App::ELanguage VRecApplication::GetDefaultLanguage()
{
   return langDefault;
}
bool VRecApplication::MessageWindowListener(unsigned int,unsigned int,long)
{
   return true;
}


void VRecApplication::OnFileOpen()
{
   m_pdocmanager->OnFileOpen();
}


