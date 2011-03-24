#if !defined(AFX_ALBUMTHREAD_H__36DEAEE9_54C3_488F_B1CF_1042FF88C3CC__INCLUDED_)
#define AFX_ALBUMTHREAD_H__36DEAEE9_54C3_488F_B1CF_1042FF88C3CC__INCLUDED_

#include "..\vms\Vms.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlbumBuildThread.h : header file
//


class CMessageFilterMainHook;  
class AlbumViewUpdateHint;


namespace SongsAlbum
{
    enum EBuildSongsAlbumOperation;
}

//Veriwell Musical Studio Internal Message
//#define VMSIM_ALBUMTHREAD WM_USER + 113

class CDBCentral;
/////////////////////////////////////////////////////////////////////////////
// AlbumBuildThread thread

class AlbumBuildThread :
	public CWinThread,
	public DBInterface
{
public:
   enum EMessage
   {
      MessageMain = WM_APP + 114,
   };

   enum EMessageMain // WPARAM
   {
      MessageMainOpenAlbum,
      MessageMainCloseAllAlbumDocuments,
      MessageMainCreateBuildAlbumThread,
   };

	DECLARE_DYNCREATE(AlbumBuildThread)
protected:
	AlbumBuildThread();           // protected constructor used by dynamic creation

// Attributes
public:
    class CBuildRequest
    {
    public:
        CDBCentral * m_pdc;
        SongsAlbum::EBuildSongsAlbumOperation m_eop; // Operation mask
        bool        m_bfb; // Full Build Flag
    };

    SingleDocTemplate * GetAlbumDocTemplate();

protected:
   	bool					m_bPendingShowCommand;
    SingleDocTemplate *            m_pAlbumDocTemplate;
    CList<AlbumViewUpdateHint*, AlbumViewUpdateHint*> m_pendingUpdates;
// Operations
public:
//	void PostMessageOnFinishedAlbumBuild();
	VMSRESULT AddUpdate(AlbumViewUpdateHint * puh);
	VMSRESULT UpdateViews();
	VMSRESULT PostMessageViewAlbum(bool bDoShow);
protected:
    static LRESULT CALLBACK MessageProc(
        int code,       // hook code
        WPARAM wParam,  // undefined
        LPARAM lParam   // address of structure with message data
        );


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AlbumBuildThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL OnIdle(LONG lCount);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~AlbumBuildThread();

	// Generated message map functions
	//{{AFX_MSG(AlbumBuildThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
    afx_msg void OnMainMessage(WPARAM wParam, LPARAM lParam );
    afx_msg void OnVmsmV001(WPARAM wParam, LPARAM lParam );
    afx_msg void OnVmsmException(WPARAM wParam, LPARAM lParam );
    afx_msg void OnUserMessage(WPARAM wParam, LPARAM lParam );
	DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALBUMTHREAD_H__36DEAEE9_54C3_488F_B1CF_1042FF88C3CC__INCLUDED_)
