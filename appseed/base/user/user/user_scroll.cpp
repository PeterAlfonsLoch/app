//#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"


namespace user
{


   scroll_x::scroll_x()
   {

      m_scrolldataHorz.m_bScroll = false;
      m_scrolldataHorz.m_iPage = 0;
      m_scrolldataHorz.m_iLine = 0;
      m_scrolldataHorz.m_bScrollEnable = true;

   }

   scroll_x::~scroll_x()
   {
   }


   void scroll_x::GetScrollRect(LPRECT lprect)
   {

      ::rect rectScroll;

      GetClientRect(rectScroll);

      rectScroll.offset(get_viewport_offset());

      *lprect = rectScroll;

   }



   void scroll_x::layout_scroll_bar()
   {

      rect rectClient;

      GetClientRect(rectClient);

      int32_t ifswp = SWP_SHOWWINDOW | SWP_NOCOPYBITS;

      _001DeferCreateXScrollBar();

      if (m_pscrollbarHorz != NULL)
      {

         if (m_scrolldataHorz.m_bScroll)
         {

            _001GetXScrollInfo(m_pscrollbarHorz->m_scrollinfo);

            m_pscrollbarHorz->SetWindowPos(ZORDER_TOP, 0, rectClient.bottom, rectClient.width(), m_scrolldataHorz.m_iWidth, ifswp);

            m_pscrollbarHorz->layout();

         }
         else
         {
            m_pscrollbarHorz->ShowWindow(SW_HIDE);
         }
      }

   }



   void scroll_x::_001OnDeferCreateXScrollBar()
   {

      if (m_scrolldataHorz.m_bScroll)
      {

         if (m_pscrollbarHorz == NULL)
            create_x_scroll_bar(null_rect());

      }


   }


   void scroll_x::_001DeferCreateXScrollBar()
   {

      bool bCreate = false;

      if (m_scrolldataHorz.m_bScroll)
      {

         if (m_pscrollbarHorz == NULL)
         {

            bCreate = true;

         }

      }


      if (bCreate)
      {

         _001OnDeferCreateXScrollBar();

      }

   }


   void scroll_x::_001OnHScroll(signal_details * pobj)
   {

      SCAST_PTR(::message::scroll, pscroll, pobj);

      {

         synch_lock slUser(m_pmutex);

         set_viewport_offset_x(pscroll->m_nPos);

      }

   }



   void scroll_x::on_change_viewport_offset()
   {

      synch_lock sl(m_pmutex);

   }




   void scroll_x::_001ConstrainXScrollPosition()
   {

      size sizeTotal = get_total_size();

      point ptOffset = get_viewport_offset();

      if (ptOffset.y < 0)
      {
         ptOffset.y = 0;
      }
      else
      {
         if (ptOffset.y > sizeTotal.cy)
            ptOffset.y = sizeTotal.cy;
      }

      if (ptOffset.x < 0)
      {
         ptOffset.x = 0;
      }
      else
      {
         if (ptOffset.x > sizeTotal.cx)
            ptOffset.x = sizeTotal.cx;
      }

      if (ptOffset != get_viewport_offset())
      {

         set_viewport_offset(ptOffset.x, ptOffset.y);

      }

   }






   void scroll_x::install_message_handling(::message::dispatch * pinterface)
   {


      IGUI_WIN_MSG_LINK(WM_HSCROLL, pinterface, this, &scroll_x::_001OnHScroll);

   }

   //   
   // void scroll_x::create_x_scroll_bar(const RECT & rect);


   void scroll_x::on_change_view_size()
   {

      size sizeTotal = get_total_size();

      m_scrolldataHorz.m_iWidth = GetSystemMetrics(SM_CXHSCROLL);

      rect rectClient;

      GetClientRect(rectClient);

      LONG iTotalHeight = sizeTotal.cy;

      LONG iTotalWidth = sizeTotal.cx;

      LONG iClientHeight = rectClient.height();

      LONG iClientWidth = rectClient.width();

      LONG iScrollHeight = iClientHeight - GetSystemMetrics(SM_CYHSCROLL);

      LONG iscrollWidth = iClientWidth - GetSystemMetrics(SM_CXVSCROLL);

      m_scrolldataHorz.m_bScroll = false;

      if (iTotalWidth > iClientWidth)
      {

         m_scrolldataHorz.m_bScroll = true;

      }
      else if (iTotalHeight > iClientHeight)
      {

         if (iTotalWidth > iscrollWidth)
         {

            m_scrolldataHorz.m_bScroll = true;

         }

      }

      m_scrolldataHorz.m_bScroll = m_scrolldataHorz.m_bScrollEnable && m_scrolldataHorz.m_bScroll;

      rect rectScroll;

      GetScrollRect(rectScroll);

      m_scrolldataHorz.m_iPage = rectScroll.width();

      _001ConstrainXScrollPosition();

      layout_scroll_bar();

      on_change_viewport_offset();

   }


   int scroll_x::get_final_x_scroll_bar_width()
   {

      return m_scrolldataHorz.m_bScroll && m_scrolldataHorz.m_bScrollEnable ? m_scrolldataHorz.m_iWidth : 0;

   }













   //   scroll::scroll()
   //   {
   //
   //      m_scrolldata.m_bVscroll = false;
   //      m_scrolldata.m_bHscroll = false;
   //      m_scrolldata.m_sizePage.cx = 0;
   //      m_scrolldata.m_sizePage.cy = 0;
   //      m_scrolldata.m_sizeLine.cx = 0;
   //      m_scrolldata.m_sizeLine.cy = 0;
   //      m_scrolldata.m_bHscrollBarEnable = true;
   //      m_scrolldata.m_bVscrollBarEnable = true;
   //
   //   }
   //
   //   scroll::~scroll()
   //   {
   //   }
   //
   //   void scroll::GetScrollRect(LPRECT lprect)
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
   //   void scroll::_001LayoutscrollBars()
   //   {
   //      rect rectClient;
   //
   //      GetClientRect(rectClient);
   //
   //      int32_t ifswp = SWP_SHOWWINDOW | SWP_NOCOPYBITS;
   //
   //      _001DeferCreatescrollBars();
   //
   //      if(m_pscrollbarHorz != NULL)
   //      {
   //         if(m_scrolldata.m_bHscroll)
   //         {
   //            m_pscrollbarHorz->SetWindowPos(ZORDER_TOP,0,rectClient.bottom - m_scrolldata.m_iscrollBarHeight,rectClient.width() - (m_scrolldata.m_bVscroll ? m_scrolldata.m_iscrollBarWidth : 0),m_scrolldata.m_iscrollBarHeight,ifswp);
   //         }
   //         else
   //         {
   //            m_pscrollbarHorz->ShowWindow(SW_HIDE);
   //         }
   //      }
   //
   //      if(m_pscrollbarVert != NULL)
   //      {
   //         if(m_scrolldata.m_bVscroll)
   //         {
   //            m_pscrollbarVert->SetWindowPos(ZORDER_TOP,rectClient.right - m_scrolldata.m_iscrollBarWidth,rectClient.top,m_scrolldata.m_iscrollBarWidth,rectClient.height() - (m_scrolldata.m_bHscroll ? m_scrolldata.m_iscrollBarHeight : 0) - rectClient.top,ifswp);
   //         }
   //         else
   //         {
   //            m_pscrollbarVert->ShowWindow(SW_HIDE);
   //         }
   //      }
   //
   //   }
   //
   //   void scroll::_001OnDeferCreatescrollBars()
   //   {
   //
   //      if(m_scrolldata.m_bHscroll)
   //      {
   //         if(m_pscrollbarHorz == NULL)
   //            create_scroll_bar(null_rect(), orientation_horizontal);
   //
   //      }
   //
   //      if(m_scrolldata.m_bVscroll)
   //      {
   //         if(m_pscrollbarVert == NULL)
   //            create_scroll_bar(null_rect(), orientation_vertical);
   //      }
   //
   //   }
   //
   //   /*UINT c_cdecl scroll::thread_proc_defer_create_scroll_bars(LPVOID lpparam)
   //   {
   //
   //      scroll * pview = (scroll *)lpparam;
   //
   //      pview->_001OnDeferCreatescrollBars();
   //
   //      return 0;
   //
   //   }
   //   */
   //
   //   void scroll::_001DeferCreatescrollBars()
   //   {
   //
   //      bool bCreate = false;
   //
   //      if(m_scrolldata.m_bHscroll)
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
   //      if(m_scrolldata.m_bVscroll)
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
   //         _001OnDeferCreatescrollBars();
   //
   //      }
   //
   //   }
   //
   //   void scroll::_001OnCreate(signal_details * pobj)
   //   {
   //
   //      SCAST_PTR(::message::create, pcreate, pobj);
   //
   //      if(pcreate->previous())
   //         return;
   //
   //   }
   //
   //   void scroll::_001OnSize(signal_details * pobj)
   //   {
   //      pobj->previous();
   //      _001LayoutscrollBars();
   //   }
   //
   //   void scroll::_001OnUser9654(signal_details * pobj)
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
   //   void scroll::_001OnVScroll(signal_details * pobj)
   //   {
   //
   //
   //      SCAST_PTR(::message::scroll, pscroll, pobj);
   //
   //
   //      keep < bool > keepVscroll(&m_scrolldata.m_bVscroll,true,false,true);
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
   //   void scroll::_001OnHScroll(signal_details * pobj)
   //   {
   //
   //
   //      SCAST_PTR(::message::scroll, pscroll, pobj);
   //
   //
   //      keep < bool > keepHscroll(&m_scrolldata.m_bHscroll,true,false,true);
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
   //   int32_t scroll::get_wheel_scroll_delta()
   //   {
   //
   //      return 1;
   //
   //   }
   //
   //   void scroll::on_change_viewport_offset()
   //   {
   //
   ////      on_change_viewport_offset();
   //
   //
   //   }
   //
   //
   //   void scroll::_001OnMouseWheel(signal_details * pobj)
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
   //   void scroll::_001ConstrainscrollPosition()
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
   //   //void scroll::on_change_viewport_offset()
   //   //{
   //
   //   //   _001DeferCreatescrollBars();
   //
   //   //   _001ConstrainscrollPosition();
   //
   //   //   ::user::scroll_info si;
   //
   //   //   if(m_pscrollbarHorz != NULL)
   //   //   {
   //   //      si.fMask       = SIF_ALL;
   //   //      si.nMin        = 0;
   //   //      si.nMax        = sizeTotal.cx;
   //   //      si.nPage       = (uint32_t) m_scrolldata.m_sizePage.cx;
   //   //      si.nPos        = m_ptscroll.x;
   //   //      si.nTrackPos   = m_ptscroll.x;
   //   //      m_pscrollbarHorz->_001SetscrollInfo(&si);
   //   //   }
   //
   //   //   if(m_pscrollbarVert != NULL)
   //   //   {
   //   //      si.fMask       = SIF_ALL;
   //   //      si.nMin        = 0;
   //   //      si.nMax        = sizeTotal.cy;
   //   //      si.nPage       = (uint32_t) m_scrolldata.m_sizePage.cy;
   //   //      si.nPos        = m_ptscroll.y;
   //   //      si.nTrackPos   = m_ptscroll.y;
   //   //      m_pscrollbarVert->_001SetscrollInfo(&si);
   //   //   }
   //
   //
   //   //}
   //
   //
   //
   //   void scroll::install_message_handling(::message::dispatch * pinterface)
   //   {
   //
   //
   //      control::install_message_handling(pinterface);
   //
   //      IGUI_WIN_MSG_LINK(WM_CREATE,          pinterface, this, &scroll::_001OnCreate);
   //      IGUI_WIN_MSG_LINK(WM_SIZE,            pinterface, this, &scroll::_001OnSize);
   //      IGUI_WIN_MSG_LINK(WM_VSCROLL,         pinterface, this, &scroll::_001OnVScroll);
   //      IGUI_WIN_MSG_LINK(WM_HSCROLL,         pinterface, this, &scroll::_001OnHScroll);
   //      IGUI_WIN_MSG_LINK(WM_MOUSEWHEEL,      pinterface, this, &scroll::_001OnMouseWheel);
   //
   //      IGUI_WIN_MSG_LINK(WM_USER + 9654,     pinterface, this, &scroll::_001OnUser9654);
   //
   //
   //   }
   //
   //
   //   void scroll::create_scroll_bar(const RECT & rect, e_orientation eorientation)
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
   //   void scroll::GetClientRect(LPRECT lprect)
   //   {
   //
   //      ::rect rectClient;
   //
   //      ::user::control::GetClientRect(rectClient);
   //
   //      if(m_scrolldata.m_bVscroll)
   //      {
   //
   //         rectClient.right -= m_scrolldata.m_iscrollBarWidth;
   //
   //      }
   //
   //      if(m_scrolldata.m_bHscroll)
   //      {
   //
   //         rectClient.bottom -= m_scrolldata.m_iscrollBarHeight;
   //
   //      }
   //
   //      *lprect = rectClient;
   //
   //   }
   //
   //
   //   void scroll::on_change_view_size()
   //   {
   //
   //      size sizeTotal = get_total_size();
   //
   //      m_scrolldata.m_iscrollBarHeight  = GetSystemMetrics(SM_CXHSCROLL);
   //
   //      m_scrolldata.m_iscrollBarWidth   = GetSystemMetrics(SM_CXVSCROLL);
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
   //      LONG iscrollWidth   = iClientWidth - GetSystemMetrics(SM_CXVSCROLL);
   //
   //      m_scrolldata.m_bHscroll = false;
   //
   //      m_scrolldata.m_bVscroll = false;
   //
   //      if(iTotalWidth > iClientWidth)
   //      {
   //
   //         m_scrolldata.m_bHscroll = true;
   //
   //         if(iTotalHeight > iScrollHeight)
   //         {
   //
   //            m_scrolldata.m_bVscroll = true;
   //
   //         }
   //
   //      }
   //      else if(iTotalHeight > iClientHeight)
   //      {
   //
   //         m_scrolldata.m_bVscroll = true;
   //
   //         if(iTotalWidth > iscrollWidth)
   //         {
   //
   //            m_scrolldata.m_bHscroll = true;
   //
   //         }
   //
   //      }
   //
   //      if(m_scrolldata.m_bVscroll)
   //      {
   //
   //         //m_scrolldata.m_sizeClient.cx = iscrollWidth;
   //
   //      }
   //      else
   //      {
   //
   //         //m_scrolldata.m_sizeClient.cx = iClientWidth;
   //
   //      }
   //
   //      if(m_scrolldata.m_bHscroll)
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
   //      m_scrolldata.m_bVscroll = m_scrolldata.m_bVscrollBarEnable && m_scrolldata.m_bVscroll;
   //
   //      m_scrolldata.m_bHscroll = m_scrolldata.m_bHscrollBarEnable && m_scrolldata.m_bHscroll;
   //
   //      rect rectScroll;
   //
   //      GetScrollRect(rectScroll);
   //
   //      m_scrolldata.m_sizePage          = rectScroll.size();
   //
   //      _001LayoutscrollBars();
   //
   //      on_change_viewport_offset();
   //
   //   }
   //
   //
   //
   //   //point scroll::get_viewport_offset()
   //   //{
   //
   //   //   return m_ptscroll;
   //
   //   //}
   //
   //   //rect scroll::get_scroll_margin()
   //   //{
   //
   //   //   return m_scrolldata.m_rectMargin;
   //
   //   //}
   //
   //
   //   int scroll::get_scroll_bar_width()
   //   {
   //
   //      return m_scrolldata.m_iscrollBarWidth;
   //
   //   }
   //
   //
   //   int scroll::get_scroll_bar_height()
   //   {
   //
   //      return m_scrolldata.m_iscrollBarHeight;
   //
   //   }
   //
   //   //void scroll::set_viewport_offset_y(int y)
   //   //{
   //
   //   //   control::set_viewport_offset_y(y);
   //
   //   //   on_change_viewport_offset();
   //
   //   //}
   //
   //
   //   //void scroll::set_viewport_offset_x(int x)
   //   //{
   //
   //   //   control::set_viewport_offset_x(x);
   //
   //   //   on_change_viewport_offset();
   //
   //   //}
   //   //
   //
   //   void scroll::layout()
   //   {
   //
   //      ::user::control::layout();
   //
   //      on_change_view_size();
   //
   //   }


   scroll_y::scroll_y()
   {

      m_scrolldataVert.m_bScroll = false;
      m_scrolldataVert.m_iPage = 0;
      m_scrolldataVert.m_iLine = 0;
      m_scrolldataVert.m_bScrollEnable = true;

   }

   scroll_y::~scroll_y()
   {
   }

   void scroll_y::GetScrollRect(LPRECT lprect)
   {

      ::rect rectScroll;

      GetClientRect(rectScroll);

      rectScroll.offset(get_viewport_offset());

      *lprect = rectScroll;

   }



   void scroll_y::layout_scroll_bar()
   {

      rect rectClient;


      GetClientRect(rectClient);

      int32_t ifswp = SWP_SHOWWINDOW | SWP_NOCOPYBITS;

      _001DeferCreateYScrollBar();

      if (m_pscrollbarVert != NULL)
      {

         if (m_scrolldataVert.m_bScroll)
         {

            _001GetYScrollInfo(m_pscrollbarVert->m_scrollinfo);

            m_pscrollbarVert->SetWindowPos(ZORDER_TOP, rectClient.right, rectClient.top, m_scrolldataVert.m_iWidth, rectClient.height() - rectClient.top, ifswp);

            m_pscrollbarVert->layout();

         }
         else
         {
            m_pscrollbarVert->ShowWindow(SW_HIDE);
         }

      }

   }



   void scroll_y::_001OnDeferCreateYScrollBar()
   {

      if (m_scrolldataVert.m_bScroll)
      {
         if (m_pscrollbarVert == NULL)
            create_y_scroll_bar(null_rect());
      }

   }



   void scroll_y::_001DeferCreateYScrollBar()
   {

      bool bCreate = false;

      if (m_scrolldataVert.m_bScroll)
      {

         if (m_pscrollbarVert == NULL)
         {

            bCreate = true;

         }

      }

      if (bCreate)
      {

         _001OnDeferCreateYScrollBar();

      }

   }


   void scroll_y::_001OnVScroll(signal_details * pobj)
   {


      SCAST_PTR(::message::scroll, pscroll, pobj);


      {

         synch_lock slUser(m_pmutex);

         set_viewport_offset_y(pscroll->m_nPos);

      }

   }



   int32_t scroll_y::get_wheel_scroll_delta()
   {

      return 1;

   }



   void scroll_y::on_change_viewport_offset()
   {

      synch_lock sl(m_pmutex);

   }


   void scroll_y::_001OnMouseWheel(signal_details * pobj)
   {

      if (!m_scrolldataVert.m_bScroll || !m_scrolldataVert.m_bScrollEnable)
      {
      
         return;

      }

      SCAST_PTR(::message::mouse_wheel, pmousewheel, pobj);

      if (pmousewheel->GetDelta() > 0)
      {
         if (m_iWheelDelta > 0)
         {
            m_iWheelDelta += pmousewheel->GetDelta();
         }
         else
         {
            m_iWheelDelta = pmousewheel->GetDelta();
         }
      }
      else if (pmousewheel->GetDelta() < 0)
      {
         if (m_iWheelDelta < 0)
         {
            m_iWheelDelta += pmousewheel->GetDelta();
         }
         else
         {
            m_iWheelDelta = pmousewheel->GetDelta();
         }
      }

      index iDelta = m_iWheelDelta / WHEEL_DELTA;

      m_iWheelDelta -= (int16_t)(WHEEL_DELTA * iDelta);

      int nPos = m_pscrollbarVert->m_scrollinfo.nPos - iDelta * get_wheel_scroll_delta();

      if (nPos < m_pscrollbarVert->m_scrollinfo.nMin)
         nPos = m_pscrollbarVert->m_scrollinfo.nMin;
      else if (nPos > m_pscrollbarVert->m_scrollinfo.nMax - m_pscrollbarVert->m_scrollinfo.nPage)
         nPos = m_pscrollbarVert->m_scrollinfo.nMax - m_pscrollbarVert->m_scrollinfo.nPage;

      m_pscrollbarVert->m_scrollinfo.nPos = nPos;

      m_pscrollbarVert->send_scroll_message(SB_THUMBPOSITION);
         
      pmousewheel->set_lresult(0);

      pmousewheel->m_bRet = true;


   }



   void scroll_y::_001ConstrainYScrollPosition()
   {

      size sizeTotal = get_total_size();

      size sizePage = get_page_size();

      point ptOffset = get_viewport_offset();

      if (ptOffset.y < 0)
      {
         ptOffset.y = 0;
      }
      else
      {
         if (ptOffset.y > MAX(0, sizeTotal.cy - sizePage.cy))
            ptOffset.y = sizeTotal.cy - sizePage.cy;
      }

      if (ptOffset.x < 0)
      {
         ptOffset.x = 0;
      }
      else
      {
         if (ptOffset.x > MAX(0, sizeTotal.cx - sizePage.cx))
            ptOffset.x = sizeTotal.cx - sizePage.cx;
      }

      if (ptOffset != get_viewport_offset())
      {

         set_viewport_offset(ptOffset.x, ptOffset.y);

      }

   }




   void scroll_y::install_message_handling(::message::dispatch * pinterface)
   {

      interaction::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_VSCROLL, pinterface, this, &scroll_y::_001OnVScroll);
      IGUI_WIN_MSG_LINK(WM_MOUSEWHEEL, pinterface, this, &scroll_y::_001OnMouseWheel);

   }


   void scroll_y::on_change_view_size()
   {

      size sizeTotal = get_total_size();

      m_scrolldataVert.m_iWidth = GetSystemMetrics(SM_CXVSCROLL);

      rect rectClient;

      GetClientRect(rectClient);

      LONG iTotalHeight = sizeTotal.cy;

      LONG iTotalWidth = sizeTotal.cx;

      LONG iClientHeight = rectClient.height();

      LONG iClientWidth = rectClient.width();

      LONG iScrollHeight = iClientHeight - GetSystemMetrics(SM_CYHSCROLL);

      LONG iscrollWidth = iClientWidth - GetSystemMetrics(SM_CXVSCROLL);

      m_scrolldataVert.m_bScroll = false;

      if (iTotalWidth > iClientWidth)
      {

         if (iTotalHeight > iScrollHeight)
         {

            m_scrolldataVert.m_bScroll = true;

         }

      }
      else if (iTotalHeight > iClientHeight)
      {

         m_scrolldataVert.m_bScroll = true;

      }

      m_scrolldataVert.m_bScroll = m_scrolldataVert.m_bScrollEnable && m_scrolldataVert.m_bScroll;

      rect rectScroll;

      GetScrollRect(rectScroll);

      m_scrolldataVert.m_iPage = rectScroll.height();

      _001ConstrainYScrollPosition();

      layout_scroll_bar();

      on_change_viewport_offset();

   }



   int scroll_y::get_final_y_scroll_bar_width()
   {

      return m_scrolldataVert.m_bScroll && m_scrolldataVert.m_bScrollEnable ? m_scrolldataVert.m_iWidth : 0;

   }

   //
   //void scroll_y::layout()
   //{

   //   BASE::layout();

   //   on_change_view_size();

   //}


   scroll::scroll()
   {
   }


   scroll::scroll(::aura::application * papp) :
      object(papp)
   {
   }

   scroll::~scroll()
   {
   }

   void scroll::install_message_handling(::message::dispatch * pinterface)
   {
      scroll_x::install_message_handling(pinterface);
      scroll_y::install_message_handling(pinterface);
   }

   void scroll::on_change_viewport_offset()
   {
      scroll_x::on_change_viewport_offset();
      scroll_y::on_change_viewport_offset();
   }
   void scroll::layout_scroll_bar()
   {
      scroll_x::layout_scroll_bar();
      scroll_y::layout_scroll_bar();
   }

   void scroll::on_change_view_size()
   {

      m_scrolldataHorz.m_bScroll = false;

      m_scrolldataVert.m_bScroll = false;

      m_scrolldataHorz.m_iWidth = GetSystemMetrics(SM_CXHSCROLL);

      m_scrolldataVert.m_iWidth = GetSystemMetrics(SM_CYVSCROLL);


      size sizeTotal = get_total_size();

      rect rectClient;

      GetClientRect(rectClient);

      LONG iTotalHeight = sizeTotal.cy;

      LONG iTotalWidth = sizeTotal.cx;

      LONG iClientHeight = rectClient.height();

      LONG iClientWidth = rectClient.width();

      LONG iScrollHeight = iClientHeight - GetSystemMetrics(SM_CYHSCROLL);

      LONG iscrollWidth = iClientWidth - GetSystemMetrics(SM_CXVSCROLL);

      if (iTotalWidth > iClientWidth)
      {

         m_scrolldataHorz.m_bScroll = true;

         if (iTotalHeight > iScrollHeight)
         {

            m_scrolldataVert.m_bScroll = true;

         }

      }
      else if (iTotalHeight > iClientHeight)
      {

         m_scrolldataVert.m_bScroll = true;

         if (iTotalWidth > iscrollWidth)
         {

            m_scrolldataHorz.m_bScroll = true;

         }

      }

      m_scrolldataHorz.m_bScroll = m_scrolldataHorz.m_bScrollEnable && m_scrolldataHorz.m_bScroll;

      m_scrolldataVert.m_bScroll = m_scrolldataVert.m_bScrollEnable && m_scrolldataVert.m_bScroll;

      rect rectScroll;

      GetScrollRect(rectScroll);

      m_scrolldataHorz.m_iPage = rectScroll.width();

      m_scrolldataVert.m_iPage = rectScroll.height();

      _001ConstrainXScrollPosition();

      _001ConstrainYScrollPosition();

      layout_scroll_bar();

      on_change_viewport_offset();

   }

   void scroll_x::create_x_scroll_bar(const RECT & rect)
   {

      if (m_pscrollbarHorz != NULL)
         return;

      scroll_bar * pbar = canew(simple_scroll_bar(get_app()));

      if (!pbar->create_window(::orientation_horizontal, WS_CHILD | WS_VISIBLE, null_rect(), this, 7000 + 1))
      {
         delete pbar;
         return;
      }

      m_pscrollbarHorz = pbar;

   }


   void scroll_y::create_y_scroll_bar(const RECT & rect)
   {

      if (m_pscrollbarVert != NULL)
         return;

      scroll_bar * pbar = canew(simple_scroll_bar(get_app()));

      if (!pbar->create_window(::orientation_vertical, WS_CHILD | WS_VISIBLE, null_rect(), this, 7002))
      {
         delete pbar;
         return;
      }

      m_pscrollbarVert = pbar;

   }


   void scroll::GetScrollRect(LPRECT lprect)
   {
      ::rect rectScroll;

      GetClientRect(rectScroll);

      if (m_scrolldataHorz.m_bScroll)
      {

         rectScroll.bottom -= GetSystemMetrics(SM_CYHSCROLL);

      }


      if (m_scrolldataVert.m_bScroll)
      {

         rectScroll.right -= GetSystemMetrics(SM_CXVSCROLL);

      }



      rectScroll.offset(get_viewport_offset());

      *lprect = rectScroll;

   }

   
   ::size scroll::get_total_size()
   {

      return m_sizeTotal;

   }


}  // namespace core






