#include "framework.h"


namespace user
{


   scroll_bar::scroll_bar()
   {

      m_scrollinfo.nMin    = 0;
      m_scrollinfo.nMax    = 100;
      m_scrollinfo.nPage   = 10;
      m_scrollinfo.nPos    = 0;

   }

   scroll_bar::~scroll_bar()
   {

   }


   void scroll_bar::send_scroll_message(UINT nSBCode)
   {

      ::message::scroll * pscroll = new ::message::scroll(get_app());

      pscroll->m_nSBCode = nSBCode;

      if(m_bTracking)
      {

         pscroll->m_nPos = m_scrollinfo.nTrackPos;

      }
      else
      {

         pscroll->m_nPos = m_scrollinfo.nPos;

      }

      if(m_eorientation == orientation_horizontal)
      {

         pscroll->m_uiMessage = WM_HSCROLL;

      }
      else
      {

         pscroll->m_uiMessage = WM_VSCROLL;

      }

      sp(::user::interaction) pParentWnd = GetParent();

      pParentWnd->send(pscroll);

   }


   bool scroll_bar::create_window(e_orientation eorientation,uint32_t dwStyle,const RECT & rect,sp(::user::interaction)pParentWnd,UINT nID)
   {

      m_eorientation = eorientation;

      return ::user::interaction::create_window(NULL, NULL, dwStyle, rect, pParentWnd, nID);

   }


   point scroll_bar::get_ascendant_scroll_position()
   {

      if(GetParent() == NULL)
         return point(0,0);

      return GetParent()->get_ascendant_scroll_position();

   }


   point scroll_bar::get_parent_scroll_position()
   {

      return point(0,0);

   }


} // namespace user









