// PlaylistInPlaceWnd.cpp : implementation file
//

#include "stdafx.h"
//#include "VMSApp.h"
#include "FontCentral.h"
#include "KaraokeMainFrame.h"

#include "Savings.h"

#include "MainFrame.h"
#include "KaraokeSDIFrame.h"



#include "PlaylistFrame.h"
#include "PlaylistView.h"

#include "XfplayerView.h"

#include "BaseRect.h"
#include "Imaging.h"

#include "ScrollBarV009.h"
#include "ButtonV007.h"

#include "WndMovingManager.h"
#include "WndSizingManagerV033.h"
#include "WndSysMenuManagerV033.h"





#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKaraokeMainFrame

IMPLEMENT_DYNCREATE(CKaraokeMainFrame, CFrameWnd)


CKaraokeMainFrame::CKaraokeMainFrame()
:CFrameWnd(),
    m_brushControlBoxBack(GetSysColor(COLOR_BTNFACE)),
    m_brushControlBoxBackSel(GetSysColor(COLOR_WINDOW)),
    m_brushControlBoxBackFocus(RGB(0, 255, 255)),
    m_brushControlBoxBackDisabled(GetSysColor(COLOR_BTNFACE)),
    m_penControlBoxBack(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE)),
    m_penControlBoxBackSel(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE)),
    m_penControlBoxBackFocus(PS_SOLID, 1, RGB(0, 255, 255)),
    m_penControlBoxBackDisabled(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE)),
    m_penText1(PS_SOLID, 1, GetSysColor(COLOR_BTNTEXT)),
    m_penFace1(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE)),
    m_penHilight1(PS_SOLID, 1, GetSysColor(COLOR_BTNHILIGHT)), 
    m_penShadow1(PS_SOLID, 1, GetSysColor(COLOR_BTNSHADOW)),
    m_penDkShadow1(PS_SOLID, 1, GetSysColor(COLOR_3DDKSHADOW)),
    minSize(144, 48)   
{
    m_crMoveableBorderHilight   = RGB(138, 190, 245);
    m_crMoveableBorder          = RGB( 78, 130, 225);
    m_crMoveableBorderShadow    = RGB( 58, 110, 175);
    m_crMoveableBorderDkShadow  = RGB( 18,  50, 105);
    m_iMargin = 7;
    m_iButtonMargin = 2;
    m_crControlBoxFore = GetSysColor(COLOR_BTNTEXT);
    m_crControlBoxForeSel = GetSysColor(COLOR_BTNTEXT);
    m_crControlBoxForeFocus = GetSysColor(COLOR_BTNTEXT);
    m_crControlBoxForeDisabled = GetSysColor(COLOR_GRAYTEXT);
    m_rgnChildren.CreateRectRgn(0, 0, 0, 0);
    
    m_pwmm = new CWndMovingManager();
    m_pwmm->SetSWPFlags(SWP_SHOWWINDOW);
    m_pwsm = new CWndSizingManagerV033();
    m_pwsm->SetSWPFlags(SWP_SHOWWINDOW);
    m_pwsmm = new CWndSysMenuManagerV033;
    
    m_pbuttonClose = new CButtonV007();
    m_pbuttonUp = new CButtonV007();
    m_pbuttonDown = new CButtonV007();
    m_pbuttonMinimize = new CButtonV007();
    m_pbuttonMaximize = new CButtonV007();
    m_pbuttonRestore = new CButtonV007();
//    m_pScrollHorizontal = new CScrollBarV009();   
  //  m_pScrollVertical = new CScrollBarV009();   
//    m_rectWindow.SetRect(0, 0, 0, 0);
//    m_iMode = ModeNormal;
//    CRuntimeClass * prtclass = RUNTIME_CLASS(CKaraokeSDIFrame);
  //  CObject * pobject = prtclass->CreateObject();
    //ASSERT(pobject->IsKindOf(RUNTIME_CLASS(CKaraokeSDIFrame)));
    //m_pMainWnd = (CKaraokeSDIFrame*) pobject;
    m_bFullScreen = false;
}

CKaraokeMainFrame::~CKaraokeMainFrame()
{
    if(m_pwmm != NULL)
        delete m_pwmm;
    if(m_pwsm != NULL)
        delete m_pwsm;
    if(m_pwsmm != NULL)
        delete m_pwsmm;
    if(m_pbuttonClose != NULL)
        delete m_pbuttonClose;
    if(m_pbuttonUp != NULL)
        delete m_pbuttonUp;
    if(m_pbuttonDown != NULL)
        delete m_pbuttonDown;
    if(m_pbuttonMinimize != NULL)
        delete m_pbuttonMinimize;
    if(m_pbuttonMaximize != NULL)
        delete m_pbuttonMaximize;
    if(m_pbuttonRestore != NULL)
        delete m_pbuttonRestore;
//    if(m_pScrollHorizontal != NULL)
  //      delete m_pScrollHorizontal;
    //if(m_pScrollVertical != NULL)
      //  delete m_pScrollVertical;
}

//void CKaraokeMainFrame::operator delete(void *it)
//{
//    it->~CKaraokeMainFrame();
//    free(it);
//    
//}

BEGIN_MESSAGE_MAP(CKaraokeMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CKaraokeMainFrame)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_COMMAND(ID_CLOSE, OnIdClose)
	ON_COMMAND(ID_UP, OnUp)
	ON_COMMAND(ID_DOWN, OnDown)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_WINDOW_MINIMIZE, OnMinimize)
	ON_COMMAND(ID_WINDOW_MAXIMIZE, OnMaximize)
	ON_COMMAND(ID_WINDOW_RESTORE, OnRestore)
	ON_COMMAND(ID_REMOVE_SONG, OnRemoveSong)
	ON_WM_SHOWWINDOW()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
    ON_MESSAGE(VMSM_ECONOMODECHANGE, OnEconoModeChange)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CKaraokeMainFrame message handlers

void CKaraokeMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	//CFrameWnd::OnSize(nType, cx, cy);

    
    CWnd::OnSize(nType, cx, cy);

    CRect rectClient;
    GetClientRect(rectClient);

    if(m_bFullScreen)
    {
    }
    else if(IsZoomed())
    {
        rectClient.DeflateRect(0,GetCaptionHeight(),0,0);
    }
    else
    {
        rectClient.DeflateRect(m_iMargin, 32, m_iMargin,m_iMargin);
    }
    
    if (GetStyle() & FWS_SNAPTOBARS)
	{
		CRect rect(0, 0, 32767, 32767);
		RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposQuery,
			&rect, &rect, FALSE);
		RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposExtra,
			&m_rectBorder, &rect, TRUE);
		CalcWindowRect(&rect);
		SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(),
			SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOZORDER);
	}
	else
        RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposExtra, &m_rectBorder, &rectClient);

    /*CPlaylistFrame * pFrame = GetParentPlaylistFrame();
    if(pFrame == NULL)
    {
        if(cx < minSize.cx ||
            cy < minSize.cy)
        {
            SetWindowPos(NULL, 0, 0, minSize.cx, minSize.cy, SWP_NOMOVE | SWP_NOZORDER);
            return;
        }
    }
    else
    {
        CRect rectWindow;
        pFrame->GetWindowRect(rectWindow);
        if(rectWindow.Width() < minSize.cx ||
            rectWindow.Height() < minSize.cy)
        {
            pFrame->SetWindowPos(NULL, 0, 0, minSize.cx, minSize.cy, SWP_NOMOVE | SWP_NOZORDER);
            return;
        }
    }*/
    
    

    UpdateControlBox();
    

	UpdateDrawingObjects();	
	

//    CListCtrl & list = pPlaylistView->GetListCtrl();
//    CRect rectView;
  //  pPlaylistView->GetViewRect(rectView);
//    CRect rectView;
  //  BOOL b =  pPlaylistView->GetListCtrl().GetViewRect(rectView);
    //CDC * pDC2 = pPlaylistView->GetDC();
    //CSize sizeExt = pDC2->GetWindowExt();
    //pPlaylistView->ReleaseDC(pDC2);
    //CRect rectClient;
    //GetClientRect(rectClient);
/*    bool bHScroll = false;
    bool bVScroll = false;
    if(rectView.Width() > rectClient.Width())
    {
        bHScroll = true;
        if(rectView.Height() > rectClient.Height() - GetSystemMetrics(SM_CYHSCROLL))
        {
            bVScroll = true;
        }
    }
    else if(rectView.Height() > rectClient.Height())
    {
        bVScroll = true;
        if(rectView.Width() > rectClient.Width() - GetSystemMetrics(SM_CXVSCROLL))
        {
            bHScroll = true;
        }
    }*/
    int iWidth = cx - m_iMargin * 2;
    /*if(iWidth < 0)
        iWidth = 0;
    if(bHScroll)
    {
        if(bVScroll)
            iWidth -= GetSystemMetrics(SM_CXVSCROLL);
        if(iWidth < 0)
            iWidth = 0;
        if(::IsWindow(m_pScrollHorizontal->m_hWnd))
        {
//            m_pScrollHorizontal->SetWindowPos(
  //              &list,
    //            m_iMargin, cy - GetSystemMetrics(SM_CYHSCROLL)- m_iMargin,
      //          iWidth, GetSystemMetrics(SM_CYHSCROLL),
        //        SWP_SHOWWINDOW);
          //  SCROLLINFO si;
//            si.fMask = SIF_ALL;
  //          m_pScrollHorizontal->GetScrollInfo(&si);
    //        si.nMin = 0;
      //      si.nMax = rectView.Width();
        //    si.nPage = iWidth;
          //  m_pScrollHorizontal->SetScrollInfo(&si);
        }
    }
    else
    {
        //m_pScrollHorizontal->ShowWindow(SW_HIDE);
    }*/
//    int iHeight = cy - m_iMargin * 2 - iCaptionHeight;
    /*if(iHeight < 0)
        iHeight = 0;
    if(bVScroll)
    {
        if(bHScroll)
            iHeight -= GetSystemMetrics(SM_CYHSCROLL);
        if(iHeight < 0)
            iHeight = 0;

        if(::IsWindow(m_pScrollVertical->m_hWnd))
        {
//            m_pScrollVertical->SetWindowPos(
  //              &list,
    //            rectClient.right - m_iMargin - GetSystemMetrics(SM_CXVSCROLL), iCaptionHeight,
      //          GetSystemMetrics(SM_CXVSCROLL), iHeight,
        //        SWP_SHOWWINDOW);
          //  SCROLLINFO si;
            //si.fMask = SIF_ALL;
            //m_pScrollVertical->GetScrollInfo(&si);
            //si.nMin = 0;
            //si.nMax = sizeView.cy;
            //si.nPage = iHeight;
            //m_pScrollVertical->SetScrollInfo(&si);
        }
    }
    else
    {
        //m_pScrollVertical->ShowWindow(SW_HIDE);
    }
    if(!bHScroll && !bVScroll)
    {
        
//        pPlaylistView->m_ptScroll = CPoint(0, 0);
    }*/

//    pPlaylistView->SetWindowPos(&CFrameWnd::wndTop, m_iMargin, iCaptionHeight, iWidth, iHeight, SWP_SHOWWINDOW | SWP_NOCOPYBITS);
	// TODO: Add your message handler code here

    if(nType & SIZE_MINIMIZED)
    {
        bool bChangeStyle = !(GetStyle() & WS_CAPTION);
        if(bChangeStyle)
        {
            ModifyStyle(0, WS_CAPTION | WS_THICKFRAME, 0);

//            SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | ;
        }
        CRect rectWindow;
        GetWindowRect(rectWindow);
        rectWindow -= rectWindow.TopLeft();
        CRgn rgnMain;
        rgnMain.CreateRectRgnIndirect(rectWindow);
        //int i = SetWindowRgn((HRGN) rgnMain.Detach(), TRUE);
        if(bChangeStyle)
        {
//            ModifyStyle(0, WS_CAPTION | WS_THICKFRAME, SWP_SHOWWINDOW | SWP_FRAMECHANGED);
            SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOMOVE | SWP_FRAMECHANGED);
        }
    }
    else if(IsFullScreen())
    {
        if((GetStyle() & WS_CAPTION))
        {
            ModifyStyle(WS_CAPTION | WS_THICKFRAME, 0, SWP_SHOWWINDOW | SWP_FRAMECHANGED);
        }

        SetWindowRgn(NULL, TRUE);
/*        CRect rectClient;
        GetClientRect(rectClient);
        CRect rectAdjust = rectClient;
	    if(AdjustWindowRectEx(rectAdjust, GetStyle(), FALSE, GetExStyle()))
        {
            CRect rectRgn = rectClient;
            rectRgn += (rectClient.TopLeft() - rectAdjust.TopLeft());
            HRGN hrgnMain = CreateRectRgnIndirect(rectRgn);
            SetWindowRgn(hrgnMain, TRUE);
        }*/
    }
    else if(IsZoomed())
    {
        if((GetStyle() & WS_CAPTION))
        {
            ModifyStyle(WS_CAPTION | WS_THICKFRAME, 0, SWP_SHOWWINDOW | SWP_FRAMECHANGED);
        }

        CRect rectClient;
        GetClientRect(rectClient);
        CRect rectAdjust = rectClient;
	    if(AdjustWindowRectEx(rectAdjust, GetStyle(), FALSE, GetExStyle()))
        {
            CRect rectRgn = rectClient;
//            HRGN hrgnOld = m_hrgnWindow;
            rectRgn += (rectClient.TopLeft() - rectAdjust.TopLeft());
            CBaseRect rectA = rectRgn;
//            rectA.top++;
  //          rectA.left++;
    //        rectA.bottom--;
      //      rectA.right--;
            HRGN hrgnMain = CreateRectRgnIndirect(rectA);
                SetWindowRgn(hrgnMain, TRUE);
        
/*            CBaseRect rectB = rectRgn;
            rectB.right = rectB.left + 16;
            rectB.bottom = rectB.top + 16;
            HRGN hrgnAdd = CreateRectRgnIndirect(rectB);
            CombineRgn(hrgnMain, hrgnMain, hrgnAdd, RGN_OR);
            DeleteObject(hrgnAdd);

            rectB = rectRgn;
            rectB.left = rectB.right - 16;
            rectB.bottom = rectB.top + 16;
            hrgnAdd = CreateRectRgnIndirect(rectB);
            CombineRgn(hrgnMain, hrgnMain, hrgnAdd, RGN_OR);
            DeleteObject(hrgnAdd);

            rectB = rectRgn;
            rectB.left = rectB.right - 16;
            rectB.top = rectB.bottom - 16;
            hrgnAdd = CreateRectRgnIndirect(rectB);
            CombineRgn(hrgnMain, hrgnMain, hrgnAdd, RGN_OR);
            DeleteObject(hrgnAdd);

            rectB = rectRgn;
            rectB.right = rectB.left + 16;
            rectB.top = rectB.bottom - 16;
            hrgnAdd = CreateRectRgnIndirect(rectB);
            CombineRgn(hrgnMain, hrgnMain, hrgnAdd, RGN_OR);
            DeleteObject(hrgnAdd);

            CPoint ptCenter = rectRgn.CenterPoint();
        
            rectB = rectRgn;
            rectB.left = ptCenter.x - 8;
            rectB.right = ptCenter.x + 8;
            hrgnAdd = CreateRectRgnIndirect(rectB);
            CombineRgn(hrgnMain, hrgnMain, hrgnAdd, RGN_OR);
            DeleteObject(hrgnAdd);

            rectB = rectRgn;
            rectB.top = ptCenter.y - 8;
            rectB.bottom = ptCenter.y + 8;
            hrgnAdd = CreateRectRgnIndirect(rectB);
            CombineRgn(hrgnMain, hrgnMain, hrgnAdd, RGN_OR);
            DeleteObject(hrgnAdd);

            //m_hrgnWindow = hrgnMain;
            SetWindowRgn(hrgnMain, TRUE);
//            if(hrgnOld != NULL)
  //              DeleteObject(hrgnOld);*/
        }
    }
    else 
    {
        if((GetStyle() & WS_CAPTION))
        {
            ModifyStyle(WS_CAPTION | WS_THICKFRAME, 0, SWP_SHOWWINDOW | SWP_FRAMECHANGED);
        }

        CRect rectClient;
        GetClientRect(rectClient);
        CRect rectAdjust = rectClient;
	    if(AdjustWindowRectEx(rectAdjust, GetStyle(), FALSE, GetExStyle()))
        {
            CRect rectRgn = rectClient;
//            HRGN hrgnOld = m_hrgnWindow;
            rectRgn += (rectClient.TopLeft() - rectAdjust.TopLeft());
            CBaseRect rectA = rectRgn;
            rectA.top++;
            rectA.left++;
            rectA.bottom--;
            rectA.right--;
            HRGN hrgnMain = CreateRectRgnIndirect(rectA);
        
            CBaseRect rectB = rectRgn;
            rectB.right = rectB.left + 16;
            rectB.bottom = rectB.top + 16;
            HRGN hrgnAdd = CreateRectRgnIndirect(rectB);
            CombineRgn(hrgnMain, hrgnMain, hrgnAdd, RGN_OR);
            DeleteObject(hrgnAdd);

            rectB = rectRgn;
            rectB.left = rectB.right - 16;
            rectB.bottom = rectB.top + 16;
            hrgnAdd = CreateRectRgnIndirect(rectB);
            CombineRgn(hrgnMain, hrgnMain, hrgnAdd, RGN_OR);
            DeleteObject(hrgnAdd);

            rectB = rectRgn;
            rectB.left = rectB.right - 16;
            rectB.top = rectB.bottom - 16;
            hrgnAdd = CreateRectRgnIndirect(rectB);
            CombineRgn(hrgnMain, hrgnMain, hrgnAdd, RGN_OR);
            DeleteObject(hrgnAdd);

            rectB = rectRgn;
            rectB.right = rectB.left + 16;
            rectB.top = rectB.bottom - 16;
            hrgnAdd = CreateRectRgnIndirect(rectB);
            CombineRgn(hrgnMain, hrgnMain, hrgnAdd, RGN_OR);
            DeleteObject(hrgnAdd);

            CPoint ptCenter = rectRgn.CenterPoint();
        
            rectB = rectRgn;
            rectB.left = ptCenter.x - 8;
            rectB.right = ptCenter.x + 8;
            hrgnAdd = CreateRectRgnIndirect(rectB);
            CombineRgn(hrgnMain, hrgnMain, hrgnAdd, RGN_OR);
            DeleteObject(hrgnAdd);

            rectB = rectRgn;
            rectB.top = ptCenter.y - 8;
            rectB.bottom = ptCenter.y + 8;
            hrgnAdd = CreateRectRgnIndirect(rectB);
            CombineRgn(hrgnMain, hrgnMain, hrgnAdd, RGN_OR);
            DeleteObject(hrgnAdd);

            //m_hrgnWindow = hrgnMain;
            SetWindowRgn(hrgnMain, TRUE);
//            if(hrgnOld != NULL)
  //              DeleteObject(hrgnOld);
        }
    }


}

//CPlaylistView * CKaraokeMainFrame::GetPlaylistView()
//{
//    return (CPlaylistView *) GetDlgItem(m_uiPlaylistID);
//}

void CKaraokeMainFrame::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

    
    if(GetExStyle() & WS_EX_TRANSPARENT)
    {
//        if(m_ptransparentWndContainer)
  //      {
    //        CRect rectClipBox = dc.m_ps.rcPaint;
//            pDC->GetClipBox(rectClipBox);
      //      if(!rectClipBox.IsRectNull())
        //    {
          //      ClientToScreen(rectClipBox);
            //    m_ptransparentWndContainer->Redraw(rectClipBox);
//            }
  //      }
        return;
    }

    if(GetExStyle() & WS_EX_TRANSPARENT)
        return;

    if(IsFullScreen())
        return;

    bool bZoomed = IsZoomed() != 0;
    //CRect rectClipBox;
    //dc.GetClipBox(rectClipBox);
    //TRACE(_T("CKaraokeMainFrame::OnPaint\n"));
//    CVMSApp * pApp = (CVMSApp *) AfxGetApp();
    //int iEconoMode = pApp->GetEconoMode();
    int iEconoMode = CSavings::AppGetEconoMode();
    CDC * pDCBuffer = &dc;
//    if(iEconoMode & CSavings::SaveMemory ||
  //      iEconoMode & CSavings::SaveProcessing)
    //{
      //  pDCBuffer = &dc;
//    }
  //  else
    //{
      //  return;
        //if(m_dcBuffer.m_hDC == NULL)
//        {
  //          UpdateDrawingObjects();
    //    }
      //  pDCBuffer = &m_dcBuffer;
    //}
	CRect rectClient;
    GetClientRect(rectClient);
//    CXfplayerView * pParentView = GetParentLyricView();
  //  CPlaylistView * pPlaylistView = GetPlaylistView();
//    if(pPlaylistView != NULL)
  //  {
//        CRect rectPlaylist;
//        pPlaylistView->GetWindowRect(rectPlaylist);
//        ScreenToClient(rectPlaylist);
//        CRgn rgnClip;
//        CRgn rgnClipDiff;
//        rgnClip.CreateRectRgnIndirect(rectClient);
//        rgnClipDiff.CreateRectRgnIndirect(rectPlaylist);
//        dc.SelectClipRgn(&rgnClip, RGN_COPY);
  //      dc.SelectClipRgn(&rgnClipDiff, RGN_DIFF);
//    }
    CRect rectClipBox = dc.m_ps.rcPaint;
    if(rectClipBox.IsRectNull())
    {
        return;
        GetClientRect(rectClipBox);
    }
/*    if(pParentView != NULL &&
        !(iEconoMode & CSavings::SaveMemory ||
        iEconoMode & CSavings::SaveProcessing))
    {
	    // TODO: Add your message handler code here
		CVMSApp * pApp = (CVMSApp *) AfxGetApp();
        CRect rectSrc;
        GetWindowRect(rectSrc);
        pParentView->ScreenToClient(rectSrc);
        CImaging * pImaging = pApp->GetImaging();
        //dc.BitBlt(0 , 0 , rectClient.Width(), rectClient.Height(), &pParentView->m_dcBack, rectSrc.left, rectSrc.top, SRCCOPY);
//        CRgn rgnClipBox;
  //      rgnClipBox.CreateRectRgnIndirect(rectClipBox);
        TRACE(_T("CKaraokeMainFrame::OnPaint\n"));
		TRACE(_T("rect.left  : %d, "), rectClipBox.left);
		TRACE(_T("rect.top   : %d, "), rectClipBox.top);
		TRACE(_T("rect.right : %d, "), rectClipBox.right);
		TRACE(_T("rect.bottom: %d\n"), rectClipBox.bottom);
        CRect rectSrcClipBox = rectClipBox;
        rectSrcClipBox += rectSrc.TopLeft();
        pDCBuffer->BitBlt(
            rectClipBox.left, rectClipBox.top,
            rectClipBox.Width(), rectClipBox.Height(),
            &pParentView->m_dcBuffer,
            rectSrcClipBox.left, rectSrcClipBox.top,
            SRCCOPY);
        pImaging->ColorBlend(
            pDCBuffer->GetSafeHdc(),
            rectClipBox.left, rectClipBox.top,
            rectClipBox.Width(), rectClipBox.Height(),
            RGB(255,255,255), 127);
    }
    else
    {*/
        //pDCBuffer->FillSolidRect(rectClipBox, GetSysColor(COLOR_WINDOW));
        //pDCBuffer->FillSolidRect(rectClipBox, GetSysColor(COLOR_WINDOW));
    
    //    pDCBuffer->FillSolidRect(rectClipBox, GetSysColor(COLOR_3DFACE));
      //  pDCBuffer->FillSolidRect(m_rectCaption, GetSysColor(COLOR_ACTIVECAPTION));
    
    pDCBuffer->FillSolidRect(rectClipBox, m_crMoveableBorder);
    //pDCBuffer->FillSolidRect(m_rectCaption, GetSysColor(COLOR_ACTIVECAPTION));
    
    pDCBuffer->SelectClipRgn(NULL);
    //}
//    CPlaylistFrame * pParentFrame = GetParentPlaylistFrame();
  //  if(pParentFrame != NULL)
    //{
    //    dc.FillSolidRect(rectClient, GetSysColor(COLOR_WINDOW));

    //}
    CRect rectD = rectClient;
    CPen * ppenOriginal = pDCBuffer->GetCurrentPen();
    CBrush * pbrushOriginal = pDCBuffer->GetCurrentBrush();
    int iOriginalBkMode = pDCBuffer->GetBkMode();
    COLORREF crOriginalTextColor = pDCBuffer->GetTextColor();


    pDCBuffer->SetBkMode(TRANSPARENT);
    HICON hIcon = GetIcon(false);
    
    DrawIconEx(pDCBuffer->GetSafeHdc(),
        m_pointWindowIcon.x, m_pointWindowIcon.y,
        hIcon, 16, 16, 0, NULL, DI_NORMAL);

    CString strWindowText;
    GetWindowText(strWindowText);
    //CRect rectWindowText;
    //rectWindowText.left = m_iMargin;
    //rectWindowText.top = m_iMargin;
    //rectWindowText.right = m_iMargin;
    pDCBuffer->SetTextColor(GetSysColor(COLOR_CAPTIONTEXT));
    pDCBuffer->DrawText(strWindowText, m_rectWindowText, DT_LEFT | DT_TOP);

    CBrush brushNull;
    brushNull.CreateStockObject(NULL_BRUSH);
    //pDCBuffer->SelectObject(&m_penDkShadow1);
//    CPen penMoveableBorder(PS_SOLID, 1, m_crMoveableBorder);
//    pDCBuffer->SelectObject(penMoveableBorder);
    pDCBuffer->SelectObject(&brushNull);

    CBaseRect rectA = rectClient;
    CBaseRect rectClientB = rectClient;

    rectClientB.bottom--;
    rectClientB.right--;
    
    if(!bZoomed)
    {
        rectA.DeflateRect(1, 1, 1, 1);
        pDCBuffer->Draw3dRect(rectA, m_crMoveableBorder, 0);//m_crMoveableBorderDkShadow);
    
        rectA.DeflateRect(1, 1, 1, 1);
        pDCBuffer->Draw3dRect(rectA, m_crMoveableBorderHilight, m_crMoveableBorderShadow);

        rectA.DeflateRect(1, 1, 1, 1);
        pDCBuffer->Draw3dRect(rectA, m_crMoveableBorder, m_crMoveableBorder);

        rectA.DeflateRect(1, 1, 1, 1);
        pDCBuffer->Draw3dRect(rectA, m_crMoveableBorder, m_crMoveableBorder);
        
        CPoint ptCenter = rectA.CenterPoint();

    
        CBaseRect rectB;

        rectB.top = rectClient.top;
        rectB.left = ptCenter.x - 8;
        rectB.right = ptCenter.x + 8;
        rectB.bottom = rectB.top + 5;
    
        pDCBuffer->Draw3dRect(rectB, GetSysColor(COLOR_BTNFACE), GetSysColor(COLOR_3DDKSHADOW));

        rectB.top++;
        rectB.bottom--;
        rectB.left++;
        rectB.right--;

        pDCBuffer->Draw3dRect(rectB, GetSysColor(COLOR_BTNHILIGHT), GetSysColor(COLOR_BTNSHADOW));

        rectB.top++;
        rectB.bottom--;
        rectB.left++;
        rectB.right--;

        pDCBuffer->FillSolidRect(rectB, GetSysColor(COLOR_BTNFACE));


        rectB.bottom = rectClient.bottom;
        rectB.left = ptCenter.x - 8;
        rectB.right = ptCenter.x + 8;
        rectB.top = rectB.bottom - 5;
    
        pDCBuffer->Draw3dRect(rectB, GetSysColor(COLOR_BTNFACE), GetSysColor(COLOR_3DDKSHADOW));

        rectB.top++;
        rectB.bottom--;
        rectB.left++;
        rectB.right--;

        pDCBuffer->Draw3dRect(rectB, GetSysColor(COLOR_BTNHILIGHT), GetSysColor(COLOR_BTNSHADOW));

        rectB.top++;
        rectB.bottom--;
        rectB.left++;
        rectB.right--;

        pDCBuffer->FillSolidRect(rectB, GetSysColor(COLOR_BTNFACE));

        rectB.top = ptCenter.y - 8;
        rectB.left = rectClient.left;
        rectB.right = rectClient.left + 5;
        rectB.bottom = ptCenter.y + 8;
    
        pDCBuffer->Draw3dRect(rectB, GetSysColor(COLOR_BTNFACE), GetSysColor(COLOR_3DDKSHADOW));

        rectB.top++;
        rectB.bottom--;
        rectB.left++;
        rectB.right--;
    
        pDCBuffer->Draw3dRect(rectB, GetSysColor(COLOR_BTNHILIGHT), GetSysColor(COLOR_BTNSHADOW));

        rectB.top++;
        rectB.bottom--;
        rectB.left++;
        rectB.right--;

        pDCBuffer->FillSolidRect(rectB, GetSysColor(COLOR_BTNFACE));

        rectB.top = ptCenter.y - 8;
        rectB.right = rectClient.right;
        rectB.left = rectClient.right - 5;
        rectB.bottom = ptCenter.y + 8;
    
        pDCBuffer->Draw3dRect(rectB, GetSysColor(COLOR_BTNFACE), GetSysColor(COLOR_3DDKSHADOW));

        rectB.top++;
        rectB.bottom--;
        rectB.left++;
        rectB.right--;

        pDCBuffer->Draw3dRect(rectB, GetSysColor(COLOR_BTNHILIGHT), GetSysColor(COLOR_BTNSHADOW));

        rectB.top++;
        rectB.bottom--;
        rectB.left++;
        rectB.right--;

        pDCBuffer->FillSolidRect(rectB, GetSysColor(COLOR_BTNFACE));

        ///////////////////////////////////////////////////
        //
        //  Pen COLOR_BTNHILIGHT
        //
        ///////////////////////////////////////////////////

        pDCBuffer->SelectObject(&m_penHilight1);

        rectA = rectClientB;

        rectA.top++;
        rectA.left++;
        rectA.bottom--;
        rectA.right--;

        CPoint ptA = rectA.TopLeft();
        ptA.y += 15;
        CPoint ptB = rectA.TopLeft();
        CPoint ptC = rectA.TopLeft();
        ptC.x += 15;
        pDCBuffer->MoveTo(ptA);
        pDCBuffer->LineTo(ptB);
        pDCBuffer->LineTo(ptC);

        ptA = rectA.TopRight();
        ptA.x -= 15;
        ptB = rectA.TopRight();
        pDCBuffer->MoveTo(ptA);
        pDCBuffer->LineTo(ptB);

        ptA = rectA.BottomLeft();
        ptA.y -= 15;
        ptB = rectA.BottomLeft();
        pDCBuffer->MoveTo(ptA);
        pDCBuffer->LineTo(ptB);

        rectA.top += 2;
        rectA.left += 2;
        rectA.bottom -= 2;
        rectA.right -= 2;

        ptB = rectA.TopRight();
        ptC = rectA.TopRight();
        ptC.y += 13;
        pDCBuffer->MoveTo(ptB);
        pDCBuffer->LineTo(ptC);

        ptA = rectA.BottomRight();
        ptA.y -= 13;
        ptB = rectA.BottomRight();
        ptC = rectA.BottomRight();
        ptC.x -= 13;
        pDCBuffer->MoveTo(ptA);
        pDCBuffer->LineTo(ptB);
        pDCBuffer->LineTo(ptC);

        ptB = rectA.BottomLeft();
        ptC = rectA.BottomLeft();
        ptC.x += 13;
        pDCBuffer->MoveTo(ptB);
        pDCBuffer->LineTo(ptC);


        ///////////////////////////////////////////////////
        //
        //  Pen COLOR_BTNFACE
        //
        ///////////////////////////////////////////////////


        pDCBuffer->SelectObject(&m_penFace1);

        // Most external rectangle

        rectA = rectClientB;

        ptA = rectA.TopLeft();
        ptA.y += 16;
        ptB = rectA.TopLeft();
        ptC = rectA.TopLeft();
        ptC.x += 16;
        pDCBuffer->MoveTo(ptA);
        pDCBuffer->LineTo(ptB);
        pDCBuffer->LineTo(ptC);

        ptA = rectA.TopRight();
        ptA.x -= 16;
        ptB = rectA.TopRight();
        pDCBuffer->MoveTo(ptA);
        pDCBuffer->LineTo(ptB);

        ptA = rectA.BottomLeft();
        ptA.y -= 16;
        ptB = rectA.BottomLeft();
        pDCBuffer->MoveTo(ptA);
        pDCBuffer->LineTo(ptB);

        // Most internal rectangle

        rectA.top += 4;
        rectA.left += 4;
        rectA.bottom -= 4;
        rectA.right -= 4;

        ptB = rectA.TopRight();
        ptC = rectA.TopRight();
        ptC.y += 12;
        pDCBuffer->MoveTo(ptB);
        pDCBuffer->LineTo(ptC);

        ptA = rectA.BottomRight();
        ptA.y -= 12;
        ptB = rectA.BottomRight();
        ptC = rectA.BottomRight();
        ptC.x -= 12;
        pDCBuffer->MoveTo(ptA);
        pDCBuffer->LineTo(ptB);
        pDCBuffer->LineTo(ptC);

        ptB = rectA.BottomLeft();
        ptC = rectA.BottomLeft();
        ptC.x += 12;
        pDCBuffer->MoveTo(ptB);
        pDCBuffer->LineTo(ptC);


        // Midle Rectangle

        rectA = rectClientB;

        rectA.top += 2;
        rectA.left += 2;
        rectA.bottom -= 2;
        rectA.right -= 2;

        ptA = rectA.TopLeft();
        ptA.y += 14;
        ptB = rectA.TopLeft();
        ptC = rectA.TopLeft();
        ptC.x += 14;
        pDCBuffer->MoveTo(ptA);
        pDCBuffer->LineTo(ptB);
        pDCBuffer->LineTo(ptC);

        ptA = rectA.TopRight();
        ptA.x -= 14;
        ptB = rectA.TopRight();
        ptC = rectA.TopRight();
        ptC.y += 14;
        pDCBuffer->MoveTo(ptA);
        pDCBuffer->LineTo(ptB);
        pDCBuffer->LineTo(ptC);

        ptA = rectA.BottomRight();
        ptA.y -= 14;
        ptB = rectA.BottomRight();
        ptC = rectA.BottomRight();
        ptC.x -= 14;
        pDCBuffer->MoveTo(ptA);
        pDCBuffer->LineTo(ptB);
        pDCBuffer->LineTo(ptC);

        ptA = rectA.BottomLeft();
        ptA.y -= 14;
        ptB = rectA.BottomLeft();
        ptC = rectA.BottomLeft();
        ptC.x += 14;
        pDCBuffer->MoveTo(ptA);
        pDCBuffer->LineTo(ptB);
        pDCBuffer->LineTo(ptC);


        ///////////////////////////////////////////////////
        //
        //  Pen COLOR_BTNSHADOW
        //
        ///////////////////////////////////////////////////

        pDCBuffer->SelectObject(&m_penShadow1);

        rectA = rectClientB;

        rectA.top++;
        rectA.left++;
        rectA.bottom--;
        rectA.right--;

        ptB = rectA.TopRight();
        ptC = rectA.TopRight();
        ptC.y += 15;
        pDCBuffer->MoveTo(ptB);
        pDCBuffer->LineTo(ptC);

        ptA = rectA.BottomRight();
        ptA.y -= 15;
        ptB = rectA.BottomRight();
        ptC = rectA.BottomRight();
        ptC.x -= 15;
        pDCBuffer->MoveTo(ptA);
        pDCBuffer->LineTo(ptB);
        pDCBuffer->LineTo(ptC);

        ptB = rectA.BottomLeft();
        ptC = rectA.BottomLeft();
        ptC.x += 15;
        pDCBuffer->MoveTo(ptB);
        pDCBuffer->LineTo(ptC);

        rectA.top += 2;
        rectA.left += 2;
        rectA.bottom -= 2;
        rectA.right -= 2;


        ptA = rectA.TopLeft();
        ptA.y += 13;
        ptB = rectA.TopLeft();
        ptC = rectA.TopLeft();
        ptC.x += 13;
        pDCBuffer->MoveTo(ptA);
        pDCBuffer->LineTo(ptB);
        pDCBuffer->LineTo(ptC);

        ptA = rectA.TopRight();
        ptA.x -= 13;
        ptB = rectA.TopRight();
        pDCBuffer->MoveTo(ptA);
        pDCBuffer->LineTo(ptB);

        ptA = rectA.BottomLeft();
        ptA.y -= 13;
        ptB = rectA.BottomLeft();
        pDCBuffer->MoveTo(ptA);
        pDCBuffer->LineTo(ptB);


        ///////////////////////////////////////////////////
        //
        //  Pen COLOR_3DDKSHADOW
        //
        ///////////////////////////////////////////////////

        pDCBuffer->SelectObject(&m_penDkShadow1);

        rectA = rectClientB;

        ptB = rectA.TopRight();
        ptC = rectA.TopRight();
        ptC.y += 16;
        pDCBuffer->MoveTo(ptB);
        pDCBuffer->LineTo(ptC);

        ptA = rectA.BottomRight();
        ptA.y -= 16;
        ptB = rectA.BottomRight();
        ptC = rectA.BottomRight();
        ptC.x -= 16;
        pDCBuffer->MoveTo(ptA);
        pDCBuffer->LineTo(ptB);
        pDCBuffer->LineTo(ptC);

        ptB = rectA.BottomLeft();
        ptC = rectA.BottomLeft();
        ptC.x += 16;
        pDCBuffer->MoveTo(ptB);
        pDCBuffer->LineTo(ptC);

        rectA.top += 4;
        rectA.left += 4;
        rectA.bottom -= 4;
        rectA.right -= 4;


        ptA = rectA.TopLeft();
        ptA.y += 12;
        ptB = rectA.TopLeft();
        ptC = rectA.TopLeft();
        ptC.x += 12;
        pDCBuffer->MoveTo(ptA);
        pDCBuffer->LineTo(ptB);
        pDCBuffer->LineTo(ptC);

        ptA = rectA.TopRight();
        ptA.x -= 12;
        ptB = rectA.TopRight();
        pDCBuffer->MoveTo(ptA);
        pDCBuffer->LineTo(ptB);

        ptA = rectA.BottomLeft();
        ptA.y -= 12;
        ptB = rectA.BottomLeft();
        pDCBuffer->MoveTo(ptA);
        pDCBuffer->LineTo(ptB);


        ///////////////////////////////////////////////////
        //
        //  Pen COLOR_BTNHILIGHT
        //
        ///////////////////////////////////////////////////

        pDCBuffer->SelectObject(&m_penHilight1);

        ptA.x = rectClientB.right - 15;
        ptA.y = rectClientB.top + 1;
        ptB.x = rectClientB.right - 15;
        ptB.y = rectClientB.top + 4;
        pDCBuffer->MoveTo(ptA);
        pDCBuffer->LineTo(ptB);

        ptA.x = rectClientB.right - 4;
        ptA.y = rectClientB.bottom - 15;
        ptB.x = rectClientB.right - 1;
        ptB.y = rectClientB.bottom - 15;
        pDCBuffer->MoveTo(ptB);
        pDCBuffer->LineTo(ptA);

        ptA.x = rectClientB.right - 15;
        ptA.y = rectClientB.bottom - 4;
        ptB.x = rectClientB.right - 15;
        ptB.y = rectClientB.bottom - 1;
        pDCBuffer->MoveTo(ptB);
        pDCBuffer->LineTo(ptA);

        ptA.x = rectClientB.left + 1;
        ptA.y = rectClientB.bottom - 15;
        ptB.x = rectClientB.left + 4;
        ptB.y = rectClientB.bottom - 15;
        pDCBuffer->MoveTo(ptA);
        pDCBuffer->LineTo(ptB);

        ///////////////////////////////////////////////////
        //
        //  Pen COLOR_BTNFACE
        //
        ///////////////////////////////////////////////////


        pDCBuffer->SelectObject(&m_penFace1);

        // Details

        ptA.x = rectClientB.right - 16;
        ptA.y = rectClientB.top;
        ptB.x = rectClientB.right - 16;
        ptB.y = rectClientB.top + 5;
        pDCBuffer->MoveTo(ptA);
        pDCBuffer->LineTo(ptB);

        ptA.x = rectClientB.right - 5;
        ptA.y = rectClientB.bottom - 16;
        ptB.x = rectClientB.right;
        ptB.y = rectClientB.bottom - 16;
        pDCBuffer->MoveTo(ptA);
        pDCBuffer->LineTo(ptB);

        ptA.x = rectClientB.right - 16;
        ptA.y = rectClientB.bottom - 5;
        ptB.x = rectClientB.right - 16;
        ptB.y = rectClientB.bottom;
        pDCBuffer->MoveTo(ptA);
        pDCBuffer->LineTo(ptB);

        ptA.x = rectClientB.left;
        ptA.y = rectClientB.bottom - 16;
        ptB.x = rectClientB.left + 5;
        ptB.y = rectClientB.bottom - 16;
        pDCBuffer->MoveTo(ptA);
        pDCBuffer->LineTo(ptB);


        ///////////////////////////////////////////////////
        //
        //  Pen COLOR_BTNSHADOW
        //
        ///////////////////////////////////////////////////

        pDCBuffer->SelectObject(&m_penShadow1);
    
        // Details

        ptA.x = rectClientB.left + 15;
        ptA.y = rectClientB.top + 1;
        ptB.x = rectClientB.left + 15;
        ptB.y = rectClientB.top + 4;
        pDCBuffer->MoveTo(ptB);
        pDCBuffer->LineTo(ptA);

        ptA.x = rectClientB.left + 1;
        ptA.y = rectClientB.top + 15;
        ptB.x = rectClientB.left + 4;
        ptB.y = rectClientB.top + 15;
        pDCBuffer->MoveTo(ptB);
        pDCBuffer->LineTo(ptA);

        ptA.x = rectClientB.left + 15;
        ptA.y = rectClientB.bottom - 4;
        ptB.x = rectClientB.left + 15;
        ptB.y = rectClientB.bottom - 1;
        pDCBuffer->MoveTo(ptA);
        pDCBuffer->LineTo(ptB);

        ptA.x = rectClientB.right - 4;
        ptA.y = rectClientB.top - 15;
        ptB.x = rectClientB.right - 1;
        ptB.y = rectClientB.top - 15;
        pDCBuffer->MoveTo(ptA);
        pDCBuffer->LineTo(ptB);

        ///////////////////////////////////////////////////
        //
        //  Pen COLOR_3DDKSHADOW
        //
        ///////////////////////////////////////////////////

        pDCBuffer->SelectObject(&m_penDkShadow1);

        // Details

        ptA.x = rectClientB.left + 16;
        ptA.y = rectClientB.top;
        ptB.x = rectClientB.left + 16;
        ptB.y = rectClientB.top + 5;
        pDCBuffer->MoveTo(ptA);
        pDCBuffer->LineTo(ptB);

        ptA.x = rectClientB.left;
        ptA.y = rectClientB.top + 16;
        ptB.x = rectClientB.left + 5;
        ptB.y = rectClientB.top + 16;
        pDCBuffer->MoveTo(ptA);
        pDCBuffer->LineTo(ptB);

        ptA.x = rectClientB.left + 16;
        ptA.y = rectClientB.bottom - 5;
        ptB.x = rectClientB.left + 16;
        ptB.y = rectClientB.bottom;
        pDCBuffer->MoveTo(ptB);
        pDCBuffer->LineTo(ptA);

        ptA.x = rectClientB.right - 5;
        ptA.y = rectClientB.top + 16;
        ptB.x = rectClientB.right;
        ptB.y = rectClientB.top + 16;
        pDCBuffer->MoveTo(ptB);
        pDCBuffer->LineTo(ptA);

        if(!(iEconoMode & CSavings::SaveMemory ||
            iEconoMode & CSavings::SaveProcessing))
        {
            GetChildrenClip();
            dc.SelectClipRgn(&m_rgnChildren, RGN_COPY);
            dc.BitBlt(
                rectClipBox.left, rectClipBox.top,
                rectClipBox.Width(), rectClipBox.Height(),
                pDCBuffer,
                rectClipBox.left, rectClipBox.top,
                SRCCOPY);
        }
    }

    pDCBuffer->SelectObject(ppenOriginal);
    pDCBuffer->SelectObject(pbrushOriginal);
    pDCBuffer->SetBkMode(iOriginalBkMode);
    pDCBuffer->SetTextColor(crOriginalTextColor);
	// Do not call CFrameWnd::OnPaint() for painting messages
}

int CKaraokeMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

    m_pwmm->SetWindows(this, this);
    m_pwsm->SetWindows(this, this);
    m_pwsmm->SetWindows(this);
      
    //TWIInitialize(this);
	CDC * pDC = GetDC();
    m_fontMarlett.CreatePointFont(90, _T("Marlett"), GetDC());
    ReleaseDC(pDC);
    CString str;

    UINT uiStyle = 0;

    str = (CHAR) 114;
    m_pbuttonClose->Create(str, WS_VISIBLE | WS_CHILD, CRect(0, 0, 0, 0), this, ID_CLOSE);
    m_pbuttonClose->SetFont(&m_fontMarlett);
    m_pbuttonClose->SetEllipseBrushs(&m_brushControlBoxBack, &m_brushControlBoxBackSel, &m_brushControlBoxBackFocus, &m_brushControlBoxBackDisabled);
    m_pbuttonClose->SetEllipsePens(&m_penControlBoxBack, &m_penControlBoxBackSel, &m_penControlBoxBackFocus, &m_penControlBoxBackDisabled);
    m_pbuttonClose->SetTextColors(m_crControlBoxFore, m_crControlBoxForeSel, m_crControlBoxForeFocus, m_crControlBoxForeDisabled);
    m_pbuttonClose->ModifyStyleEx(0, WS_EX_TRANSPARENT);

    str = (CHAR) 53;
    m_pbuttonUp->Create(str, WS_VISIBLE | WS_CHILD, CRect(0, 0, 0, 0), this, ID_UP);
    m_pbuttonUp->SetFont(&m_fontMarlett);
    m_pbuttonUp->SetEllipseBrushs(&m_brushControlBoxBack, &m_brushControlBoxBackSel, &m_brushControlBoxBackFocus, &m_brushControlBoxBackDisabled);
    m_pbuttonUp->SetEllipsePens(&m_penControlBoxBack, &m_penControlBoxBackSel, &m_penControlBoxBackFocus, &m_penControlBoxBackDisabled);
    m_pbuttonUp->SetTextColors(m_crControlBoxFore, m_crControlBoxForeSel, m_crControlBoxForeFocus, m_crControlBoxForeDisabled);
    m_pbuttonUp->ModifyStyleEx(0, WS_EX_TRANSPARENT);

    str = (CHAR) 54;
    m_pbuttonDown->Create(str, WS_VISIBLE | WS_CHILD, CRect(0, 0, 0, 0), this, ID_DOWN);
    m_pbuttonDown->SetFont(&m_fontMarlett);
    m_pbuttonDown->SetEllipseBrushs(&m_brushControlBoxBack, &m_brushControlBoxBackSel, &m_brushControlBoxBackFocus, &m_brushControlBoxBackDisabled);
    m_pbuttonDown->SetEllipsePens(&m_penControlBoxBack, &m_penControlBoxBackSel, &m_penControlBoxBackFocus, &m_penControlBoxBackDisabled);
	m_pbuttonDown->SetTextColors(m_crControlBoxFore, m_crControlBoxForeSel, m_crControlBoxForeFocus, m_crControlBoxForeDisabled);
    // TODO: Add your specialized creation code here
	m_pbuttonDown->ModifyStyleEx(0, WS_EX_TRANSPARENT);
    m_pwsm->SetMinSize(minSize);

    str = (CHAR) 48;
    m_pbuttonMinimize->Create(str, WS_VISIBLE | WS_CHILD, CRect(0, 0, 0, 0), this, ID_WINDOW_MINIMIZE);
    m_pbuttonMinimize->SetFont(&m_fontMarlett);
    m_pbuttonMinimize->SetEllipseBrushs(&m_brushControlBoxBack, &m_brushControlBoxBackSel, &m_brushControlBoxBackFocus, &m_brushControlBoxBackDisabled);
    m_pbuttonMinimize->SetEllipsePens(&m_penControlBoxBack, &m_penControlBoxBackSel, &m_penControlBoxBackFocus, &m_penControlBoxBackDisabled);
	m_pbuttonMinimize->SetTextColors(m_crControlBoxFore, m_crControlBoxForeSel, m_crControlBoxForeFocus, m_crControlBoxForeDisabled);
    m_pbuttonMinimize->ModifyStyleEx(0, WS_EX_TRANSPARENT);
    // TODO: Add your specialized creation code here
	m_pwsm->SetMinSize(minSize);

    str = (CHAR) 49;
    m_pbuttonMaximize->Create(str, WS_VISIBLE | WS_CHILD, CRect(0, 0, 0, 0), this, ID_WINDOW_MAXIMIZE);
    m_pbuttonMaximize->SetFont(&m_fontMarlett);
    m_pbuttonMaximize->SetEllipseBrushs(&m_brushControlBoxBack, &m_brushControlBoxBackSel, &m_brushControlBoxBackFocus, &m_brushControlBoxBackDisabled);
    m_pbuttonMaximize->SetEllipsePens(&m_penControlBoxBack, &m_penControlBoxBackSel, &m_penControlBoxBackFocus, &m_penControlBoxBackDisabled);
	m_pbuttonMaximize->SetTextColors(m_crControlBoxFore, m_crControlBoxForeSel, m_crControlBoxForeFocus, m_crControlBoxForeDisabled);
    m_pbuttonMaximize->ModifyStyleEx(0, WS_EX_TRANSPARENT);
    // TODO: Add your specialized creation code here
	m_pwsm->SetMinSize(CSize(48, 48));
    
    str = (CHAR) 50;
    m_pbuttonRestore->Create(str, WS_VISIBLE | WS_CHILD, CRect(0, 0, 0, 0), this, ID_WINDOW_RESTORE);
    m_pbuttonRestore->SetFont(&m_fontMarlett);
    m_pbuttonRestore->SetEllipseBrushs(&m_brushControlBoxBack, &m_brushControlBoxBackSel, &m_brushControlBoxBackFocus, &m_brushControlBoxBackDisabled);
    m_pbuttonRestore->SetEllipsePens(&m_penControlBoxBack, &m_penControlBoxBackSel, &m_penControlBoxBackFocus, &m_penControlBoxBackDisabled);
	m_pbuttonRestore->SetTextColors(m_crControlBoxFore, m_crControlBoxForeSel, m_crControlBoxForeFocus, m_crControlBoxForeDisabled);
    // TODO: Add your specialized creation code here
	m_pbuttonRestore->ModifyStyleEx(0, WS_EX_TRANSPARENT);
    m_pwsm->SetMinSize(CSize(48, 48));
    
    UpdateDrawingObjects();
//    m_pScrollHorizontal->Create(m_pScrollHorizontal->OrientationHorizontal, SBS_HORZ, CRect(0, 0, 0, 0), this, IDC_HSCROLL);
  //  m_pScrollVertical->Create(m_pScrollVertical->OrientationVertical, SBS_HORZ, CRect(0, 0, 0, 0), this, IDC_HSCROLL);
   //str.LoadString(IDS_PLAYLIST_TITLE);
//    SetWindowText(str);
//    
//    CVMSApp * pApp = (CVMSApp *) AfxGetApp();
//
//    HICON hIcon = (HICON) LoadImage(pApp->m_hInstance,
//        MAKEINTRESOURCE(IDR_PLAYLIST),
//        IMAGE_ICON,
//        16, 16,
//        0);
//
//
//    SetIcon(hIcon, false);
//
//    hIcon = (HICON) LoadImage(pApp->m_hInstance,
//        MAKEINTRESOURCE(IDR_PLAYLIST),
//        IMAGE_ICON,
//        0, 0,
//        LR_DEFAULTSIZE);
//
//SetIcon(hIcon, true);

//    InitializeTWI(this);
    CMenu * pmenu = GetMenu();
    SetMenu(NULL);
    if(pmenu)
        pmenu->DestroyMenu();

//    UpdateControlBox();

    if(GetStyle() & (WS_CAPTION | WS_THICKFRAME))
    {
        ModifyStyle(WS_CAPTION | WS_THICKFRAME, 0, SWP_FRAMECHANGED);
    }

    if(GetExStyle() & (WS_EX_CLIENTEDGE))
    {
        ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);
    }

	return 0;
}


void CKaraokeMainFrame::OnIdClose() 
{
	// TODO: Add your command handler code here
//	CXfplayerView * pParentView = GetParentLyricView();
//    if(pParentView != NULL)
  //  {
    //    CPlaylistView * pPlaylistView = GetPlaylistView();
      //  CPlaylistDoc * pPlaylistDoc = pParentView->DetachPlaylistDoc();
//        CFrameWnd *pFrame = pPlaylistView->GetParentFrame();
  //      pFrame->PostMessage(WM_CLOSE);
    //    return;
    //}
//    CPlaylistFrame * pParentFrame = GetParentPlaylistFrame();
//    if(pParentFrame != NULL)
  //  {
    //    pParentFrame->PostMessage(WM_CLOSE);
      //  return;
    //}
    PostMessage(WM_CLOSE);
}

void CKaraokeMainFrame::OnUp() 
{
	// TODO: Add your command handler code here
//	CXfplayerView * pParentView = GetParentLyricView();
  //  if(pParentView != NULL)
    //{
      //  CPlaylistView * pPlaylistView = GetPlaylistView();
        //if(pPlaylistView->GetMode() == pPlaylistView->ModeMinimum)
//        {
  //          pPlaylistView->SetMode(pPlaylistView->ModeNormal);
    //    }
      //  else
        //{
//            pParentView->DetachPlaylistView();
  //          CFrameWnd *pFrame = pPlaylistView->GetParentFrame();
    //        pFrame->ShowWindow(SW_SHOW);
      //  }
//        UpdateControlBox();
  //      return;
    //}
//    CPlaylistFrame * pParentFrame = GetParentPlaylistFrame();
  //  if(pParentFrame != NULL)
    //{
      //  ASSERT(FALSE);
        //return;
    //}

    
	
}

/*CPlaylistFrame * CKaraokeMainFrame::GetParentPlaylistFrame()
{
    CFrameWnd * pParentFrame = GetParentFrame();
    if(pParentFrame != NULL &&
        pParentFrame->IsKindOf(RUNTIME_CLASS(CPlaylistFrame)))
        return (CPlaylistFrame *) pParentFrame;
    return NULL;
}*/

/*CXfplayerView * CKaraokeMainFrame::GetParentLyricView()
{
    CWnd * pParentWnd = GetParent();
    if(pParentWnd != NULL &&
        pParentWnd->IsKindOf(RUNTIME_CLASS(CXfplayerView)))
        return (CXfplayerView *) pParentWnd;
    return NULL;
}*/

void CKaraokeMainFrame::OnDown() 
{
	// TODO: Add your command handler code here
/*	CXfplayerView * pParentView = GetParentLyricView();
    if(pParentView != NULL)
    {
        CPlaylistView * pPlaylistView = GetPlaylistView();
        if(pPlaylistView->GetMode() == CPlaylistView::ModeMinimum)
        {
            ASSERT(FALSE);
            return;
        }
        else
        {
            pPlaylistView->SetMode(CPlaylistView::ModeMinimum);
        }
    }
    CPlaylistFrame * pParentFrame = GetParentPlaylistFrame();
    if(pParentFrame != NULL)
    {
        CVMSApp * pApp = (CVMSApp *) AfxGetApp();
        pApp->GetPlayerDocument()->GetLyricView()->AttachPlaylistDoc(GetPlaylistView()->GetDocument());
        return;
    }

    UpdateControlBox();*/

}


BOOL CKaraokeMainFrame::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
    if(!IsFullScreen() || !IsZoomed())
    {
        if(m_pwsm->RelayEvent(pMsg))
            return TRUE;

        if(m_pwmm->RelayEvent(pMsg))
            return TRUE;

        if(!IsFullScreen())
        {
            if(m_pwsmm->RelayEvent(pMsg))
                return TRUE;
        }
    }

	if(pMsg->hwnd == m_hWnd)
	{
		switch(pMsg->message)
		{
		case WM_DISPLAYCHANGE:
			OnDisplayChange(pMsg->wParam, CSize(LOWORD(pMsg->lParam), HIWORD(pMsg->lParam)));
			return TRUE;
		default:
			break;
		}
	}

	return CFrameWnd::PreTranslateMessage(pMsg);
}

BOOL CKaraokeMainFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	//cs.dwExStyle |= WS_EX_TRANSPARENT;
    //cs.dwExStyle &= ~WS_EX_TRANSPARENT;
    //cs.style &= ~WS_CLIPCHILDREN;
    //cs.style |= WS_CLIPCHILDREN;

    cs.style &= ~WS_CAPTION;
    cs.style &= ~WS_THICKFRAME;
    cs.style |= WS_CLIPCHILDREN;

    cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

	return CFrameWnd::PreCreateWindow(cs);
}

/*CDC * CKaraokeMainFrame::GetBufferDC()
{
    return &m_dcBuffer;
}*/

int CKaraokeMainFrame::GetChildrenClip()
{
    CWnd * pWndChild  = GetTopWindow();
    CWnd * pWndFirstChild = pWndChild;
    CRgn rgnChild;
    CRect rectClient;
    CRect rectChild;
    GetClientRect(rectClient);
    m_rgnChildren.SetRectRgn(rectClient);
    rgnChild.CreateRectRgn(0, 0, 0, 0);
    while(pWndChild != NULL)
    {
        if(!pWndChild->IsKindOf(RUNTIME_CLASS(CButtonV007)))
        {
            if(pWndChild->GetWindowRgn(rgnChild) != ERROR)
            {
                pWndChild->GetWindowRect(rectChild);
                ScreenToClient(rectChild);
                rgnChild.OffsetRgn(rectChild.TopLeft());
                m_rgnChildren.CombineRgn(&m_rgnChildren, &rgnChild, RGN_DIFF);
            }
            else
            {
                pWndChild->GetWindowRect(rectChild);
                ScreenToClient(rectChild);
                rgnChild.SetRectRgn(rectChild);
                m_rgnChildren.CombineRgn(&m_rgnChildren, &rgnChild, RGN_DIFF);
            }
        }
        pWndChild = pWndChild->GetNextWindow();
        if(pWndChild  == NULL || pWndChild->m_hWnd == pWndFirstChild->m_hWnd)
            break;
    }
    return TRUE;
}

void CKaraokeMainFrame::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
//    CPlaylistView * pPlaylistView = GetPlaylistView();
  //  if(!::IsWindow(m_pScrollHorizontal->m_hWnd))
    //{
      //  m_pScrollHorizontal->SubclassWindow(pScrollBar->m_hWnd);
    //}
//    if(pPlaylistView != NULL)
  //  {
//        CRect rectScroll;
  //      pPlaylistView->GetClientRect(rectScroll);
//        rectScroll += CPoint(nPos, 0);
        //CRect rectWindow;
//        pPlaylistView->m_ptScroll.x = -nPos;
//        pPlaylistView->GetListCtrl().Scroll(CSize(-nPos, -m_pScrollVertical->GetScrollPos()));
//        pPlaylistView->RedrawWindow();
        //pPlaylistView->GetListCtrl().ScrollWindowEx(m_ptScroll.x - nPos, 0, NULL, NULL, NULL, NULL, SW_INVALIDATE);
//        pPlaylistView->GetListCtrl().Scroll(CSize(m_ptScroll.x - nPos, 0));
        //m_ptScroll.x = nPos;
        //pPlaylistView->UpdateWindow();
    //}
	CFrameWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CKaraokeMainFrame::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	//    CPlaylistView * pPlaylistView = GetPlaylistView();
    //if(!::IsWindow(m_pScrollVertical->m_hWnd))
    //{
      //  m_pScrollVertical->SubclassWindow(pScrollBar->m_hWnd);
    //}

    //if(pPlaylistView != NULL)
   // {
//        CRect rectScroll;
  //      pPlaylistView->GetClientRect(rectScroll);
//        rectScroll += CPoint(nPos, 0);
        //CRect rectWindow;
//        pPlaylistView->m_ptScroll.y = -nPos;
//        pPlaylistView->GetListCtrl().Scroll(CSize(-m_pScrollHorizontal->GetScrollPos(),- nPos ));
  //      pPlaylistView->RedrawWindow();

        //pPlaylistView->GetListCtrl().ScrollWindowEx(0, nPos - m_ptScroll.y, NULL, NULL, NULL, NULL, SW_INVALIDATE);
        //m_ptScroll.y = nPos;
        //pPlaylistView->UpdateWindow();
//        pPlaylistView->GetListCtrl().Scroll(CSize(0, nPos - m_ptScroll.y));
//        TRACE(_T("CKaraokeMainFrame::OnVScroll %d"), nPos);
  //  }

	CFrameWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CKaraokeMainFrame::UpdateDrawingObjects()
{
//    CVMSApp * pApp = (CVMSApp *) AfxGetApp();
  //  int iEconoMode = pApp->GetEconoMode();
    int iEconoMode = CSavings::AppGetEconoMode();
	
    CDC * pDC = GetDC();

    CRect rectClient;
	GetClientRect(rectClient);
	int cx = rectClient.Width();
	int cy = rectClient.Height();

  /*  if(iEconoMode == CSavings::SaveNoSave)
    {
        if(m_dcBuffer.m_hDC == NULL)
        {
            m_dcBuffer.CreateCompatibleDC(pDC);
            m_bitmapBufferOriginal.Attach(m_dcBuffer.GetCurrentBitmap()->GetSafeHandle());
        }
        else
        {
            m_dcBuffer.SelectObject(m_bitmapBufferOriginal);
        }

        if(m_bitmapBuffer.m_hObject == NULL)
        {
            m_bitmapBuffer.CreateCompatibleBitmap(pDC, cx + 100, cy + 100);
        }
        else
        {
            BITMAP bm;
            if(!m_bitmapBuffer.GetBitmap(&bm))
            {
                ATTENTION;
                m_bitmapBuffer.DeleteObject();
                m_bitmapBuffer.CreateCompatibleBitmap(pDC, cx + 100, cy + 100);        
            }
            if(cx > bm.bmWidth ||
                cy > bm.bmHeight)
            {
                m_bitmapBuffer.DeleteObject();
                m_bitmapBuffer.CreateCompatibleBitmap(pDC, cx + 100, cy + 100);
            }
        }
        m_dcBuffer.SelectObject(m_bitmapBuffer);
    }
    else
    {
        if(m_dcBuffer.m_hDC != NULL)
        {
            m_dcBuffer.SelectObject(m_bitmapBufferOriginal.Detach());
            m_dcBuffer.DeleteDC();
        }
        if(m_bitmapBuffer.m_hObject != NULL)
        {
            m_bitmapBuffer.DeleteObject();
        }
    }*/
	ReleaseDC(pDC);
    HeapCompact(GetProcessHeap(), 0);
    CDC::DeleteTempMap();
}

void CKaraokeMainFrame::OnDisplayChange(int iBitsPerPixel, CSize sizeScreen)
{
	UpdateDrawingObjects();
}

void CKaraokeMainFrame::OnSetFocus(CWnd* pOldWnd) 
{
	CFrameWnd::OnSetFocus(pOldWnd);
//	GetPlaylistView()->SetFocus();
	// TODO: Add your message handler code here
	
}

void CKaraokeMainFrame::OnMinimize() 
{
	// TODO: Add your command handler code here
//    CXfplayerView * pParentView = GetParentLyricView();
  //  if(pParentView != NULL)
    //{
      //  CPlaylistView * pPlaylistView = GetPlaylistView();
        //pParentView->DetachPlaylistView();
//    }
//    CPlaylistFrame * pParentFrame = GetParentPlaylistFrame();
  //  CString str;
    //GetWindowText(str);
    //pParentFrame->SetWindowText(str);
    //pParentFrame->ShowWindow(SW_MINIMIZE);
    ShowWindow(SW_MINIMIZE);

}

void CKaraokeMainFrame::OnMaximize() 
{
	// TODO: Add your command handler code here
//    CXfplayerView * pParentView = GetParentLyricView();
  //  if(pParentView != NULL)
    //{
      //  CPlaylistView * pPlaylistView = GetPlaylistView();
        //pParentView->DetachPlaylistView();
//    }
  //  CPlaylistFrame * pParentFrame = GetParentPlaylistFrame();

	//pParentFrame->ShowWindow(SW_SHOWMAXIMIZED);
    ShowWindow(SW_SHOWMAXIMIZED);
}

void CKaraokeMainFrame::OnRestore() 
{
	// TODO: Add your command handler code here
//    CXfplayerView * pParentView = GetParentLyricView();
  //  if(pParentView != NULL)
    //{
      //  CPlaylistView * pPlaylistView = GetPlaylistView();
        //pParentView->DetachPlaylistView();
//    }
  //  CPlaylistFrame * pParentFrame = GetParentPlaylistFrame();
//
//	pParentFrame->ShowWindow(SW_RESTORE);
  //  pParentFrame->BringWindowToTop();
	ShowWindow(SW_RESTORE);
    BringWindowToTop();
	
}

void CKaraokeMainFrame::OnRemoveSong() 
{
	// TODO: Add your command handler code here
//	CPlaylistView * pView = GetPlaylistView();
//    pView->DeleteSelectedItems();
}

afx_msg LRESULT CKaraokeMainFrame::OnEconoModeChange(WPARAM wParam, LPARAM lParam)
{
    UpdateDrawingObjects();
    return true;
}

int CKaraokeMainFrame::UpdateControlBox()
{
//    CPlaylistView * pPlaylistView = GetPlaylistView();
  //  if(pPlaylistView == NULL)
    //    return 0;
//    CXfplayerView * pParentView = GetParentLyricView();
  //  CPlaylistFrame * pParentFrame = GetParentPlaylistFrame();
//    if(!IsWindow(m_hWnd))
  //      return 0;
    bool bZoomed = IsZoomed() != 0;
    if(m_bFullScreen)
    {
        m_pbuttonClose->ShowWindow(SW_HIDE);
        m_pbuttonDown->ShowWindow(SW_HIDE);
        m_pbuttonMaximize->ShowWindow(SW_HIDE);
        m_pbuttonMinimize->ShowWindow(SW_HIDE);
        m_pbuttonRestore->ShowWindow(SW_HIDE);
        m_pbuttonUp->ShowWindow(SW_HIDE);
    }

    int iMargin = GetMargin();
    int iCaptionHeight = GetCaptionHeight();
    int iButtonSize = GetButtonSize();

    CRect rectClient;

    GetClientRect(rectClient);

    int cx = rectClient.Width();
    int cy = rectClient.Height();

    CRect rect;
    
    m_rectCaption.left = rectClient.left + iMargin;
    m_rectCaption.top = rectClient.top + iMargin;
    m_rectCaption.right = rectClient.right - iMargin;
    m_rectCaption.bottom = m_rectCaption.top + iButtonSize;



    rect.right = cx - iMargin;
    m_rectControlBox.right = rect.right;
    rect.top = iMargin;
    m_rectControlBox.top = rect.top;
    rect.bottom = iMargin + iButtonSize;
    m_rectControlBox.bottom = rect.bottom;
    rect.left = rect.right - iButtonSize;
    m_pbuttonClose->SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), SWP_SHOWWINDOW);
    rect.right -= - m_iButtonMargin;
//    if(pParentView != NULL)
  //  {
    //}
//    else if(pParentFrame != NULL)
  //  {
    //    m_pwmm->SetWindows(this, GetParent());
      //  m_pwsm->SetWindows(this, GetParent());
    //}

//    if(pParentView == NULL)
  //  {
        m_pbuttonUp->ShowWindow(SW_HIDE);
    //}
//    else
  //  {
    //    rect.right = rect.left - m_iButtonMargin;
      //  rect.left = rect.right - iButtonSize;
        //m_pbuttonUp->SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), SWP_SHOWWINDOW);
//    }
//    if(pParentFrame != NULL ||
  //      (pParentView != NULL &&
    //    pPlaylistView->GetMode() == CPlaylistView::ModeNormal))
//    {
  //      rect.right = rect.left - m_iButtonMargin;
    //    rect.left = rect.right - iButtonSize;
      //  m_pbuttonDown->SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), SWP_SHOWWINDOW);
//    }
  //  else
    //{
        m_pbuttonDown->ShowWindow(SW_HIDE);
    //}
    
    //if(pParentFrame != NULL && pParentFrame->IsZoomed())
    if(IsZoomed())
    {
        m_pbuttonMaximize->ShowWindow(SW_HIDE);
    }
    else
    {
        rect.right = rect.left - m_iButtonMargin;
        rect.left = rect.right - iButtonSize;
        m_pbuttonMaximize->SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), SWP_SHOWWINDOW);
    }

//    if(pParentFrame != NULL && !pParentFrame->IsIconic() &&
  //      ! pParentFrame->IsZoomed())
    if(!IsIconic() &&
        !IsZoomed())
    {
        m_pbuttonRestore->ShowWindow(SW_HIDE);
    }
    else
    {
        rect.right = rect.left - m_iButtonMargin;
        rect.left = rect.right - iButtonSize;
        m_pbuttonRestore->SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), SWP_SHOWWINDOW);
    }

    //if(pParentFrame != NULL && pParentFrame->IsIconic())
    if(IsIconic())
    {
        m_pbuttonMinimize->ShowWindow(SW_HIDE);
    }
    else
    {
        rect.right = rect.left - m_iButtonMargin;
        rect.left = rect.right - iButtonSize;
        m_pbuttonMinimize->SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), SWP_SHOWWINDOW);
    }

    m_rectControlBox.left = rect.left;

    m_pointWindowIcon.x = iMargin;
    m_pointWindowIcon.y = iMargin;

    m_rectWindowText.left = m_pointWindowIcon.x + 16 + 2;
    m_rectWindowText.top = iMargin;
    m_rectWindowText.right = m_rectControlBox.left;
    m_rectWindowText.bottom = iCaptionHeight;

    int iWidth = cx - m_iMargin * 2;
    int iHeight = cy - m_iMargin * 2 - iCaptionHeight;

//    pPlaylistView->SetWindowPos(&CFrameWnd::wndTop, m_iMargin, iCaptionHeight, iWidth, iHeight, SWP_SHOWWINDOW | SWP_NOCOPYBITS);
    return 0;
}


/*VMSRESULT CKaraokeMainFrame::TWIRender(LPRECT lprect, CDC * pdcBuffer)
{
    return CTransparentWndInterface::TWIRender(lprect, pdcBuffer);
    CDC * pdc = CDC::FromHandle(pdcBuffer->GetSafeHdc());

    CRect rectClip;
    rectClip = lprect;
    ScreenToClient(rectClip);

    CRect rectClient;
    GetClientRect(rectClient);

    if(rectClip.IntersectRect(rectClip, rectClient))
    {

        CRgn rgnClipOld;
        rgnClipOld.CreateRectRgn(0, 0, 0, 0);
        GetClipRgn(pdc->GetSafeHdc(), rgnClipOld);

        CRgn rgnClip;
        CPoint ptClip = pdc->GetViewportOrg();
        rectClip.OffsetRect(ptClip);
        rgnClip.CreateRectRgnIndirect(rectClip);
        pdc->SelectClipRgn(&rgnClip);

        TWIOnDraw(pdc);
        
        pdcBuffer->SelectClipRgn(&rgnClipOld);
    }
    return VMSR_SUCCESS;
}*/

void CKaraokeMainFrame::TWIOnDraw(CDC *pdc)
{
//    CVMSApp * pApp = (CVMSApp *) AfxGetApp();
//    int iEconoMode = pApp->GetEconoMode();
    int iEconoMode = CSavings::AppGetEconoMode();
    CDC * pDCBuffer = pdc;
    if(iEconoMode & CSavings::SaveMemory ||
        iEconoMode & CSavings::SaveProcessing)
    {
        // transparent rendering not supported in saving mode
        ASSERT(FALSE);
        return;
        pDCBuffer = pdc;
    }

    CRect rectClient;
    GetClientRect(rectClient);
    CRect rectClipBox;
    pDCBuffer->GetClipBox(rectClipBox);
    if(rectClipBox.IsRectNull())
    {
        return;
        GetClientRect(rectClipBox);
    }
    if(!(iEconoMode & CSavings::SaveMemory ||
        iEconoMode & CSavings::SaveProcessing))
    {
	    // TODO: Add your message handler code here
//		CVMSApp * pApp = (CVMSApp *) AfxGetApp();
//        CRect rectSrc;
  //      GetWindowRect(rectSrc);
    //    pParentView->ScreenToClient(rectSrc);
        CImaging * pImaging = CImaging::AppGetImaging();
        //dc.BitBlt(0 , 0 , rectClient.Width(), rectClient.Height(), &pParentView->m_dcBack, rectSrc.left, rectSrc.top, SRCCOPY);
//        CRgn rgnClipBox;
  //      rgnClipBox.CreateRectRgnIndirect(rectClipBox);
        TRACE(_T("CKaraokeMainFrame::OnDrawTransparent\n"));
		TRACE(_T("rect.left  : %d, "), rectClipBox.left);
		TRACE(_T("rect.top   : %d, "), rectClipBox.top);
		TRACE(_T("rect.right : %d, "), rectClipBox.right);
		TRACE(_T("rect.bottom: %d\n"), rectClipBox.bottom);
      //  CRect rectSrcClipBox = rectClipBox;
        //rectSrcClipBox += rectSrc.TopLeft();
//        pDCBuffer->BitBlt(
  //          rectClipBox.left, rectClipBox.top,
    //        rectClipBox.Width(), rectClipBox.Height(),
      //      &pParentView->m_dcBuffer,
        //    rectSrcClipBox.left, rectSrcClipBox.top,
          //  SRCCOPY);
        pImaging->ColorBlend(
            pDCBuffer->GetSafeHdc(),
            rectClipBox.left, rectClipBox.top,
            rectClipBox.Width(), rectClipBox.Height(),
            RGB(255,255,255), 127);
    }
    else
    {
        pDCBuffer->FillSolidRect(rectClipBox, GetSysColor(COLOR_WINDOW));
        pDCBuffer->SelectClipRgn(NULL);
    }
//    CPlaylistFrame * pParentFrame = GetParentPlaylistFrame();
  //  if(pParentFrame != NULL)
    //{
    //    dc.FillSolidRect(rectClient, GetSysColor(COLOR_WINDOW));

//    }
    CRect rectD = rectClient;
    CPen * ppenOriginal = pDCBuffer->GetCurrentPen();
    CBrush * pbrushOriginal = pDCBuffer->GetCurrentBrush();
    int iOriginalBkMode = pDCBuffer->GetBkMode();


    pDCBuffer->SetBkMode(TRANSPARENT);
    HICON hIcon = GetIcon(false);
    
    DrawIconEx(pDCBuffer->GetSafeHdc(),
        m_pointWindowIcon.x, m_pointWindowIcon.y,
        hIcon, 16, 16, 0, NULL, DI_NORMAL);

    CString strWindowText;
    GetWindowText(strWindowText);
    //CRect rectWindowText;
    //rectWindowText.left = m_iMargin;
    //rectWindowText.top = m_iMargin;
    //rectWindowText.right = m_iMargin;

    CFont * lpfontOld = pDCBuffer->GetCurrentFont();

//   	CVMSApp * pApp = (CVMSApp *) AfxGetApp();
    CFontCentral * pfontcentral = CFontCentral::AppGetFontCentral();
    CXfplayerFont * lpfont = pfontcentral->GetSongLabelFont();
    pDCBuffer->SelectObject(lpfont->GetFont());
    pDCBuffer->DrawText(strWindowText, m_rectWindowText, DT_LEFT | DT_TOP);

    CBrush brushNull;
    brushNull.CreateStockObject(NULL_BRUSH);
    pDCBuffer->SelectObject(&m_penDkShadow1);
    pDCBuffer->SelectObject(&brushNull);

    CBaseRect rectA = rectClient;
    CBaseRect rectClientB = rectClient;

    rectClientB.bottom--;
    rectClientB.right--;
    
    rectA.top++;
    rectA.bottom--;
    rectA.left++;
    rectA.right--;
    pDCBuffer->Rectangle(rectA);

    rectA.top++;
    rectA.bottom--;
    rectA.left++;
    rectA.right--;
    pDCBuffer->Rectangle(rectA);

    rectA.top++;
    rectA.bottom--;
    rectA.left++;
    rectA.right--;
    pDCBuffer->Rectangle(rectA);

    
    CPoint ptCenter = rectA.CenterPoint();
    
    CBaseRect rectB;

    rectB.top = rectClient.top;
    rectB.left = ptCenter.x - 8;
    rectB.right = ptCenter.x + 8;
    rectB.bottom = rectB.top + 5;
    
    pDCBuffer->Draw3dRect(rectB, GetSysColor(COLOR_BTNFACE), GetSysColor(COLOR_3DDKSHADOW));

    rectB.top++;
    rectB.bottom--;
    rectB.left++;
    rectB.right--;

    pDCBuffer->Draw3dRect(rectB, GetSysColor(COLOR_BTNHILIGHT), GetSysColor(COLOR_BTNSHADOW));

    rectB.top++;
    rectB.bottom--;
    rectB.left++;
    rectB.right--;

    pDCBuffer->FillSolidRect(rectB, GetSysColor(COLOR_BTNFACE));


    rectB.bottom = rectClient.bottom;
    rectB.left = ptCenter.x - 8;
    rectB.right = ptCenter.x + 8;
    rectB.top = rectB.bottom - 5;
    
    pDCBuffer->Draw3dRect(rectB, GetSysColor(COLOR_BTNFACE), GetSysColor(COLOR_3DDKSHADOW));

    rectB.top++;
    rectB.bottom--;
    rectB.left++;
    rectB.right--;

    pDCBuffer->Draw3dRect(rectB, GetSysColor(COLOR_BTNHILIGHT), GetSysColor(COLOR_BTNSHADOW));

    rectB.top++;
    rectB.bottom--;
    rectB.left++;
    rectB.right--;

    pDCBuffer->FillSolidRect(rectB, GetSysColor(COLOR_BTNFACE));

    rectB.top = ptCenter.y - 8;
    rectB.left = rectClient.left;
    rectB.right = rectClient.left + 5;
    rectB.bottom = ptCenter.y + 8;
    
    pDCBuffer->Draw3dRect(rectB, GetSysColor(COLOR_BTNFACE), GetSysColor(COLOR_3DDKSHADOW));

    rectB.top++;
    rectB.bottom--;
    rectB.left++;
    rectB.right--;
    
    pDCBuffer->Draw3dRect(rectB, GetSysColor(COLOR_BTNHILIGHT), GetSysColor(COLOR_BTNSHADOW));

    rectB.top++;
    rectB.bottom--;
    rectB.left++;
    rectB.right--;

    pDCBuffer->FillSolidRect(rectB, GetSysColor(COLOR_BTNFACE));

    rectB.top = ptCenter.y - 8;
    rectB.right = rectClient.right;
    rectB.left = rectClient.right - 5;
    rectB.bottom = ptCenter.y + 8;
    
    pDCBuffer->Draw3dRect(rectB, GetSysColor(COLOR_BTNFACE), GetSysColor(COLOR_3DDKSHADOW));

    rectB.top++;
    rectB.bottom--;
    rectB.left++;
    rectB.right--;

    pDCBuffer->Draw3dRect(rectB, GetSysColor(COLOR_BTNHILIGHT), GetSysColor(COLOR_BTNSHADOW));

    rectB.top++;
    rectB.bottom--;
    rectB.left++;
    rectB.right--;

    pDCBuffer->FillSolidRect(rectB, GetSysColor(COLOR_BTNFACE));

    ///////////////////////////////////////////////////
    //
    //  Pen COLOR_BTNHILIGHT
    //
    ///////////////////////////////////////////////////

    pDCBuffer->SelectObject(&m_penHilight1);

    rectA = rectClientB;

    rectA.top++;
    rectA.left++;
    rectA.bottom--;
    rectA.right--;

    CPoint ptA = rectA.TopLeft();
    ptA.y += 15;
    CPoint ptB = rectA.TopLeft();
    CPoint ptC = rectA.TopLeft();
    ptC.x += 15;
    pDCBuffer->MoveTo(ptA);
    pDCBuffer->LineTo(ptB);
    pDCBuffer->LineTo(ptC);

    ptA = rectA.TopRight();
    ptA.x -= 15;
    ptB = rectA.TopRight();
    pDCBuffer->MoveTo(ptA);
    pDCBuffer->LineTo(ptB);

    ptA = rectA.BottomLeft();
    ptA.y -= 15;
    ptB = rectA.BottomLeft();
    pDCBuffer->MoveTo(ptA);
    pDCBuffer->LineTo(ptB);

    rectA.top += 2;
    rectA.left += 2;
    rectA.bottom -= 2;
    rectA.right -= 2;

    ptB = rectA.TopRight();
    ptC = rectA.TopRight();
    ptC.y += 13;
    pDCBuffer->MoveTo(ptB);
    pDCBuffer->LineTo(ptC);

    ptA = rectA.BottomRight();
    ptA.y -= 13;
    ptB = rectA.BottomRight();
    ptC = rectA.BottomRight();
    ptC.x -= 13;
    pDCBuffer->MoveTo(ptA);
    pDCBuffer->LineTo(ptB);
    pDCBuffer->LineTo(ptC);

    ptB = rectA.BottomLeft();
    ptC = rectA.BottomLeft();
    ptC.x += 13;
    pDCBuffer->MoveTo(ptB);
    pDCBuffer->LineTo(ptC);


    ///////////////////////////////////////////////////
    //
    //  Pen COLOR_BTNFACE
    //
    ///////////////////////////////////////////////////


    pDCBuffer->SelectObject(&m_penFace1);

    // Most external rectangle

    rectA = rectClientB;

    ptA = rectA.TopLeft();
    ptA.y += 16;
    ptB = rectA.TopLeft();
    ptC = rectA.TopLeft();
    ptC.x += 16;
    pDCBuffer->MoveTo(ptA);
    pDCBuffer->LineTo(ptB);
    pDCBuffer->LineTo(ptC);

    ptA = rectA.TopRight();
    ptA.x -= 16;
    ptB = rectA.TopRight();
    pDCBuffer->MoveTo(ptA);
    pDCBuffer->LineTo(ptB);

    ptA = rectA.BottomLeft();
    ptA.y -= 16;
    ptB = rectA.BottomLeft();
    pDCBuffer->MoveTo(ptA);
    pDCBuffer->LineTo(ptB);

    // Most internal rectangle

    rectA.top += 4;
    rectA.left += 4;
    rectA.bottom -= 4;
    rectA.right -= 4;

    ptB = rectA.TopRight();
    ptC = rectA.TopRight();
    ptC.y += 12;
    pDCBuffer->MoveTo(ptB);
    pDCBuffer->LineTo(ptC);

    ptA = rectA.BottomRight();
    ptA.y -= 12;
    ptB = rectA.BottomRight();
    ptC = rectA.BottomRight();
    ptC.x -= 12;
    pDCBuffer->MoveTo(ptA);
    pDCBuffer->LineTo(ptB);
    pDCBuffer->LineTo(ptC);

    ptB = rectA.BottomLeft();
    ptC = rectA.BottomLeft();
    ptC.x += 12;
    pDCBuffer->MoveTo(ptB);
    pDCBuffer->LineTo(ptC);


    // Midle Rectangle

    rectA = rectClientB;

    rectA.top += 2;
    rectA.left += 2;
    rectA.bottom -= 2;
    rectA.right -= 2;

    ptA = rectA.TopLeft();
    ptA.y += 14;
    ptB = rectA.TopLeft();
    ptC = rectA.TopLeft();
    ptC.x += 14;
    pDCBuffer->MoveTo(ptA);
    pDCBuffer->LineTo(ptB);
    pDCBuffer->LineTo(ptC);

    ptA = rectA.TopRight();
    ptA.x -= 14;
    ptB = rectA.TopRight();
    ptC = rectA.TopRight();
    ptC.y += 14;
    pDCBuffer->MoveTo(ptA);
    pDCBuffer->LineTo(ptB);
    pDCBuffer->LineTo(ptC);

    ptA = rectA.BottomRight();
    ptA.y -= 14;
    ptB = rectA.BottomRight();
    ptC = rectA.BottomRight();
    ptC.x -= 14;
    pDCBuffer->MoveTo(ptA);
    pDCBuffer->LineTo(ptB);
    pDCBuffer->LineTo(ptC);

    ptA = rectA.BottomLeft();
    ptA.y -= 14;
    ptB = rectA.BottomLeft();
    ptC = rectA.BottomLeft();
    ptC.x += 14;
    pDCBuffer->MoveTo(ptA);
    pDCBuffer->LineTo(ptB);
    pDCBuffer->LineTo(ptC);


    ///////////////////////////////////////////////////
    //
    //  Pen COLOR_BTNSHADOW
    //
    ///////////////////////////////////////////////////

    pDCBuffer->SelectObject(&m_penShadow1);

    rectA = rectClientB;

    rectA.top++;
    rectA.left++;
    rectA.bottom--;
    rectA.right--;

    ptB = rectA.TopRight();
    ptC = rectA.TopRight();
    ptC.y += 15;
    pDCBuffer->MoveTo(ptB);
    pDCBuffer->LineTo(ptC);

    ptA = rectA.BottomRight();
    ptA.y -= 15;
    ptB = rectA.BottomRight();
    ptC = rectA.BottomRight();
    ptC.x -= 15;
    pDCBuffer->MoveTo(ptA);
    pDCBuffer->LineTo(ptB);
    pDCBuffer->LineTo(ptC);

    ptB = rectA.BottomLeft();
    ptC = rectA.BottomLeft();
    ptC.x += 15;
    pDCBuffer->MoveTo(ptB);
    pDCBuffer->LineTo(ptC);

    rectA.top += 2;
    rectA.left += 2;
    rectA.bottom -= 2;
    rectA.right -= 2;


    ptA = rectA.TopLeft();
    ptA.y += 13;
    ptB = rectA.TopLeft();
    ptC = rectA.TopLeft();
    ptC.x += 13;
    pDCBuffer->MoveTo(ptA);
    pDCBuffer->LineTo(ptB);
    pDCBuffer->LineTo(ptC);

    ptA = rectA.TopRight();
    ptA.x -= 13;
    ptB = rectA.TopRight();
    pDCBuffer->MoveTo(ptA);
    pDCBuffer->LineTo(ptB);

    ptA = rectA.BottomLeft();
    ptA.y -= 13;
    ptB = rectA.BottomLeft();
    pDCBuffer->MoveTo(ptA);
    pDCBuffer->LineTo(ptB);


    ///////////////////////////////////////////////////
    //
    //  Pen COLOR_3DDKSHADOW
    //
    ///////////////////////////////////////////////////

    pDCBuffer->SelectObject(&m_penDkShadow1);

    rectA = rectClientB;

    ptB = rectA.TopRight();
    ptC = rectA.TopRight();
    ptC.y += 16;
    pDCBuffer->MoveTo(ptB);
    pDCBuffer->LineTo(ptC);

    ptA = rectA.BottomRight();
    ptA.y -= 16;
    ptB = rectA.BottomRight();
    ptC = rectA.BottomRight();
    ptC.x -= 16;
    pDCBuffer->MoveTo(ptA);
    pDCBuffer->LineTo(ptB);
    pDCBuffer->LineTo(ptC);

    ptB = rectA.BottomLeft();
    ptC = rectA.BottomLeft();
    ptC.x += 16;
    pDCBuffer->MoveTo(ptB);
    pDCBuffer->LineTo(ptC);

    rectA.top += 4;
    rectA.left += 4;
    rectA.bottom -= 4;
    rectA.right -= 4;


    ptA = rectA.TopLeft();
    ptA.y += 12;
    ptB = rectA.TopLeft();
    ptC = rectA.TopLeft();
    ptC.x += 12;
    pDCBuffer->MoveTo(ptA);
    pDCBuffer->LineTo(ptB);
    pDCBuffer->LineTo(ptC);

    ptA = rectA.TopRight();
    ptA.x -= 12;
    ptB = rectA.TopRight();
    pDCBuffer->MoveTo(ptA);
    pDCBuffer->LineTo(ptB);

    ptA = rectA.BottomLeft();
    ptA.y -= 12;
    ptB = rectA.BottomLeft();
    pDCBuffer->MoveTo(ptA);
    pDCBuffer->LineTo(ptB);


    ///////////////////////////////////////////////////
    //
    //  Pen COLOR_BTNHILIGHT
    //
    ///////////////////////////////////////////////////

    pDCBuffer->SelectObject(&m_penHilight1);

    ptA.x = rectClientB.right - 15;
    ptA.y = rectClientB.top + 1;
    ptB.x = rectClientB.right - 15;
    ptB.y = rectClientB.top + 4;
    pDCBuffer->MoveTo(ptA);
    pDCBuffer->LineTo(ptB);

    ptA.x = rectClientB.right - 4;
    ptA.y = rectClientB.bottom - 15;
    ptB.x = rectClientB.right - 1;
    ptB.y = rectClientB.bottom - 15;
    pDCBuffer->MoveTo(ptB);
    pDCBuffer->LineTo(ptA);

    ptA.x = rectClientB.right - 15;
    ptA.y = rectClientB.bottom - 4;
    ptB.x = rectClientB.right - 15;
    ptB.y = rectClientB.bottom - 1;
    pDCBuffer->MoveTo(ptB);
    pDCBuffer->LineTo(ptA);

    ptA.x = rectClientB.left + 1;
    ptA.y = rectClientB.bottom - 15;
    ptB.x = rectClientB.left + 4;
    ptB.y = rectClientB.bottom - 15;
    pDCBuffer->MoveTo(ptA);
    pDCBuffer->LineTo(ptB);

    ///////////////////////////////////////////////////
    //
    //  Pen COLOR_BTNFACE
    //
    ///////////////////////////////////////////////////


    pDCBuffer->SelectObject(&m_penFace1);

    // Details

    ptA.x = rectClientB.right - 16;
    ptA.y = rectClientB.top;
    ptB.x = rectClientB.right - 16;
    ptB.y = rectClientB.top + 5;
    pDCBuffer->MoveTo(ptA);
    pDCBuffer->LineTo(ptB);

    ptA.x = rectClientB.right - 5;
    ptA.y = rectClientB.bottom - 16;
    ptB.x = rectClientB.right;
    ptB.y = rectClientB.bottom - 16;
    pDCBuffer->MoveTo(ptA);
    pDCBuffer->LineTo(ptB);

    ptA.x = rectClientB.right - 16;
    ptA.y = rectClientB.bottom - 5;
    ptB.x = rectClientB.right - 16;
    ptB.y = rectClientB.bottom;
    pDCBuffer->MoveTo(ptA);
    pDCBuffer->LineTo(ptB);

    ptA.x = rectClientB.left;
    ptA.y = rectClientB.bottom - 16;
    ptB.x = rectClientB.left + 5;
    ptB.y = rectClientB.bottom - 16;
    pDCBuffer->MoveTo(ptA);
    pDCBuffer->LineTo(ptB);


    ///////////////////////////////////////////////////
    //
    //  Pen COLOR_BTNSHADOW
    //
    ///////////////////////////////////////////////////

    pDCBuffer->SelectObject(&m_penShadow1);
    
    // Details

    ptA.x = rectClientB.left + 15;
    ptA.y = rectClientB.top + 1;
    ptB.x = rectClientB.left + 15;
    ptB.y = rectClientB.top + 4;
    pDCBuffer->MoveTo(ptB);
    pDCBuffer->LineTo(ptA);

    ptA.x = rectClientB.left + 1;
    ptA.y = rectClientB.top + 15;
    ptB.x = rectClientB.left + 4;
    ptB.y = rectClientB.top + 15;
    pDCBuffer->MoveTo(ptB);
    pDCBuffer->LineTo(ptA);

    ptA.x = rectClientB.left + 15;
    ptA.y = rectClientB.bottom - 4;
    ptB.x = rectClientB.left + 15;
    ptB.y = rectClientB.bottom - 1;
    pDCBuffer->MoveTo(ptA);
    pDCBuffer->LineTo(ptB);

    ptA.x = rectClientB.right - 4;
    ptA.y = rectClientB.top - 15;
    ptB.x = rectClientB.right - 1;
    ptB.y = rectClientB.top - 15;
    pDCBuffer->MoveTo(ptA);
    pDCBuffer->LineTo(ptB);

    ///////////////////////////////////////////////////
    //
    //  Pen COLOR_3DDKSHADOW
    //
    ///////////////////////////////////////////////////

    pDCBuffer->SelectObject(&m_penDkShadow1);

    // Details

    ptA.x = rectClientB.left + 16;
    ptA.y = rectClientB.top;
    ptB.x = rectClientB.left + 16;
    ptB.y = rectClientB.top + 5;
    pDCBuffer->MoveTo(ptA);
    pDCBuffer->LineTo(ptB);

    ptA.x = rectClientB.left;
    ptA.y = rectClientB.top + 16;
    ptB.x = rectClientB.left + 5;
    ptB.y = rectClientB.top + 16;
    pDCBuffer->MoveTo(ptA);
    pDCBuffer->LineTo(ptB);

    ptA.x = rectClientB.left + 16;
    ptA.y = rectClientB.bottom - 5;
    ptB.x = rectClientB.left + 16;
    ptB.y = rectClientB.bottom;
    pDCBuffer->MoveTo(ptB);
    pDCBuffer->LineTo(ptA);

    ptA.x = rectClientB.right - 5;
    ptA.y = rectClientB.top + 16;
    ptB.x = rectClientB.right;
    ptB.y = rectClientB.top + 16;
    pDCBuffer->MoveTo(ptB);
    pDCBuffer->LineTo(ptA);

    if(!(iEconoMode & CSavings::SaveMemory ||
        iEconoMode & CSavings::SaveProcessing))
    {
//        GetChildrenClip();
  //      dc.SelectClipRgn(&m_rgnChildren, RGN_COPY);
    //    dc.BitBlt(
      //      rectClipBox.left, rectClipBox.top,
        //    rectClipBox.Width(), rectClipBox.Height(),
          //  pDCBuffer,
            //rectClipBox.left, rectClipBox.top,
            //SRCCOPY);
    }

    pDCBuffer->SelectObject(lpfontOld);
    pDCBuffer->SelectObject(ppenOriginal);
    pDCBuffer->SelectObject(pbrushOriginal);
    pDCBuffer->SetBkMode(iOriginalBkMode);
	// Do not call CFrameWnd::OnPaint() for painting messages

}

void CKaraokeMainFrame::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CFrameWnd::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here


}

BOOL CKaraokeMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
//    if(!m_pMainWnd->Create(
  //      NULL, 
    //    NULL,
      //  WS_CHILD
        //| WS_VISIBLE,
//        CRect(0, 0, 0, 0),
  //      this,
    //    NULL, 
      //  0,
        //pContext))
        //return FALSE;
    //m_pMainWnd->SetDlgCtrlID(AFX_IDW_PANE_FIRST);

    return TRUE;
//	return CFrameWnd::OnCreateClient(lpcs, pContext);
}


BOOL CKaraokeMainFrame::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
//	return CFrameWnd::OnEraseBkgnd(pDC);
    return TRUE;
}

void CKaraokeMainFrame::OnDestroy() 
{
	CFrameWnd::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CKaraokeMainFrame::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CFrameWnd::PostNcDestroy();
}

////////////////////////////////////////////////////////////////

int CKaraokeMainFrame::GetMargin()
{
    int iMargin = m_iMargin;

    if(IsZoomed() || IsFullScreen())
    {
        iMargin = 0;
    }

    return iMargin;

}

int CKaraokeMainFrame::GetCaptionHeight()
{
    CDC * pDC = GetDC();
    
    CFont * pOriginalFont = pDC->GetCurrentFont();
    
    TEXTMETRIC tm;
    pDC->SelectObject(&m_fontMarlett);
    pDC->GetTextMetrics(&tm);

    int iMargin = GetMargin();
    int iCaptionHeight = tm.tmHeight + m_iButtonMargin * 2 + iMargin * 2 ;

    pDC->SelectObject(pOriginalFont);
	ReleaseDC(pDC);

    return iCaptionHeight;

}

int CKaraokeMainFrame::GetButtonSize()
{
    CDC * pDC = GetDC();

    CFont * pOriginalFont = pDC->GetCurrentFont();
    
    TEXTMETRIC tm;
    pDC->SelectObject(&m_fontMarlett);
    pDC->GetTextMetrics(&tm);
    
    int iMargin = GetMargin();
    int iButtonSize = tm.tmHeight + m_iButtonMargin * 2;
    
    pDC->SelectObject(pOriginalFont);
	ReleaseDC(pDC);

    return iButtonSize;

}
