#include "StdAfx.h"


#ifdef Application
#undef Application
#endif

#define Application System



namespace npca2
{
   
   host_interaction::host_interaction(::ca::application * papp) :
      ::ca::ca(papp)
   {
      m_pframe = NULL;
   }

   host_interaction::~host_interaction()
   {
      if(m_papp != NULL)
      {
         try
         {
            delete m_papp;
         }
         catch(...)
         {
         }
      }
   }

   void host_interaction::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::user::interaction::_001InstallMessageHandling(pinterface);
//      IGUI_WIN_MSG_LINK(WM_SIZE        , pinterface, this, &host_interaction::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE   , pinterface, this, &host_interaction::_001OnMouseMove);
      IGUI_WIN_MSG_LINK(message_check  , pinterface, this, &host_interaction::_001OnCheck);
        IGUI_WIN_MSG_LINK(WM_CREATE        , pinterface, this, &host_interaction::_001OnCreate);
        
   }

   void host_interaction::_001OnMouseMove(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }
   
   void host_interaction::_001OnCreate(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      Application.m_bSessionSynchronizedCursor = false;
   }

   void host_interaction::_001OnCheck(gen::signal_object * pobj)
   {
      SCAST_PTR(user::win::message::base, pbase, pobj);
      if(pbase->m_wparam == 0)
      {
         pbase->set_lresult(m_pplugin->check((e_check) pbase->m_lparam) ? 1 : 0);
      }
      else if(pbase->m_wparam == 1)
      {
         m_pplugin->redraw();
      }
   }



   void host_interaction::_000OnDraw(::ca::graphics * pdc)
   {
      

      rect rectWindow;
      m_pguie->GetWindowRect(rectWindow);
      point ptPreviousViewportOrg = pdc->GetViewportOrg();
      pdc->SetViewportOrg(rectWindow.top_left());

      rect rectClient;
      GetClientRect(rectClient);
      /*TRIVERTEX v[4];
      GRADIENT_RECT    grect;

      v[0].x = 0;
      v[0].y = 0;
      v[0].Red = 240 << 8;
      v[0].Green = 255 << 8;
      v[0].Blue = 87 << 8;
      v[0].Alpha = 0;

      v[1].x = rectClient.width();
      v[1].y = rectClient.height();
      v[1].Red = 170 << 8;
      v[1].Green = 255 << 8;
      v[1].Blue = 87 << 8;
      v[1].Alpha = 0;

      grect.UpperLeft = 0;
      grect.LowerRight = 1;

      pdc->GradientFill(v, 2, &grect, 1, GRADIENT_FILL_RECT_V);*/

     /* pdc->FillSolidRect(rectClient, ::GetSysColor(COLOR_BTNFACE));*/


      _001DrawChildren(pdc);

      pdc->SetViewportOrg(rectWindow.top_left());
      pdc->SelectClipRgn(NULL);
      point ptCursor;
      Application.get_cursor_pos(&ptCursor);
      ScreenToClient(&ptCursor);
      ::visual::cursor * pcursor = Application.get_cursor();
      if(pcursor != NULL)
      {
         pcursor->to(pdc, ptCursor); 
      }
   }

   bool host_interaction::defer_check(e_check echeck)
   {

      if(!m_pplugin->is_ok())
         return false;

      return SendMessage((UINT)message_check, 0, (LPARAM) echeck) != 0;
   }


   void host_interaction::layout()
   {
      if(m_pframe != NULL)
      {
         class rect rect;
         GetClientRect(rect);
         m_pframe->SetWindowPos(0, 0, 0, rect.width(), rect.height(), SWP_SHOWWINDOW);
      }
      else
      {
         user::interaction * pui = get_top_child();
         if(pui != NULL)
         {
            class rect rectClient;
            GetClientRect(rectClient);
            class rect rectWindow;
            pui->GetWindowRect(rectWindow);
            ScreenToClient(rectWindow);
            if(rectWindow != rectClient)
            {
               pui->SetWindowPos(0, 0, 0, rectClient.width(), rectClient.height(), SWP_SHOWWINDOW);
            }
            else
            {
               pui->ShowWindow(SW_SHOW);
               pui->layout();
            }
         }
      }
   }

   BOOL host_interaction::IsWindowVisible()
   {
      return m_bVisible;
   }

   void host_interaction::GetWindowRect(__rect64 * lprect)
   {
      m_pplugin->get_window_rect(lprect);
   }
   

   BOOL host_interaction::RedrawWindow(LPCRECT lpRectUpdate, ::ca::rgn* prgnUpdate, UINT flags)
   { 
      UNREFERENCED_PARAMETER(lpRectUpdate);
      UNREFERENCED_PARAMETER(prgnUpdate);
      UNREFERENCED_PARAMETER(flags);
      if(!m_pplugin->m_bOnPaint && (::GetTickCount() - m_pplugin->m_last_redraw) >= 84)
      {
         PostMessage(message_check, 1);
      }
      /*nsPluginInstance * pplugin = m_pplugin;
      NPRect invalidRect;
      invalidRect.left = pplugin->m_rect.left;
      invalidRect.top = pplugin->m_rect.top;
      invalidRect.right = pplugin->m_rect.right;
      invalidRect.bottom = pplugin->m_rect.bottom;
      NPN_InvalidateRect(pplugin->m_instance, &invalidRect);
      NPN_ForceRedraw(pplugin->m_instance);*/
      return TRUE;
   }

   ::user::interaction * host_interaction::get_os_focus_uie()
   {
      return Application.window_from_os_data(m_pplugin->get_host_window());
   }

} // namespace npca2
