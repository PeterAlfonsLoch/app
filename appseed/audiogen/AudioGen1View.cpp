// AudioGen1View.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAudioGen1View

IMPLEMENT_DYNCREATE(CAudioGen1View, CFormView)

CAudioGen1View::CAudioGen1View()
	: CFormView(CAudioGen1View::IDD)
{
	//{{AFX_DATA_INIT(CAudioGen1View)
	m_dFreq = 0.0;
	//}}AFX_DATA_INIT
   m_pwaveout = _vmsaudio::WaveOut::BeginThread();
   m_paudiogen = (AudioGen *) AfxBeginThread(RUNTIME_CLASS(AudioGen));
   m_paudiogen->m_pwaveout = m_pwaveout;
   m_pwaveout->Open(m_paudiogen, 4, 8 * 1024);

}

CAudioGen1View::~CAudioGen1View()
{
}

void CAudioGen1View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAudioGen1View)
	DDX_Text(pDX, IDC_EDIT_FREQUENCY, m_dFreq);
	DDV_MinMaxDouble(pDX, m_dFreq, 1., 22100.);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAudioGen1View, CFormView)
	//{{AFX_MSG_MAP(CAudioGen1View)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_COMMAND(ID_EXECUTE_PLAY, OnExecutePlay)
	ON_COMMAND(ID_EXECUTE_STOP, OnExecuteStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAudioGen1View diagnostics

#ifdef _DEBUG
void CAudioGen1View::AssertValid() const
{
	CFormView::AssertValid();
}

void CAudioGen1View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAudioGen1View message handlers

void CAudioGen1View::OnButtonApply() 
{
   UpdateData();
   m_paudiogen->m_dFreq = m_dFreq; 	
   m_paudiogen->Gen();
}

void CAudioGen1View::OnExecutePlay() 
{
	m_pwaveout->Start();
	
}

void CAudioGen1View::OnExecuteStop() 
{
	m_pwaveout->Stop();
	
}
