// lyricsXtractDlg.cpp : implementation file
//

#include "stdafx.h"
#include "lyricsxtract.h"
#include "lyricsXtractDlg.h"
#include "DlgProxy.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

/////////////////////////////////////////////////////////////////////////////
// CLyricsXtractDlg dialog

IMPLEMENT_DYNAMIC(CLyricsXtractDlg, CDialog);

CLyricsXtractDlg::CLyricsXtractDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLyricsXtractDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLyricsXtractDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CLyricsXtractDlg::~CLyricsXtractDlg()
{
	// If there is an automation proxy for this dialog, set
	//  its back pointer to this dialog to NULL, so it knows
	//  the dialog has been deleted.
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CLyricsXtractDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLyricsXtractDlg)
	DDX_Control(pDX, IDC_EDIT_FOLDER_PATH, m_editFolderPath);
	DDX_Control(pDX, IDC_EDIT_FILE_PATH, m_editFilePath);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLyricsXtractDlg, CDialog)
	//{{AFX_MSG_MAP(CLyricsXtractDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_EXTRACT, OnExtract)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLyricsXtractDlg message handlers

BOOL CLyricsXtractDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLyricsXtractDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CLyricsXtractDlg::OnDestroy()
{
	WinHelp(0L, HELP_QUIT);
	CDialog::OnDestroy();
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLyricsXtractDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLyricsXtractDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// Automation servers should not exit when a user closes the UI
//  if a controller still holds on to one of its objects.  These
//  message handlers make sure that if the proxy is still in use,
//  then the UI is hidden but the dialog remains around if it
//  is dismissed.

void CLyricsXtractDlg::OnClose() 
{
	if (CanExit())
		CDialog::OnClose();
}

void CLyricsXtractDlg::OnOK() 
{
	if (CanExit())
		CDialog::OnOK();
}

void CLyricsXtractDlg::OnCancel() 
{
	if (CanExit())
		CDialog::OnCancel();
}

BOOL CLyricsXtractDlg::CanExit()
{
	// If the proxy object is still around, then the automation
	//  controller is still holding on to this application.  Leave
	//  the dialog around, but hide its UI.
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}

void CLyricsXtractDlg::GetPaths(
   CWStrArray & wstra,
   CWStr wstrFolder,
   CWStrArray wstraExtensions)
{

   CFileFind fileFind;
	CString strB;
   CWStr wstrFind;
   CWStr wstrFile;
   CString strFind;
   CString strFile;
   CString strDebug;
   bool bOk;

   for(int j = 0; j < wstraExtensions.GetSize(); j++)
   {
	   wstrFind = wstraFolders.ElementAt(i);
		wstrFind += L"\\*.";
      wstrFind += wstraExtensions.ElementAt(j);
		CInternational::UnicodeToOEM(strFind, wstrFind);
      if(!fileFind.FindFile(str))
      {
         continue;
      }
      bOk = true
		while(bOk)
		{
         bOk = fileFind.FindNextFile() != FALSE;
			strFile = fileFind.GetFilePath();
	      wstrFile.SetOEM(strFoçe);
		   CInternational::UnicodeToOEM(strDebug, wstr);
			ASSERT(strFile.Collate(strDebug) == 0);
         wstra.Add(wstrFile);
      }
   }
   
}

void CLyricsXtractDlg::OnExtract() 
{
   CWStr wstrFolder;
   CString strFolder;
   CWStrArray wstraFiles;
   CWStrArray wstraExtensions;


   wstraExtensions.Add(L"*.mid");
   wstraExtensions.Add(L"*.kar");
   wstraExtensions.Add(L"*.st3");

   m_editFolderPath.GetWindowText(strFolder);
   wstrFolder.SetOEM(strFolder);	

   GetPaths(wstraFiles, wstrFolder, wstraExtensions);

}
