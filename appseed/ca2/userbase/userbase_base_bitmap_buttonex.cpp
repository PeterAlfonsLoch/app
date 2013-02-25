#include "framework.h"

namespace userbase
{

   bitmap_button::bitmap_button(::ca::application * papp) :
      ca(papp),
      ::user::button(papp),
      ::userbase::button(papp)
   {
      m_bHover          = false;
      m_bCommandEnable  = true;
   }

   bitmap_button::~bitmap_button()
   {
   }

   void bitmap_button::install_message_handling(::ca::message::dispatch * pinterface)
   {
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &bitmap_button::_001OnMouseMove);
   }

   bool bitmap_button::LoadBitmaps(
      const char * lpszBitmapResource,
      const char * lpszBitmapResourceSel,
      const char * lpszBitmapResourceFocus,
      const char * lpszBitmapResourceDisabled,
      const char * lpszBitmapResourceHover)
   {
      UNREFERENCED_PARAMETER(lpszBitmapResource);
      UNREFERENCED_PARAMETER(lpszBitmapResourceSel);
      UNREFERENCED_PARAMETER(lpszBitmapResourceFocus);
      UNREFERENCED_PARAMETER(lpszBitmapResourceDisabled);
      UNREFERENCED_PARAMETER(lpszBitmapResourceHover);
       throw not_implemented(get_app());
       /*
       if (!m_bitmap.LoadBitmap(lpszBitmapResource))
       {
           TRACE0("Failed to load bitmap for normal image.\n");
           return FALSE;   // need this one image
       }
       bool bAllLoaded = TRUE;
       if (lpszBitmapResourceSel != NULL)
       {
           if (!m_bitmapSel.LoadBitmap(lpszBitmapResourceSel))
           {
               TRACE0("Failed to load bitmap for selected image.\n");
               bAllLoaded = FALSE;
           }
       }
       if (lpszBitmapResourceFocus != NULL)
       {
           if (!m_bitmapFocus.LoadBitmap(lpszBitmapResourceFocus))
               bAllLoaded = FALSE;
       }
       if (lpszBitmapResourceDisabled != NULL)
       {
           if (!m_bitmapDisabled.LoadBitmap(lpszBitmapResourceDisabled))
               bAllLoaded = FALSE;
       }
       if (lpszBitmapResourceHover != NULL)
       {
           if (!m_bitmapHover.LoadBitmap(lpszBitmapResourceHover))
               bAllLoaded = FALSE;
       }*/
       //return bAllLoaded;
   }


   void bitmap_button::ResizeToFit()
   {

      class size size = m_bitmap.get_size();

      SetWindowPos(0, 0, 0, size.cx, size.cy, SWP_NOMOVE | SWP_NOZORDER);

   }

   void bitmap_button::_001OnMouseMove(::ca::signal_object * pobj)
   {
      UpdateHover();
      pobj->previous();
   }


#ifdef WINDOWSEX

   void bitmap_button::DrawItem(LPDRAWITEMSTRUCT lpDIS)
   {
       ASSERT(lpDIS != NULL);
       // must have at least the first bitmap loaded before calling DrawItem
       ASSERT(m_bitmap.get_os_data() != NULL);     // required

      UpdateHover();

       // use the main bitmap for up, the selected bitmap for down
       ::ca::bitmap* pBitmap = &m_bitmap;
       UINT state = lpDIS->itemState;
      if(!IsControlCommandEnabled())
         state = ODS_DISABLED;

       if ((state & ODS_SELECTED) && m_bitmapSel.get_os_data() != NULL)
           pBitmap = &m_bitmapSel;
      else if(m_bHover && ((state & ODS_DISABLED) == 0) && m_bitmapHover.get_os_data() != NULL)
           pBitmap = &m_bitmapHover;
       else if ((state & ODS_FOCUS) && m_bitmapFocus.get_os_data() != NULL)
           pBitmap = &m_bitmapFocus;   // third image for focused
       else if ((state & ODS_DISABLED) && m_bitmapDisabled.get_os_data() != NULL)
           pBitmap = &m_bitmapDisabled;   // last image for disabled

       throw not_implemented(get_app());
       // draw the whole button
       /*::ca::graphics * pgraphics = ::ca::graphics_sp::from_handle(lpDIS->hDC);
       ::ca::graphics_sp memDC;
       memDC.CreateCompatibleDC(pgraphics);
       ::ca::bitmap* pOld = memDC.SelectObject(pBitmap);
       if (pOld == NULL)
           return;     // destructors will clean up

       rect rect;
       rect.copy(&lpDIS->rcItem);
       pgraphics->BitBlt(rect.left, rect.top, rect.width(), rect.height(),
           &memDC, 0, 0, SRCCOPY);
       memDC.SelectObject(pOld);*/
   }

#endif

   void bitmap_button::UpdateHover()
   {
      point point;
      GetCursorPos(&point);

      if(m_bHover || System.get_capture_uie() == this)
      {
         rect rectClient;
         GetWindowRect(rectClient);
         if(!rectClient.contains(point))
         {
             m_bHover = false;
            if(System.get_capture_uie() == this)
            {
               System.release_capture_uie();
            }
            RedrawWindow();
         }
         else
         {
            m_bHover = true;
            if(System.get_capture_uie() != this)
            {
               set_capture();
            }
         }
      }
      else
      {
         if(!m_bHover)
         {
            rect rectClient;
            GetWindowRect(rectClient);
            if(rectClient.contains(point))
            {
                m_bHover = true;
               set_capture();
               RedrawWindow();
            }
         }
      }

   }

   void bitmap_button::pre_translate_message(::ca::signal_object * pobj)
   {
      // Relay events from this button to the tool tip tool handler
      BaseToolTipRelayEvent(pobj);
      return ::userbase::button::pre_translate_message(pobj);
   }


   void bitmap_button::BaseToolTipGetRect(LPRECT lprect)
   {
      // use ::ca::window client rect as the tool rect
      GetClientRect(lprect);
   }

   int32_t bitmap_button::BaseToolTipGetIndex()
   {
      // use ::ca::window dialog control id as the index
      return (int32_t) GetDlgCtrlId();
   }


   void bitmap_button::message_handler(::ca::signal_object * pobj)
   {
      BaseControlExWndProcBefore(pobj);
      if(pobj->m_bRet)
         return;

      return ::userbase::button::message_handler(pobj);
   }

} // namespace userbase
