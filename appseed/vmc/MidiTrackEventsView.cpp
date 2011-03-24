// MidiEventsView.cpp : implementation file
//


#include "stdafx.h"
#include "resource.h"
#include "MidiTrackEventsView.h"

#include "MidiDoc.h"
#include "MidiEventsNoteEdit.h"


CMidiTrackEventsView::CMidiTrackEventsView(::ca::application * papp) :
   ::ca::ca(papp),
   Ex1VirtualGuieInterface(papp),
   BaseVirtualGuie(papp),
   Ex1ScrollViewInterface(papp),
   BaseScrollView(papp)
{
    m_iRowHeight = 20;
    m_pNoteEdit = new CMidiEventsNoteEdit();
    m_iPressed = -1;
}

CMidiTrackEventsView::~CMidiTrackEventsView()
{
    if(m_pNoteEdit != NULL)
    {
        delete m_pNoteEdit;
    }
}

/*
BEGIN_MESSAGE_MAP(CMidiTrackEventsView, BaseView)
	//{{AFX_MSG_MAP(CMidiTrackEventsView)
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
*/

/////////////////////////////////////////////////////////////////////////////
// CMidiTrackEventsView drawing

void CMidiTrackEventsView::OnInitialUpdate()
{
	BaseScrollView::OnInitialUpdate();

//    CVMSApp * pApp = (CVMSApp *) AfxGetApp();

//    SetFont(pApp->GetStandartFont());
//	class size sizeTotal;
//	// TODO: calculate the total size of this view
//	sizeTotal.cx = sizeTotal.cy = 100;
//	SetScrollSizes(MM_TEXT, sizeTotal);

/*   	class size sizeTotal, sizePage, sizeLine;
    int nMapMode;
    GetDeviceScrollSizes(nMapMode, sizeTotal, sizePage, sizeLine);
    ASSERT(nMapMode == MM_TEXT);
    GetViewSize(&sizeTotal);
    SetScrollSizes(nMapMode, sizeTotal, sizePage, sizeLine); */

}

void CMidiTrackEventsView::OnDraw(CDC* pDC)
{
	CMidiDoc* pDoc = GetDocument();
    MidiSequence * pSeq = &pDoc->HelperGetMidiSequence();
//    if(pDoc->IsSaving())
  //      return;
    MidiFile * pFile = &pSeq->GetFile();
    //pFile->ToWorkStorage();
    if(!pFile->GetTracks().TrackAt(m_iTrackIndex)->IsType(MidiTrackBase::TypeMidi))
        return;
    MidiTrack * pTrack = (MidiTrack *) pFile->GetTracks().TrackAt(m_iTrackIndex);
    MidiTrackV008 & track = pTrack->GetWorkTrack();
    //class point ptScrollPosition = GetScrollPosition();
    
    class rect rectClipBox;
    pDC->GetClipBox(rectClipBox);
    if(rectClipBox.IsRectNull())
        return;


//    class point ptOriginalViewportOrg = pDC->GetViewportOrg();
//    pDC->SetViewportOrg(m_ptScroll);

    //int iFirstRow = HitTestRow(ptScrollPosition.y);
    int iFirstRow = HitTestRow(rectClipBox.top);
//    int iFirstRowOffset = GetRowPositionOffset(ptScrollPosition.y);

    class size sizeTotal, sizePage, sizeLine;
    int nMapMode;
    GetDeviceScrollSizes(nMapMode, sizeTotal, sizePage, sizeLine);
    ASSERT(nMapMode == MM_TEXT);

    //int iLastRow = HitTestRow(ptScrollPosition.y + sizePage.cy);
    int iLastRow = HitTestRow(rectClipBox.bottom);
//    int iLastRowOffset = GetRowPositionOffset(ptScrollPosition.y + sizePage.cy);

    if(iLastRow >= track.GetEventCount())
    {
        iLastRow = track.GetEventCount() - 1;
    }
    //CVMSApp * pApp = (CVMSApp *) AfxGetApp();

    CFont * pfont  = FontCentral::AppGetFontCentral()->GetStandartFont();

    int iBkModeOld = pDC->GetBkMode();
    CPen * ppenOld = pDC->GetCurrentPen();
    CFont * pfontOld = pDC->GetCurrentFont();

    pDC->SetBkMode(TRANSPARENT);
    pDC->SelectObject(pfont);

    string str;
    BaseRect rectItem;
    BaseRect rectItemSel;
    BaseRect rectItem1;
    MidiEventV008 * lpEvent;
    for(int iRow = iFirstRow; iRow <= iLastRow; iRow++)
    {
        lpEvent = &track.EventAt(iRow);

        GetItemText(str, lpEvent, 0);
        GetItemRect(rectItem, iRow, 0);
        GetItemRect(rectItem1, iRow, 1);
        GetItemRect(rectItemSel, iRow, -1);
        rectItemSel.TopLeft() = rectItem1.TopLeft();
        
        if(iRow == m_iFocused)
        {
            if(m_iPressed == iRow) 
            {
                pDC->FillSolidRect(rectItem, GetSysColor(COLOR_3DHILIGHT));
                pDC->Draw3dRect(rectItem, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));
                
                pDC->FillSolidRect(rectItemSel, GetSysColor(COLOR_HIGHLIGHT));
            }
            else
            {
                class rect rectHover = rectItem;
                rectHover.DeflateRect(0, 0, 1, 1);
                pDC->FillSolidRect(rectItem, GetSysColor(COLOR_3DFACE));
                pDC->Draw3dRect(rectItem, GetSysColor(COLOR_3DFACE), GetSysColor(COLOR_3DDKSHADOW));
                pDC->Draw3dRect(rectHover, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW));
                
                pDC->FillSolidRect(rectItemSel, GetSysColor(COLOR_HIGHLIGHT));
            }
        }
        else
        {
            if(m_iPressed == iRow) 
            {
                pDC->FillSolidRect(rectItem, GetSysColor(COLOR_3DFACE));
                pDC->Draw3dRect(rectItem, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));
                
                pDC->FillSolidRect(rectItemSel, GetSysColor(COLOR_WINDOW));

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
                
                pDC->FillSolidRect(rectItemSel, GetSysColor(COLOR_WINDOW));
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
        pDC->DrawText(str, rectItem, DT_BOTTOM | DT_LEFT);

        GetItemText(str, lpEvent, 4);
        GetItemRect(rectItem, iRow, 4);
        pDC->DrawText(str, rectItem, DT_BOTTOM | DT_LEFT);
    }

    //track.m_events();
	// TODO: add draw code here

//    pDC->SetViewportOrg(ptOriginalViewportOrg);
    pDC->SetBkMode(iBkModeOld);
    pDC->SelectObject(ppenOld);
    pDC->SelectObject(pfontOld);

}

/////////////////////////////////////////////////////////////////////////////
// CMidiTrackEventsView diagnostics

#ifdef _DEBUG
void CMidiTrackEventsView::AssertValid() const
{
	BaseScrollView::AssertValid();
}

void CMidiTrackEventsView::Dump(CDumpContext& dc) const
{
	BaseScrollView::Dump(dc);
}

CMidiDoc* CMidiTrackEventsView::GetDocument() // non-debug version is inline
{
   ASSERT(base < CMidiDoc > ::bases(m_pDocument));
	return (CMidiDoc*)m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMidiTrackEventsView message handlers

int CMidiTrackEventsView::HitTestRow(int iy)
{
    return iy / m_iRowHeight;
}

int CMidiTrackEventsView::GetRowPositionOffset(int iy)
{
    return iy % m_iRowHeight;
}

VMSRESULT CMidiTrackEventsView::GetItemRect(LPRECT lprect, int iRow, int iCol)
{
    if(iCol == -1)
    {
        lprect->left = 0;
        lprect->right = lprect->left + 350;
        lprect->top = m_iRowHeight * iRow;
        lprect->bottom = lprect->top + m_iRowHeight;
    }
    else if(iCol == 0)
    {
        lprect->left = 0;
        lprect->right = lprect->left + 20;
        lprect->top = m_iRowHeight * iRow;
        lprect->bottom = lprect->top + m_iRowHeight;
    }
    else if(iCol == 1)
    {
        lprect->left = 25;
        lprect->right = lprect->left + 45;
        lprect->top = m_iRowHeight * iRow;
        lprect->bottom = lprect->top + m_iRowHeight;
    }
    else if(iCol == 2)
    {
        lprect->left = 75;
        lprect->right = lprect->left + 95;
        lprect->top = m_iRowHeight * iRow;
        lprect->bottom = lprect->top + m_iRowHeight;
    }
    else if(iCol == 3)
    {
        lprect->left = 175;
        lprect->right = lprect->left + 95;
        lprect->top = m_iRowHeight * iRow;
        lprect->bottom = lprect->top + m_iRowHeight;
    }
    else if(iCol == 4)
    {
        lprect->left = 275;
        lprect->right = lprect->left + 95;
        lprect->top = m_iRowHeight * iRow;
        lprect->bottom = lprect->top + m_iRowHeight;
    }
    return VMSR_SUCCESS;

}

void CMidiTrackEventsView::OnSize(UINT nType, int cx, int cy) 
{
	BaseScrollView::OnSize(nType, cx, cy);
	class size sizeTotal, sizePage, sizeLine;
    int nMapMode;
    GetDeviceScrollSizes(nMapMode, sizeTotal, sizePage, sizeLine);
    //ASSERT(nMapMode == MM_TEXT);
    nMapMode = MM_TEXT;
    sizePage.cx = cx;
    sizePage.cy = cy;
    sizeLine.cx = cx / 10;
    sizeLine.cy = m_iRowHeight;
    SetScrollSizes(nMapMode, sizeTotal, sizePage, sizeLine);
    CScrollBar * pScrollBar = GetScrollBarCtrl(SB_HORZ);
	// TODO: Add your message handler code here
	
}

void CMidiTrackEventsView::OnUpdate(BaseView* pSender, LPARAM lHint, base_object* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class

	class size sizeTotal, sizePage, sizeLine;
    int nMapMode;
    GetDeviceScrollSizes(nMapMode, sizeTotal, sizePage, sizeLine);

    nMapMode = MM_TEXT;
    GetViewSize(&sizeTotal);
    SetScrollSizes(nMapMode, sizeTotal, sizePage, sizeLine);
    
	
}

VMSRESULT CMidiTrackEventsView::GetViewSize(LPSIZE lpsize)
{
    lpsize->cx = 1000;
    CMidiDoc* pDoc = GetDocument();
    MidiSequence * pSeq = &pDoc->HelperGetMidiSequence();
    MidiFile * pFile = &pSeq->GetFile();
    if(!pFile->GetTracks().TrackAt(m_iTrackIndex)->IsType(MidiTrackBase::TypeMidi))
        return VMSR_SUCCESS;
    MidiTrack * pTrack = (MidiTrack *) pFile->GetTracks().TrackAt(m_iTrackIndex);
    MidiTrackV008 & track = pTrack->GetWorkTrack();
    class point ptScrollPosition = GetScrollPosition();

    lpsize->cy = m_iRowHeight * track.GetEventCount();
    return VMSR_SUCCESS;
}

VMSRESULT CMidiTrackEventsView::GetItemText(string &rstr, MidiEventBase *lpEvent, int iCol)
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
        if (Midi::Msg > bEvent)
        {
            rstr.LoadString(IDS_MIDIEVENTSVIEW_RUNNINGSTATUS);
        }
        else if(Midi::SysEx > bEvent)
        {
            BYTE bType = lpEvent->GetType();
            if(bType == Midi::NoteOn)
            {
                //rstr.LoadString(IDS_MIDIEVENTSVIEW_NOTEON);
                rstr.LoadString(IDS_MIDI_NOTEON);
            }
            else if (bType == Midi::NoteOff)
            {
                //rstr.LoadString(IDS_MIDIEVENTSVIEW_NOTEOFF);
                rstr.LoadString(IDS_MIDI_NOTEOFF);
            }
            else if(bType == Midi::ControlChange)
            {
                rstr.LoadString(IDS_MIDI_CONTROLCHANGE);
            }
            else if(bType == Midi::ProgramChange)
            {
                BYTE bPC  = lpEvent->GetChB1();
                rstr.LoadString(Midi::voiceText[bPC]);
            }
            else
            {
                rstr.Empty();
            }

        }
        else if(Midi::Meta == bEvent)
        {
            rstr.LoadString(IDS_MIDIEVENTSVIEW_META);
        }
        else if (Midi::SysEx == bEvent)
        {
            rstr.LoadString(IDS_MIDIEVENTSVIEW_SYSEX);
        }
        else if (Midi::SysExEnd == bEvent)
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
        BYTE bType = lpEvent->GetType();
        BYTE bEvent = lpEvent->GetFullType();
        if (Midi::Msg > bEvent)
        {
            rstr.Format("%d", bEvent);
        }
        else if(Midi::SysEx > bEvent)
        {
//            BYTE bTrack = lpEvent->GetTrack();
//            rstr.Format("%d", bTrack);
            BYTE bType = lpEvent->GetType();
            if(bType == Midi::NoteOn)
            {
                BYTE bNote = lpEvent->GetNotePitch();
                rstr = Midi::pitchText[bNote];
            }
            else if (bType == Midi::NoteOff)
            {
                BYTE bNote = lpEvent->GetNotePitch();
                rstr = Midi::pitchText[bNote];
            }
            else if(bType == Midi::ControlChange)
            {
                BYTE bCCType  = lpEvent->GetChB1();
                if(bCCType == Midi::ControlChangeSostenuto)
                {
                    rstr.LoadString(IDS_MIDIEVENTSVIEW_SOSTENUTO);
                }
                else if(bCCType == Midi::ControlChangeExpressionController)
                {
                    rstr.LoadString(IDS_MIDI_EXPRESSIONCONTROLLER);
                }
                else
                {
                    rstr.Format("%d", bCCType);
                }
            }
        }
        else
        {
            rstr.Empty();
        }

    }
    else if(iCol == 4)
    {
        BYTE bEvent = lpEvent->GetFullType();
        if (Midi::Msg > bEvent)
        {
            rstr.Format("%d", bEvent);
        }
        else if(Midi::SysEx > bEvent)
        {
//            BYTE bTrack = lpEvent->GetTrack();
//            rstr.Format("%d", bTrack);
            BYTE bType = lpEvent->GetType();
            if(bType == Midi::NoteOn)
            {
                BYTE bVelocity = lpEvent->GetNoteVelocity();
                rstr.Format(IDS_MIDI_VELOCITY_F001, bVelocity);
            }
            else if (bType == Midi::NoteOff)
            {
                BYTE bVelocity = lpEvent->GetNoteVelocity();
                rstr.Format(IDS_MIDI_VELOCITY_F001, bVelocity);
            }
            else if(bType == Midi::ControlChange)
            {
                BYTE bValue = lpEvent->GetChB2();
                rstr.Format(IDS_MIDI_CONTROLLERVALUE_F001, bValue);
            }

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

void CMidiTrackEventsView::OnMouseMove(UINT nFlags, class point point) 
{
	// TODO: Add your message handler code here and/or call default
    class point ptScrollPosition = GetScrollPosition();
    int iRow = HitTestRow(point.y + ptScrollPosition.y);
    //int iCol = HitTestColumn(point.x ,point.y + ptScrollPosition.y);
    if(iRow != m_iFocused)
    {
        int iFocused = iRow;
        int iOldFocused = m_iFocused;
        m_iFocused = iFocused;
    
        class rect rectUpdate;
        class point ptScroll = GetScrollPosition();
        
        if(iOldFocused >= 0)
        {
  //          HideEditWindows();
            GetItemRect(rectUpdate, iOldFocused, -1);
            rectUpdate -= ptScrollPosition;
            RedrawWindow(rectUpdate, NULL);
        }
    
        base_wnd * pWndCapture = GetCapture();
        class rect rectClient;
        base_wnd::GetClientRect(rectClient);
        base_wnd * pwndFromPoint = ChildWindowFromPoint(point);
        //if(iFocused < 0 || !rectClient.PtInRect(point))
        if(iFocused < 0 || pwndFromPoint == NULL ||
            pwndFromPoint != this)
        {
            if(pWndCapture != NULL && pWndCapture->get_handle() == get_handle())
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
        
            if(pWndCapture == NULL || pWndCapture->get_handle() != get_handle())
                SetCapture();
            GetItemRect(rectUpdate,  iFocused, -1);
            rectUpdate -= ptScrollPosition;
            RedrawWindow(rectUpdate, NULL);
            //ShowEditWindow(iRow);
        }
    }	
	BaseScrollView::OnMouseMove(nFlags, point);
}

int CMidiTrackEventsView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (BaseScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
    m_pNoteEdit->Create(IDD_MIDI_EVENTS_NOTE_EDIT, this);
	// TODO: Add your specialized creation code here
    SetFont(base_wnd::GetParent()->GetFont());
	return 0;
}

VMSRESULT CMidiTrackEventsView::HideEditWindows()
{
    if(m_pNoteEdit->IsWindowVisible())
    {
        m_pNoteEdit->ShowWindow(SW_HIDE);
    }
    return VMSR_SUCCESS;
}

VMSRESULT CMidiTrackEventsView::ShowEditWindow(int iRow)
{
    CMidiDoc* pDoc = GetDocument();
    MidiSequence * pSeq = &pDoc->HelperGetMidiSequence();
    MidiFile * pFile = &pSeq->GetFile();
    //pFile->ToWorkStorage();
    if(!pFile->GetTracks().TrackAt(m_iTrackIndex)->IsType(MidiTrackBase::TypeMidi))
        return VMSR_SUCCESS;
    MidiTrack * pTrack = (MidiTrack *) pFile->GetTracks().TrackAt(m_iTrackIndex);
    MidiTrackV008 & track = pTrack->GetWorkTrack();
    MidiEventV008 * lpevent = &track.EventAt(iRow);

    class rect rectItem;
    GetItemRect(rectItem, iRow, 1);
    if(lpevent->GetType_() == Midi::NoteOn ||
        lpevent->GetType_() == Midi::NoteOff)
    {
        ReleaseCapture();
        class point ptScrollPosition = GetScrollPosition();
        m_pNoteEdit->FromEvent(lpevent, iRow);
        m_pNoteEdit->SetWindowPos(
            &wndTop,
            rectItem.left - ptScrollPosition.x,
            rectItem.top - ptScrollPosition.y,
            0, 0, SWP_NOSIZE | SWP_SHOWWINDOW); 
    }
    return VMSR_SUCCESS;
}

void CMidiTrackEventsView::OnLButtonDown(UINT nFlags, class point point) 
{
	// TODO: Add your message handler code here and/or call default
    class point ptScroll = GetScrollPosition();
    int iColumn = HitTestColumn(point.x + ptScroll.x, point.y + ptScroll.y);
//    base_wnd * pWndCapture = GetCapture();
    if(iColumn >= 0)
    {
//        if(pWndCapture == NULL || pWndCapture->get_handle() != get_handle())
//            SetCapture();
        int iRow = HitTestRow(point.y + ptScroll.y);
        int iPressedOld = m_iPressed;
        if(m_iPressed == iRow)
            m_iPressed = -1;
        else
            m_iPressed = iRow;
        class point ptScroll = GetScrollPosition();
        if(iPressedOld >= 0)
        {
            class rect rectUpdate;
            HitTestRow(point.y + ptScroll.y);
            GetItemRect(rectUpdate, iPressedOld, 0);
            rectUpdate -= ptScroll;
            RedrawWindow(rectUpdate, NULL);

            HideEditWindows();
        }
        if(m_iPressed >= 0)
        {
        
            class rect rectUpdate;
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
	BaseScrollView::OnLButtonDown(nFlags, point);
}

void CMidiTrackEventsView::OnLButtonUp(UINT nFlags, class point point) 
{
	// TODO: Add your message handler code here and/or call default
    class point ptScroll = GetScrollPosition();
    int iColumn = HitTestColumn(point.x + ptScroll.x, point.y + ptScroll.y);
//    base_wnd * pWndCapture = GetCapture();
/*    if(m_bPressed)
    {
	    m_bPressed = false;

        int iRow = HitTestRow(point.y + ptScroll.y);
        class rect rectUpdate;
        class point ptScroll = GetScrollPosition();
        HitTestRow(point.y + ptScroll.y);
        GetItemRect(rectUpdate, iRow, 0);
        rectUpdate -= ptScroll;
        RedrawWindow(rectUpdate, NULL);
    }*/
	BaseScrollView::OnLButtonUp(nFlags, point);
}

int CMidiTrackEventsView::HitTestColumn(int ix, int iy)
{
    int iRow = HitTestRow(iy);

    if(iRow < 0)
        return -1;

    CMidiDoc* pDoc = GetDocument();
    MidiSequence * pSeq = &pDoc->HelperGetMidiSequence();
    MidiFile * pFile = &pSeq->GetFile();
    //pFile->ToWorkStorage();
    if(!pFile->GetTracks().TrackAt(m_iTrackIndex)->IsType(MidiTrackBase::TypeMidi))
        return -1;
    MidiTrack * pTrack = (MidiTrack *) pFile->GetTracks().TrackAt(m_iTrackIndex);
    MidiTrackV008 & track = pTrack->GetWorkTrack();
    MidiEventV008 & event = track.EventAt(iRow);

    class rect rectItem;
    GetItemRect(rectItem, iRow, 0);
    if(rectItem.PtInRect(class point(ix, iy)))
    {
        return 0;
    }
    GetItemRect(rectItem, iRow, 1);
    if(rectItem.PtInRect(class point(ix, iy)))
    {
        return 1;
    }
    GetItemRect(rectItem, iRow, 2);
    if(rectItem.PtInRect(class point(ix, iy)))
    {
        return 2;
    }
    GetItemRect(rectItem, iRow, 3);
    if(rectItem.PtInRect(class point(ix, iy)))
    {
        return 3;
    }
    return -1;

}

afx_msg LRESULT CMidiTrackEventsView::OnUserMessage(WPARAM wParam, LPARAM lParam)
{
    if(lParam == 0)
    {
        if(m_iPressed >= 0)
        {
            class rect rectUpdate;
            class point ptScroll = GetScrollPosition();
            int iPressed = m_iPressed;
            m_iPressed = -1;
            GetItemRect(rectUpdate,  iPressed, -1);
            rectUpdate -= ptScroll;
            RedrawWindow(rectUpdate, NULL);
    
        }
    }
    else if(lParam == 1)
    {
        int iRow = wParam;
        CMidiDoc* pDoc = GetDocument();
        MidiSequence * pSeq = &pDoc->HelperGetMidiSequence();
        MidiFile * pFile = &pSeq->GetFile();
        //pFile->ToWorkStorage();
        if(!pFile->GetTracks().TrackAt(m_iTrackIndex)->IsType(MidiTrackBase::TypeMidi))
            return -1;
        MidiTrack * pTrack = (MidiTrack *) pFile->GetTracks().TrackAt(m_iTrackIndex);
        MidiTrackV008 & track = pTrack->GetWorkTrack();
        track.EventAt(iRow) = *m_pNoteEdit->m_pevent;
        GetDocument()->SetModifiedFlag();
    }
    return 0;
}

void CMidiTrackEventsView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
//    m_ptScroll.x = -(long)nPos;
  //  RedrawWindow();

	BaseScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CMidiTrackEventsView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
//    m_ptScroll.y = -(long)nPos;
  //  RedrawWindow();
	BaseScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
}
