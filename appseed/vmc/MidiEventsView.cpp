// MidiEventsView.cpp : implementation file
//


#include "stdafx.h"
#include "VmcApp.h"
#include "MidiEventsView.h"

#include "XfplayerDoc.h"

#include "MidiEventsNoteEdit.h"

#include "BaseRect.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMidiEventsView

IMPLEMENT_DYNCREATE(CMidiEventsView, CView)

CMidiEventsView::CMidiEventsView()
{
    m_iRowHeight = 20;
    m_pNoteEdit = new CMidiEventsNoteEdit();
    m_iPressed = -1;
}

CMidiEventsView::~CMidiEventsView()
{
    if(m_pNoteEdit != NULL)
    {
        delete m_pNoteEdit;
    }
}


BEGIN_MESSAGE_MAP(CMidiEventsView, CView)
	//{{AFX_MSG_MAP(CMidiEventsView)
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
    ON_MESSAGE(WM_USER, OnUserMessage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMidiEventsView drawing

void CMidiEventsView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

//	CSize sizeTotal;
//	// TODO: calculate the total size of this view
//	sizeTotal.cx = sizeTotal.cy = 100;
//	SetScrollSizes(MM_TEXT, sizeTotal);

/*   	CSize sizeTotal, sizePage, sizeLine;
    int nMapMode;
    GetDeviceScrollSizes(nMapMode, sizeTotal, sizePage, sizeLine);
    ASSERT(nMapMode == MM_TEXT);
    GetViewSize(&sizeTotal);
    SetScrollSizes(nMapMode, sizeTotal, sizePage, sizeLine); */

}

void CMidiEventsView::OnDraw(CDC* pDC)
{
	CXfplayerDoc* pDoc = GetDocument();
    CMidiSequence * pSeq = pDoc->GetMidiSequence();
    CMidiFile * pFile = pSeq->GetFile();
    //pFile->ToWorkStorage();
    if(!pFile->m_tracks.ElementAt(0)->IsKindOf(RUNTIME_CLASS(CMidiTrack)))
        return;
    CMidiTrack * pTrack = (CMidiTrack *) pFile->m_tracks.ElementAt(0);
    CMidiTrackV008 & track = pTrack->GetWorkTrack();
    CBaseArray<CMidiEventV008, CMidiEventV008 &> & events = track.m_events;
    //CPoint ptScrollPosition = GetScrollPosition();
    
    CRect rectClipBox;
    pDC->GetClipBox(rectClipBox);
    if(rectClipBox.IsRectNull())
        return;


    CPoint ptOriginalViewportOrg = pDC->GetViewportOrg();
    pDC->SetViewportOrg(m_ptScroll);

    //int iFirstRow = HitTestRow(ptScrollPosition.y);
    int iFirstRow = HitTestRow(rectClipBox.top);
//    int iFirstRowOffset = GetRowPositionOffset(ptScrollPosition.y);

    CSize sizeTotal, sizePage, sizeLine;
    int nMapMode;
    GetDeviceScrollSizes(nMapMode, sizeTotal, sizePage, sizeLine);
    ASSERT(nMapMode == MM_TEXT);

    //int iLastRow = HitTestRow(ptScrollPosition.y + sizePage.cy);
    int iLastRow = HitTestRow(rectClipBox.bottom);
//    int iLastRowOffset = GetRowPositionOffset(ptScrollPosition.y + sizePage.cy);

    if(iLastRow >= events.GetSize())
    {
        iLastRow = events.GetSize() - 1;
    }

    int iBkModeOld = pDC->GetBkMode();
    pDC->SetBkMode(TRANSPARENT);
    CPen * ppenOld = pDC->GetCurrentPen();

    CString str;
    CBaseRect rectItem;
    CMidiEventV008 * lpEvent;
    for(int iRow = iFirstRow; iRow <= iLastRow; iRow++)
    {
        lpEvent = &events.ElementAt(iRow);

        GetItemText(str, lpEvent, 0);
        GetItemRect(rectItem, iRow, 0);
        if(iRow == m_iFocused)
        {
            if(m_iPressed == iRow) 
            {
                pDC->FillSolidRect(rectItem, GetSysColor(COLOR_3DHILIGHT));
                pDC->Draw3dRect(rectItem, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));
            }
            else
            {
                CRect rectHover = rectItem;
                rectHover.DeflateRect(0, 0, 1, 1);
                pDC->FillSolidRect(rectItem, GetSysColor(COLOR_3DFACE));
                pDC->Draw3dRect(rectItem, GetSysColor(COLOR_3DFACE), GetSysColor(COLOR_3DDKSHADOW));
                pDC->Draw3dRect(rectHover, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW));
            }
        }
        else
        {
            if(m_iPressed == iRow) 
            {
                pDC->FillSolidRect(rectItem, GetSysColor(COLOR_3DFACE));
                pDC->Draw3dRect(rectItem, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));
            }
            else
            {
                CPen pen(PS_SOLID, 1, GetSysColor(COLOR_3DHILIGHT));
                pDC->FillSolidRect(rectItem, GetSysColor(COLOR_3DFACE));
                pDC->Draw3dRect(rectItem, GetSysColor(COLOR_3DFACE), GetSysColor(COLOR_3DSHADOW));
                pDC->MoveTo(rectItem.TopLeft());
                pDC->SelectObject(&pen);
                pDC->LineTo(rectItem.TopRight());
                pDC->SelectObject(ppenOld);
    //            pDC->FillSolidRect(rectItem, GetSysColor(COLOR_3DFACE));
            }
        }
        pDC->DrawText(str, rectItem, DT_BOTTOM | DT_RIGHT);


        GetItemText(str, lpEvent, 1);
        GetItemRect(rectItem, iRow, 1);
        pDC->DrawText(str, rectItem, DT_BOTTOM | DT_RIGHT);

        GetItemText(str, lpEvent, 2);
        GetItemRect(rectItem, iRow, 2);
        pDC->DrawText(str, rectItem, DT_BOTTOM | DT_LEFT);

        GetItemText(str, lpEvent, 3);
        GetItemRect(rectItem, iRow, 3);
        pDC->DrawText(str, rectItem, DT_BOTTOM | DT_RIGHT);

    }

    //track.m_events();
	// TODO: add draw code here

    pDC->SetViewportOrg(ptOriginalViewportOrg);
    pDC->SetBkMode(iBkModeOld);
    pDC->SelectObject(ppenOld);

}

/////////////////////////////////////////////////////////////////////////////
// CMidiEventsView diagnostics

#ifdef _DEBUG
void CMidiEventsView::AssertValid() const
{
	CView::AssertValid();
}

void CMidiEventsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CXfplayerDoc* CMidiEventsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CXfplayerDoc)));
	return (CXfplayerDoc*)m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMidiEventsView message handlers

int CMidiEventsView::HitTestRow(int iy)
{
    return iy / m_iRowHeight;
}

int CMidiEventsView::GetRowPositionOffset(int iy)
{
    return iy % m_iRowHeight;
}

VMSRESULT CMidiEventsView::GetItemRect(LPRECT lprect, int iRow, int iCol)
{
    if(iCol == -1)
    {
        lprect->left = 0;
        lprect->right = lprect->left + 250;
        lprect->top = m_iRowHeight * iRow;
        lprect->bottom = lprect->top + m_iRowHeight;
    }
    else if(iCol == 0)
    {
        lprect->left = 0;
        lprect->right = lprect->left + 25;
        lprect->top = m_iRowHeight * iRow;
        lprect->bottom = lprect->top + m_iRowHeight;
    }
    else if(iCol == 1)
    {
        lprect->left = 25;
        lprect->right = lprect->left + 50;
        lprect->top = m_iRowHeight * iRow;
        lprect->bottom = lprect->top + m_iRowHeight;
    }
    else if(iCol == 2)
    {
        lprect->left = 75;
        lprect->right = lprect->left + 100;
        lprect->top = m_iRowHeight * iRow;
        lprect->bottom = lprect->top + m_iRowHeight;
    }
    else if(iCol == 3)
    {
        lprect->left = 175;
        lprect->right = lprect->left + 100;
        lprect->top = m_iRowHeight * iRow;
        lprect->bottom = lprect->top + m_iRowHeight;
    }
    return VMSR_SUCCESS;

}

void CMidiEventsView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	CSize sizeTotal, sizePage, sizeLine;
    int nMapMode;
    GetDeviceScrollSizes(nMapMode, sizeTotal, sizePage, sizeLine);
    //ASSERT(nMapMode == MM_TEXT);
    nMapMode = MM_TEXT;
    sizePage.cx = cx;
    sizePage.cy = cy;
    SetScrollSizes(nMapMode, sizeTotal, sizePage, sizeLine);
    CScrollBar * pScrollBar = GetScrollBarCtrl(SB_HORZ);
	// TODO: Add your message handler code here
	
}

void CMidiEventsView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
    CXfplayerDoc* pDoc = GetDocument();
    CMidiSequence * pSeq = pDoc->GetMidiSequence();
    CMidiFile * pFile = pSeq->GetFile();
    pFile->m_tracks.ExpandTrack();
    pFile->ToWorkStorage();

	CSize sizeTotal, sizePage, sizeLine;
    int nMapMode;
    GetDeviceScrollSizes(nMapMode, sizeTotal, sizePage, sizeLine);

    nMapMode = MM_TEXT;
    GetViewSize(&sizeTotal);
    SetScrollSizes(nMapMode, sizeTotal, sizePage, sizeLine);
    
	
}

VMSRESULT CMidiEventsView::GetViewSize(LPSIZE lpsize)
{
    lpsize->cx = 1000;
    CXfplayerDoc* pDoc = GetDocument();
    CMidiSequence * pSeq = pDoc->GetMidiSequence();
    CMidiFile * pFile = pSeq->GetFile();
    if(!pFile->m_tracks.ElementAt(0)->IsKindOf(RUNTIME_CLASS(CMidiTrack)))
        return VMSR_SUCCESS;
    CMidiTrack * pTrack = (CMidiTrack *) pFile->m_tracks.ElementAt(0);
    CMidiTrackV008 & track = pTrack->GetWorkTrack();
    CBaseArray<CMidiEventV008, CMidiEventV008 &> & events = track.m_events;
    CPoint ptScrollPosition = GetScrollPosition();

    lpsize->cy = m_iRowHeight * events.GetSize();
    return VMSR_SUCCESS;
}

VMSRESULT CMidiEventsView::GetItemText(CString &rstr, CMidiEventBase *lpEvent, int iCol)
{
    if(iCol == 0)
    {
        // Event Delta Column
        rstr.Empty();
    }
    if(iCol == 1)
    {
        // Event Delta Column
        rstr.Format("%d", lpEvent->GetDelta());
    }
    else if(iCol == 2)
    {
        // Event Type Column
        BYTE bEvent = lpEvent->GetFullType();
        if (CMidi::Msg > bEvent)
        {
            rstr.LoadString(IDS_MIDIEVENTSVIEW_RUNNINGSTATUS);
        }
        else if(CMidi::SysEx > bEvent)
        {
            BYTE bType = lpEvent->GetType_();
            if(bType == CMidi::NoteOn)
            {
                rstr.LoadString(IDS_MIDIEVENTSVIEW_NOTEON);
            }
            else if (bType == CMidi::NoteOff)
            {
                rstr.LoadString(IDS_MIDIEVENTSVIEW_NOTEOFF);
            }
            else if(bType == CMidi::ControlChange)
            {
                BYTE bCCType  = lpEvent->GetChB1();
                if(bCCType == CMidi::CCSostenuto)
                {
                    rstr.LoadString(IDS_MIDIEVENTSVIEW_SOSTENUTO);
                }
                else
                {
                    rstr.Empty();
                }
            }
            else if(bType == CMidi::ProgramChange)
            {
                BYTE bPC  = lpEvent->GetChB1();
                rstr.LoadString(CMidi::voiceText[bPC]);
            }
            else
            {
                rstr.Empty();
            }

        }
        else if(CMidi::Meta == bEvent)
        {
            rstr.LoadString(IDS_MIDIEVENTSVIEW_META);
        }
        else if (CMidi::SysEx == bEvent)
        {
            rstr.LoadString(IDS_MIDIEVENTSVIEW_SYSEX);
        }
        else if (CMidi::SysExEnd == bEvent)
        {
            rstr.LoadString(IDS_MIDIEVENTSVIEW_SYSEXEND);
        }
        else
        {
            rstr.Empty();
        }
    }
    else if(iCol == 3)
    {
        BYTE bEvent = lpEvent->GetFullType();
        if (CMidi::Msg > bEvent)
        {
            rstr.Format("%d", bEvent);
        }
        else if(CMidi::SysEx > bEvent)
        {
            BYTE bTrack = lpEvent->GetTrack();
            rstr.Format("%d", bTrack);
        }
        else
        {
            rstr.Empty();
        }

    }
    else
    {
        rstr.Empty();
    }
    return VMSR_SUCCESS;

}

void CMidiEventsView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
    CPoint ptScrollPosition = GetScrollPosition();
    int iRow = HitTestRow(point.y + ptScrollPosition.y);
    //int iCol = HitTestColumn(point.x ,point.y + ptScrollPosition.y);
    if(iRow != m_iFocused)
    {
        int iFocused = iRow;
        int iOldFocused = m_iFocused;
        m_iFocused = iFocused;
    
        CRect rectUpdate;
        CPoint ptScroll = GetScrollPosition();
        
        if(iOldFocused >= 0)
        {
  //          HideEditWindows();
            GetItemRect(rectUpdate, iOldFocused, -1);
            rectUpdate -= ptScrollPosition;
            RedrawWindow(rectUpdate, NULL);
        }
    
        CWnd * pWndCapture = GetCapture();
        CRect rectClient;
        GetClientRect(rectClient);
        if(iFocused < 0 || !rectClient.PtInRect(point))
        {
            if(pWndCapture != NULL && pWndCapture->m_hWnd == m_hWnd)
            ReleaseCapture();
            if(m_iPressed >= 0)
            {
                int iPressed = m_iPressed;
//                m_iPressed = -1;
                GetItemRect(rectUpdate,  iPressed, -1);
                rectUpdate -= ptScrollPosition;
                RedrawWindow(rectUpdate, NULL);
//                
            }
        }
        else
        {
        
            if(pWndCapture == NULL || pWndCapture->m_hWnd != m_hWnd)
                SetCapture();
            GetItemRect(rectUpdate,  iFocused, -1);
            rectUpdate -= ptScrollPosition;
            RedrawWindow(rectUpdate, NULL);
            //ShowEditWindow(iRow);
        }
    }	
	CView::OnMouseMove(nFlags, point);
}

int CMidiEventsView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
    m_pNoteEdit->Create(IDD_MIDIEVENTS_NOTEEDIT, this);
	// TODO: Add your specialized creation code here
	
	return 0;
}

VMSRESULT CMidiEventsView::HideEditWindows()
{
    if(m_pNoteEdit->IsWindowVisible())
    {
        m_pNoteEdit->ShowWindow(SW_HIDE);
    }
    return VMSR_SUCCESS;
}

VMSRESULT CMidiEventsView::ShowEditWindow(int iRow)
{
    CXfplayerDoc* pDoc = GetDocument();
    CMidiSequence * pSeq = pDoc->GetMidiSequence();
    CMidiFile * pFile = pSeq->GetFile();
    //pFile->ToWorkStorage();
    if(!pFile->m_tracks.ElementAt(0)->IsKindOf(RUNTIME_CLASS(CMidiTrack)))
        return VMSR_SUCCESS;
    CMidiTrack * pTrack = (CMidiTrack *) pFile->m_tracks.ElementAt(0);
    CMidiTrackV008 & track = pTrack->GetWorkTrack();
    CBaseArray<CMidiEventV008, CMidiEventV008 &> & events = track.m_events;
    CMidiEventV008 & event = events.ElementAt(iRow);

    CRect rectItem;
    GetItemRect(rectItem, iRow, 1);
    if(event.GetType_() == CMidi::NoteOn ||
        event.GetType_() == CMidi::NoteOff)
    {
        ReleaseCapture();
        CPoint ptScrollPosition = GetScrollPosition();
        m_pNoteEdit->FromEvent(&event);
        m_pNoteEdit->SetWindowPos(
            &wndTop,
            rectItem.left - ptScrollPosition.x,
            rectItem.top - ptScrollPosition.y,
            0, 0, SWP_NOSIZE | SWP_SHOWWINDOW); 
    }
    return VMSR_SUCCESS;
}

void CMidiEventsView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
    CPoint ptScroll = GetScrollPosition();
    int iColumn = HitTestColumn(point.x + ptScroll.x, point.y + ptScroll.y);
//    CWnd * pWndCapture = GetCapture();
    if(iColumn == 0)
    {
//        if(pWndCapture == NULL || pWndCapture->m_hWnd != m_hWnd)
//            SetCapture();
        int iRow = HitTestRow(point.y + ptScroll.y);
        int iPressedOld = m_iPressed;
        if(m_iPressed == iRow)
            m_iPressed = -1;
        else
            m_iPressed = iRow;
        CPoint ptScroll = GetScrollPosition();
        if(iPressedOld >= 0)
        {
            CRect rectUpdate;
            HitTestRow(point.y + ptScroll.y);
            GetItemRect(rectUpdate, iPressedOld, 0);
            rectUpdate -= ptScroll;
            RedrawWindow(rectUpdate, NULL);

            HideEditWindows();
        }
        if(m_iPressed >= 0)
        {
        
            CRect rectUpdate;
            HitTestRow(point.y + ptScroll.y);
            GetItemRect(rectUpdate, iRow, 0);
            rectUpdate -= ptScroll;
            RedrawWindow(rectUpdate, NULL);

            ShowEditWindow(iRow);
        }
    }
    else
    {
        HideEditWindows();
    }
	CView::OnLButtonDown(nFlags, point);
}

void CMidiEventsView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
    CPoint ptScroll = GetScrollPosition();
    int iColumn = HitTestColumn(point.x + ptScroll.x, point.y + ptScroll.y);
//    CWnd * pWndCapture = GetCapture();
/*    if(m_bPressed)
    {
	    m_bPressed = false;

        int iRow = HitTestRow(point.y + ptScroll.y);
        CRect rectUpdate;
        CPoint ptScroll = GetScrollPosition();
        HitTestRow(point.y + ptScroll.y);
        GetItemRect(rectUpdate, iRow, 0);
        rectUpdate -= ptScroll;
        RedrawWindow(rectUpdate, NULL);
    }*/
	CView::OnLButtonUp(nFlags, point);
}

int CMidiEventsView::HitTestColumn(int ix, int iy)
{
    int iRow = HitTestRow(iy);

    if(iRow < 0)
        return -1;

    CXfplayerDoc* pDoc = GetDocument();
    CMidiSequence * pSeq = pDoc->GetMidiSequence();
    CMidiFile * pFile = pSeq->GetFile();
    //pFile->ToWorkStorage();
    if(!pFile->m_tracks.ElementAt(0)->IsKindOf(RUNTIME_CLASS(CMidiTrack)))
        return -1;
    CMidiTrack * pTrack = (CMidiTrack *) pFile->m_tracks.ElementAt(0);
    CMidiTrackV008 & track = pTrack->GetWorkTrack();
    CBaseArray<CMidiEventV008, CMidiEventV008 &> & events = track.m_events;
    CMidiEventV008 & event = events.ElementAt(iRow);

    CRect rectItem;
    GetItemRect(rectItem, iRow, 0);
    if(rectItem.PtInRect(CPoint(ix, iy)))
    {
        return 0;
    }
    return -1;

}

afx_msg LRESULT CMidiEventsView::OnUserMessage(WPARAM wParam, LPARAM lParam)
{
    if(lParam == 0)
    {
        if(m_iPressed >= 0)
        {
            CRect rectUpdate;
            CPoint ptScroll = GetScrollPosition();
            int iPressed = m_iPressed;
            m_iPressed = -1;
            GetItemRect(rectUpdate,  iPressed, -1);
            rectUpdate -= ptScroll;
            RedrawWindow(rectUpdate, NULL);
    
        }
    }
    return 0;
}

void CMidiEventsView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
    m_ptScroll.x = -(long)nPos;
    RedrawWindow();

	CView::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CMidiEventsView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
    m_ptScroll.y = -(long)nPos;
    RedrawWindow();
	CView::OnVScroll(nSBCode, nPos, pScrollBar);
}
