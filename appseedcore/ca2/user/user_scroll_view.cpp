#include "StdAfx.h"

namespace user
{

   scroll_view::scroll_view(::ca::application * papp) :
      ca(papp)
   {
      m_pscrollbarHorz = NULL;
      m_pscrollbarVert = NULL;


      m_scrollinfo.m_ptScroll.x = 0;
      m_scrollinfo.m_ptScroll.y = 0;
      m_scrollinfo.m_rectMargin.left = 0;
      m_scrollinfo.m_rectMargin.top = 0;
      m_scrollinfo.m_rectMargin.right = 0;
      m_scrollinfo.m_rectMargin.bottom = 0;
      m_scrollinfo.m_bVScroll = false;
      m_scrollinfo.m_bHScroll = false;

   }

   scroll_view::~scroll_view()
   {
   }

   void scroll_view::GetClientRect(LPRECT lprect)
   {
      rect rectClient;
      control::GetClientRect(rectClient);
      rectClient.left               += m_scrollinfo.m_rectMargin.left;
      rectClient.top                += m_scrollinfo.m_rectMargin.top;
      rectClient.right              += m_scrollinfo.m_rectMargin.right;
      rectClient.bottom             += m_scrollinfo.m_rectMargin.bottom;
      m_scrollinfo.m_iScrollHeight  = GetSystemMetrics(SM_CYHSCROLL);
      m_scrollinfo.m_iScrollWidth   = GetSystemMetrics(SM_CXVSCROLL);

      m_scrollinfo.m_sizeClient.cx = rectClient.width();
      if(m_scrollinfo.m_bVScroll)
      {
         m_scrollinfo.m_sizeClient.cx -= m_scrollinfo.m_iScrollWidth;
      }
      m_scrollinfo.m_sizeClient.cy = rectClient.height();
      if(m_scrollinfo.m_bHScroll)
      {
         m_scrollinfo.m_sizeClient.cy -= m_scrollinfo.m_iScrollHeight;
      }
      
      m_scrollinfo.m_sizePage.cx    = m_scrollinfo.m_sizeClient.cx;
      m_scrollinfo.m_sizePage.cy    = m_scrollinfo.m_sizeClient.cy;

      m_scrollinfo.m_bVScroll       = m_scrollinfo.m_sizeTotal.cy > (rectClient.height() - m_scrollinfo.m_iScrollHeight);
      m_scrollinfo.m_bHScroll       = m_scrollinfo.m_sizeTotal.cx > (rectClient.width() - m_scrollinfo.m_iScrollWidth);


      _001UpdateScrollBars();

      *lprect = rectClient;
   }

   /*void scroll_view::GetClientRect(LPRECT lprect)
   {
      rect rect;
      GetClientRect(rect);
      ::copy(lprect, rect);
   }*/

   void scroll_view::LayoutScrollBars()
   {
      rect rectClient;

      GetClientRect(rectClient);
       

      int ifswp = SWP_SHOWWINDOW | SWP_NOCOPYBITS;

      if(m_pscrollbarHorz != NULL)
      {
         if(m_scrollinfo.m_bHScroll)
         {
            m_pscrollbarHorz->SetWindowPos(
               ZORDER_TOP,
               0,
               rectClient.bottom - m_scrollinfo.m_iScrollHeight,
               rectClient.width() - m_scrollinfo.m_iScrollWidth,
               m_scrollinfo.m_iScrollHeight,
               ifswp);
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
            m_pscrollbarVert->SetWindowPos(
               ZORDER_TOP,
               rectClient.right - m_scrollinfo.m_iScrollWidth,
               rectClient.top, 
               m_scrollinfo.m_iScrollWidth,
               rectClient.height() - m_scrollinfo.m_iScrollHeight - rectClient.top,
               ifswp);
         }
         else
         {
            m_pscrollbarVert->ShowWindow(SW_HIDE);
         }
      }
       
   }

   void scroll_view::_001OnCreate(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::create, pcreate, pobj);

      if(pcreate->previous())
         return;

      class rect rect;
      rect.null();

      if(m_pscrollbarHorz != NULL)
      {
         VERIFY(m_pscrollbarHorz->create(
            ::user::scroll_bar::orientation_vertical,
            WS_CHILD 
            | WS_VISIBLE,
            rect,
            this,
            1024));
      }

      rect.null();

      if(m_pscrollbarVert != NULL)
      {
         VERIFY(m_pscrollbarVert->create(
            ::user::scroll_bar::orientation_vertical,
            WS_CHILD 
            | WS_VISIBLE,
            rect,
            this,
            1025));
      }
   }

   void scroll_view::_001OnSize(gen::signal_object * pobj)
   {
      pobj->previous();
      LayoutScrollBars();
   }

   void scroll_view::_001OnUser9654(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj);
      if(pbase->m_wparam == 0)
      {
         if(pbase->m_lparam == 0)
         {
            _001RedrawWindow();
         }
      }
   }

   void scroll_view::_001OnVScroll(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::scroll, pscroll, pobj);
      keeper < bool > keepVScroll(&m_scrollinfo.m_bVScroll, true, false, true);
      m_scrollinfo.m_ptScroll.y = pscroll->m_nPos;
      PostMessage(WM_USER + 9654, 0, 0);
   }

   void scroll_view::_001OnHScroll(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::scroll, pscroll, pobj);
      keeper < bool > keepHScroll(&m_scrollinfo.m_bHScroll, true, false, true);
      m_scrollinfo.m_ptScroll.x = pscroll->m_nPos;
      PostMessage(WM_USER + 9654, 0, 0);
   }

   void scroll_view::_001UpdateScrollBars()
   {
      ::user::scroll_info si;

      if(m_pscrollbarHorz != NULL)
      {
         si.fMask       = SIF_ALL;
         si.nMin        = 0;
         si.nMax        = m_scrollinfo.m_sizeTotal.cx;
         si.nPage       = (uint) m_scrollinfo.m_sizePage.cx;
         si.nPos        = m_scrollinfo.m_ptScroll.x;
         si.nTrackPos   = m_scrollinfo.m_ptScroll.x;
         m_pscrollbarHorz->_001SetScrollInfo(&si);
      }

      if(m_pscrollbarVert != NULL)
      {
         si.fMask       = SIF_ALL;
         si.nMin        = 0;
         si.nMax        = m_scrollinfo.m_sizeTotal.cy;
         si.nPage       = (uint) m_scrollinfo.m_sizePage.cy;
         si.nPos        = m_scrollinfo.m_ptScroll.y;
         si.nTrackPos   = m_scrollinfo.m_ptScroll.y;
         m_pscrollbarVert->_001SetScrollInfo(&si);
      }


   }



   void scroll_view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      control::_001InstallMessageHandling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE,          pinterface, this, &scroll_view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_SIZE,            pinterface, this, &scroll_view::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_VSCROLL,         pinterface, this, &scroll_view::_001OnVScroll);
      IGUI_WIN_MSG_LINK(WM_HSCROLL,         pinterface, this, &scroll_view::_001OnHScroll);
      IGUI_WIN_MSG_LINK(WM_USER + 9654,     pinterface, this, &scroll_view::_001OnUser9654);
   }


}  // namespace ex1