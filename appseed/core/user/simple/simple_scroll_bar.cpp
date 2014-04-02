#include "framework.h"


simple_scroll_bar::simple_scroll_bar(sp(base_application) papp) :
   element(papp),
   ::user::interaction(papp),
   m_penDraw(allocer()),
   m_brushDraw(allocer()),
   m_rgnA(allocer()), // região da primeira seta
   m_rgnB(allocer()) // região da segunda seta
{
   //m_brushNull->CreateStockObject(NULL_BRUSH);

   m_bTracking          = false;
   m_scrollinfo.nMin    = 0;
   m_scrollinfo.nMax    = 100;
   m_scrollinfo.nPage   = 10;
   m_scrollinfo.nPos    = 0;
   m_etranslucency      = TranslucencyPresent;
}

simple_scroll_bar::~simple_scroll_bar()
{
}


void simple_scroll_bar::install_message_handling(::message::dispatch * pinterface)
{
   ::user::interaction::install_message_handling(pinterface);
   IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &simple_scroll_bar::_001OnMouseMove);
   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &simple_scroll_bar::_001OnLButtonDown);
   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &simple_scroll_bar::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_HSCROLL, pinterface, this, &simple_scroll_bar::_001OnHScroll);
   IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &simple_scroll_bar::_001OnSize);
   IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &simple_scroll_bar::_001OnTimer);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &simple_scroll_bar::_001OnCreate);
   IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &simple_scroll_bar::_001OnShowWindow);
   IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &simple_scroll_bar::_001OnDestroy);
}

bool simple_scroll_bar::create(const char * lpszClassName, const char * lpszWindowName, uint32_t dwStyle, const RECT& rect, sp(::user::interaction) pParentWnd, UINT nID, sp(::create_context) pContext)
{
   return ::user::interaction::create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

bool simple_scroll_bar::create(e_orientation eorientation, uint32_t dwStyle, rect &rect, sp(::user::interaction)pParentWnd, UINT nID)
{
   if(!::user::scroll_bar::create(eorientation, dwStyle, rect, pParentWnd, nID))
      return FALSE;
   return TRUE;
}

void simple_scroll_bar::_001OnMouseMove(signal_details * pobj)
{

   SCAST_PTR(::message::mouse, pmouse, pobj)

   point pt = pmouse->m_pt;

   ScreenToClient(&pt);

   if(m_bTracking)
   {

      SetTrackingPos(pt);
      send_scroll_message(SB_THUMBPOSITION);
      pmouse->set_lresult(1);
      pmouse->m_bRet = true;
   }
   else
   {
      rect rectTrack;
      GetTrackRect(rectTrack);
      rect rectPageA;
      rect rectClient;
      GetClientRect(rectClient);
      GetPageARect(rectClient, rectTrack, rectPageA);
      rect rectPageB;
      GetPageBRect(rectClient, rectTrack, rectPageB);
      pmouse->m_bRet = false;
      if(rectTrack.contains(pt))
      {
         pmouse->m_bRet = true;
      }
      else if(m_rgnA->contains(pt))
      {
         pmouse->m_bRet = true;
      }
      else if(m_rgnB->contains(pt))
      {
         pmouse->m_bRet = true;
      }
      else if(rectPageA.contains(pt))
      {
         pmouse->m_bRet = true;
      }
      else if(rectPageB.contains(pt))
      {
         pmouse->m_bRet = true;
      }

   }

   if(pmouse->m_bRet)
   {

      pmouse->m_ecursor = ::visual::cursor_arrow;

   }

}

void simple_scroll_bar::_001OnLButtonDown(signal_details * pobj)
{
   SCAST_PTR(::message::mouse, pmouse, pobj)
      point pt = pmouse->m_pt;
   ScreenToClient(&pt);
   rect rectTrack;
   GetTrackRect(rectTrack);
   rect rectPageA;
   rect rectClient;
   GetClientRect(rectClient);
   GetPageARect(rectClient, rectTrack, rectPageA);
   rect rectPageB;
   GetPageBRect(rectClient, rectTrack, rectPageB);
   pmouse->m_bRet = false;
   if(rectTrack.contains(pt))
   {
      set_capture();
      m_bTracking = true;
      point ptTrackOffset;
      ptTrackOffset = pt;
      ptTrackOffset -= rectTrack.top_left();
      m_ptTrackOffset = ptTrackOffset;
      pmouse->m_bRet = true;
      pmouse->set_lresult(1);
   }
   else if(m_rgnA->contains(pt))
   {
      set_capture();
      ScrollLineA();
      SetTimer(100, 300, NULL);
      pmouse->m_bRet = true;
      pmouse->set_lresult(1);
   }
   else if(m_rgnB->contains(pt))
   {
      set_capture();
      ScrollLineB();
      SetTimer(200, 300, NULL);
      pmouse->m_bRet = true;
      pmouse->set_lresult(1);
   }
   else if(rectPageA.contains(pt))
   {
      if(!rectTrack.contains(pt))
      {
         set_capture();
         ScrollPageA();
         SetTimer(300, 300, NULL);
         pmouse->m_bRet = true;
         pmouse->set_lresult(1);
      }
   }
   else if(rectPageB.contains(pt))
   {
      if(!rectTrack.contains(pt))
      {
         set_capture();
         ScrollPageB();
         SetTimer(400, 300, NULL);
         pmouse->m_bRet = true;
         pmouse->set_lresult(1);
      }
   }
}

void simple_scroll_bar::_001OnLButtonUp(signal_details * pobj)
{
   SCAST_PTR(::message::mouse, pmouse, pobj)
      point pt = pmouse->m_pt;
   ScreenToClient(&pt);
   simple_scroll_bar * pcandidate =
      dynamic_cast < simple_scroll_bar * > (
      System.get_capture_uie().m_p);
   KillTimer(100);
   KillTimer(110);
   KillTimer(200);
   KillTimer(210);
   KillTimer(300);
   KillTimer(310);
   KillTimer(400);
   KillTimer(410);
   pmouse->m_bRet = false;

   if((pcandidate != NULL && pcandidate == this) || m_bTracking)
   {
      System.release_capture_uie();
      bool bWasTracking = m_bTracking;
      m_bTracking = false;
//      sp(::user::interaction) pParentWnd = get_parent();
      if(bWasTracking)
         SetTrackingPos(pt);
      send_scroll_message(SB_THUMBPOSITION);
      Redraw();
      pmouse->m_bRet = true;
      pmouse->set_lresult(1);
   }
}

bool simple_scroll_bar::GetTrackRect(LPRECT lpRect)
{
#ifdef WINDOWSEX
   rect rectClient;
   GetClientRect(rectClient);
   size sizeTrack;
   GetTrackSize(sizeTrack);
   int32_t iPos;
   if(m_bTracking)
      iPos = m_scrollinfo.nTrackPos;
   else
      iPos = m_scrollinfo.nPos;
   if(m_eorientation == orientation_horizontal)
   {
      int32_t iWidth = rectClient.width() - GetSystemMetrics(SM_CXHSCROLL) * 2 - sizeTrack.cx - 1;
      lpRect->top = rectClient.top + 2;
      lpRect->bottom = rectClient.top + sizeTrack.cy;
      if(m_scrollinfo.nMax - m_scrollinfo.nMin - m_scrollinfo.nPage == 0)
         lpRect->left = 0;
      else
         lpRect->left = GetSystemMetrics(SM_CXHSCROLL) + 1 + (iPos - m_scrollinfo.nMin) * iWidth / (m_scrollinfo.nMax - m_scrollinfo.nMin - m_scrollinfo.nPage);
      lpRect->right = lpRect->left + sizeTrack.cx;
   }
   else if(m_eorientation == orientation_vertical)
   {
      int32_t iHeight = rectClient.height() - GetSystemMetrics(SM_CYVSCROLL) * 2 - sizeTrack.cy - 1;
      if(m_scrollinfo.nMax - m_scrollinfo.nMin - m_scrollinfo.nPage == 0)
         lpRect->top = 0;
      else
         lpRect->top = GetSystemMetrics(SM_CYVSCROLL) + 1 + (iPos - m_scrollinfo.nMin) * iHeight / (m_scrollinfo.nMax - m_scrollinfo.nMin - m_scrollinfo.nPage);
      lpRect->bottom = lpRect->top + sizeTrack.cy;
      lpRect->left = rectClient.left + 1;
      lpRect->right = lpRect->left + sizeTrack.cx;
   }
#endif
   return TRUE;
}

bool simple_scroll_bar::_001GetScrollInfo(::user::scroll_info * lpsi)
{
   if(lpsi->fMask & SIF_PAGE)
   {
      lpsi->nPage = m_scrollinfo.nPage;
   }
   if(lpsi->fMask & SIF_POS)
   {
      lpsi->nPos = m_scrollinfo.nPos ;
   }
   if(lpsi->fMask & SIF_RANGE)
   {
      lpsi->nMin = m_scrollinfo.nMin;
      lpsi->nMax = m_scrollinfo.nMax;
   }
   if(lpsi->fMask & SIF_TRACKPOS)
   {
      lpsi->nTrackPos = m_scrollinfo.nTrackPos;
   }
   return TRUE;
}

bool simple_scroll_bar::_001SetScrollInfo(::user::scroll_info * lpsi, bool bRedraw)
{
   if(lpsi->fMask & SIF_PAGE)
   {
      m_scrollinfo.nPage = lpsi->nPage;
   }
   if(lpsi->fMask & SIF_RANGE)
   {
      m_scrollinfo.nMin = lpsi->nMin;
      m_scrollinfo.nMax = lpsi->nMax;
   }
   if(lpsi->fMask & SIF_POS)
   {
      m_scrollinfo.nPos = lpsi->nPos ;
      if(m_scrollinfo.nPos < m_scrollinfo.nMin)
      {
         m_scrollinfo.nPos = m_scrollinfo.nMin;
      }
      else if(m_scrollinfo.nPos > m_scrollinfo.nMax - m_scrollinfo.nPage)
      {
         m_scrollinfo.nPos = m_scrollinfo.nMax - m_scrollinfo.nPage;
      }
   }
   if(lpsi->fMask & SIF_TRACKPOS)
   {
      m_scrollinfo.nTrackPos = lpsi->nTrackPos;
   }
   if(bRedraw)
   {
      //      Redraw();
   }
   return TRUE;
   m_scrollinfo.fMask = SIF_ALL;
   // trans   ::user::interaction::SetScrollInfo(SB_CTL, &m_scrollinfo);
   return true;
}


bool simple_scroll_bar::GetTrackClientRect(LPRECT lpRect)
{
#ifdef WINDOWSEX
   rect rectClient;
   GetClientRect(rectClient);
   if(m_eorientation == orientation_horizontal)
   {
//      int32_t iWidth = rectClient.width() - GetSystemMetrics(SM_CXHSCROLL) * 2;
      lpRect->bottom = rectClient.bottom;
      lpRect->top = rectClient.top;
      lpRect->left = rectClient.left + GetSystemMetrics(SM_CXHSCROLL);
      lpRect->right = rectClient.right - GetSystemMetrics(SM_CXHSCROLL);
   }
   else if(m_eorientation == orientation_vertical)
   {
//      int32_t iWidth = rectClient.width() - GetSystemMetrics(SM_CYVSCROLL) * 2;
      lpRect->top = rectClient.top + GetSystemMetrics(SM_CYVSCROLL);
      lpRect->bottom = rectClient.bottom - GetSystemMetrics(SM_CYVSCROLL);
      lpRect->left = rectClient.left + 1;
      lpRect->right = rectClient.right - 1;
   }
#else
   throw todo(get_app());
#endif
   return TRUE;
}

int32_t simple_scroll_bar::GetTrackSize(size &size)
{
#ifdef WINDOWSEX
   rect rectClient;
   GetClientRect(rectClient);
   if(m_eorientation == orientation_horizontal)
   {
      int32_t iWidth = rectClient.width() - GetSystemMetrics(SM_CXHSCROLL) * 2;
      int32_t cx = 5;
      if(iWidth > 0)
      {
         int32_t idiff = (m_scrollinfo.nMax - m_scrollinfo.nMin);
         if(idiff == 0)
            cx = 0;
         else
            cx = m_scrollinfo.nPage * iWidth / idiff;
      }
      if(cx < 5)
         cx = 5;
      size.cx = cx;
      size.cy = rectClient.height();
   }
   else if(m_eorientation == orientation_vertical)
   {
      int32_t iHeight = rectClient.height() - GetSystemMetrics(SM_CYVSCROLL) * 2;
      size.cx = rectClient.width() - 1;
      int32_t cy = 5;
      int32_t iRange = (m_scrollinfo.nMax - m_scrollinfo.nMin);
      if( iHeight > 0)
         cy = iRange ? m_scrollinfo.nPage * iHeight / (m_scrollinfo.nMax - m_scrollinfo.nMin) : iHeight;
      if(cy < 5)
         cy = 5;
      size.cy = cy;
   }
#else
   throw todo(get_app());
#endif
   return TRUE;
}

int32_t simple_scroll_bar::SetTrackingPos(point point)
{
#ifdef WINDOWSEX
   int32_t nPos;
   size sizeTrack;
   GetTrackSize(sizeTrack);
   rect rectClient;
   GetClientRect(rectClient);
   if(m_eorientation == orientation_horizontal)
   {
      int32_t iWidth = rectClient.width() - GetSystemMetrics(SM_CXHSCROLL) * 2 - sizeTrack.cx;
      nPos = point.x - m_ptTrackOffset.x;
      nPos -= GetSystemMetrics(SM_CXHSCROLL);
      nPos *= (m_scrollinfo.nMax - m_scrollinfo.nMin  - m_scrollinfo.nPage);
      if(iWidth != 0)
         nPos /= iWidth;
      nPos += m_scrollinfo.nMin;

   }
   else if(m_eorientation == orientation_vertical)
   {
      int32_t iHeight = rectClient.height() - GetSystemMetrics(SM_CYVSCROLL) * 2 - sizeTrack.cy;
      nPos = point.y - m_ptTrackOffset.y;
      nPos -= GetSystemMetrics(SM_CXHSCROLL);
      nPos *= (m_scrollinfo.nMax - m_scrollinfo.nMin  - m_scrollinfo.nPage);
      if(iHeight != 0)
         nPos /= iHeight;
      nPos += m_scrollinfo.nMin;
   }
   else
   {
      ASSERT(FALSE);
   }
   if(nPos < m_scrollinfo.nMin)
      nPos = m_scrollinfo.nMin;
   else if(nPos > m_scrollinfo.nMax - m_scrollinfo.nPage)
      nPos = m_scrollinfo.nMax - m_scrollinfo.nPage;
   if(m_bTracking)
   {
      m_scrollinfo.nTrackPos = nPos;
   }
   else
   {
      m_scrollinfo.nPos = nPos;
   }
   m_scrollinfo.fMask = SIF_ALL;
   // trans   ::user::interaction::SetScrollInfo(SB_CTL, &m_scrollinfo);
#else
   throw todo(get_app());
#endif
   return TRUE;
}

void simple_scroll_bar::_001OnHScroll(signal_details * pobj)
{
   SCAST_PTR(::message::scroll, pscroll, pobj)
      pscroll->m_bRet = false;
}

int32_t simple_scroll_bar::_001GetScrollPos()
{
   if(m_bTracking)
      return m_scrollinfo.nTrackPos;
   else
      return m_scrollinfo.nPos;
}

void simple_scroll_bar::_001OnSize(signal_details * pobj)
{

   //SCAST_PTR(::message::size, psize, pobj)
   pobj->previous();
   // trans   ::user::interaction::OnSize(psize->m_wparam, size.cx, size.cy);

   rect rectClient;
   GetClientRect(rectClient);
   class size size = rectClient.size();

   if(m_eorientation == orientation_horizontal)
   {
      m_ptaA[0].x = 0;
      m_ptaA[0].y = size.cy / 2;
      m_ptaA[1].x = min(GetSystemMetrics(SM_CXHSCROLL), size.cx / 2);
      m_ptaA[1].y = size.cy - 1;
      m_ptaA[2].x = m_ptaA[1].x;
      m_ptaA[2].y = 1;
      m_ptaA[3].x = m_ptaA[0].x;
      m_ptaA[3].y = m_ptaA[0].y;


      m_ptaB[0].x = size.cx;
      m_ptaB[0].y = size.cy / 2;
      m_ptaB[1].x = max(size.cx - GetSystemMetrics(SM_CXHSCROLL), size.cx / 2);
      m_ptaB[1].y = 1;
      m_ptaB[2].x = m_ptaB[1].x;
      m_ptaB[2].y = size.cy - 1;
      m_ptaB[3].x = m_ptaB[0].x;
      m_ptaB[3].y = m_ptaA[0].y;
   }
   else if(m_eorientation == orientation_vertical)
   {
      m_ptaA[0].x = size.cx / 2;
      m_ptaA[0].y = 0;
      m_ptaA[1].x = 1;
      m_ptaA[1].y = min(GetSystemMetrics(SM_CYVSCROLL), size.cy / 2);
      m_ptaA[2].x = size.cx - 1;
      m_ptaA[2].y = m_ptaA[1].y;
      m_ptaA[3].x = m_ptaA[0].x;
      m_ptaA[3].y = m_ptaA[0].y;

      m_ptaB[0].x = size.cx / 2;
      m_ptaB[0].y = size.cy;
      m_ptaB[1].x = size.cx - 1;
      m_ptaB[1].y = max(size.cy - GetSystemMetrics(SM_CYVSCROLL), size.cy / 2);
      m_ptaB[2].x = 1;
      m_ptaB[2].y = m_ptaB[1].y;
      m_ptaB[3].x = m_ptaA[0].x;
      m_ptaB[3].y = m_ptaB[0].y;
   }
   else
   {
      ASSERT(FALSE);
   }

   m_rgnA->create_polygon(m_ptaA, 4, ::draw2d::fill_mode_winding);
   m_rgnB->create_polygon(m_ptaB, 4, ::draw2d::fill_mode_winding);


//   psize->m_bRet = false;
}

void simple_scroll_bar::_001OnTimer(signal_details * pobj)
{
//   return; //xxxtimer
   SCAST_PTR(::message::timer, ptimer, pobj)

      point point;
   rect rect;
   class rect rectTrack;
   class rect rectClient;
   switch(ptimer->m_nIDEvent)
   {
   case 100:
      KillTimer(ptimer->m_nIDEvent);
      SetTimer(110, 10, NULL);
   case 110:
      ScrollLineA();
      if(m_scrollinfo.nPos == m_scrollinfo.nMin)
      {
         KillTimer(110);
      }
      break;
   case 200:
      KillTimer(ptimer->m_nIDEvent);
      SetTimer(210, 10, NULL);
   case 210:
      ScrollLineB();
      if(m_scrollinfo.nPos == m_scrollinfo.nMax - m_scrollinfo.nPage)
      {
         KillTimer(210);
      }
      break;
   case 300:
      KillTimer(ptimer->m_nIDEvent);
      SetTimer(310, 10, NULL);
   case 310:
      GetCursorPos(&point);
      ScreenToClient(&point);
      GetClientRect(rectClient);
      GetTrackRect(rectTrack);
      GetPageARect(rectClient, rectTrack, rect);
      if(!rect.contains(point))
      {
         KillTimer(310);
         break;
      }
      if(m_scrollinfo.nPos == m_scrollinfo.nMin)
      {
         KillTimer(ptimer->m_nIDEvent);
         break;
      }
      ScrollPageA();
      break;
   case 400:
      KillTimer(ptimer->m_nIDEvent);
      SetTimer(410, 10, NULL);
   case 410:
      GetCursorPos(&point);
      ScreenToClient(&point);
      GetClientRect(rectClient);
      GetTrackRect(rectTrack);
      GetPageBRect(rectClient, rectTrack, rect);
      if(!rect.contains(point))
      {
         KillTimer(410);
         break;
      }
      if(m_scrollinfo.nPos == m_scrollinfo.nMax - m_scrollinfo.nPage)
      {
         KillTimer(410);
         break;
      }
      ScrollPageB();
      break;
   default:
      KillTimer(ptimer->m_nIDEvent);
      break;
   }
   ptimer->m_bRet = false;
}

int32_t simple_scroll_bar::ScrollLineA()
{
   int32_t nPos = m_scrollinfo.nPos;
   nPos-=3;
   if(nPos < m_scrollinfo.nMin)
      nPos = m_scrollinfo.nMin;
   m_scrollinfo.nPos = nPos;

   if(m_eorientation == orientation_horizontal)
   {
      send_scroll_message(SB_LINELEFT);
   }
   else
   {
      send_scroll_message(SB_LINEUP);
   }
   return true;
}

int32_t simple_scroll_bar::ScrollLineB()
{
   int32_t nPos = m_scrollinfo.nPos;
   nPos+=3;
   if(nPos > m_scrollinfo.nMax - m_scrollinfo.nPage)
      nPos = m_scrollinfo.nMax - m_scrollinfo.nPage;
   m_scrollinfo.nPos = nPos;

   if(m_eorientation == orientation_horizontal)
   {
      send_scroll_message(SB_LINERIGHT);
   }
   else
   {
      send_scroll_message(SB_LINEDOWN);
   }
   return true;
}

int32_t simple_scroll_bar::ScrollPageA()
{
//   sp(::user::interaction) pParentWnd = get_parent();
   int32_t nPos = m_scrollinfo.nPos;
   nPos-=m_scrollinfo.nPage ;
   if(nPos < m_scrollinfo.nMin)
      nPos = m_scrollinfo.nMin;
   m_scrollinfo.nPos = nPos;
   if(m_eorientation == orientation_horizontal)
   {
      send_scroll_message(SB_LINELEFT);
   }
   else
   {
      send_scroll_message(SB_LINEUP);
   }
   return true;

}

int32_t simple_scroll_bar::ScrollPageB()
{
//   sp(::user::interaction) pParentWnd = get_parent();
   int32_t nPos = m_scrollinfo.nPos;
   nPos+=m_scrollinfo.nPage ;
   if(nPos > m_scrollinfo.nMax - m_scrollinfo.nPage)
      nPos = m_scrollinfo.nMax - m_scrollinfo.nPage;
   m_scrollinfo.nPos = nPos;

   if(m_eorientation == orientation_horizontal)
   {
      send_scroll_message(SB_LINERIGHT);
   }
   else
   {
      send_scroll_message(SB_LINEDOWN);
   }
   return true;
}

//void simple_scroll_bar::OnDraw(::draw2d::graphics * pgraphics)
//{
/*    if(GetExStyle() & WS_EX_TRANSPARENT)
{
return;
}

sp(::user::interaction) pParentWnd = get_parent();
int32_t nPos = m_scrollinfo.nPos;
nPos+=m_scrollinfo.nPage;
if(nPos > m_scrollinfo.nMax - m_scrollinfo.nPage)
nPos = m_scrollinfo.nMax - m_scrollinfo.nPage;
m_scrollinfo.nPos = nPos;

if(m_eorientation == orientation_horizontal)
{
pParentWnd->SendMessage(WM_HSCROLL, MAKEWPARAM(SB_LINERIGHT, m_scrollinfo.nPos), (LPARAM) this->get_handle());
}
else
{
pParentWnd->SendMessage(WM_VSCROLL, MAKEWPARAM(SB_LINEDOWN, m_scrollinfo.nPos), (LPARAM) this->get_handle());
}*/

//}

void simple_scroll_bar::_001OnCreate(signal_details * pobj)
{
   SCAST_PTR(::message::create, pcreate, pobj)

      update_drawing_objects();

   pcreate->set_lresult(0);
}

void simple_scroll_bar::OnDisplayChange(int32_t iBitsPerPixel, size sizeScreen)
{
   UNREFERENCED_PARAMETER(iBitsPerPixel);
   UNREFERENCED_PARAMETER(sizeScreen);
}

void simple_scroll_bar::pre_translate_message(signal_details * pobj)
{

   SCAST_PTR(::message::base, pbase, pobj);

   if(pbase->m_pwnd == this)
   {
      switch(pbase->m_uiMessage)
      {
      case WM_DISPLAYCHANGE:
         OnDisplayChange((int32_t) pbase->m_wparam, size(LOWORD(pbase->m_lparam), HIWORD(pbase->m_lparam)));
         pbase->m_bRet = true;
         return;
      default:
         break;
      }
   }

   return ::user::interaction::pre_translate_message(pobj);

}

void simple_scroll_bar::UpdateBitmaps()
{

}

bool simple_scroll_bar::GetPageARect(LPRECT lpRectClient,LPRECT lpRectTrack, LPRECT lpRect)
{
//#ifdef WINDOWSEX
   if(m_eorientation == orientation_horizontal)
   {
      lpRect->left = lpRectClient->left + GetSystemMetrics(SM_CXHSCROLL);
      lpRect->top = lpRectTrack->top;
      lpRect->right = lpRectTrack->left;
      lpRect->bottom = lpRectTrack->bottom;
   }
   else if(m_eorientation == orientation_vertical)
   {
      lpRect->left = lpRectTrack->left;
      lpRect->top = lpRectClient->top + GetSystemMetrics(SM_CYVSCROLL);
      lpRect->right = lpRectTrack->right;
      lpRect->bottom = lpRectTrack->top;
   }
//#else
  // throw todo(get_app());
//#endif
   return true;
}

bool simple_scroll_bar::GetPageBRect(LPRECT lpRectClient,LPRECT lpRectTrack, LPRECT lpRect)
{
//#ifdef WINDOWSEX
   if(m_eorientation == orientation_horizontal)
   {
      lpRect->left = lpRectTrack->right;
      lpRect->top = lpRectTrack->top;
      lpRect->right = lpRectClient->right - GetSystemMetrics(SM_CXHSCROLL);
      lpRect->bottom = lpRectTrack->bottom;
   }
   else if(m_eorientation == orientation_vertical)
   {
      lpRect->left = lpRectTrack->left;
      lpRect->top = lpRectTrack->bottom;
      lpRect->right = lpRectTrack->right;
      lpRect->bottom = lpRectClient->bottom - GetSystemMetrics(SM_CYVSCROLL);
   }
//#else
  // throw todo(get_app());
//#endif
   return true;
}


int32_t simple_scroll_bar::_001SetScrollPos(int32_t iPos)
{
   m_scrollinfo.nPos = iPos ;
   if(m_scrollinfo.nPos < m_scrollinfo.nMin)
   {
      m_scrollinfo.nPos = m_scrollinfo.nMin;
   }
   else if(m_scrollinfo.nPos > m_scrollinfo.nMax - m_scrollinfo.nPage)
   {
      m_scrollinfo.nPos = m_scrollinfo.nMax - m_scrollinfo.nPage;
   }
   //Redraw();
   return true;
}


LRESULT simple_scroll_bar::OnEconoModeChange(WPARAM wParam, LPARAM lParam)
{
   UNREFERENCED_PARAMETER(wParam);
   UNREFERENCED_PARAMETER(lParam);
   update_drawing_objects();
   //Redraw();

   return true;
}

void simple_scroll_bar::update_drawing_objects()
{

}


void simple_scroll_bar::_001OnDraw(::draw2d::graphics * pdc)
{

   m_penDraw->create_solid(1, ARGB(255, 0, 0, 0));

   m_brushDraw->m_etype = ::draw2d::brush::type_null;

   pdc->SelectClipRgn(NULL);

   rect rectClient;

   GetClientRect(rectClient);

   if(System.savings().is_trying_to_save(::core::resource_processing))
   {

      pdc->FillSolidRect(rectClient, RGB(255,255,255));

   }
   else
   {
      class imaging & imaging = System.visual().imaging();
      imaging.color_blend(
         pdc,
         rectClient.left, rectClient.top,
         rectClient.width(), rectClient.height(),
         RGB(255,255,255),
         127);
   }

   pdc->SelectObject(m_penDraw);

   rect rectTrack;

   GetTrackRect(rectTrack);

   class ::rect rectWindow;

   GetWindowRect(rectWindow);

   pdc->DrawRectangle(rectTrack);

   pdc->SelectObject(m_brushDraw);
   pdc->Polygon(m_ptaA, 4);
   pdc->Polygon(m_ptaB, 4);




}

void simple_scroll_bar::_001OnShowWindow(signal_details * pobj)
{
   SCAST_PTR(::message::show_window, pshowwindow, pobj)
      pshowwindow->m_bRet = false;

   // xxx   TwiOnShowWindow(bShow, nStatus);
}

void simple_scroll_bar::_001OnDestroy(signal_details * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
}
