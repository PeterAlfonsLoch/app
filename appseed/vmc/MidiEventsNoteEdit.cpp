// MidiEventsNoteEdit.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MidiEventsNoteEdit.h"


CMidiEventsNoteEdit::CMidiEventsNoteEdit(base_wnd* pParent /*=NULL*/)
	: CDialog(CMidiEventsNoteEdit::IDD, pParent),
    m_brushControlBoxBack(GetSysColor(COLOR_BTNFACE)),
    m_brushControlBoxBackSel(GetSysColor(COLOR_WINDOW)),
    m_brushControlBoxBackFocus(RGB(0, 255, 255)),
    m_brushControlBoxBackDisabled(GetSysColor(COLOR_BTNFACE)),
    m_penControlBoxBack(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE)),
    m_penControlBoxBackSel(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE)),
    m_penControlBoxBackFocus(PS_SOLID, 1, RGB(0, 255, 255)),
    m_penControlBoxBackDisabled(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE)),
    m_brushBackground(GetSysColor(COLOR_WINDOW))
{
	//{{AFX_DATA_INIT(CMidiEventsNoteEdit)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
//    m_lpevent = NULL;

    m_crControlBoxFore = GetSysColor(COLOR_BTNTEXT);
    m_crControlBoxForeSel = GetSysColor(COLOR_BTNTEXT);
    m_crControlBoxForeFocus = GetSysColor(COLOR_BTNTEXT);
    m_crControlBoxForeDisabled = GetSysColor(COLOR_GRAYTEXT);

    m_crBackground = GetSysColor(COLOR_WINDOW);
    m_crForeground = GetSysColor(COLOR_WINDOWTEXT);

    m_pevent = new MidiEventV008();

}

CMidiEventsNoteEdit::~CMidiEventsNoteEdit()
{
    if(m_pevent != NULL)
    {
        delete m_pevent;
        m_pevent = NULL;
    }
}

void CMidiEventsNoteEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMidiEventsNoteEdit)
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_btClose);
	//}}AFX_DATA_MAP
}

/*
BEGIN_MESSAGE_MAP(CMidiEventsNoteEdit, CDialog)
	//{{AFX_MSG_MAP(CMidiEventsNoteEdit)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/

/////////////////////////////////////////////////////////////////////////////
// CMidiEventsNoteEdit message handlers

int CMidiEventsNoteEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
    CDC * pDC = GetDC();
    m_fontMarlett.CreatePointFont(90, _T("Marlett"), GetDC());
    ReleaseDC(pDC);
    pDC = NULL;


   
	// TODO: Add your specialized creation code here
	
	return 0;
}

VMSRESULT CMidiEventsNoteEdit::FromEvent(MidiEventBase *lpevent, int iRow)
{
    ASSERT(lpevent->GetType() == Midi::NoteOn ||
        lpevent->GetType() == Midi::NoteOff);

	CComboBox * pTypeCombo = (CComboBox *) GetDlgItem(IDC_COMBO_FULLTYPE);
    Midi::SelectTypeCombo(pTypeCombo, lpevent);

    CComboBox * pPitchCombo = (CComboBox *) GetDlgItem(IDC_COMBO_PITCH);
    Midi::SelectPitchCombo(pPitchCombo, lpevent);


    string str;
    str.Format("%d", lpevent->GetNoteVelocity());
    CEdit * peditVelocity = (CEdit *) GetDlgItem(IDC_EDIT_VELOCITY);
    peditVelocity->SetWindowText(str);

    *m_pevent = *lpevent;
    m_iRow = iRow;

    return VMSR_SUCCESS;
}


BOOL CMidiEventsNoteEdit::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CComboBox * pTypeCombo = (CComboBox *) GetDlgItem(IDC_COMBO_FULLTYPE);

    Midi::FillTypeCombo(pTypeCombo);

    CComboBox * pPitchCombo = (CComboBox *) GetDlgItem(IDC_COMBO_PITCH);

    Midi::FillPitchCombo(pPitchCombo);
    
    string str;

    str = (CHAR) 114;
    m_btClose.SetWindowText(str);
    m_btClose.SetFont(&m_fontMarlett);
    m_btClose.SetEllipseBrushs(&m_brushControlBoxBack, &m_brushControlBoxBackSel, &m_brushControlBoxBackFocus, &m_brushControlBoxBackDisabled);
    m_btClose.SetEllipsePens(&m_penControlBoxBack, &m_penControlBoxBackSel, &m_penControlBoxBackFocus, &m_penControlBoxBackDisabled);
    m_btClose.SetTextColors(m_crControlBoxFore, m_crControlBoxForeSel, m_crControlBoxForeFocus, m_crControlBoxForeDisabled);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMidiEventsNoteEdit::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnClose();
}


void CMidiEventsNoteEdit::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	
}


void CMidiEventsNoteEdit::OnCancel() 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnCancel();
    base_wnd * pParent = GetParent();
	if(pParent != NULL)
    {
        pParent->SendMessage(WM_USER, (WPARAM) (base_wnd *) this, 0);
    }
}

void CMidiEventsNoteEdit::OnOK() 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnOK();
    ToEvent();
    base_wnd * pParent = GetParent();
	if(pParent != NULL)
    {
        pParent->SendMessage(WM_USER, m_iRow, 1);
    }
}


VMSRESULT CMidiEventsNoteEdit::ToEvent()
{
    ASSERT(m_pevent->GetType_() == Midi::NoteOn ||
        m_pevent->GetType_() == Midi::NoteOff);

	CComboBox * pTypeCombo = (CComboBox *) GetDlgItem(IDC_COMBO_FULLTYPE);
    m_pevent->SetType_(pTypeCombo->GetItemData(pTypeCombo->GetCurSel()));

    CComboBox * pPitchCombo = (CComboBox *) GetDlgItem(IDC_COMBO_PITCH);
    m_pevent->SetNotePitch(pPitchCombo->GetItemData(pPitchCombo->GetCurSel()));

    CEdit * peditVelocity = (CEdit *) GetDlgItem(IDC_EDIT_VELOCITY);
    string str;
    peditVelocity->GetWindowText(str);
    m_pevent->SetNoteVelocity(_ttoi(str));

//    m_lpevent = lpevent;

    return VMSR_SUCCESS;

}

void CMidiEventsNoteEdit::OnButtonClose() 
{
	// TODO: Add your control notification handler code here
	PostMessage(WM_CLOSE);
}

HBRUSH CMidiEventsNoteEdit::OnCtlColor(CDC* pDC, base_wnd* pWnd, UINT nCtlColor) 
{
	//HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
		HBRUSH hbr;
	if(nCtlColor == CTLCOLOR_EDIT)
	{
		pDC->SetTextColor(m_crForeground);
		hbr = m_brushBackground;
		pDC->SetBkColor(m_crBackground);
	}
	else if(nCtlColor == CTLCOLOR_MSGBOX)
	{
		hbr = m_brushBackground;
	}
	else if(nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(m_crForeground);
		hbr = m_brushBackground;
		pDC->SetBkColor(m_crBackground);
	}
	else if(nCtlColor == CTLCOLOR_DLG)
	{
//		pDC->SetTextColor(RGB(255, 255, 255));
		hbr = m_brushBackground;
//		pDC->SetBkColor(RGB(0, 0, 0));
	}
	else
	{
		hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	}
    // TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
