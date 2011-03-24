// MidiTracksEventsView.cpp : implementation file
//

#include "stdafx.h"
#include "vmsmusresource.h"
#include "resource.h"
//#include "Vms.h"
#include "MidiTracksEventsView.h"


#include "XfplayerDoc.h"

#include "MidiDoc.h"
#include "MidiFile.h"
#include "MidiSequence.h"
#include "MidiTrackEventsView.h"
#include "MidiTrack.h"
#include "MidiTracks.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMidiTracksEventsView

IMPLEMENT_DYNCREATE(CMidiTracksEventsView, CFormView)

CMidiTracksEventsView::CMidiTracksEventsView()
	: CFormView(CMidiTracksEventsView::IDD)
{
	//{{AFX_DATA_INIT(CMidiTracksEventsView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_iCurrentView = 0;
}

CMidiTracksEventsView::~CMidiTracksEventsView()
{
}

void CMidiTracksEventsView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMidiTracksEventsView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMidiTracksEventsView, CFormView)
	//{{AFX_MSG_MAP(CMidiTracksEventsView)
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnSelchangeTab)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB, OnSelchangingTab)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMidiTracksEventsView diagnostics

#ifdef _DEBUG
void CMidiTracksEventsView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMidiTracksEventsView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

//CMidiDoc* CMidiTracksEventsView::GetDocument() // non-debug version is inline
//{
//	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMidiDoc)));
//	return (CMidiDoc*)m_pDocument;
//}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMidiTracksEventsView message handlers

void CMidiTracksEventsView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	CreateViews();
    m_iCurrentView = 0;
    OnChangedView();


	// TODO: Add your specialized code here and/or call the base class
	
}

void CMidiTracksEventsView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here

    CFormView::OnSize(nType, cx, cy);
    
    //CWnd::RepositionBars(0, 0xffff, IDC_TAB);
    //CStatic * pStatic = (CStatic *) GetDlgItem(IDC_STATIC_CLIENT);
	CTabCtrl * pTab	= (CTabCtrl *) GetDlgItem(IDC_TAB);
	if(pTab)
	{
        
		CRect clientRect;
        GetClientRect(clientRect);
        pTab->MoveWindow(clientRect);
		pTab->GetClientRect(clientRect);
        pTab->AdjustRect(false, clientRect);
        pTab->ClientToScreen(clientRect);
		ScreenToClient(clientRect);
        for(int i = 0; i < m_tracksViews.GetSize(); i++)
        {
            CMidiTrackEventsView * pview = m_tracksViews.ElementAt(i);
            if(pview)
                if(::IsWindow(pview->m_hWnd))
                    pview->MoveWindow(clientRect);
        }

	}
	
}

void CMidiTracksEventsView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
    CMidiDocHelper * pdoc = HelperGetMidiDocHelper();
    CMidiSequence * pseq = NULL;
    if(pdoc != NULL)
        pseq = pdoc->HelperGetMidiSequence();
    CMidiFile * pfile = NULL;
    if(pseq != NULL)
        pfile = pseq->GetFile();
    //pfile->m_ptracks->ExpandTrack(0);
    //pFile->ToWorkStorage();

    CreateViews();

	
}

VMSRESULT CMidiTracksEventsView::CreateViews()
{
    CMidiDocHelper * pdoc = HelperGetMidiDocHelper();
    CMidiSequence * pseq = NULL;
    if(pdoc != NULL)
        pseq = pdoc->HelperGetMidiSequence();
    CMidiFile * pfile = NULL;
    if(pseq != NULL)
        pfile = pseq->GetFile();

    if(pfile == NULL)
        return VMSR_E_FAIL;

    CTabCtrl * pTab	= (CTabCtrl *) GetDlgItem(IDC_TAB);

    for(int i = 0; i < pfile->m_ptracks->GetSize(); i++)
    {
        CMidiTrackBase * ptrackBase = pfile->m_ptracks->ElementAt(i);
        if(ptrackBase->IsKindOf(RUNTIME_CLASS(CMidiTrack)))
        {
            CMidiTrack * ptrack = (CMidiTrack *) ptrackBase;
            //CMidiTrackEventsView * pview =FindViewByMidiTrackIndex(ptrack->GetMidiTrackIndex());
            CMidiTrackEventsView * pview = FindViewByTrackIndex(i);
            if(NULL == pview)
            {
                pview = new CMidiTrackEventsView();
                m_tracksViews.Add(pview);
                pview->m_iMidiTrackIndex = ptrack->GetMidiTrackIndex();
                pview->m_iTrackIndex = i;
                CCreateContext cs;
                cs.m_pCurrentDoc = GetDocument();
                cs.m_pCurrentFrame = NULL;
                cs.m_pLastView = this;
                cs.m_pNewDocTemplate = NULL;
                cs.m_pNewViewClass = NULL;
                pview->Create(NULL, NULL, WS_CHILD |
                    WS_HSCROLL | WS_VSCROLL, CRect(0, 0, 0, 0),
                    pTab, i,&cs);
                pview->OnInitialUpdate();
                CString str;
//                if(pview->m_iMidiTrackIndex < 0)
  //              {
                    str.Format("Trilha %d", i + 1);
    //            }
      //          else
        //        {
          //          str.Format("Trilha %d", i + 1);
            //    }
                pTab->InsertItem(pTab->GetItemCount(), str);
            }
        }
    }
    return VMSR_SUCCESS;
}

CMidiTrackEventsView * CMidiTracksEventsView::FindViewByMidiTrackIndex(int iMidiTrackIndex)
{
    for(int i = 0; i < m_tracksViews.GetSize(); i++)
    {
        if(m_tracksViews.ElementAt(i)->m_iMidiTrackIndex == iMidiTrackIndex)
        {
            return m_tracksViews.ElementAt(i);
        }
    }
    return NULL;
}

void CMidiTracksEventsView::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    CTabCtrl * pTab	= (CTabCtrl *) GetDlgItem(IDC_TAB);

	m_iCurrentView = pTab->GetCurSel();
    OnChangedView();

	*pResult = 0;
    
}

void CMidiTracksEventsView::OnSelchangingTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnChangeView();

	*pResult = 0;
}

void CMidiTracksEventsView::OnChangedView()
{
	if(m_iCurrentView >= 0 && m_iCurrentView < m_tracksViews.GetSize())
	{
		CMidiTrackEventsView * pview = m_tracksViews.ElementAt(m_iCurrentView);
		pview->ShowWindow(SW_SHOW);
	}

}


void CMidiTracksEventsView::OnChangeView()
{

    CMidiTrackEventsView * pview = m_tracksViews.ElementAt(m_iCurrentView);
    pview->ShowWindow(SW_HIDE);

}

CMidiTrackEventsView * CMidiTracksEventsView::FindViewByTrackIndex(int iTrackIndex)
{
    for(int i = 0; i < m_tracksViews.GetSize(); i++)
    {
        if(m_tracksViews.ElementAt(i)->m_iTrackIndex == iTrackIndex)
        {
            return m_tracksViews.ElementAt(i);
        }
    }
    return NULL;

}

BOOL CMidiTracksEventsView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	HINSTANCE hinst = GetModuleHandle(NULL);
	HINSTANCE hinst2 = AfxGetInstanceHandle();
	HINSTANCE hinstance = AfxGetResourceHandle();
    AfxSetResourceHandle(GetModuleHandle("vmse.dll"));
    BOOL bResult = CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
    AfxSetResourceHandle(hinstance);
	return bResult;

}

int CMidiTracksEventsView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

LRESULT CMidiTracksEventsView::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CFormView::DefWindowProc(message, wParam, lParam);
}

BOOL CMidiTracksEventsView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
    if(!CFormView::PreCreateWindow(cs))
        return FALSE;
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	return TRUE;
}
