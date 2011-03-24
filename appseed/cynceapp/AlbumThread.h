#if !defined(AFX_ALBUMTHREAD_H__7E88E715_8DEC_432A_8DC8_FFF63C63B61F__INCLUDED_)
#define AFX_ALBUMTHREAD_H__7E88E715_8DEC_432A_8DC8_FFF63C63B61F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlbumThread.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// AlbumThread thread

class AlbumThread : public CWinThread
{
	DECLARE_DYNCREATE(AlbumThread)
protected:
	AlbumThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AlbumThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~AlbumThread();

	// Generated message map functions
	//{{AFX_MSG(AlbumThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALBUMTHREAD_H__7E88E715_8DEC_432A_8DC8_FFF63C63B61F__INCLUDED_)
