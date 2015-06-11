#pragma once


namespace user
{


   class scroll_bar;


   class scroll_data
   {
   public:


      LONG        m_iPage;
      LONG        m_iLine;
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
      
      
      
      virtual void GetScrollRect(LPRECT lprect);
      virtual void send_scroll_message(::message::scroll * pscroll);
      virtual void on_change_view_size();
      virtual void on_change_viewport_offset();
      virtual void create_x_scroll_bar(const RECT & rect);
      virtual void _001LayoutXScrollBar();
      virtual void _001DeferCreateXScrollBar();
      virtual void _001OnDeferCreateXScrollBar();
      virtual void _001GetXScrollInfo(scroll_info & info);
      virtual void _001UpdateXScrollBar();
      virtual void _001ConstrainXScrollPosition();


      DECL_GEN_SIGNAL(_001OnHScroll);

      virtual int get_final_x_scroll_bar_width();

   };


   template < class BASE >
   scroll_x < BASE >::scroll_x()
   {

      m_scrolldataHorz.m_bScroll = false;
      m_scrolldataHorz.m_iPage = 0;
      m_scrolldataHorz.m_iLine = 0;
      m_scrolldataHorz.m_bScrollEnable = true;

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
   void scroll_x < BASE >::_001LayoutXScrollBar()
   {
      rect rectClient;

      GetClientRect(rectClient);

      int32_t ifswp = SWP_SHOWWINDOW | SWP_NOCOPYBITS;

      _001DeferCreateXScrollBar();

      if(m_pscrollbarHorz != NULL)
      {
         if(m_scrolldataHorz.m_bScroll)
         {
            m_pscrollbarHorz->SetWindowPos(ZORDER_TOP,0,rectClient.bottom - m_scrolldataHorz.m_iWidth,rectClient.width() - get_final_y_scroll_bar_width(),m_scrolldataHorz.m_iWidth,ifswp);
         }
         else
         {
            m_pscrollbarHorz->ShowWindow(SW_HIDE);
         }
      }

   }


   template < class BASE >
   void scroll_x < BASE >::_001OnDeferCreateXScrollBar()
   {

      if(m_scrolldataHorz.m_bScroll)
      {
         if(m_pscrollbarHorz == NULL)
            create_scroll_bar(null_rect(),orientation_horizontal);

      }


   }

   template < class BASE >
   void scroll_x < BASE >::_001DeferCreateXScrollBar()
   {

      bool bCreate = false;

      if(m_scrolldataHorz.m_bScroll)
      {

         if(m_pscrollbarHorz == NULL)
         {

            bCreate = true;

         }

      }


      if(bCreate)
      {

         _001OnDeferCreateXScrollBar();

      }

   }

   template < class BASE >
   void scroll_x < BASE >::_001OnHScroll(signal_details * pobj)
   {

      SCAST_PTR(::message::scroll,pscroll,pobj);

      keep < bool > keepHScroll(&m_scrolldataHorz.m_bHScroll,true,false,true);

      {

         synch_lock slUser(m_spmutex);

         set_viewport_offset_x(pscroll->m_nPos);

      }

   }


   template < class BASE >
   void scroll_x < BASE >::on_change_viewport_offset()
   {

      BASE::on_change_viewport_offset();

   }



   template < class BASE >
   void scroll_x < BASE >::_001ConstrainXScrollPosition()
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

      IGUI_WIN_MSG_LINK(WM_HSCROLL,pinterface,this,&scroll_x < BASE >::_001OnHScroll);

   }

   template < class BASE >
   void scroll_x < BASE >::create_x_scroll_bar(const RECT & rect)
   {

      if(m_pscrollbarHorz != NULL)
         return;

      scroll_bar * pbar = new simple_scroll_bar(get_app());

      if(!pbar->create_window(::orientation_horizontal,WS_CHILD | WS_VISIBLE,null_rect(),this,7000 + 1))
      {
         delete pbar;
         return;
      }

      m_pscrollbarHorz = pbar;

   }

   template < class BASE >
   void scroll_x < BASE >::on_change_view_size()
   {

      size sizeTotal = get_total_size();

      m_scrolldataHorz.m_iWidth  = GetSystemMetrics(SM_CXHSCROLL);

      rect rectClient;

      BASE::GetClientRect(rectClient);

      LONG iTotalHeight    = sizeTotal.cy;

      LONG iTotalWidth     = sizeTotal.cx;

      LONG iClientHeight   = rectClient.height();

      LONG iClientWidth    = rectClient.width();

      LONG iScrollHeight  = iClientHeight - GetSystemMetrics(SM_CYHSCROLL);

      LONG iScrollWidth   = iClientWidth - GetSystemMetrics(SM_CXVSCROLL);

      m_scrolldataHorz.m_bScroll = false;

      if(iTotalWidth > iClientWidth)
      {

         m_scrolldataHorz.m_bScroll = true;

      }
      else if(iTotalHeight > iClientHeight)
      {

         if(iTotalWidth > iScrollWidth)
         {

            m_scrolldataHorz.m_bScroll = true;

         }

      }

      m_scrolldataHorz.m_bScroll = m_scrolldataHorz.m_bScrollEnable && m_scrolldataHorz.m_bScroll;

      rect rectScroll;

      GetScrollRect(rectScroll);

      m_scrolldataHorz.m_iPage          = rectScroll.width();

      _001LayoutXScrollBar();

      on_change_viewport_offset();

   }

   template < class BASE >
   int scroll_x < BASE >::get_final_x_scroll_bar_width()
   {

      return m_scrolldataHorz.m_bScroll && m_scrolldataHorz.m_bScrollEnable ? m_scrolldataHorz.m_iWidth: BASE::get_final_x_scroll_bar_width();

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

      
      virtual void GetScrollRect(LPRECT lprect);
      virtual void send_scroll_message(::message::scroll * pscroll);
      virtual void on_change_view_size();
      virtual void on_change_viewport_offset();
      virtual int32_t get_wheel_scroll_delta();
      virtual void create_y_scroll_bar(const RECT & rect);
      virtual void _001LayoutYScrollBar();
      virtual void _001DeferCreateYScrollBar();
      virtual void _001OnDeferCreateYScrollBar();
      virtual void _001GetScrollInfo(scroll_info & info);
      virtual void _001UpdateYScrollBar();
      virtual void _001ConstrainYScrollPosition();


      DECL_GEN_SIGNAL(_001OnVScroll);
      DECL_GEN_SIGNAL(_001OnMouseWheel);


      virtual int get_final_y_scroll_bar_width();


   };

   template < class BASE >
   scroll_y < BASE >::scroll_y()
   {

      m_scrolldataVert.m_bScroll = false;
      m_scrolldataVert.m_iPage = 0;
      m_scrolldataVert.m_iLine = 0;
      m_scrolldataVert.m_bScrollEnable = true;

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
   void scroll_y < BASE >::_001LayoutYScrollBar()
   {
      rect rectClient;

      GetClientRect(rectClient);

      int32_t ifswp = SWP_SHOWWINDOW | SWP_NOCOPYBITS;

      _001DeferCreateTScrollBar();

      if(m_pscrollbarVert != NULL)
      {
         if(m_scrolldataVert.m_bScroll)
         {
            m_pscrollbarVert->SetWindowPos(ZORDER_TOP,rectClient.right - m_scrolldataVert.m_iWidth,rectClient.top,m_scrolldataVert.m_iScrollBarWidth,rectClient.height() - get_final_x_scroll_bar_widht() - rectClient.top,ifswp);
         }
         else
         {
            m_pscrollbarVert->ShowWindow(SW_HIDE);
         }
      }

   }



   template < class BASE >
   void scroll_y < BASE >::_001OnDeferCreateYScrollBar()
   {

      if(m_scrolldataVert.m_bScroll)
      {
         if(m_pscrollbarVert == NULL)
            create_y_scroll_bar(null_rect(),orientation_vertical);
      }

   }


   template < class BASE >
   void scroll_y < BASE >::_001DeferCreateYScrollBar()
   {

      bool bCreate = false;

      if(m_scrolldataVert.m_bScroll)
      {

         if(m_pscrollbarVert == NULL)
         {

            bCreate = true;

         }

      }

      if(bCreate)
      {

         _001OnDeferCreateYScrollBar();

      }

   }

   template < class BASE >
   void scroll_y < BASE >::_001OnVScroll(signal_details * pobj)
   {


      SCAST_PTR(::message::scroll,pscroll,pobj);


      keep < bool > keepVScroll(&m_scrolldataVert.m_bScroll,true,false,true);

      {

         synch_lock slUser(m_spmutex);

         set_viewport_offset_y(pscroll->m_nPos);

      }

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
   void scroll_y < BASE >::_001ConstrainYScrollPosition()
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

      IGUI_WIN_MSG_LINK(WM_VSCROLL,pinterface,this,&scroll_y < BASE >::_001OnVScroll);
      IGUI_WIN_MSG_LINK(WM_MOUSEWHEEL,pinterface,this,&scroll_y < BASE >::_001OnMouseWheel);

   }

   template < class BASE >
   void scroll_y < BASE >::create_y_scroll_bar(const RECT & rect)
   {

      if(m_pscrollbarVert != NULL)
         return;

      scroll_bar * pbar = new simple_scroll_bar(get_app());

      if(!pbar->create_window(::orientation_vertical,WS_CHILD | WS_VISIBLE,null_rect(),this,7002))
      {
         delete pbar;
         return;
      }

      m_pscrollbarVert = pbar;

   }

   template < class BASE >
   void scroll_y < BASE >::on_change_view_size()
   {

      size sizeTotal = get_total_size();

      m_scrolldataVert.m_iWidth   = GetSystemMetrics(SM_CXVSCROLL);

      rect rectClient;

      BASE::GetClientRect(rectClient);

      LONG iTotalHeight    = sizeTotal.cy;

      LONG iTotalWidth     = sizeTotal.cx;

      LONG iClientHeight   = rectClient.height();

      LONG iClientWidth    = rectClient.width();

      LONG iScrollHeight  = iClientHeight - GetSystemMetrics(SM_CYHSCROLL);

      LONG iScrollWidth   = iClientWidth - GetSystemMetrics(SM_CXVSCROLL);

      m_scrolldataVert.m_bScroll = false;

      if(iTotalWidth > iClientWidth)
      {

         if(iTotalHeight > iScrollHeight)
         {

            m_scrolldataVert.m_bScroll = true;

         }

      }
      else if(iTotalHeight > iClientHeight)
      {

         m_scrolldataVert.m_bScroll = true;

      }



      m_scrolldataVert.m_bScroll = m_scrolldataVert.m_bScrollEnable && m_scrolldataVert.m_bScroll;

      rect rectScroll;

      GetScrollRect(rectScroll);

      m_scrolldataVert.m_iPage          = rectScroll.height();

      _001LayoutYScrollBar();

      on_change_viewport_offset();

   }


   template < class BASE >
   int scroll_y < BASE >::get_final_y_scroll_bar_width()
   {

      return m_scrolldataVert.m_bScroll && m_scrolldataVert.m_bScrollEnable ? m_scrolldataVert.m_iWidth : BASE::get_final_y_scroll_bar_width();

   }

   //template < class BASE >
   //void scroll_y < BASE >::layout()
   //{

   //   BASE::layout();

   //   on_change_view_size();

   //}

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

