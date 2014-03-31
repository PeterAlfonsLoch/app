#include "framework.h"


namespace user
{


   button::button(sp(base_application) papp) :
      element(papp),
      ::user::interaction(papp),
      m_istrButtonText(papp),
      m_dib(allocer())
   {
      
      m_iHover    = -1;
      m_bEnabled  = true;
      m_echeck    = check::unchecked;
      m_pschema   = NULL;

   }

   button::~button()
   {

   }


   void button::install_message_handling(::message::dispatch * pinterface)
   {
      //::user::window_interface::install_message_handling(pinterface);
      ::user::control::install_message_handling(pinterface);
      //::user::button::install_message_handling(pinterface);

      //   IGUI_WIN_MSG_LINK(WM_SIZE                    , pinterface, this, &button::OnParentSize);
      USER_MESSAGE_LINK(message_create             , pinterface, this, &button::on_create);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN             , pinterface, this, &button::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP               , pinterface, this, &button::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE               , pinterface, this, &button::_001OnMouseMove);
      IGUI_WIN_MSG_LINK(WM_MOUSELEAVE              , pinterface, this, &button::_001OnMouseLeave);
      IGUI_WIN_MSG_LINK(WM_SIZE                    , pinterface, this, &button::_001OnSize);
      //IGUI_WIN_MSG_LINK(WM_CREATE                  , pinterface, this, &button::_001OnCreate);
      //   IGUI_WIN_MSG_LINK(CVmsGenApp::APPM_LANGUAGE  , pinterface, this, &button::_001OnAppLanguage);
      IGUI_WIN_MSG_LINK(WM_CREATE                  , pinterface, this, &button::_001OnCreate);
   }

   void button::_001OnDraw(::draw2d::graphics * pdc)
   {
      
      string strText(m_istrButtonText);

      rect rectClient;
      GetClientRect(rectClient);


      ::draw2d::brush_sp brushText(allocer());

      
      if(m_pschema == NULL)
      {

         if(m_iHover == 0)
         {
            
            pdc->FillSolidRect(rectClient, ARGB(255, 127, 127, 127));

            brushText->create_solid(ARGB(255, 0, 100, 255));

         }
         else
         {

            pdc->FillSolidRect(rectClient, ARGB(255, 127, 127, 127));

            brushText->create_solid(ARGB(255, 0, 0, 0));

         }

      }
      else
      {
         if(m_iHover == 0)
         {
            color ca;
            ca.set_rgb(m_pschema->m_crBkHover);
            ca.hls_rate(0.0, -0.33, -0.23);
            COLORREF crBorder = ca.get_rgb() | (0xff << 24);
            pdc->Draw3dRect(rectClient, crBorder, crBorder);
            rectClient.deflate(1, 1);
            //pdc->Draw3dRect(rectClient, crBorder, crBorder);
            //rectClient.deflate(1, 1);
            //pdc->Draw3dRect(rectClient, crBorder, crBorder);
            //rectClient.deflate(1, 1);
            pdc->FillSolidRect(rectClient, m_pschema->m_crBkHover);
            brushText->create_solid(m_pschema->m_crTextHover);
         }
         else
         {
            color ca;
            ca.set_rgb(m_pschema->m_crBkNormal);
            ca.hls_rate(0.0, -0.33, -0.23);
            COLORREF crBorder = ca.get_rgb() | (0xff << 24);
            pdc->Draw3dRect(rectClient, crBorder, crBorder);
            rectClient.deflate(1, 1);
            //pdc->Draw3dRect(rectClient, crBorder, crBorder);
            //rectClient.deflate(1, 1);
            //pdc->Draw3dRect(rectClient, crBorder, crBorder);
            //rectClient.deflate(1, 1);
            pdc->FillSolidRect(rectClient, m_pschema->m_crBkNormal);
            brushText->create_solid(m_pschema->m_crTextNormal);
         }

      }

      ::draw2d::font_sp font(allocer());

      *font = *_001GetFont();

      font->m_dFontSize = m_rectText.height() * 0.84;

      font->m_eunitFontSize = ::draw2d::unit_pixel;

      font->m_bUpdated = false;

      pdc->selectFont(font);

      pdc->SelectObject(brushText);

      pdc->draw_text(strText, m_rectText, DT_LEFT | DT_TOP);

   }


   void button::_001OnLButtonDown(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj)

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

   void button::_001OnLButtonUp(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj)

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
               ::message::message_event, 0, (LPARAM) &ev);
         }
         else
         {
            get_parent()->send_message(
               ::message::message_event, 0, (LPARAM) &ev);
         }
         pobj->m_bRet = true;
         pmouse->set_lresult(1);
      }

   }

   void button::_001OnMouseMove(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj)
         if(get_form() == NULL)
         {

            e_element eelement;

            index iHover = hit_test(pmouse->m_pt, eelement);
            if(iHover != m_iHover)
            {
               index iOldHover = m_iHover;
               m_iHover = iHover;
               _001RedrawWindow();
               if(iOldHover == -1)
               {
                  ::user::control_event ev;
                  ev.m_puie = this;
                  ev.m_eevent = ::user::event_mouse_enter;
                  get_parent()->send_message(
                     ::message::message_event, 0, (LPARAM) &ev);
               }
               else if(iHover == -1)
               {
                  ::user::control_event ev;
                  ev.m_puie = this;
                  ev.m_eevent = ::user::event_mouse_leave;
                  get_parent()->send_message(
                     ::message::message_event, 0, (LPARAM) &ev);
               }
               track_mouse_hover();
            }
            pobj->m_bRet = false;
         }
   }

   void button::_001OnMouseLeave(signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj)
         if(get_form() == NULL)
         {
            index iOldHover = m_iHover;
            m_iHover = -1;
            if(iOldHover >= 0)
            {
               _001RedrawWindow();
               ::user::control_event ev;
               ev.m_puie = this;
               ev.m_eevent = ::user::event_mouse_leave;
               if(get_parent() != NULL)
               {
                  get_parent()->send_message(::message::message_event, 0, (LPARAM) &ev);
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

   void button::ResizeToFit()
   {

      ::draw2d::memory_graphics pdc(allocer());

      if(pdc.is_null())
         return;

      pdc->SelectObject(m_pschema->m_font);

      string strText(m_istrButtonText);
      size size = pdc->GetTextExtent(strText);

      rect rect(0, 0, 0, 0);
      rect.right = (LONG) (size.cx / 0.77 + 4);
      rect.bottom = (LONG) (size.cy / 0.77 + 4);

      SetWindowPos(0, 0, 0, rect.width(), rect.height(), SWP_NOMOVE);

   }

   void button::_001SetButtonText(const char * lpcszText)
   {
      m_istrButtonText = lpcszText;
   }

   void button::_001SetButtonTextId(const char * lpcszText)
   {
      m_istrButtonText = lpcszText;
   }


   bool button::is_window_enabled()
   {
      return m_bEnabled;
   }

   void button::enable_window(bool bEnable)
   {
      m_bEnabled = bEnable;
   }


   void button::_001SetCheck(check::e_check echeck, ::action::context actioncontext)
   {

      UNREFERENCED_PARAMETER(actioncontext);

      m_echeck = echeck;

   }


   check::e_check button::_001GetCheck()
   {

      return m_echeck;

   }


   void button::_001SetState(state::state state, ::action::context actioncontext)
   {

      UNREFERENCED_PARAMETER(actioncontext);

      m_state = state;

   }


   state::state button::_001GetState()
   {
      return m_state;
   }

   void button::_001OnSize(signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj)
         _001Layout();
      pbase->m_bRet = false;
   }

   void button::on_create(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(::message::create, pcreate, pobj)

      sp(::simple_frame_window) pframewindow = GetTypedParent < ::simple_frame_window > ();

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
            
            m_pschema = &Application.userex()->GetUfeSchema()->m_button;
            
            SetFont(m_pschema->m_font);

         }
         else
         {
            
            m_pschema = &pframewindow->m_workset.m_pframeschema->get_user_front_end_schema()->m_button;

            SetFont(m_pschema->m_font);

         }

      }

   }

   void button::_001Layout()
   {
      
      rect rectClient;
      GetClientRect(rectClient);


      ::rect rect(rectClient);

      rect.deflate((LONG) (rect.height() * 0.15), (LONG) (rect.height() * 0.15));

      m_rectText = rect;

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


   ::draw2d::font * button::_001GetFont()
   {
      if(m_pschema == NULL)
         return GetFont();
      return m_pschema->m_font;
   }

   void button::_002OnDraw(::draw2d::graphics * pdc)
   {

      if(m_pschema == NULL)
         return;


      rect rectClient;
      m_pui->GetClientRect(rectClient);

      COLORREF crBk;
      if(!is_window_enabled())
      {
         crBk = m_pschema->m_crBkDisabled;
      }
      else if(_001IsPressed())
      {
         crBk = m_pschema->m_crBkPress;
      }
      else if(m_iHover >= 0)
      {
         crBk = m_pschema->m_crBkHover;
      }
      else
      {
         crBk = m_pschema->m_crBkNormal;
      }


      if(::user::button::_001IsTranslucent())
      {
         class imaging & imaging = System.visual().imaging();
         imaging.color_blend(
            pdc,
            rectClient,
            crBk,
            127);
      }
      else
      {
         pdc->FillSolidRect(rectClient, crBk);
      }


      COLORREF crBorder;
      if(!is_window_enabled())
      {
         crBorder = ARGB(255, 127, 127, 127);
      }
      else if(_001IsPressed())
      {
         crBorder = ARGB(255, 255, 255, 255);
      }
      else if(m_iHover >= 0)
      {
         crBorder = ARGB(255, 100, 100, 200);
      }
      else
      {
         crBorder = ARGB(255, 10, 10, 100);
      }

      if(m_pschema->m_bBorder)
      {
         pdc->Draw3dRect(rectClient, crBorder, crBorder);
      }

//      pdc->SetBkMode(TRANSPARENT);

      rectClient.left   += 3;
      rectClient.top    += 3;
      rect rectText = m_rectText;
//      string str = ::str::international::utf8_to_unicode(str);
      if(m_dib.is_set())
      {
         if(m_dib->m_size.cx > 0 && m_dib->m_size.cy > 0)
         {
            rect rectDib;
            rectDib = m_rectText;
            rectDib.bottom = min(rectText.top + m_dib->m_size.cy, rectText.bottom);
            rectDib.right = min(rectText.left + m_dib->m_size.cx, rectText.right);
            //m_dib->to(pdc, rectDib);
            m_dib->bitmap_blend(pdc, rectDib);
            rectText.left += m_dib->m_size.cx;
         }
      }

      
      ::draw2d::brush_sp brushText(allocer());


      if(!is_window_enabled())
      {
//         pdc->set_text_color(m_pschema->m_crTextDisabled);
         brushText->create_solid(m_pschema->m_crTextDisabled);
      }
      else if(_001IsPressed())
      {
//         pdc->set_text_color(m_pschema->m_crTextPress);
         brushText->create_solid(m_pschema->m_crTextPress);
      }
      else if(m_iHover >= 0)
      {
//         pdc->set_text_color(m_pschema->m_crTextHover);
         brushText->create_solid(m_pschema->m_crTextHover);
      }
      else
      {
//         pdc->set_text_color(m_pschema->m_crTextNormal);
         brushText->create_solid(m_pschema->m_crTextNormal);
      }

      pdc->SelectObject(brushText);

      string strText(m_istrButtonText);
      pdc->SelectObject(m_pschema->m_font);
      pdc->draw_text(strText, rectText, DT_LEFT | DT_TOP);

   }

   void button::_001OnCreate(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      m_pschema   = &::userex::GetUfeSchema(get_app())->m_button;
   }



} // namespace user


