#if !defined(AFX_MIDIDOC_H__90D3DBFB_9061_440C_A6C5_0563698166E8__INCLUDED_)
#define AFX_MIDIDOC_H__90D3DBFB_9061_440C_A6C5_0563698166E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MidiDoc.h : header file
//

#include "XfplayerDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CMidiDoc document

class CMidiDoc : public CXfplayerDoc
{
protected:
	CMidiDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMidiDoc)

// Attributes
public:

protected:
    int m_iTargetFileType;
// Operations
public:
    BOOL DoSave(LPCTSTR lpszPathName, BOOL bReplace);
    BOOL OnSaveDocument(LPCTSTR lpszPathName);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMidiDoc)
	public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMidiDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMidiDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIDIDOC_H__90D3DBFB_9061_440C_A6C5_0563698166E8__INCLUDED_)
