#pragma once


namespace user
{


   class scroll_bar;


   class scroll_data
   {
   public:
      LONG        m_iPage;
      LONG        m_iLing;
      bool        m_bScroll;
      int32_t     m_iWidth;
      bool        m_bScrollEnable;
   };


   template < class BASE >
   class scroll_x :
      virtual public BASE
   {
   public:


      sp(scroll_bar)    m_pscrollbarHorz;
      scroll_data       m_scrolldataHorz;


      scroll_x();
      virtual ~scroll_x();


      virtual void install_message_handling(::message::dispatch * pinterface);
      virtual void on_change_view_size();
      virtual void _001LayoutScrollBars();
      virtual void _001DeferCreateScrollBars();
      virtual void _001OnDeferCreateScrollBars();
      virtual void GetScrollRect(LPRECT lprect);
      virtual void create_scroll_bar(const RECT & rect, e_orientation eorientation);
      virtual int32_t get_wheel_scroll_delta();
      virtual void _001GetScrollInfo(scroll_info & info);
      virtual void _001UpdateScrollBars();
      virtual void _001ConstrainScrollPosition();
      virtual void on_change_viewport_offset();
      virtual void send_scroll_message(::message::scroll * pscroll);


      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnSize);
      DECL_GEN_SIGNAL(_001OnVScroll);
      DECL_GEN_SIGNAL(_001OnHScroll);
      DECL_GEN_SIGNAL(_001OnMouseWheel);
      DECL_GEN_SIGNAL(_001OnUser9654);


      virtual int get_final_x_scroll_bar_width();
      virtual void layout();
      virtual void GetClientRect(LPRECT lprect);

   };

   template < class BASE >
   scroll_x < BASE >::scroll_x()
   {

      m_scrolldata.m_bVScroll = false;
      m_scrolldata.m_bHScroll = false;
      m_scrolldata.m_sizePage.cx = 0;
      m_scrolldata.m_sizePage.cy = 0;
      m_scrolldata.m_sizeLine.cx = 0;
      m_scrolldata.m_sizeLine.cy = 0;
      m_scrolldata.m_bHScrollBarEnable = true;
      m_scrolldata.m_bVScrollBarEnable = true;

   }
   template < class BASE >
   scroll_x < BASE >::~scroll_x()
   {
   }

   template < class BASE >
   void scroll_x < BASE >::GetScrollRect(LPRECT lprect)
   {

      ::rect rectScroll;

      GetClientRect(rectScroll);

      rectScroll.offset(get_viewport_offset());

      *lprect = rectScroll;

   }
   template < class BASE >
   void scroll_x < BASE >::_001LayoutScrollBars()
   {
      rect rectClient;

      GetClientRect(rectClient);

      int32_t ifswp = SWP_SHOWWINDOW | SWP_NOCOPYBITS;

      _001DeferCreateScrollBars();

      if(m_pscrollbarHorz != NULL)
      {
         if(m_scrolldata.m_bHScroll)
         {
            m_pscrollbarHorz->SetWindowPos(ZORDER_TOP,0,rectClient.bottom - m_scrolldata.m_iScrollBarHeight,rectClient.width() - (m_scrolldata.m_bVScroll ? m_scrolldata.m_iScrollBarWidth : 0),m_scrolldata.m_iScrollBarHeight,ifswp);
         }
         else
         {
            m_pscrollbarHorz->ShowWindow(SW_HIDE);
         }
      }

      if(m_pscrollbarVert != NULL)
      {
         if(m_scrolldata.m_bVScroll)
         {
            m_pscrollbarVert->SetWindowPos(ZORDER_TOP,rectClient.right - m_scrolldata.m_iScrollBarWidth,rectClient.top,m_scrolldata.m_iScrollBarWidth,rectClient.height() - (m_scrolldata.m_bHScroll ? m_scrolldata.m_iScrollBarHeight : 0) - rectClient.top,ifswp);
         }
         else
         {
            m_pscrollbarVert->ShowWindow(SW_HIDE);
         }
      }

   }
   template < class BASE >
   void scroll_x < BASE >::_001OnDeferCreateScrollBars()
   {

      if(m_scrolldata.m_bHScroll)
      {
         if(m_pscrollbarHorz == NULL)
            create_scroll_bar(null_rect(),orientation_horizontal);

      }

      if(m_scrolldata.m_bVScroll)
      {
         if(m_pscrollbarVert == NULL)
            create_scroll_bar(null_rect(),orientation_vertical);
      }

   }

   template < class BASE >
   void scroll_x < BASE >::_001DeferCreateScrollBars()
   {

      bool bCreate = false;

      if(m_scrolldata.m_bHScroll)
      {

         if(m_pscrollbarHorz == NULL)
         {

            bCreate = true;

         }

      }

      if(m_scrolldata.m_bVScroll)
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
   template < class BASE >
   void scroll_x < BASE >::_001OnCreate(signal_details * pobj)
   {

      SCAST_PTR(::message::create,pcreate,pobj);

      if(pcreate->previous())
         return;

   }
   template < class BASE >
   void scroll_x < BASE >::_001OnSize(signal_details * pobj)
   {
      pobj->previous();
      _001LayoutScrollBars();
   }
   template < class BASE >
   void scroll_x < BASE >::_001OnUser9654(signal_details * pobj)
   {
      SCAST_PTR(::message::base,pbase,pobj);
      if(pbase->m_wparam == 0)
      {
         if(pbase->m_lparam == 0)
         {
            _001RedrawWindow();
         }
      }
   }
   template < class BASE >
   void scroll_x < BASE >::_001OnVScroll(signal_details * pobj)
   {


      SCAST_PTR(::message::scroll,pscroll,pobj);


      keep < bool > keepVScroll(&m_scrolldata.m_bVScroll,true,false,true);

      {

         synch_lock slUser(m_spmutex);

         set_viewport_offset_y(pscroll->m_nPos);

      }

      post_message(WM_USER + 9654);


   }

   template < class BASE >
   void scroll_x < BASE >::_001OnHScroll(signal_details * pobj)
   {


      SCAST_PTR(::message::scroll,pscroll,pobj);


      keep < bool > keepHScroll(&m_scrolldata.m_bHScroll,true,false,true);


      {

         //         synch_lock slUser(&user_mutex());
         synch_lock slUser(m_spmutex);

         set_viewport_offset_x(pscroll->m_nPos);

      }

      post_message(WM_USER + 9654);


   }
   template < class BASE >
   int32_t scroll_x < BASE >::get_wheel_scroll_delta()
   {

      return 1;

   }


   template < class BASE >
   void scroll_x < BASE >::on_change_viewport_offset()
   {

      BASE::on_change_viewport_offset();

   }


   template < class BASE >
   void scroll_x < BASE >::_001OnMouseWheel(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse_wheel,pmousewheel,pobj);

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

      m_iWheelDelta -= (int16_t)(WHEEL_DELTA * iDelta);

      offset_viewport_offset_y(- iDelta * get_wheel_scroll_delta());

      pmousewheel->set_lresult(0);

      pmousewheel->m_bRet = true;


   }
   template < class BASE >
   void scroll_x < BASE >::_001ConstrainScrollPosition()
   {

      size sizeTotal = get_total_size();

      point ptOffset = get_viewport_offset();

      if(ptOffset.y < 0)
      {
         ptOffset.y = 0;
      }
      else
      {
         if(ptOffset.y > sizeTotal.cy)
            ptOffset.y = sizeTotal.cy;
      }

      if(ptOffset.x < 0)
      {
         ptOffset.x = 0;
      }
      else
      {
         if(ptOffset.x > sizeTotal.cx)
            ptOffset.x = sizeTotal.cx;
      }

      if(ptOffset != get_viewport_offset())
      {

         set_viewport_offset(ptOffset.x,ptOffset.y);

      }

   }





   template < class BASE >
   void scroll_x < BASE >::install_message_handling(::message::dispatch * pinterface)
   {


      BASE::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_CREATE,pinterface,this,&scroll_x < BASE >::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_SIZE,pinterface,this,&scroll_x < BASE >::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_VSCROLL,pinterface,this,&scroll_x < BASE >::_001OnVScroll);
      IGUI_WIN_MSG_LINK(WM_HSCROLL,pinterface,this,&scroll_x < BASE >::_001OnHScroll);
      IGUI_WIN_MSG_LINK(WM_MOUSEWHEEL,pinterface,this,&scroll_x < BASE >::_001OnMouseWheel);

      IGUI_WIN_MSG_LINK(WM_USER + 9654,pinterface,this,&scroll_x < BASE >::_001OnUser9654);


   }

   template < class BASE >
   void scroll_x < BASE >::create_scroll_bar(const RECT & rect,e_orientation eorientation)
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

      if(!pbar->create_window(eorientation,WS_CHILD | WS_VISIBLE,null_rect(),this,7000 + eorientation))
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
   template < class BASE >
   void scroll_x < BASE >::GetClientRect(LPRECT lprect)
   {

      ::rect rectClient;

      ::user::BASE::GetClientRect(rectClient);

      if(m_scrolldata.m_bVScroll)
      {

         rectClient.right -= m_scrolldata.m_iScrollBarWidth;

      }

      if(m_scrolldata.m_bHScroll)
      {

         rectClient.bottom -= m_scrolldata.m_iScrollBarHeight;

      }

      *lprect = rectClient;

   }

   template < class BASE >
   void scroll_x < BASE >::on_change_view_size()
   {

      size sizeTotal = get_total_size();

      m_scrolldata.m_iScrollBarHeight  = GetSystemMetrics(SM_CXHSCROLL);

      m_scrolldata.m_iScrollBarWidth   = GetSystemMetrics(SM_CXVSCROLL);

      rect rectClient;

      ::user::BASE::GetClientRect(rectClient);

      LONG iTotalHeight    = sizeTotal.cy;

      LONG iTotalWidth     = sizeTotal.cx;

      LONG iClientHeight   = rectClient.height();

      LONG iClientWidth    = rectClient.width();

      LONG iScrollHeight  = iClientHeight - GetSystemMetrics(SM_CYHSCROLL);

      LONG iScrollWidth   = iClientWidth - GetSystemMetrics(SM_CXVSCROLL);

      m_scrolldata.m_bHScroll = false;

      m_scrolldata.m_bVScroll = false;

      if(iTotalWidth > iClientWidth)
      {

         m_scrolldata.m_bHScroll = true;

         if(iTotalHeight > iScrollHeight)
         {

            m_scrolldata.m_bVScroll = true;

         }

      }
      else if(iTotalHeight > iClientHeight)
      {

         m_scrolldata.m_bVScroll = true;

         if(iTotalWidth > iScrollWidth)
         {

            m_scrolldata.m_bHScroll = true;

         }

      }

      if(m_scrolldata.m_bVScroll)
      {

         //m_scrolldata.m_sizeClient.cx = iScrollWidth;

      }
      else
      {

         //m_scrolldata.m_sizeClient.cx = iClientWidth;

      }

      if(m_scrolldata.m_bHScroll)
      {

         //m_scrolldata.m_sizeClient.cy = iScrollHeight;

      }
      else
      {

         //m_scrolldata.m_sizeClient.cy = iClientHeight;

      }

      m_scrolldata.m_bVScroll = m_scrolldata.m_bVScrollBarEnable && m_scrolldata.m_bVScroll;

      m_scrolldata.m_bHScroll = m_scrolldata.m_bHScrollBarEnable && m_scrolldata.m_bHScroll;

      rect rectScroll;

      GetScrollRect(rectScroll);

      m_scrolldata.m_sizePage          = rectScroll.size();

      _001LayoutScrollBars();

      on_change_viewport_offset();

   }

   template < class BASE >
   int scroll_x < BASE >::get_final_x_scroll_bar_width()
   {

      return m_scrolldataHorz.m_bScroll && m_scrolldataHorz.m_bScrollEnable ? m_iScrollBarWidth : BASE::get_final_x_scroll_bar_width(); 

   }

   template < class BASE >
   void scroll_x < BASE >::layout()
   {

      ::user::BASE::layout();

      on_change_view_size();

   }

































   template < class BASE >
   class scroll_y:
      virtual public BASE
   {
   public:


      sp(scroll_bar)       m_pscrollbarVert;
      scroll_data          m_scrolldataVert;
      int16_t              m_iWheelDelta;


      scroll_y();
      virtual ~scroll_y();

      
      virtual void install_message_handling(::message::dispatch * pinterface);

      
      virtual void on_change_view_size();
      virtual void _001LayoutScrollBars();
      virtual void _001DeferCreateScrollBars();
      virtual void _001OnDeferCreateScrollBars();
      virtual void GetScrollRect(LPRECT lprect);
      virtual void create_scroll_bar(const RECT & rect,e_orientation eorientation);
      virtual int32_t get_wheel_scroll_delta();
      virtual void _001GetScrollInfo(scroll_info & info);
      virtual void _001UpdateScrollBars();
      virtual void _001ConstrainScrollPosition();
      virtual void on_change_viewport_offset();
      virtual void send_scroll_message(::message::scroll * pscroll);


      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnSize);
      DECL_GEN_SIGNAL(_001OnVScroll);
      DECL_GEN_SIGNAL(_001OnHScroll);
      DECL_GEN_SIGNAL(_001OnMouseWheel);
      DECL_GEN_SIGNAL(_001OnUser9654);


      virtual int get_final_y_scroll_bar_width();
      virtual void layout();
      virtual void GetClientRect(LPRECT lprect);


   };

   template < class BASE >
   scroll_y < BASE >::scroll_y()
   {

      m_scrolldata.m_bVScroll = false;
      m_scrolldata.m_bHScroll = false;
      m_scrolldata.m_sizePage.cx = 0;
      m_scrolldata.m_sizePage.cy = 0;
      m_scrolldata.m_sizeLine.cx = 0;
      m_scrolldata.m_sizeLine.cy = 0;
      m_scrolldata.m_bHScrollBarEnable = true;
      m_scrolldata.m_bVScrollBarEnable = true;

   }
   template < class BASE >
   scroll_y < BASE >::~scroll_y()
   {
   }
   template < class BASE >
   void scroll_y < BASE >::GetScrollRect(LPRECT lprect)
   {

      ::rect rectScroll;

      GetClientRect(rectScroll);

      rectScroll.offset(get_viewport_offset());

      *lprect = rectScroll;

   }
   template < class BASE >
   void scroll_y < BASE >::_001LayoutScrollBars()
   {
      rect rectClient;

      GetClientRect(rectClient);

      int32_t ifswp = SWP_SHOWWINDOW | SWP_NOCOPYBITS;

      _001DeferCreateScrollBars();

      if(m_pscrollbarHorz != NULL)
      {
         if(m_scrolldata.m_bHScroll)
         {
            m_pscrollbarHorz->SetWindowPos(ZORDER_TOP,0,rectClient.bottom - m_scrolldata.m_iScrollBarHeight,rectClient.width() - (m_scrolldata.m_bVScroll ? m_scrolldata.m_iScrollBarWidth : 0),m_scrolldata.m_iScrollBarHeight,ifswp);
         }
         else
         {
            m_pscrollbarHorz->ShowWindow(SW_HIDE);
         }
      }

      if(m_pscrollbarVert != NULL)
      {
         if(m_scrolldata.m_bVScroll)
         {
            m_pscrollbarVert->SetWindowPos(ZORDER_TOP,rectClient.right - m_scrolldata.m_iScrollBarWidth,rectClient.top,m_scrolldata.m_iScrollBarWidth,rectClient.height() - (m_scrolldata.m_bHScroll ? m_scrolldata.m_iScrollBarHeight : 0) - rectClient.top,ifswp);
         }
         else
         {
            m_pscrollbarVert->ShowWindow(SW_HIDE);
         }
      }

   }
   template < class BASE >
   void scroll_y < BASE >::_001OnDeferCreateScrollBars()
   {

      if(m_scrolldata.m_bHScroll)
      {
         if(m_pscrollbarHorz == NULL)
            create_scroll_bar(null_rect(),orientation_horizontal);

      }

      if(m_scrolldata.m_bVScroll)
      {
         if(m_pscrollbarVert == NULL)
            create_scroll_bar(null_rect(),orientation_vertical);
      }

   }


   template < class BASE >
   void scroll_y < BASE >::_001DeferCreateScrollBars()
   {

      bool bCreate = false;

      if(m_scrolldata.m_bHScroll)
      {

         if(m_pscrollbarHorz == NULL)
         {

            bCreate = true;

         }

      }

      if(m_scrolldata.m_bVScroll)
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
   template < class BASE >
   void scroll_y < BASE >::_001OnCreate(signal_details * pobj)
   {

      SCAST_PTR(::message::create,pcreate,pobj);

      if(pcreate->previous())
         return;

   }
   template < class BASE >
   void scroll_y < BASE >::_001OnSize(signal_details * pobj)
   {
      pobj->previous();
      _001LayoutScrollBars();
   }
   template < class BASE >
   void scroll_y < BASE >::_001OnUser9654(signal_details * pobj)
   {
      SCAST_PTR(::message::base,pbase,pobj);
      if(pbase->m_wparam == 0)
      {
         if(pbase->m_lparam == 0)
         {
            _001RedrawWindow();
         }
      }
   }
   template < class BASE >
   void scroll_y < BASE >::_001OnVScroll(signal_details * pobj)
   {


      SCAST_PTR(::message::scroll,pscroll,pobj);


      keep < bool > keepVScroll(&m_scrolldata.m_bVScroll,true,false,true);

      {

         synch_lock slUser(m_spmutex);

         set_viewport_offset_y(pscroll->m_nPos);

      }

      post_message(WM_USER + 9654);


   }

   template < class BASE >
   void scroll_y < BASE >::_001OnHScroll(signal_details * pobj)
   {


      SCAST_PTR(::message::scroll,pscroll,pobj);


      keep < bool > keepHScroll(&m_scrolldata.m_bHScroll,true,false,true);


      {

         //         synch_lock slUser(&user_mutex());
         synch_lock slUser(m_spmutex);

         set_viewport_offset_x(pscroll->m_nPos);

      }

      post_message(WM_USER + 9654);


   }
   template < class BASE >
   int32_t scroll_y < BASE >::get_wheel_scroll_delta()
   {

      return 1;

   }


   template < class BASE >
   void scroll_y < BASE >::on_change_viewport_offset()
   {

      BASE::on_change_viewport_offset();

   }

   template < class BASE >
   void scroll_y < BASE >::_001OnMouseWheel(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse_wheel,pmousewheel,pobj);

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

      m_iWheelDelta -= (int16_t)(WHEEL_DELTA * iDelta);

      offset_viewport_offset_y(- iDelta * get_wheel_scroll_delta());

      pmousewheel->set_lresult(0);

      pmousewheel->m_bRet = true;


   }
   template < class BASE >
   void scroll_y < BASE >::_001ConstrainScrollPosition()
   {

      size sizeTotal = get_total_size();

      point ptOffset = get_viewport_offset();

      if(ptOffset.y < 0)
      {
         ptOffset.y = 0;
      }
      else
      {
         if(ptOffset.y > sizeTotal.cy)
            ptOffset.y = sizeTotal.cy;
      }

      if(ptOffset.x < 0)
      {
         ptOffset.x = 0;
      }
      else
      {
         if(ptOffset.x > sizeTotal.cx)
            ptOffset.x = sizeTotal.cx;
      }

      if(ptOffset != get_viewport_offset())
      {

         set_viewport_offset(ptOffset.x,ptOffset.y);

      }

   }



   template < class BASE >
   void scroll_y < BASE >::install_message_handling(::message::dispatch * pinterface)
   {


      BASE::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_CREATE,pinterface,this,&scroll_y < BASE >::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_SIZE,pinterface,this,&scroll_y < BASE >::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_VSCROLL,pinterface,this,&scroll_y < BASE >::_001OnVScroll);
      IGUI_WIN_MSG_LINK(WM_HSCROLL,pinterface,this,&scroll_y < BASE >::_001OnHScroll);
      IGUI_WIN_MSG_LINK(WM_MOUSEWHEEL,pinterface,this,&scroll_y < BASE >::_001OnMouseWheel);

      IGUI_WIN_MSG_LINK(WM_USER + 9654,pinterface,this,&scroll_y < BASE >::_001OnUser9654);


   }

   template < class BASE >
   void scroll_y < BASE >::create_scroll_bar(const RECT & rect,e_orientation eorientation)
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

      if(!pbar->create_window(eorientation,WS_CHILD | WS_VISIBLE,null_rect(),this,7000 + eorientation))
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
   template < class BASE >
   void scroll_y < BASE >::GetClientRect(LPRECT lprect)
   {

      ::rect rectClient;

      ::user::BASE::GetClientRect(rectClient);

      if(m_scrolldata.m_bVScroll)
      {

         rectClient.right -= m_scrolldata.m_iScrollBarWidth;

      }

      if(m_scrolldata.m_bHScroll)
      {

         rectClient.bottom -= m_scrolldata.m_iScrollBarHeight;

      }

      *lprect = rectClient;

   }

   template < class BASE >
   void scroll_y < BASE >::on_change_view_size()
   {

      size sizeTotal = get_total_size();

      m_scrolldata.m_iScrollBarHeight  = GetSystemMetrics(SM_CXHSCROLL);

      m_scrolldata.m_iScrollBarWidth   = GetSystemMetrics(SM_CXVSCROLL);

      rect rectClient;

      ::user::BASE::GetClientRect(rectClient);

      LONG iTotalHeight    = sizeTotal.cy;

      LONG iTotalWidth     = sizeTotal.cx;

      LONG iClientHeight   = rectClient.height();

      LONG iClientWidth    = rectClient.width();

      LONG iScrollHeight  = iClientHeight - GetSystemMetrics(SM_CYHSCROLL);

      LONG iScrollWidth   = iClientWidth - GetSystemMetrics(SM_CXVSCROLL);

      m_scrolldata.m_bHScroll = false;

      m_scrolldata.m_bVScroll = false;

      if(iTotalWidth > iClientWidth)
      {

         m_scrolldata.m_bHScroll = true;

         if(iTotalHeight > iScrollHeight)
         {

            m_scrolldata.m_bVScroll = true;

         }

      }
      else if(iTotalHeight > iClientHeight)
      {

         m_scrolldata.m_bVScroll = true;

         if(iTotalWidth > iScrollWidth)
         {

            m_scrolldata.m_bHScroll = true;

         }

      }

      if(m_scrolldata.m_bVScroll)
      {

         //m_scrolldata.m_sizeClient.cx = iScrollWidth;

      }
      else
      {

         //m_scrolldata.m_sizeClient.cx = iClientWidth;

      }

      if(m_scrolldata.m_bHScroll)
      {

         //m_scrolldata.m_sizeClient.cy = iScrollHeight;

      }
      else
      {

         //m_scrolldata.m_sizeClient.cy = iClientHeight;

      }

      m_scrolldata.m_bVScroll = m_scrolldata.m_bVScrollBarEnable && m_scrolldata.m_bVScroll;

      m_scrolldata.m_bHScroll = m_scrolldata.m_bHScrollBarEnable && m_scrolldata.m_bHScroll;

      rect rectScroll;

      GetScrollRect(rectScroll);

      m_scrolldata.m_sizePage          = rectScroll.size();

      _001LayoutScrollBars();

      on_change_viewport_offset();

   }


   template < class BASE >
   int scroll_y < BASE >::get_final_y_scroll_bar_width()
   {

      return m_scrolldataVert.m_bScroll && m_scrolldataVert.m_bScrollEnable ? m_iScrollWidth : BASE::get_final_y_scroll_bar_width();

   }

   template < class BASE >
   void scroll_y < BASE >::layout()
   {

      ::user::BASE::layout();

      on_change_view_size();

   }

   template < class BASE >
   class scroll:
      virtual public ::user::scroll_y < ::user::scroll_x < BASE > >
   {
   public:

      scroll()
      {
      }


      scroll(::aura::application * papp):
         object(papp)
      {
      }

      virtual ~scroll()
      {
      }


   };




} // namespace user

