#include "StdAfx.h"



#pragma warning(disable: 4706) // assignment within conditional

/////////////////////////////////////////////////////////////////////////////
// CMiniFrameWnd

// // BEGIN_MESSAGE_MAP(CMiniFrameWnd, frame_window)
   //{{AFX_MSG_MAP(CMiniFrameWnd)
/* xxx   ON_WM_NCACTIVATE()
   ON_WM_NCHITTEST()
   ON_WM_GETMINMAXINFO()
   ON_WM_NCCREATE()
   ON_MESSAGE(WM_FLOATSTATUS, &CMiniFrameWnd::OnFloatStatus)
   ON_MESSAGE(WM_QUERYCENTERWND, &CMiniFrameWnd::OnQueryCenterWnd) */
   //}}AFX_MSG_MAP
// // END_MESSAGE_MAP()


CMiniFrameWnd::CMiniFrameWnd()
{
   m_bActive = FALSE;
}

CMiniFrameWnd::~CMiniFrameWnd()
{
   DestroyWindow();
}

BOOL CMiniFrameWnd::create(const char * lpClassName, const char * lpszWindowName,
   DWORD dwStyle, const RECT& rect, virtual_user_interface* pParentWnd, UINT nID)
{
   return CMiniFrameWnd::CreateEx(0, lpClassName, lpszWindowName, dwStyle,
      rect, pParentWnd, nID);
}

BOOL CMiniFrameWnd::CreateEx(DWORD dwExStyle, const char * lpClassName,
   const char * lpszWindowName, DWORD dwStyle, const RECT& rect,
   virtual_user_interface* pParentWnd, UINT nID)
{
   UNREFERENCED_PARAMETER(dwExStyle);
   UNREFERENCED_PARAMETER(lpClassName);
   UNREFERENCED_PARAMETER(dwStyle);
   UNREFERENCED_PARAMETER(rect);
   UNREFERENCED_PARAMETER(pParentWnd);
   UNREFERENCED_PARAMETER(nID);
   m_strCaption = lpszWindowName;
   return FALSE;
/* trans   return virtual_user_interface::CreateEx(dwExStyle, lpClassName ? lpClassName :
      System.RegisterWndClass(CS_DBLCLKS, ::LoadCursor(NULL, IDC_ARROW)),
      lpszWindowName, dwStyle, rect.left, rect.top, rect.right - rect.left,
      rect.bottom - rect.top, pParentWnd, (HMENU)(UINT_PTR)nID);*/
}

/////////////////////////////////////////////////////////////////////////////
// CMiniFrameWnd message handlers

BOOL CMiniFrameWnd::OnNcCreate(LPCREATESTRUCT lpcs)
{
   UNREFERENCED_PARAMETER(lpcs);
/* trans   if (!frame_window::OnNcCreate(lpcs))
      return FALSE; 

   if (GetStyle() & MFS_SYNCACTIVE)
   {
      // syncronize activation state with top level parent
      virtual_user_interface* pParentWnd = EnsureTopLevelParent();
      virtual_user_interface* pActiveWnd = GetForegroundWindow();
      BOOL bActive = (pParentWnd == pActiveWnd) ||
         (pParentWnd->GetLastActivePopup() == pActiveWnd &&
          pActiveWnd->SendMessage(WM_FLOATSTATUS, FS_SYNCACTIVE) != 0);

      // the WM_FLOATSTATUS does the actual work
      SendMessage(WM_FLOATSTATUS, bActive ? FS_ACTIVATE : FS_DEACTIVATE);
   }*/

   return TRUE;
}

BOOL CMiniFrameWnd::PreCreateWindow(CREATESTRUCT& cs)
{
   // WS_4THICKFRAME and MFS_THICKFRAME imply WS_THICKFRAME
   if (cs.style & (MFS_4THICKFRAME | MFS_THICKFRAME))
      cs.style |= WS_THICKFRAME;

   // WS_CAPTION implies WS_EX_TOOLWINDOW
   if (cs.style & WS_CAPTION)
      cs.dwExStyle |= WS_EX_TOOLWINDOW;

   VERIFY(frame_window::PreCreateWindow(cs));
   cs.dwExStyle &= ~(WS_EX_CLIENTEDGE);

   return TRUE;
}

void CMiniFrameWnd::OnGetMinMaxInfo(MINMAXINFO* pMMI)
{
   UNREFERENCED_PARAMETER(pMMI);
   // allow Windows to fill in the defaults
/* trans   frame_window::OnGetMinMaxInfo(pMMI);

   // don't allow sizing smaller than the non-client area
   rect rectWindow, rectClient;
   GetWindowRect(rectWindow);
   GetClientRect(rectClient);
   pMMI->ptMinTrackSize.x = rectWindow.width() - rectClient.right;
   pMMI->ptMinTrackSize.y = rectWindow.height() - rectClient.bottom;*/
}

BOOL CMiniFrameWnd::OnNcActivate(BOOL /* bActive */)
{
   if ((GetStyle() & MFS_SYNCACTIVE) == 0)
      return Default() != 0;

/* trans   if(m_nFlags & WF_KEEPMINIACTIVE)
      return FALSE; */

   return TRUE;
}

LRESULT CMiniFrameWnd::OnNcHitTest(point point)
{
   UNREFERENCED_PARAMETER(point);
//   DWORD dwStyle = GetStyle();
   rect rectWindow;
   GetWindowRect(&rectWindow);

   size sizeFrame(GetSystemMetrics(SM_CXFRAME),
      GetSystemMetrics(SM_CYFRAME));

/* trans   LRESULT nHit = frame_window::OnNcHitTest(point);

   // MFS_BLOCKSYSMENU translates system menu hit to caption hit
   if (dwStyle & MFS_BLOCKSYSMENU)
   {
      if (nHit == HTSYSMENU)
         nHit = HTCAPTION;
      if (GetKeyState(VK_RBUTTON) < 0)
         return HTNOWHERE;
   }

   if ((nHit < HTSIZEFIRST || nHit > HTSIZELAST) && nHit != HTGROWBOX)
      return nHit;

   // MFS_MOVEFRAME translates all size requests to move requests
   if (dwStyle & MFS_MOVEFRAME)
      return HTCAPTION;

   // MFS_4THICKFRAME does not allow diagonal sizing
   rectWindow.inflate(-sizeFrame.cx, -sizeFrame.cy);
   if (dwStyle & MFS_4THICKFRAME)
   {
      switch (nHit)
      {
      case HTTOPLEFT:
         return point.y < rectWindow.top ? HTTOP : HTLEFT;
      case HTTOPRIGHT:
         return point.y < rectWindow.top ? HTTOP : HTRIGHT;
      case HTBOTTOMLEFT:
         return point.y > rectWindow.bottom ? HTBOTTOM : HTLEFT;
      case HTGROWBOX:
      case HTBOTTOMRIGHT:
         return point.y > rectWindow.bottom ? HTBOTTOM : HTRIGHT;
      }
   }
   return nHit;    // no special translation*/
   return 0;
}

void CMiniFrameWnd::OnSysCommand(UINT nID, LPARAM lParam)
{
   UNREFERENCED_PARAMETER(nID);
   UNREFERENCED_PARAMETER(lParam);
/* trans   DWORD dwStyle = GetStyle();
   if ((dwStyle & WS_POPUP) &&
      ((nID & 0xFFF0) != SC_CLOSE ||
      (GetKeyState(VK_F4) < 0 && GetKeyState(VK_MENU) < 0 &&
      (dwStyle & MFS_SYNCACTIVE))))
   {
      if (HandleFloatingSysCommand(nID, lParam))
         return;
   }
   frame_window::OnSysCommand(nID, lParam); */
}

void PASCAL CMiniFrameWnd::CalcBorders(
   LPRECT lpClientRect, DWORD dwStyle, DWORD dwExStyle)
{
   UNUSED_ALWAYS(dwExStyle);

   AdjustWindowRectEx(lpClientRect, dwStyle, FALSE, WS_EX_PALETTEWINDOW);
}

LRESULT CMiniFrameWnd::OnFloatStatus(WPARAM wParam, LPARAM)
{
   // these asserts make sure no conflicting actions are requested
   ASSERT(!((wParam & FS_SHOW) && (wParam & FS_HIDE)));
   ASSERT(!((wParam & FS_ENABLE) && (wParam & FS_DISABLE)));
   ASSERT(!((wParam & FS_ACTIVATE) && (wParam & FS_DEACTIVATE)));

   // FS_SYNCACTIVE is used to detect MFS_SYNCACTIVE windows
   LRESULT lResult = 0;
   if ((GetStyle() & MFS_SYNCACTIVE) && (wParam & FS_SYNCACTIVE))
      lResult = 1;

   if (wParam & (FS_SHOW|FS_HIDE))
   {
      SetWindowPos(NULL, 0, 0, 0, 0,
         ((wParam & FS_SHOW) ? SWP_SHOWWINDOW : SWP_HIDEWINDOW) | SWP_NOZORDER |
         SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
   }
   if (wParam & (FS_ENABLE|FS_DISABLE))
      EnableWindow((wParam & FS_ENABLE) != 0);

   if ((wParam & (FS_ACTIVATE|FS_DEACTIVATE)) &&
      GetStyle() & MFS_SYNCACTIVE)
   {
      ModifyStyle(MFS_SYNCACTIVE, 0);
      SendMessage(WM_NCACTIVATE, (wParam & FS_ACTIVATE) != 0);
      ModifyStyle(0, MFS_SYNCACTIVE);
   }

   return lResult;
}

LRESULT CMiniFrameWnd::OnQueryCenterWnd(WPARAM, LPARAM)
{
   // forward WM_QUERYCENTERWND to parent ::ca::window
/* trans    HWND hWndParent = ::GetParent(get_handle());
   LRESULT lResult = ::SendMessage(hWndParent, WM_QUERYCENTERWND, 0, 0);
   if (lResult == 0)
      lResult = (LRESULT)hWndParent;
   return lResult;*/
   return 0;
}


// IMPLEMENT_DYNCREATE(CMiniFrameWnd, frame_window)

////////////////////////////////////////////////////////////////////////////
