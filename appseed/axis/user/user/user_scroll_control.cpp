//#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"


namespace user
{


   scroll_control::scroll_control()
   {

      m_scrollinfo.m_ptScroll.x = 0;
      m_scrollinfo.m_ptScroll.y = 0;
      m_scrollinfo.m_rectMargin.left = 0;
      m_scrollinfo.m_rectMargin.top = 0;
      m_scrollinfo.m_rectMargin.right = 0;
      m_scrollinfo.m_rectMargin.bottom = 0;
      m_scrollinfo.m_bVScroll = false;
      m_scrollinfo.m_bHScroll = false;
      m_scrollinfo.m_sizeTotal.cx = 0;
      m_scrollinfo.m_sizeTotal.cy = 0;
      m_scrollinfo.m_sizePage.cx = 0;
      m_scrollinfo.m_sizePage.cy = 0;
      m_scrollinfo.m_sizeLine.cx = 0;
      m_scrollinfo.m_sizeLine.cy = 0;
      m_scrollinfo.m_bHScrollBarEnable = true;
      m_scrollinfo.m_bVScrollBarEnable = true;

   }

   scroll_control::~scroll_control()
   {
   }

   void scroll_control::GetScrollRect(LPRECT lprect)
   {
      
      ::rect rectScroll;

      GetClientRect(rectScroll);

      rectScroll.offset(get_viewport_offset());

      if(m_scrollinfo.m_bVScroll)
      {

         rectScroll.right -= m_scrollinfo.m_iScrollBarWidth;

      }

      if(m_scrollinfo.m_bHScroll)
      {

         rectScroll.bottom -= m_scrollinfo.m_iScrollBarHeight;

      }

      *lprect = rectScroll;

   }

   void scroll_control::_001LayoutScrollBars()
   {
      rect rectClient;

      GetClientRect(rectClient);

      int32_t ifswp = SWP_SHOWWINDOW | SWP_NOCOPYBITS;

      _001DeferCreateScrollBars();

      if(m_pscrollbarHorz != NULL)
      {
         if(m_scrollinfo.m_bHScroll)
         {
            m_pscrollbarHorz->SetWindowPos(ZORDER_TOP,0,rectClient.bottom - m_scrollinfo.m_iScrollBarHeight,rectClient.width() - (m_scrollinfo.m_bVScroll ? m_scrollinfo.m_iScrollBarWidth : 0),m_scrollinfo.m_iScrollBarHeight,ifswp);
         }
         else
         {
            m_pscrollbarHorz->ShowWindow(SW_HIDE);
         }
      }

      if(m_pscrollbarVert != NULL)
      {
         if(m_scrollinfo.m_bVScroll)
         {
            m_pscrollbarVert->SetWindowPos(ZORDER_TOP,rectClient.right - m_scrollinfo.m_iScrollBarWidth,rectClient.top,m_scrollinfo.m_iScrollBarWidth,rectClient.height() - (m_scrollinfo.m_bHScroll ? m_scrollinfo.m_iScrollBarHeight : 0) - rectClient.top,ifswp);
         }
         else
         {
            m_pscrollbarVert->ShowWindow(SW_HIDE);
         }
      }

   }

   void scroll_control::_001OnDeferCreateScrollBars()
   {

      if(m_scrollinfo.m_bHScroll)
      {
         if(m_pscrollbarHorz == NULL)
            create_scroll_bar(null_rect(), orientation_horizontal);

      }

      if(m_scrollinfo.m_bVScroll)
      {
         if(m_pscrollbarVert == NULL)
            create_scroll_bar(null_rect(), orientation_vertical);
      }

   }

   /*UINT c_cdecl scroll_control::thread_proc_defer_create_scroll_bars(LPVOID lpparam)
   {

      scroll_control * pview = (scroll_control *)lpparam;

      pview->_001OnDeferCreateScrollBars();

      return 0;

   }
   */

   void scroll_control::_001DeferCreateScrollBars()
   {

      bool bCreate = false;

      if(m_scrollinfo.m_bHScroll)
      {

         if(m_pscrollbarHorz == NULL)
         {

            bCreate = true;

         }

      }

      if(m_scrollinfo.m_bVScroll)
      {

         if(m_pscrollbarVert == NULL)
         {

            bCreate = true;

         }

      }

      if(bCreate)
      {

         _001OnDeferCreateScrollBars();

      }

   }

   void scroll_control::_001OnCreate(signal_details * pobj)
   {

      SCAST_PTR(::message::create, pcreate, pobj);

      if(pcreate->previous())
         return;

   }

   void scroll_control::_001OnSize(signal_details * pobj)
   {
      pobj->previous();
      _001LayoutScrollBars();
   }

   void scroll_control::_001OnUser9654(signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj);
      if(pbase->m_wparam == 0)
      {
         if(pbase->m_lparam == 0)
         {
            _001RedrawWindow();
         }
      }
   }

   void scroll_control::_001OnVScroll(signal_details * pobj)
   {


      SCAST_PTR(::message::scroll, pscroll, pobj);


      keep < bool > keepVScroll(&m_scrollinfo.m_bVScroll,true,false,true);

      {

//         synch_lock slUser(&user_mutex());
         synch_lock slUser(m_spmutex);

         m_scrollinfo.m_ptScroll.y = pscroll->m_nPos;

      }

      _001OnUpdateScrollPosition();


      post_message(WM_USER + 9654);


   }


   void scroll_control::_001OnHScroll(signal_details * pobj)
   {


      SCAST_PTR(::message::scroll, pscroll, pobj);


      keep < bool > keepHScroll(&m_scrollinfo.m_bHScroll,true,false,true);


      {

//         synch_lock slUser(&user_mutex());
         synch_lock slUser(m_spmutex);

         m_scrollinfo.m_ptScroll.x = pscroll->m_nPos;

      }

      _001OnUpdateScrollPosition();


      post_message(WM_USER + 9654);


   }

   int32_t scroll_control::get_wheel_scroll_delta()
   {

      return 1;

   }

   void scroll_control::_001OnUpdateScrollPosition()
   {

      _001UpdateScrollBars();


   }


   void scroll_control::_001OnMouseWheel(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse_wheel, pmousewheel, pobj);

      if(pmousewheel->GetDelta() > 0)
      {
         if(m_iWheelDelta > 0)
         {
            m_iWheelDelta += pmousewheel->GetDelta();
         }
         else
         {
            m_iWheelDelta = pmousewheel->GetDelta();
         }
      }
      else if(pmousewheel->GetDelta() < 0)
      {
         if(m_iWheelDelta < 0)
         {
            m_iWheelDelta += pmousewheel->GetDelta();
         }
         else
         {
            m_iWheelDelta = pmousewheel->GetDelta();
         }
      }

      index iDelta = m_iWheelDelta / WHEEL_DELTA;

      m_iWheelDelta -= (int16_t) (WHEEL_DELTA * iDelta);

      m_scrollinfo.m_ptScroll.y -= (LONG) (iDelta * get_wheel_scroll_delta());



      _001OnUpdateScrollPosition();





      pmousewheel->set_lresult(0);
      pmousewheel->m_bRet = true;


   }

   void scroll_control::_001ConstrainScrollPosition()
   {

      rect rectMargin = get_scroll_margin();

      if(m_scrollinfo.m_ptScroll.y < rectMargin.top)
      {
         m_scrollinfo.m_ptScroll.y = rectMargin.top;
      }
      else
      {
         if(m_scrollinfo.m_ptScroll.y > m_scrollinfo.m_sizeTotal.cy + rectMargin.bottom)
            m_scrollinfo.m_ptScroll.y = m_scrollinfo.m_sizeTotal.cy + rectMargin.bottom;
      }

      if(m_scrollinfo.m_ptScroll.x < rectMargin.left)
      {
         m_scrollinfo.m_ptScroll.x = rectMargin.left;
      }
      else
      {
         if(m_scrollinfo.m_ptScroll.x > m_scrollinfo.m_sizeTotal.cx + rectMargin.right)
            m_scrollinfo.m_ptScroll.x = m_scrollinfo.m_sizeTotal.cx + rectMargin.right;
      }


   }



   void scroll_control::_001UpdateScrollBars()
   {

      _001DeferCreateScrollBars();

      _001ConstrainScrollPosition();

      ::user::scroll_info si;

      rect rectMargin = get_scroll_margin();

      if(m_pscrollbarHorz != NULL)
      {
         si.fMask       = SIF_ALL;
         si.nMin        = rectMargin.left;
         si.nMax        = m_scrollinfo.m_sizeTotal.cx + rectMargin.right;
         si.nPage       = (uint32_t) m_scrollinfo.m_sizePage.cx;
         si.nPos        = m_scrollinfo.m_ptScroll.x;
         si.nTrackPos   = m_scrollinfo.m_ptScroll.x;
         m_pscrollbarHorz->_001SetScrollInfo(&si);
      }

      if(m_pscrollbarVert != NULL)
      {
         si.fMask       = SIF_ALL;
         si.nMin        = rectMargin.top;
         si.nMax        = m_scrollinfo.m_sizeTotal.cy + rectMargin.bottom;
         si.nPage       = (uint32_t) m_scrollinfo.m_sizePage.cy;
         si.nPos        = m_scrollinfo.m_ptScroll.y;
         si.nTrackPos   = m_scrollinfo.m_ptScroll.y;
         m_pscrollbarVert->_001SetScrollInfo(&si);
      }


   }



   void scroll_control::install_message_handling(::message::dispatch * pinterface)
   {


      control::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_CREATE,          pinterface, this, &scroll_control::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_SIZE,            pinterface, this, &scroll_control::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_VSCROLL,         pinterface, this, &scroll_control::_001OnVScroll);
      IGUI_WIN_MSG_LINK(WM_HSCROLL,         pinterface, this, &scroll_control::_001OnHScroll);
      IGUI_WIN_MSG_LINK(WM_MOUSEWHEEL,      pinterface, this, &scroll_control::_001OnMouseWheel);

      IGUI_WIN_MSG_LINK(WM_USER + 9654,     pinterface, this, &scroll_control::_001OnUser9654);


   }


   void scroll_control::create_scroll_bar(const RECT & rect, e_orientation eorientation)
   {

      if(eorientation == orientation_horizontal)
      {
         if(m_pscrollbarHorz != NULL)
            return;
      }
      else
      {
         if(m_pscrollbarVert != NULL)
            return;
      }

      scroll_bar * pbar = new simple_scroll_bar(get_app());

      if(!pbar->create_window(eorientation, WS_CHILD | WS_VISIBLE, null_rect(), this, 7000 + eorientation))
      {
         delete pbar;
         return;
      }

      if(eorientation == orientation_horizontal)
      {
         m_pscrollbarHorz = pbar;
      }
      else
      {
         m_pscrollbarVert = pbar;
      }

   }


   void scroll_control::_001GetViewRect(LPRECT lprect)
   {

      GetClientRect(lprect);

   }



   void scroll_control::_001GetViewClientRect(LPRECT lprect)
   {


      rect rectClient;

      GetClientRect(rectClient);

      rect rectTotal;

      _001GetViewRect(&rectTotal);


      index iTotalHeight = (index)rectTotal.height();

      index iTotalWidth = (index)rectTotal.width();

      index iClientHeight = (index)rectClient.height();

      index iClientWidth = (index)rectClient.width();

      index iScrollHeight =  iClientHeight - GetSystemMetrics(SM_CYHSCROLL);

      index iScrollWidth = iClientWidth - GetSystemMetrics(SM_CXVSCROLL);

      bool bHScroll = false;

      bool bVScroll = false;

      if(iTotalWidth > iClientWidth)
      {
         bHScroll = true;
         if(iTotalHeight > iScrollHeight)
         {
            bVScroll = true;
         }
      }
      else if(iTotalHeight > iClientHeight)
      {
         bVScroll = true;
         if(iTotalWidth > iScrollWidth)
         {
            bHScroll = true;
         }
      }

      lprect->left = 0;
      lprect->top = 0;

      if(bVScroll)
         lprect->right = (LONG) (lprect->left + iScrollWidth);
      else
         lprect->right = (LONG) (lprect->left + iClientWidth);
      if(bHScroll)
         lprect->bottom = (LONG) (lprect->top + iScrollHeight);
      else
         lprect->bottom = (LONG) (lprect->top + iClientHeight);

   }


   void scroll_control::SetScrollSizes()
   {

      rect rectTotal;

      _001GetViewRect(&rectTotal);

      size sizeTotal = rectTotal.size();

      m_scrollinfo.m_sizeTotal = sizeTotal;

      rect rectScroll;

      GetScrollRect(rectScroll);

      m_scrollinfo.m_sizeTotal = sizeTotal;
      m_scrollinfo.m_sizePage = rectScroll.size();

      if(m_scrollinfo.m_ptScroll.y > (m_scrollinfo.m_sizeTotal.cy - m_scrollinfo.m_sizePage.cy))
      {
         m_scrollinfo.m_ptScroll.y = (m_scrollinfo.m_sizeTotal.cy - m_scrollinfo.m_sizePage.cy);
      }


      m_scrollinfo.m_iScrollBarHeight  = GetSystemMetrics(SM_CXHSCROLL);
      m_scrollinfo.m_iScrollBarWidth   = GetSystemMetrics(SM_CXVSCROLL);

      m_scrollinfo.m_sizeClient     = rectScroll.size();
      m_scrollinfo.m_sizePage       = m_scrollinfo.m_sizeClient;

      rect rectMargin = get_scroll_margin();

      if(rectScroll.area() <= 0)
      {

         m_scrollinfo.m_bHScroll = false;
         m_scrollinfo.m_bVScroll = false;

      }
      else
      {

         m_scrollinfo.m_bVScroll = m_scrollinfo.m_bVScrollBarEnable && (m_scrollinfo.m_sizeTotal.cy + rectMargin.height()) > (rectScroll.height());

         m_scrollinfo.m_bHScroll = m_scrollinfo.m_bHScrollBarEnable && (m_scrollinfo.m_sizeTotal.cx + rectMargin.width()) > (rectScroll.width() - (m_scrollinfo.m_bVScroll ? get_scroll_bar_width() : 0));

         m_scrollinfo.m_bVScroll = m_scrollinfo.m_bVScrollBarEnable && (m_scrollinfo.m_sizeTotal.cy + rectMargin.height()) > (rectScroll.height() - (m_scrollinfo.m_bHScroll ? get_scroll_bar_height() : 0));

         m_scrollinfo.m_bHScroll = m_scrollinfo.m_bHScrollBarEnable && (m_scrollinfo.m_sizeTotal.cx + rectMargin.width()) > (rectScroll.width() - (m_scrollinfo.m_bVScroll ? get_scroll_bar_width() : 0));

         m_scrollinfo.m_bVScroll = m_scrollinfo.m_bVScrollBarEnable && (m_scrollinfo.m_sizeTotal.cy + rectMargin.height()) > (rectScroll.height() - (m_scrollinfo.m_bHScroll ? get_scroll_bar_height() : 0));

      }

      _001UpdateScrollBars();



   }


   point scroll_control::get_viewport_offset()
   {

      return m_scrollinfo.m_ptScroll;

   }

   rect scroll_control::get_scroll_margin()
   {

      return m_scrollinfo.m_rectMargin;

   }


   int scroll_control::get_scroll_bar_width()
   {

      return m_scrollinfo.m_iScrollBarWidth;

   }


   int scroll_control::get_scroll_bar_height()
   {

      return m_scrollinfo.m_iScrollBarHeight;

   }


}  // namespace core



