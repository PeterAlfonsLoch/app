#pragma once

/////////////////////////////////////////////////////////////////////////////
// WinApp - the root of all Windows applications

#define _AFX_MRU_COUNT   4      // default support for 4 entries in file MRU
#define _AFX_MRU_MAX_COUNT 16   // currently allocated id range supports 16

class WinApp :
   public thread,
   public WinAppInterfaceImpl
{
	// DECLARE_DYNAMIC(WinApp)
public:

// Constructor
	WinApp(LPCTSTR lpszAppName = NULL);     // cast name defaults to EXE name

// Attributes
	// Startup args (do not change)
	HINSTANCE m_hInstance;
	HINSTANCE m_hPrevInstance;
	LPTSTR m_lpCmdLine;
	int m_nCmdShow;

	// Running args (can be changed in initialize_instance)
	LPCTSTR m_pszAppName;  // human readable name
								//  (from constructor or AFX_IDS_APP_TITLE)
	LPCTSTR m_pszRegistryKey;   // used for registry entries
	DocumentManager* m_pdocmanager;

	// Support for Shift+F1 help mode.
	BOOL m_bHelpMode;           // are we in Shift+F1 mode?

public:  // set in constructor to override default
	LPCTSTR m_pszExeName;       // executable name (no spaces)
	LPCTSTR m_pszHelpFilePath;  // default based on module path
	LPCTSTR m_pszProfileName;   // default based on cast name

// Initialization Operations - should be done in initialize_instance
protected:
	void LoadStdProfileSettings(UINT nMaxMRU = _AFX_MRU_COUNT); // load MRU file list and last preview state
	void EnableShellOpen();

#ifndef _AFX_NO_GRAYDLG_SUPPORT
	void SetDialogBkColor(COLORREF clrCtlBk = RGB(192, 192, 192),
				COLORREF clrCtlText = RGB(0, 0, 0));
		// set dialog box and message box background color
#endif

	void SetRegistryKey(LPCTSTR lpszRegistryKey);
	void SetRegistryKey(UINT nIDRegistryKey);
		// enables cast settings in registry instead of INI files
		//  (registry key is usually a "company name")

#ifndef _AFX_NO_CTL3D_SUPPORT
	BOOL Enable3dControls(); // use CTL3D32.DLL for 3D controls in dialogs
#ifndef _ApplicationFrameworkDLL
	BOOL Enable3dControlsStatic();  // statically link CTL3D.LIB instead
#endif
#endif

	void RegisterShellFileTypes(BOOL bCompat=FALSE);
		// call after all doc templates are registered
	void RegisterShellFileTypesCompat();
		// for backwards compatibility
	void UnregisterShellFileTypes();

// Helper Operations - usually done in initialize_instance
public:
	// Cursors
	HCURSOR LoadCursor(LPCTSTR lpszResourceName) const;
	HCURSOR LoadCursor(UINT nIDResource) const;
	HCURSOR LoadStandardCursor(LPCTSTR lpszCursorName) const; // for IDC_ values
	HCURSOR LoadOEMCursor(UINT nIDCursor) const;             // for OCR_ values

	// Icons
	HICON LoadIcon(LPCTSTR lpszResourceName) const;
	HICON LoadIcon(UINT nIDResource) const;
	HICON LoadStandardIcon(LPCTSTR lpszIconName) const;       // for IDI_ values
	HICON LoadOEMIcon(UINT nIDIcon) const;                   // for OIC_ values

	// Profile settings (to the cast specific .INI file, or registry)
	UINT GetProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nDefault);
	BOOL WriteProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nValue);
	string GetProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry,
				LPCTSTR lpszDefault = NULL);
	BOOL WriteProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry,
				LPCTSTR lpszValue);
	BOOL GetProfileBinary(LPCTSTR lpszSection, LPCTSTR lpszEntry,
				LPBYTE* ppData, UINT* pBytes);
	BOOL WriteProfileBinary(LPCTSTR lpszSection, LPCTSTR lpszEntry,
				LPBYTE pData, UINT nBytes);

	BOOL Unregister();
	LONG DelRegTree(HKEY hParentKey, const string& strKeyName);

// Running Operations - to be done on a running application
	// Dealing with document templates
	void AddDocTemplate(document_template* pTemplate);
	POSITION GetFirstDocTemplatePosition() const;
	document_template* GetNextDocTemplate(POSITION& pos) const;

	// Dealing with files
	virtual document* OpenDocumentFile(LPCTSTR lpszFileName); // open named file
	virtual void AddToRecentFileList(LPCTSTR lpszPathName);  // add to MRU

	// Printer DC Setup routine, 'struct tagPD' is a PRINTDLG structure
	void SelectPrinter(HANDLE hDevNames, HANDLE hDevMode,
		BOOL bFreeOld = TRUE);
	BOOL CreatePrinterDC(CDC& dc);
#ifndef _UNICODE
	BOOL GetPrinterDeviceDefaults(struct tagPDA* pPrintDlg);
#else
	BOOL GetPrinterDeviceDefaults(struct tagPDW* pPrintDlg);
#endif

	// Command line parsing
	BOOL RunEmbedded();
	BOOL RunAutomated();
	void ParseCommandLine(CCommandLineInfo& rCmdInfo);
	BOOL ProcessShellCommand(CCommandLineInfo& rCmdInfo);

// Overridables
	// hooks for your initialization code
	virtual BOOL InitApplication();

	// exiting
	virtual BOOL SaveAllModified(); // save before exit
	void HideApplication();
	void CloseAllDocuments(BOOL bEndSession); // close documents before exiting

	// Advanced: to override message boxes and other hooks
	virtual int DoMessageBox(LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt);
	virtual void DoWaitCursor(int nCode); // 0 => restore, 1=> begin, -1=> end

	// Advanced: process async DDE request
	virtual BOOL OnDDECommand(LPTSTR lpszCommand);

	// Advanced: Help support
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);

// Command Handlers
protected:
	// map to the following for file new/open
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();

	// map to the following to enable print setup
	afx_msg void OnFilePrintSetup();

	// map to the following to enable help
	afx_msg void OnContextHelp();   // shift-F1
	afx_msg void OnHelp();          // F1 (uses current context)
	afx_msg void OnHelpIndex();     // ID_HELP_INDEX
	afx_msg void OnHelpFinder();    // ID_HELP_FINDER, ID_DEFAULT_HELP
	afx_msg void OnHelpUsing();     // ID_HELP_USING

// Implementation
protected:
	HGLOBAL m_hDevMode;             // printer Dev Mode
	HGLOBAL m_hDevNames;            // printer Device Names
	DWORD m_dwPromptContext;        // help context override for message box

	int m_nWaitCursorCount;         // for wait cursor (>0 => waiting)
	HCURSOR m_hcurWaitCursorRestore; // old cursor to restore after wait cursor

	CRecentFileList* m_pRecentFileList;

	void UpdatePrinterSelection(BOOL bForceDefaults);
	void SaveStdProfileSettings();  // save options to .INI file

public: // public for implementation access
	CCommandLineInfo* m_pCmdInfo;

	ATOM m_atomApp, m_atomSystemTopic;   // for DDE open
	UINT m_nNumPreviewPages;        // number of default printed pages

	size_t  m_nSafetyPoolSize;      // ideal size

	void (AFXAPI* m_lpfnDaoTerm)();

	void DevModeChange(LPTSTR lpDeviceName);
	void SetCurrentHandles();
	int GetOpenDocumentCount();

	// helpers for standard commdlg dialogs
	BOOL DoPromptFileName(string& fileName, UINT nIDSTitle,
			DWORD lFlags, BOOL bOpenFileDialog, document_template* pTemplate);
	int DoPrintDialog(CPrintDialog* pPD);

	void EnableModeless(BOOL bEnable); // to disable OLE in-place dialogs

	// overrides for implementation
	virtual bool initialize_instance();
	virtual int exit_instance(); // return cast exit code
	virtual int Run();
	virtual BOOL OnIdle(LONG lCount); // return TRUE if more idle processing
	virtual LRESULT ProcessWndProcException(base_exception* e, const MSG* pMsg);

public:
	virtual ~WinApp();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// helpers for registration
	HKEY GetSectionKey(LPCTSTR lpszSection);
	HKEY GetAppRegistryKey();

protected:
	//{{AFX_MSG(WinApp)
	afx_msg void OnAppExit();
	afx_msg void OnUpdateRecentFileMenu(CCmdUI* pCmdUI);
	afx_msg BOOL OnOpenRecentFile(UINT nID);
	//}}AFX_MSG
	// DECLARE_MESSAGE_MAP()
};

WinApp* AFXAPI vfxGetApp();
base_wnd* AFXAPI vfxGetMainWnd();

#define vfxCurrentWinApp    vfxGetModuleState()->m_pCurrentWinApp
#define vfxCurrentInstanceHandle    vfxGetModuleState()->m_hCurrentInstanceHandle

// Global helper functions
inline WinApp* AFXAPI vfxGetApp()
	{ return vfxCurrentWinApp; }


