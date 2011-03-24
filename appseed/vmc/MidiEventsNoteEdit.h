#pragma once

#include "resource.h"

class MidiEventBase;
class MidiEventV008;

/////////////////////////////////////////////////////////////////////////////
// CMidiEventsNoteEdit dialog

class CMidiEventsNoteEdit : public CDialog
{
// Construction
public:
	VMSRESULT FromEvent(MidiEventBase * lpevent, int iRow);
	CMidiEventsNoteEdit(base_wnd* pParent = NULL);   // standard constructor
    virtual ~CMidiEventsNoteEdit();   // standard constructor

public:
	VMSRESULT ToEvent();
    MidiEventV008 *m_pevent;
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

	enum { IDD = IDD_MIDI_EVENTS_NOTE_EDIT };
	MetaButton	m_btClose;
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnButtonClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, base_wnd* pWnd, UINT nCtlColor);
};

