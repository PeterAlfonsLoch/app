#include "framework.h"


namespace user
{


   button::button(::ca::application * papp) :
      ca(papp),
      ::user::interaction(papp),
      m_istrButtonText(papp)
   {
      m_iHover    = -1;
      m_bEnabled  = true;
      m_echeck    = check::unchecked;
      m_pschema   = NULL;
   }

   button::~button()
   {

   }


   void button::install_message_handling(::gen::message::dispatch * pinterface)
   {
      ::user::window_interface::install_message_handling(pinterface);

      //   IGUI_WIN_MSG_LINK(WM_SIZE                    , pinterface, this, &button::OnParentSize);
      USER_MESSAGE_LINK(message_create             , pinterface, this, &button::on_create);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN             , pinterface, this, &button::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP               , pinterface, this, &button::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE               , pinterface, this, &button::_001OnMouseMove);
      IGUI_WIN_MSG_LINK(WM_MOUSELEAVE              , pinterface, this, &button::_001OnMouseLeave);
      IGUI_WIN_MSG_LINK(WM_SIZE                    , pinterface, this, &button::_001OnSize);
      //IGUI_WIN_MSG_LINK(WM_CREATE                  , pinterface, this, &button::_001OnCreate);
      //   IGUI_WIN_MSG_LINK(CVmsGenApp::APPM_LANGUAGE  , pinterface, this, &button::_001OnAppLanguage);
   }

   void button::_001OnDraw(::ca::graphics * pdc)
   {
      
      string strText(m_istrButtonText);

      rect rectClient;
      GetClientRect(rectClient);
      if(m_pschema == NULL)
      {
   
         pdc->SelectObject(_001GetFont());

         if(m_iHover == 0)
         {
            pdc->FillSolidRect(rectClient, ARGB(255, 127, 127, 127));
            pdc->SetTextColor(ARGB(255, 0, 100, 255));
         }
         else
         {
            pdc->FillSolidRect(rectClient, ARGB(255, 127, 127, 127));
            pdc->SetTextColor(ARGB(255, 0, 0, 0));
         }
      }
      else
      {
         if(m_iHover == 0)
         {
            color c;
            c.set_rgb(m_pschema->m_crBkHover);
            c.hls_rate(0.0, -0.33, -0.23);
            COLORREF crBorder = c.get_rgb() | (0xff << 24);
            pdc->Draw3dRect(rectClient, crBorder, crBorder);
            rectClient.deflate(1, 1);
            //pdc->Draw3dRect(rectClient, crBorder, crBorder);
            //rectClient.deflate(1, 1);
            //pdc->Draw3dRect(rectClient, crBorder, crBorder);
            //rectClient.deflate(1, 1);
            pdc->FillSolidRect(rectClient, m_pschema->m_crBkHover);
            pdc->SetTextColor(m_pschema->m_crTextHover);
         }
         else
         {
            color c;
            c.set_rgb(m_pschema->m_crBkNormal);
            c.hls_rate(0.0, -0.33, -0.23);
            COLORREF crBorder = c.get_rgb() | (0xff << 24);
            pdc->Draw3dRect(rectClient, crBorder, crBorder);
            rectClient.deflate(1, 1);
            //pdc->Draw3dRect(rectClient, crBorder, crBorder);
            //rectClient.deflate(1, 1);
            //pdc->Draw3dRect(rectClient, crBorder, crBorder);
            //rectClient.deflate(1, 1);
            pdc->FillSolidRect(rectClient, m_pschema->m_crBkNormal);
            pdc->SetTextColor(m_pschema->m_crTextNormal);
         }

         pdc->selectFont(m_pschema->m_font);

         pdc->m_fontxyz.m_dFontSize = rectClient.height() * 0.5;

         pdc->m_fontxyz.m_bUpdated = false;

      }

      pdc->draw_text(strText, m_rectText, DT_LEFT | DT_TOP);

   }

   void button::_001OnLButtonDown(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::mouse, pmouse, pobj)

         e_element eelement;

      if(hit_test(pmouse->m_pt, eelement) >= 0)
      {
         g_pwndLastLButtonDown = this;
         pmouse->set_lresult(1);
         pobj->m_bRet = true;
      }
   }

   bool button::_001IsPressed()
   {
      return g_pwndLastLButtonDown == this;
   }

   void button::_001OnLButtonUp(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::mouse, pmouse, pobj)

         e_element eelement;

      if(hit_test(pmouse->m_pt, eelement) >= 0 && g_pwndLastLButtonDown == this)
      {
         g_pwndLastLButtonDown = NULL;
         ::user::control_event ev;
         ev.m_puie = this;
         ev.m_eevent = ::user::event_button_clicked;
         if(get_form() != NULL)
         {
            get_form()->send_message(
               ::gen::message_event, 0, (LPARAM) &ev);
         }
         else
         {
            get_parent()->send_message(
               ::gen::message_event, 0, (LPARAM) &ev);
         }
         pobj->m_bRet = true;
         pmouse->set_lresult(1);
      }

   }

   void button::_001OnMouseMove(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::mouse, pmouse, pobj)
         if(get_form() == NULL)
         {

            e_element eelement;

            int iHover = hit_test(pmouse->m_pt, eelement);
            if(iHover != m_iHover)
            {
               int iOldHover = m_iHover;
               m_iHover = iHover;
               _001RedrawWindow();
               if(iOldHover == -1)
               {
                  ::user::control_event ev;
                  ev.m_puie = this;
                  ev.m_eevent = ::user::event_mouse_enter;
                  get_parent()->send_message(
                     ::gen::message_event, 0, (LPARAM) &ev);
               }
               else if(iHover == -1)
               {
                  ::user::control_event ev;
                  ev.m_puie = this;
                  ev.m_eevent = ::user::event_mouse_leave;
                  get_parent()->send_message(
                     ::gen::message_event, 0, (LPARAM) &ev);
               }
               track_mouse_hover();
            }
            pobj->m_bRet = false;
         }
   }

   void button::_001OnMouseLeave(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::base, pbase, pobj)
         if(get_form() == NULL)
         {
            int iOldHover = m_iHover;
            m_iHover = -1;
            if(iOldHover >= 0)
            {
               _001RedrawWindow();
               ::user::control_event ev;
               ev.m_puie = this;
               ev.m_eevent = ::user::event_mouse_leave;
               if(get_parent() != NULL)
               {
                  get_parent()->send_message(::gen::message_event, 0, (LPARAM) &ev);
               }
               track_mouse_leave();
            }
            pbase->m_bRet = false;
         }
   }

   index button::hit_test(point pt, e_element & eelement)
   {
      rect rectWindow;
      GetWindowRect(rectWindow);
      if(rectWindow.contains(pt))
      {
         eelement = element_area;
         return 0;
      }
      else
      {
         eelement = element_none;
         return -1;
      }
   }

   ::ca::font * button::_001GetFont()
   {
      return GetFont();
   }

   void button::ResizeToFit()
   {
   }

   void button::_001SetButtonText(const char * lpcszText)
   {
      m_istrButtonText = lpcszText;
   }

   void button::_001SetButtonTextId(const char * lpcszText)
   {
      m_istrButtonText = lpcszText;
   }


   bool button::_001IsWindowEnabled()
   {
      return m_bEnabled;
   }

   void button::_001EnableWindow(bool bEnable)
   {
      m_bEnabled = bEnable;
   }

   void button::_001SetCheck(check::e_check echeck, bool bUser)
   {
      UNREFERENCED_PARAMETER(bUser);
      m_echeck = echeck;
   }


   check::e_check button::_001GetCheck()
   {
      return m_echeck;
   }

   void button::_001SetState(state::state state, bool bUser)
   {
      UNREFERENCED_PARAMETER(bUser);
      m_state = state;
   }

   state::state button::_001GetState()
   {
      return m_state;
   }

   void button::_001OnSize(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::base, pbase, pobj)
         _001Layout();
      pbase->m_bRet = false;
   }

   void button::on_create(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(::gen::message::create, pcreate, pobj)

      ::simple_frame_window * pframewindow = GetTypedParent < ::simple_frame_window > ();
      if(pframewindow != NULL)
      {
         if(pframewindow->GetTypedParent < ::simple_frame_window > () != NULL)
         {
            pframewindow = pframewindow->GetTypedParent < ::simple_frame_window > ();
         }
         if(pframewindow->GetTypedParent < ::simple_frame_window > () != NULL)
         {
            pframewindow = pframewindow->GetTypedParent < ::simple_frame_window > ();
         }
         if(pframewindow->m_workset.m_pframeschema == NULL)
         {
            m_pschema = &Application.GetUfeSchema()->m_button;
         }
         else
         {
            m_pschema = &pframewindow->m_workset.m_pframeschema->get_user_front_end_schema()->m_button;
         }
      }

   }

   void button::_001Layout()
   {
      
      rect rectClient;
      GetClientRect(rectClient);


      ::rect rect(rectClient);

      rect.left   += (LONG) (rect.height() * 0.15);
      rect.top    += (LONG) (rect.height() * 0.15);

      m_rectText = rect;


      /*::ca::font font;

      font.m_strFontFamilyName = "Calibri";
      font.m_dFontSize = rect.height() * 0.7;
      font.m_eunitFontSize = ::ca::unit_pixel;

      SetFont(&font);*/

   }

   string button::_001GetButtonText()
   {
      return m_istrButtonText;
   }


   void button::VirtualOnSize()
   {
      
      _001Layout();

   }

   bool button::create_control(class control::descriptor * pdescriptor)
   {
      
      if(!create(
         NULL,
         NULL,
         WS_VISIBLE | WS_CHILD, 
         rect(0, 0, 0, 0), 
         pdescriptor->m_pform, 
         pdescriptor->m_id))
      {
         TRACE("Failed to create control");
         return false;
      }

      return control::create_control(pdescriptor);


   }

   index button::get_hover()
   {
      
      
      POINT pt;
      // netshare
      // System.get_cursor_position(&pt);
      System.get_cursor_pos(&pt);
      e_element eelement;
      return hit_test(pt, eelement);


   }


} // namespace user


