//#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"


namespace user
{


//   scroll_base::scroll_base()
//   {
//
//      m_scrolldata.m_bVScroll = false;
//      m_scrolldata.m_bHScroll = false;
//      m_scrolldata.m_sizePage.cx = 0;
//      m_scrolldata.m_sizePage.cy = 0;
//      m_scrolldata.m_sizeLine.cx = 0;
//      m_scrolldata.m_sizeLine.cy = 0;
//      m_scrolldata.m_bHScrollBarEnable = true;
//      m_scrolldata.m_bVScrollBarEnable = true;
//
//   }
//
//   scroll_base::~scroll_base()
//   {
//   }
//
//   void scroll_base::GetScrollRect(LPRECT lprect)
//   {
//      
//      ::rect rectScroll;
//
//      GetClientRect(rectScroll);
//
//      rectScroll.offset(get_viewport_offset());
//
//      *lprect = rectScroll;
//
//   }
//
//   void scroll_base::_001LayoutScrollBars()
//   {
//      rect rectClient;
//
//      GetClientRect(rectClient);
//
//      int32_t ifswp = SWP_SHOWWINDOW | SWP_NOCOPYBITS;
//
//      _001DeferCreateScrollBars();
//
//      if(m_pscrollbarHorz != NULL)
//      {
//         if(m_scrolldata.m_bHScroll)
//         {
//            m_pscrollbarHorz->SetWindowPos(ZORDER_TOP,0,rectClient.bottom - m_scrolldata.m_iScrollBarHeight,rectClient.width() - (m_scrolldata.m_bVScroll ? m_scrolldata.m_iScrollBarWidth : 0),m_scrolldata.m_iScrollBarHeight,ifswp);
//         }
//         else
//         {
//            m_pscrollbarHorz->ShowWindow(SW_HIDE);
//         }
//      }
//
//      if(m_pscrollbarVert != NULL)
//      {
//         if(m_scrolldata.m_bVScroll)
//         {
//            m_pscrollbarVert->SetWindowPos(ZORDER_TOP,rectClient.right - m_scrolldata.m_iScrollBarWidth,rectClient.top,m_scrolldata.m_iScrollBarWidth,rectClient.height() - (m_scrolldata.m_bHScroll ? m_scrolldata.m_iScrollBarHeight : 0) - rectClient.top,ifswp);
//         }
//         else
//         {
//            m_pscrollbarVert->ShowWindow(SW_HIDE);
//         }
//      }
//
//   }
//
//   void scroll_base::_001OnDeferCreateScrollBars()
//   {
//
//      if(m_scrolldata.m_bHScroll)
//      {
//         if(m_pscrollbarHorz == NULL)
//            create_scroll_bar(null_rect(), orientation_horizontal);
//
//      }
//
//      if(m_scrolldata.m_bVScroll)
//      {
//         if(m_pscrollbarVert == NULL)
//            create_scroll_bar(null_rect(), orientation_vertical);
//      }
//
//   }
//
//   /*UINT c_cdecl scroll_base::thread_proc_defer_create_scroll_bars(LPVOID lpparam)
//   {
//
//      scroll_base * pview = (scroll_base *)lpparam;
//
//      pview->_001OnDeferCreateScrollBars();
//
//      return 0;
//
//   }
//   */
//
//   void scroll_base::_001DeferCreateScrollBars()
//   {
//
//      bool bCreate = false;
//
//      if(m_scrolldata.m_bHScroll)
//      {
//
//         if(m_pscrollbarHorz == NULL)
//         {
//
//            bCreate = true;
//
//         }
//
//      }
//
//      if(m_scrolldata.m_bVScroll)
//      {
//
//         if(m_pscrollbarVert == NULL)
//         {
//
//            bCreate = true;
//
//         }
//
//      }
//
//      if(bCreate)
//      {
//
//         _001OnDeferCreateScrollBars();
//
//      }
//
//   }
//
//   void scroll_base::_001OnCreate(signal_details * pobj)
//   {
//
//      SCAST_PTR(::message::create, pcreate, pobj);
//
//      if(pcreate->previous())
//         return;
//
//   }
//
//   void scroll_base::_001OnSize(signal_details * pobj)
//   {
//      pobj->previous();
//      _001LayoutScrollBars();
//   }
//
//   void scroll_base::_001OnUser9654(signal_details * pobj)
//   {
//      SCAST_PTR(::message::base, pbase, pobj);
//      if(pbase->m_wparam == 0)
//      {
//         if(pbase->m_lparam == 0)
//         {
//            _001RedrawWindow();
//         }
//      }
//   }
//
//   void scroll_base::_001OnVScroll(signal_details * pobj)
//   {
//
//
//      SCAST_PTR(::message::scroll, pscroll, pobj);
//
//
//      keep < bool > keepVScroll(&m_scrolldata.m_bVScroll,true,false,true);
//
//      {
//
//         synch_lock slUser(m_spmutex);
//
//         set_viewport_offset_y(pscroll->m_nPos);
//
//      }
//
//      post_message(WM_USER + 9654);
//
//
//   }
//
//
//   void scroll_base::_001OnHScroll(signal_details * pobj)
//   {
//
//
//      SCAST_PTR(::message::scroll, pscroll, pobj);
//
//
//      keep < bool > keepHScroll(&m_scrolldata.m_bHScroll,true,false,true);
//
//
//      {
//
////         synch_lock slUser(&user_mutex());
//         synch_lock slUser(m_spmutex);
//
//         set_viewport_offset_x(pscroll->m_nPos);
//
//      }
//
//      post_message(WM_USER + 9654);
//
//
//   }
//
//   int32_t scroll_base::get_wheel_scroll_delta()
//   {
//
//      return 1;
//
//   }
//
//   void scroll_base::on_change_viewport_offset()
//   {
//
////      on_change_viewport_offset();
//
//
//   }
//
//
//   void scroll_base::_001OnMouseWheel(signal_details * pobj)
//   {
//
//      SCAST_PTR(::message::mouse_wheel, pmousewheel, pobj);
//
//      if(pmousewheel->GetDelta() > 0)
//      {
//         if(m_iWheelDelta > 0)
//         {
//            m_iWheelDelta += pmousewheel->GetDelta();
//         }
//         else
//         {
//            m_iWheelDelta = pmousewheel->GetDelta();
//         }
//      }
//      else if(pmousewheel->GetDelta() < 0)
//      {
//         if(m_iWheelDelta < 0)
//         {
//            m_iWheelDelta += pmousewheel->GetDelta();
//         }
//         else
//         {
//            m_iWheelDelta = pmousewheel->GetDelta();
//         }
//      }
//
//      index iDelta = m_iWheelDelta / WHEEL_DELTA;
//
//      m_iWheelDelta -= (int16_t) (WHEEL_DELTA * iDelta);
//
//      offset_viewport_offset_y( - iDelta * get_wheel_scroll_delta());
//
//      pmousewheel->set_lresult(0);
//
//      pmousewheel->m_bRet = true;
//
//
//   }
//
//   void scroll_base::_001ConstrainScrollPosition()
//   {
//
//      size sizeTotal = get_total_size();
//
//      point ptOffset = get_viewport_offset();
//
//      if(ptOffset.y < 0)
//      {
//         ptOffset.y = 0;
//      }
//      else
//      {
//         if(ptOffset.y > sizeTotal.cy)
//            ptOffset.y = sizeTotal.cy;
//      }
//
//      if(ptOffset.x < 0)
//      {
//         ptOffset.x = 0;
//      }
//      else
//      {
//         if(ptOffset.x > sizeTotal.cx)
//            ptOffset.x = sizeTotal.cx;
//      }
//
//      if(ptOffset != get_viewport_offset())
//      {
//
//         set_viewport_offset(ptOffset.x, ptOffset.y);
//
//      }
//
//   }
//
//
//
//   //void scroll_base::on_change_viewport_offset()
//   //{
//
//   //   _001DeferCreateScrollBars();
//
//   //   _001ConstrainScrollPosition();
//
//   //   ::user::scroll_info si;
//
//   //   if(m_pscrollbarHorz != NULL)
//   //   {
//   //      si.fMask       = SIF_ALL;
//   //      si.nMin        = 0;
//   //      si.nMax        = sizeTotal.cx;
//   //      si.nPage       = (uint32_t) m_scrolldata.m_sizePage.cx;
//   //      si.nPos        = m_ptScroll.x;
//   //      si.nTrackPos   = m_ptScroll.x;
//   //      m_pscrollbarHorz->_001SetScrollInfo(&si);
//   //   }
//
//   //   if(m_pscrollbarVert != NULL)
//   //   {
//   //      si.fMask       = SIF_ALL;
//   //      si.nMin        = 0;
//   //      si.nMax        = sizeTotal.cy;
//   //      si.nPage       = (uint32_t) m_scrolldata.m_sizePage.cy;
//   //      si.nPos        = m_ptScroll.y;
//   //      si.nTrackPos   = m_ptScroll.y;
//   //      m_pscrollbarVert->_001SetScrollInfo(&si);
//   //   }
//
//
//   //}
//
//
//
//   void scroll_base::install_message_handling(::message::dispatch * pinterface)
//   {
//
//
//      control::install_message_handling(pinterface);
//
//      IGUI_WIN_MSG_LINK(WM_CREATE,          pinterface, this, &scroll_base::_001OnCreate);
//      IGUI_WIN_MSG_LINK(WM_SIZE,            pinterface, this, &scroll_base::_001OnSize);
//      IGUI_WIN_MSG_LINK(WM_VSCROLL,         pinterface, this, &scroll_base::_001OnVScroll);
//      IGUI_WIN_MSG_LINK(WM_HSCROLL,         pinterface, this, &scroll_base::_001OnHScroll);
//      IGUI_WIN_MSG_LINK(WM_MOUSEWHEEL,      pinterface, this, &scroll_base::_001OnMouseWheel);
//
//      IGUI_WIN_MSG_LINK(WM_USER + 9654,     pinterface, this, &scroll_base::_001OnUser9654);
//
//
//   }
//
//
//   void scroll_base::create_scroll_bar(const RECT & rect, e_orientation eorientation)
//   {
//
//      if(eorientation == orientation_horizontal)
//      {
//         if(m_pscrollbarHorz != NULL)
//            return;
//      }
//      else
//      {
//         if(m_pscrollbarVert != NULL)
//            return;
//      }
//
//      scroll_bar * pbar = new simple_scroll_bar(get_app());
//
//      if(!pbar->create_window(eorientation, WS_CHILD | WS_VISIBLE, null_rect(), this, 7000 + eorientation))
//      {
//         delete pbar;
//         return;
//      }
//
//      if(eorientation == orientation_horizontal)
//      {
//         m_pscrollbarHorz = pbar;
//      }
//      else
//      {
//         m_pscrollbarVert = pbar;
//      }
//
//   }
//
//   void scroll_base::GetClientRect(LPRECT lprect)
//   {
//
//      ::rect rectClient;
//
//      ::user::control::GetClientRect(rectClient);
//
//      if(m_scrolldata.m_bVScroll)
//      {
//
//         rectClient.right -= m_scrolldata.m_iScrollBarWidth;
//
//      }
//
//      if(m_scrolldata.m_bHScroll)
//      {
//
//         rectClient.bottom -= m_scrolldata.m_iScrollBarHeight;
//
//      }
//
//      *lprect = rectClient;
//
//   }
//
//
//   void scroll_base::on_change_view_size()
//   {
//
//      size sizeTotal = get_total_size();
//
//      m_scrolldata.m_iScrollBarHeight  = GetSystemMetrics(SM_CXHSCROLL);
//
//      m_scrolldata.m_iScrollBarWidth   = GetSystemMetrics(SM_CXVSCROLL);
//
//      rect rectClient;
//
//      ::user::control::GetClientRect(rectClient);
//
//      LONG iTotalHeight    = sizeTotal.cy;
//
//      LONG iTotalWidth     = sizeTotal.cx;
//
//      LONG iClientHeight   = rectClient.height();
//
//      LONG iClientWidth    = rectClient.width();
//
//      LONG iScrollHeight  = iClientHeight - GetSystemMetrics(SM_CYHSCROLL);
//
//      LONG iScrollWidth   = iClientWidth - GetSystemMetrics(SM_CXVSCROLL);
//
//      m_scrolldata.m_bHScroll = false;
//
//      m_scrolldata.m_bVScroll = false;
//
//      if(iTotalWidth > iClientWidth)
//      {
//
//         m_scrolldata.m_bHScroll = true;
//
//         if(iTotalHeight > iScrollHeight)
//         {
//
//            m_scrolldata.m_bVScroll = true;
//
//         }
//
//      }
//      else if(iTotalHeight > iClientHeight)
//      {
//
//         m_scrolldata.m_bVScroll = true;
//
//         if(iTotalWidth > iScrollWidth)
//         {
//
//            m_scrolldata.m_bHScroll = true;
//
//         }
//
//      }
//
//      if(m_scrolldata.m_bVScroll)
//      {
//
//         //m_scrolldata.m_sizeClient.cx = iScrollWidth;
//
//      }
//      else
//      {
//
//         //m_scrolldata.m_sizeClient.cx = iClientWidth;
//
//      }
//
//      if(m_scrolldata.m_bHScroll)
//      {
//
//         //m_scrolldata.m_sizeClient.cy = iScrollHeight;
//
//      }
//      else
//      {
//
//         //m_scrolldata.m_sizeClient.cy = iClientHeight;
//
//      }
//
//      m_scrolldata.m_bVScroll = m_scrolldata.m_bVScrollBarEnable && m_scrolldata.m_bVScroll;
//
//      m_scrolldata.m_bHScroll = m_scrolldata.m_bHScrollBarEnable && m_scrolldata.m_bHScroll;
//
//      rect rectScroll;
//
//      GetScrollRect(rectScroll);
//
//      m_scrolldata.m_sizePage          = rectScroll.size();
//
//      _001LayoutScrollBars();
//
//      on_change_viewport_offset();
//
//   }
//
//
//
//   //point scroll_base::get_viewport_offset()
//   //{
//
//   //   return m_ptScroll;
//
//   //}
//
//   //rect scroll_base::get_scroll_margin()
//   //{
//
//   //   return m_scrolldata.m_rectMargin;
//
//   //}
//
//
//   int scroll_base::get_scroll_bar_width()
//   {
//
//      return m_scrolldata.m_iScrollBarWidth;
//
//   }
//
//
//   int scroll_base::get_scroll_bar_height()
//   {
//
//      return m_scrolldata.m_iScrollBarHeight;
//
//   }
//
//   //void scroll_base::set_viewport_offset_y(int y)
//   //{
//
//   //   control::set_viewport_offset_y(y);
//
//   //   on_change_viewport_offset();
//
//   //}
//
//
//   //void scroll_base::set_viewport_offset_x(int x)
//   //{
//
//   //   control::set_viewport_offset_x(x);
//
//   //   on_change_viewport_offset();
//
//   //}
//   //
//
//   void scroll_base::layout()
//   {
//
//      ::user::control::layout();
//
//      on_change_view_size();
//
//   }


}  // namespace core






