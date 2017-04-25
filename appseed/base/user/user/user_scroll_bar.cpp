//#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"


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

      sp(::message::scroll) pscroll = canew(::message::scroll(get_app()));

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


   point scroll_bar::get_ascendant_viewport_offset()
   {

      if(GetParent() == NULL)
         return point(0,0);

      return GetParent()->get_ascendant_viewport_offset();

   }


   point scroll_bar::get_parent_viewport_offset()
   {

      return point(0,0);

   }


   void scroll_bar::_001OnClip(::draw2d::graphics * pgraphics)
   {

      //return;



      try
      {

         rect rectClip;

         ::aura::draw_context * pdrawcontext = pgraphics->::core::simple_chain < ::aura::draw_context >::get_last();

         rect rectClient;

         bool bFirst = true;

         if (pdrawcontext != NULL)
         {

            rectClient = pdrawcontext->m_rectWindow;

            ScreenToClient(rectClient);

            rectClient.bottom++;
            rectClient.right++;

            rectClip = rectClient;

            bFirst = false;

         }

         ::user::interaction * pui = this;

         ::rect rectFocus;

         index i = 0;

         while (pui != NULL)
         {

            if (i != 1)
            {

               pui->GetWindowRect(rectClient);

               pui->GetFocusRect(rectFocus);

               rectFocus.offset(rectClient.top_left());

               ScreenToClient(rectFocus);

               rectFocus.bottom++;
               rectFocus.right++;

               pgraphics->IntersectClipRect(rectFocus);

            }

            i++;

            pui = pui->GetParent();

         }

      }
      catch (...)
      {

         throw simple_exception(::get_thread_app(), "no more a window");

      }

   }




} // namespace user









