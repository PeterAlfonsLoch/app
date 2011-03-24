#pragma once

class CVmpHighThread :
   public gen::Thread
{
	DECLARE_DYNCREATE(CVmpHighThread)
protected:
	CVmpHighThread();        // protected constructor used by dynamic creation
	
public:
	CCriticalSection		m_csBitmap;
	DWORD					m_dwImageLoaderEventAdvise;
    CCriticalSection                    m_csTimersWindows;
    base_array <CTimerWnd *, CTimerWnd *>   m_timersWindows;


// Attributes
public:
	CVMSApp * m_pMainApp;
protected:
    bool        m_bEnableTimers;
	
// Operations
public:
	static CVmpHighThread * AppGetHighThread();
	bool TranslateApp3388Message(LPMSG lpmsg);
//	bool CreateTimer(CTimerCallback * ptc, UINT uiElapse, UINT uiIDEvent);
//	int DeleteTimerWnd(CTimerWnd * pTimerWnd);
	HBITMAP LoadImageSync(LPCTSTR lpcsz);
	virtual BOOL ProcessMessageFilter(int code, LPMSG lpMsg);
	void EnableTimers(bool bEnable = true);
	void DeleteTimersWindows();
	BOOL TranslateUserMessage(MSG *pMsg);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXfplayerThreadV1)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle(LONG lCount);
	virtual int Run();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CVmpHighThread();

	// Generated message map functions
	//{{AFX_MSG(CXfplayerThreadV1)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	afx_msg void OnVmsmV001(WPARAM wparam, LPARAM lparam);
    
};

