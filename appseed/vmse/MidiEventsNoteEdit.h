#if !defined(AFX_MIDIEVENTSNOTEEDIT_H__3F112F74_368B_41C2_8D02_2C2E65F62C41__INCLUDED_)
#define AFX_MIDIEVENTSNOTEEDIT_H__3F112F74_368B_41C2_8D02_2C2E65F62C41__INCLUDED_

#include "../vms/Vms.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MidiEventsNoteEdit.h : header file
//
//#include "MidiEventV008.h"

#include "ButtonV007.h"

#include "resource.h"

class CMidiEventBase;
class CMidiEventV008;

/////////////////////////////////////////////////////////////////////////////
// CMidiEventsNoteEdit dialog

class CMidiEventsNoteEdit : public CDialog
{
// Construction
public:
	VMSRESULT FromEvent(CMidiEventBase * lpevent, int iRow);
	CMidiEventsNoteEdit(CWnd* pParent = NULL);   // standard constructor
    virtual ~CMidiEventsNoteEdit();   // standard constructor

public:
	CWnd * m_pwndCallback;
	void SetCallbackWnd(CWnd * pwnd);
	BOOL Create(CWnd * pwndParent, CWnd * pwndCallback);
	VMSRESULT ToEvent();
    CMidiEventV008 *m_pevent;
    int             m_iRow;
    virtual void OnCancel( );
    virtual void OnOK( );

protected:
    CFont       m_fontMarlett;
    CBrush      m_brushControlBoxBack;
    CBrush      m_brushControlBoxBackSel;
    CBrush      m_brushControlBoxBackFocus;
    CBrush      m_brushControlBoxBackDisabled;
    CPen        m_penControlBoxBack;
    CPen        m_penControlBoxBackSel;
    CPen        m_penControlBoxBackFocus;
    CPen        m_penControlBoxBackDisabled;
    COLORREF    m_crControlBoxFore;
    COLORREF    m_crControlBoxForeSel;
    COLORREF    m_crControlBoxForeFocus;
    COLORREF    m_crControlBoxForeDisabled;

    CBrush      m_brushBackground;
    COLORREF    m_crBackground;
    COLORREF    m_crForeground;

// Dialog Data
	//{{AFX_DATA(CMidiEventsNoteEdit)
	enum { IDD = IDD_MIDI_EVENTS_NOTE_EDIT };
	CButtonV007	m_btClose;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMidiEventsNoteEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMidiEventsNoteEdit)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnButtonClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIDIEVENTSNOTEEDIT_H__3F112F74_368B_41C2_8D02_2C2E65F62C41__INCLUDED_)
