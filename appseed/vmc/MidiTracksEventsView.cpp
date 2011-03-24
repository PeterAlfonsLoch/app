// MidiTracksEventsView.cpp : implementation file
//

#include "stdafx.h"
#include "../vmsp/resource.h"
#include "resource.h"
#include "VmcApp.h"
#include "MidiTracksEventsView.h"
#include "MidiTrackEventsView.h"
#include "MidiDoc.h"




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

/*
BEGIN_MESSAGE_MAP(CMidiTracksEventsView, CFormView)
	//{{AFX_MSG_MAP(CMidiTracksEventsView)
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnSelchangeTab)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB, OnSelchangingTab)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
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

CMidiDoc* CMidiTracksEventsView::GetDocument() // non-debug version is inline
{
   ASSERT(base < CMidiDoc > ::bases(m_pDocument));
	return (CMidiDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMidiTracksEventsView message handlers

void CMidiTracksEventsView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
    m_iCurrentView = 0;
    OnChangedView();


	// TODO: Add your specialized code here and/or call the base class
	
}

void CMidiTracksEventsView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here

    CFormView::OnSize(nType, cx, cy);
    
    //base_wnd::RepositionBars(0, 0xffff, IDC_TAB);
    //CStatic * pStatic = (CStatic *) GetDlgItem(IDC_STATIC_CLIENT);
	CTabCtrl * pTab	= (CTabCtrl *) GetDlgItem(IDC_TAB);
	if(pTab)
	{
        
		class rect clientRect;
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
                if(::IsWindow(pview->get_handle()))
                    pview->MoveWindow(clientRect);
        }

	}
	
}

void CMidiTracksEventsView::OnUpdate(View* pSender, LPARAM lHint, base_object* pHint) 
{
    CreateViews();
}

VMSRESULT CMidiTracksEventsView::CreateViews()
{
    CMidiDoc* pdoc = GetDocument();
    MidiSequence * pseq = &pdoc->HelperGetMidiSequence();
    MidiFile * pfile = &pseq->GetFile();
    
    CTabCtrl * pTab	= (CTabCtrl *) GetDlgItem(IDC_TAB);

    for(int i = 0; i < pfile->GetTracks().GetTrackCount(); i++)
    {
        MidiTrackBase * ptrackBase = pfile->GetTracks().TrackAt(i);
        if(ptrackBase->IsType(MidiTrackBase::TypeMidi))
        {
            MidiTrack * ptrack = (MidiTrack *) ptrackBase;
            //CMidiTrackEventsView * pview =FindViewByMidiTrackIndex(ptrack->GetMidiTrackIndex());
            CMidiTrackEventsView * pview = FindViewByTrackIndex(i);
            if(NULL == pview)
            {
                pview = new CMidiTrackEventsView(get_app());
                m_tracksViews.Add(pview);
                pview->m_iMidiTrackIndex = ptrack->GetMidiTrackIndex();
                pview->m_iTrackIndex = i;
                CreateContext cs;
                cs.m_pCurrentDoc = GetDocument();
                cs.m_pCurrentFrame = NULL;
                cs.m_pLastView = this;
                cs.m_pNewDocTemplate = NULL;
                cs.m_pNewViewClass = NULL;
                pview->base_wnd::Create(NULL, NULL, WS_CHILD |
                    WS_HSCROLL | WS_VSCROLL, class rect(0, 0, 0, 0),
                    pTab, i,&cs);
                string str;
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
    CMidiTrackEventsView * pview = m_tracksViews.ElementAt(m_iCurrentView);
    pview->ShowWindow(SW_SHOW);

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
