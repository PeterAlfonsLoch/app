#include "framework.h"


namespace user
{


   button::button(::aura::application * papp) :
      element(papp),
      ::user::interaction(papp),
      m_dib(allocer()),
      m_brushBkg(allocer())
   {
      
      m_estyle = style_none;


      m_bHover          = false;
      m_bCommandEnable  = true;
      m_bFocus = true;
      m_bTransparent = true;
      m_iHover = -1;
         m_bEnabled = true;
         m_echeck = check::unchecked;
         m_pschema = NULL;

         m_bLButtonDown = false;
      
         m_bTransitionEffect = false;
         //   m_crPush = RGB(70, 150, 100);
         //   m_crPushHover = RGB(120, 200, 150);
         //   m_crNormal = RGB(70, 200, 110);
         //   m_crHover = RGB(120, 230, 150);
         m_cr =  RGB(70,200,110);
         m_bPush = false;
         m_bHover = false;
         m_pcolorschema = NULL;
         m_iClick = 0;
         m_pimagelistNormal = NULL;
         m_pimagelistItemHover = NULL;
         m_pimagelistSubItemHover = NULL;
   }

   button::~button()
   {

   }


   void button::install_message_handling(::message::dispatch * pinterface)
   {
      //::user::interaction_base::install_message_handling(pinterface);
      ::user::control::install_message_handling(pinterface);
      //::user::button::install_message_handling(pinterface);

      //   IGUI_WIN_MSG_LINK(WM_SIZE                    , pinterface, this, &button::OnParentSize);
      USER_MESSAGE_LINK(message_create, pinterface, this, &button::on_create);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &button::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &button::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &button::_001OnMouseMove);
      IGUI_WIN_MSG_LINK(WM_MOUSELEAVE, pinterface, this, &button::_001OnMouseLeave);
      IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &button::_001OnSize);
      //IGUI_WIN_MSG_LINK(WM_CREATE                  , pinterface, this, &button::_001OnCreate);
      //   IGUI_WIN_MSG_LINK(CVmsGenApp::APPM_LANGUAGE  , pinterface, this, &button::_001OnAppLanguage);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &button::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_KEYDOWN,pinterface,this,&button::_001OnKeyDown);

      IGUI_WIN_MSG_LINK(WM_DESTROY,pinterface,this,&button::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_TIMER,pinterface,this,&button::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_SETFOCUS,pinterface,this,&button::_001OnSetFocus);

   }

#include "framework.h"



   void button::pre_subclass_window()
   {
      PreSubClassWindow();


      // trans ::user::button::pre_subclass_window();
   }

   void button::_001OnCtlColor(signal_details * pobj)
   {
      SCAST_PTR(::message::ctl_color,pctlcolor,pobj)
         if(m_bTransparent)
         {
            //      pctlcolor->m_pdc->SetBkMode(TRANSPARENT);
            pctlcolor->m_hbrush = (HBRUSH)m_brushBkg->get_os_data();
         }
         else
         {
            pctlcolor->m_hbrush = NULL;
         }
   }




   void button::_001OnSetFocus(signal_details * pobj)
   {
      SCAST_PTR(::message::set_focus,psetfocus,pobj)
         //  if(!m_bFocus)
         //{
         // pOldWnd->SetFocus();
         //}
         psetfocus->previous();
   }

   void button::_001OnDraw(::draw2d::graphics * pdc)
   {

      if(m_estyle == style_push)
      {
         
         _001OnDrawPush(pdc);

      }
      else if(m_estyle == style_list)
      {

         _001OnDrawPush(pdc);

      }
      else if(m_estyle == style_bitmap)
      {

         _001OnDrawBitmap(pdc);

      }
      else
      {

         string strText(m_strWindowText);

         rect rectClient;
         GetClientRect(rectClient);


         if(m_pschema == NULL)
         {

            if(m_iHover == 0 || m_bLButtonDown)
            {

               pdc->FillSolidRect(rectClient,ARGB(255,127,127,127));

               pdc->set_text_color(ARGB(255,0,100,255));

            }
            else
            {

               pdc->FillSolidRect(rectClient,ARGB(255,127,127,127));

               pdc->set_text_color(ARGB(255,0,0,0));

            }

         }
         else
         {
            if(m_iHover == 0 || m_bLButtonDown)
            {

               pdc->Draw3dRect(rectClient,m_pschema->_001GetColor(color_border_hover),m_pschema->_001GetColor(color_border_hover));

               rectClient.deflate(1,1);

               pdc->FillSolidRect(rectClient,m_pschema->_001GetColor(color_background_hover));

               pdc->set_text_color(m_pschema->_001GetColor(color_text_hover));

            }
            else
            {

               pdc->Draw3dRect(rectClient,m_pschema->_001GetColor(color_border_normal),m_pschema->_001GetColor(color_border_normal));

               rectClient.deflate(1,1);

               pdc->FillSolidRect(rectClient,m_pschema->_001GetColor(color_background_normal));

               pdc->set_text_color(m_pschema->_001GetColor(color_text_normal));

            }

         }

         select_font(pdc);

         pdc->TextOut(m_rectText.left,m_rectText.top,strText);

      }

   }


   void button::_001OnLButtonDown(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj)

         e_element eelement;

      if(hit_test(pmouse->m_pt, eelement) >= 0)
      {

         if(simple_process_system_message(pobj,::user::event_button_down))
         {
            
            Session.m_puiLastLButtonDown = this;

         }

      }

   }

   bool button::is_pressed()
   {
      return Session.m_puiLastLButtonDown == this;
   }

   void button::_001OnLButtonUp(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj)

      e_element eelement;

      if(hit_test(pmouse->m_pt, eelement) >= 0 && Session.m_puiLastLButtonDown == this)
      {
         Session.m_puiLastLButtonDown = NULL;
         ::user::control_event ev;
         ev.m_puie = this;
         ev.m_eevent = ::user::event_button_clicked;
         BaseOnControlEvent(&ev);
         pobj->m_bRet = ev.m_bRet;
         if(pobj->m_bRet)
         {
            pmouse->set_lresult(1);
         }
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
            RedrawWindow();
            if(iOldHover == -1)
            {
               ::user::control_event ev;
               ev.m_puie = this;
               ev.m_eevent = ::user::event_mouse_enter;
               GetParent()->send_message(
                  ::message::message_event, 0, (LPARAM)&ev);
            }
            else if(iHover == -1)
            {
               ::user::control_event ev;
               ev.m_puie = this;
               ev.m_eevent = ::user::event_mouse_leave;
               GetParent()->send_message(
                  ::message::message_event, 0, (LPARAM)&ev);
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
            RedrawWindow();
            ::user::control_event ev;
            ev.m_puie = this;
            ev.m_eevent = ::user::event_mouse_leave;
            if(GetParent() != NULL)
            {
               GetParent()->send_message(::message::message_event, 0, (LPARAM)&ev);
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


   ::size button::calc_text_size()
   {

      ::draw2d::memory_graphics pdc(allocer());

      if(pdc.is_null())
         return size(0, 0);

      select_font(pdc);

      string strText(m_strWindowText);

      size size = pdc->GetTextExtent(strText);

      ::draw2d::text_metric tm;

      pdc->get_text_metrics(&tm);

      ::size sizeTotal;

      sizeTotal.cx = size.cx;

      sizeTotal.cy = tm.tmHeight;

      return sizeTotal;
   
   }


   void button::ResizeToFit()
   {

      if(m_estyle == style_simple)
      {

            ::draw2d::memory_graphics pdc(allocer());

            select_font(pdc);

            string str;
            GetWindowText(str);
            size size = pdc->GetTextExtent(str);

            rect rect(0,0,0,0);
            rect.right = size.cx + 4;
            rect.bottom = size.cy + 4;

            SetWindowPos(0,0,0,rect.width(),rect.height(),SWP_NOMOVE);


      }
      else if(m_estyle == style_bitmap)
      {
         class size size = m_dib->size();

         SetWindowPos(0,0,0,size.cx,size.cy,SWP_NOMOVE | SWP_NOZORDER);

      }
      else
      {

         ::size sizeTotal = calc_text_size();

         sizeTotal.cx += 10 * 2;

         sizeTotal.cy += 5 * 2;

         SetWindowPos(0,0,0,sizeTotal.cx,sizeTotal.cy,SWP_NOMOVE);

      }

   }

   //void button::_001SetButtonText(const char * lpcszText)
   //{
   //   m_istrButtonText = lpcszText;
   //}

   //void button::_001SetButtonTextId(const char * lpcszText)
   //{
   //   m_istrButtonText = lpcszText;
   //}


   bool button::is_window_enabled()
   {

      return m_bEnabled;

   }

   
   bool button::enable_window(bool bEnable)
   {

      m_bEnabled = bEnable;

      return bEnable;

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



   //void button::_001OnSize(signal_details * pobj)
   //{
   //   SCAST_PTR(::message::base, pbase, pobj)
   //      _001Layout();
   //   pbase->m_bRet = false;
   //}

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
            
            m_pschema = &Platform.userex()->GetUfeSchema()->m_button;
            
         }
         else
         {
            
            m_pschema = &pframewindow->m_workset.m_pframeschema->get_user_front_end_schema()->m_button;

         }

      }

   }

   void button::layout()
   {
      
      rect rectClient;

      GetClientRect(rectClient);

      ::size sizeText = calc_text_size();

      ::rect rect;

      rect.left = rectClient.left + (rectClient.width() - sizeText.cx) / 2;

      rect.top = rectClient.top + (rectClient.height() - sizeText.cy) / 2;

      rect.right = rect.left + sizeText.cx;

      rect.bottom = rect.top + sizeText.cy;

      m_rectText = rect;

   }


   //string button::_001GetButtonText()
   //{
   //   return m_istrButtonText;
   //}


   //void button::VirtualOnSize()
   //{
   //   
   //   _001Layout();

   //}

   bool button::create_control(class control::descriptor * pdescriptor)
   {
      
      if(!create_window(
         NULL,
         NULL,
         WS_VISIBLE | WS_CHILD, 
         pdescriptor->m_rect, 
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
      Session.get_cursor_pos(&pt);
      e_element eelement;
      return hit_test(pt, eelement);


   }


   void button::_002OnDraw(::draw2d::graphics * pdc)
   {

      if(m_pschema == NULL)
         return;


      rect rectClient;
      
      GetClientRect(rectClient);

      COLORREF crBk;
      if(!is_window_enabled())
      {
         crBk = m_pschema->_001GetColor(color_background_disabled);
      }
      else if(is_pressed())
      {
         crBk = m_pschema->_001GetColor(color_background_press);
      }
      else if(m_iHover >= 0)
      {
         crBk = m_pschema->_001GetColor(color_background_hover);
      }
      else
      {
         crBk = m_pschema->_001GetColor(color_background_normal);
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
      else if(is_pressed())
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
            rectDib.bottom = MIN(rectText.top + m_dib->m_size.cy, rectText.bottom);
            rectDib.right = MIN(rectText.left + m_dib->m_size.cx, rectText.right);
            //m_dib->to(pdc, rectDib);
            m_dib->bitmap_blend(pdc, rectDib);
            rectText.left += m_dib->m_size.cx;
         }
      }

      
      ::draw2d::brush_sp brushText(allocer());


      if(!is_window_enabled())
      {
//         pdc->set_text_color(m_pschema->m_crTextDisabled);
         brushText->create_solid(m_pschema->_001GetColor(color_text_disabled));
      }
      else if(is_pressed())
      {
//         pdc->set_text_color(m_pschema->m_crTextPress);
         brushText->create_solid(m_pschema->_001GetColor(color_text_press));
      }
      else if(m_iHover >= 0)
      {
//         pdc->set_text_color(m_pschema->m_crTextHover);
         brushText->create_solid(m_pschema->_001GetColor(color_text_hover));
      }
      else
      {
//         pdc->set_text_color(m_pschema->m_crTextNormal);
         brushText->create_solid(m_pschema->_001GetColor(color_text_normal));
      }

      pdc->SelectObject(brushText);

      string strText(GetWindowText());

      select_font(pdc);

      pdc->draw_text(strText, rectText, DT_LEFT | DT_TOP);

   }

   void button::_001OnCreate(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

      if(m_estyle == style_none)
      {
         
         set_button_style(style_normal);

      }

      m_pschema   = &::userex::GetUfeSchema(get_app())->m_button;

   }

   bool button::keyboard_focus_is_focusable()
   {

      return is_window_enabled() && IsWindowVisible();

   }


   void button::_001OnKeyDown(signal_details * pobj)
   {

      SCAST_PTR(::message::key,pkey,pobj);

      ::user::e_key iKey = pkey->m_ekey;

      if(iKey == ::user::key_return || iKey == ::user::key_space)
      {

         ::user::control_event ev;
         ev.m_puie = this;
         ev.m_eevent = ::user::event_button_clicked;
         ev.m_pobj = pobj;
         BaseOnControlEvent(&ev);
         pobj->m_bRet = ev.m_bRet;
         if(pobj->m_bRet)
         {
            pkey->set_lresult(1);
         }

      }

   }



//   /////////////////////////////////////////////////////////////////////////////
//   // button message handlers
//
//   bool button::pre_create_window(::user::create_struct& cs)
//   {
//
//#ifdef WINDOWS
//      cs.style |= BS_OWNERDRAW;
//      cs.style |= BS_PUSHBUTTON;
//#endif
//
//      return ::user::button::pre_create_window(cs);
//
//   }

   void button::_001OnDrawBitmap(::draw2d::graphics * pdc)
   {

      ASSERT(m_dib.is_set() && m_dib->area() > 0); // required

      // use the main bitmap for up, the selected bitmap for down
      ::draw2d::dib * pdib = m_dib;

      if(_001GetCheck() == ::check::checked && m_dibSel.is_set() && m_dibSel->area() > 0)
         pdib = m_dibSel;
      else if(m_bHover && !m_bCommandEnable && m_dibHover.is_set() && m_dibHover->area() > 0)
         pdib = m_dibHover;
      else if(m_bFocus && m_dibFocus.is_set() && m_dibFocus->area() > 0)
         pdib = m_dibFocus;   // third image for focused
      else if(!m_bCommandEnable && m_dibDisabled.is_set() && m_dibDisabled->area() > 0)
         pdib = m_dibDisabled;   // last image for disabled

      pdc->from(pdib->m_size, pdib->get_graphics(), SRCCOPY);

   }


   void button::_001OnDrawPush(::draw2d::graphics *pdc)
   {

      //   int32_t iOriginalBkMode = pdc->GetBkMode();
      //   pdc->SetBkMode(TRANSPARENT);
      rect rectClient;
      GetClientRect(rectClient);

      //   state::state state = _001GetState();
      //   const int32_t ihilite = 0x0004; // hilighted
      //   const int32_t ifocus = 0x0008; // focus
      //   const int32_t iPushState = state & 3;

      color color;

      color.set_rgb(m_cr);

      COLORREF cr;

      if(m_pcolorschema != NULL)
      {
         if(is_pushed())
         {
            color.hls_rate(m_pcolorschema->m_hlsRatePush);
         }
         if(m_bHover)
         {
            color.hls_rate(m_pcolorschema->m_hlsRateHover);
         }
      }
      else
      {
         if(is_pushed())
         {
            color.hls_rate(0.0,- 0.2,- 0.3);
         }
         if(m_bHover)
         {
            color.hls_rate(0.0,0.2,0.0);
         }
      }
      cr = color;
      if(m_bTransitionEffect)
      {
         class color color;
         color.set_rgb(cr);
         cr = color;

         double dH,dL,dS;
         color.get_hls(dH,dL,dS);
         color.set_hls(dH,dL,dS);
         cr = color;
         double dRate;
         if(m_iStep <= m_iStepCount / 2)
         {
            dRate = m_iStep * 2.0 / m_iStepCount;
         }
         else
         {
            dRate = (m_iStepCount - m_iStep) * 2.0 / m_iStepCount;
         }
         if(is_pushed())
         {
            dL = dL * (1.0 - dRate);
         }
         else
         {
            dL = (1.0 - dL) * dRate + dL;
         }
         color.set_hls(dH,dL,dS);
         cr = color.get_rgb();
      }

      class color colorExt1TL;
      class color colorExt2TL;
      class color colorExt1BR;
      class color colorExt2BR;

      colorExt1TL.set_rgb(cr);
      colorExt2TL.set_rgb(cr);
      colorExt1BR.set_rgb(cr);
      colorExt2BR.set_rgb(cr);
      if(is_pushed())
      {
         colorExt1TL.hls_rate(0.0,- 0.5,0.0);
         colorExt2TL.hls_rate(0.0,- 0.2,0.0);
         colorExt2BR.hls_rate(0.0,0.2,0.0);
         colorExt1BR.hls_rate(0.0,0.85,0.0);
      }
      else
      {
         colorExt1TL.hls_rate(0.0,0.85,0.0);
         colorExt2TL.hls_rate(0.0,0.2,0.0);
         colorExt2BR.hls_rate(0.0,- 0.2,0.0);
         colorExt1BR.hls_rate(0.0,- 0.5,0.0);
      }

      class imaging & imaging = System.visual().imaging();

      rect rect = rectClient;
      imaging.color_blend_3dRect(pdc,rect,colorExt1TL,215,colorExt1BR,215);
      rect.deflate(1,1,1,1);
      imaging.color_blend_3dRect(pdc,rect,colorExt1TL,210,colorExt1BR,210);
      rect.deflate(1,1,1,1);
      imaging.color_blend_3dRect(pdc,rect,colorExt2TL,205,colorExt2BR,205);
      rect.deflate(1,1,1,1);
      imaging.color_blend_3dRect(pdc,rect,colorExt2TL,200,colorExt2BR,200);
      rect.deflate(1,1,1,1);
      imaging.color_blend(pdc,rect.left,rect.top,rect.width(),rect.height(),cr,200);
      rect.deflate(1,1,1,1);
      int32_t x1 = rect.left;
      int32_t x2 = x1 + rect.width() / 3;
      rect.left = x1;
      rect.right = x2;
      rect.bottom = rect.top + 5;
      ::draw2d::pen_sp pen(pdc,1,colorExt1TL);
      pdc->SelectObject(pen);
      imaging.color_blend_3dRect(pdc,rect,colorExt1TL,220,colorExt1BR,220);




      //   pdc->SetBkMode(iOriginalBkMode);

   }


   void button::set_button_style(e_style estyle)
   {

      on_exit_button_style(m_estyle);

      m_estyle = estyle;

      on_enter_button_style(estyle);

   }


   void button::on_enter_button_style(e_style estyle)
   {

      if(estyle == style_push)
      {

         SetTimer(16384,100,NULL);

      }

   }

   
   void button::on_exit_button_style(e_style estyle)
   {

      if(estyle == style_push)
      {

         KillTimer(16384);

      }

   }


   void button::_001OnDestroy(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //   ::user::button::OnDestroy();

      KillTimer(16384);

   }

   void button::_001OnTimer(signal_details * pobj)
   {
      SCAST_PTR(::message::timer,ptimer,pobj);
      if(ptimer->m_nIDEvent == 16384)
      {
         //UpdateHover();
      }
      else if(ptimer->m_nIDEvent == 3)
      {
         TransitionEffectRunStep();
      }

      // trans   ::user::button::OnTimer(ptimer->m_nIDEvent);
   }


   void button::Hover(bool bHover)
   {
      m_bHover = bHover;
      RedrawWindow();
   }

   
   //void button::push(bool bPush)


   //   ASSERT(m_etyle == style_push);


   //   if(m_estyle != style_push)
   //      return;

   //   m_bPush = bPush;
   //   TransitionEffectStart();
   //   RedrawWindow();
   //}


   bool button::is_pushed()
   {
      return _001GetCheck() == ::check::checked;
   }

   void button::TransitionEffectRunStep()
   {
      m_iStep++;
      if(m_iStep >= m_iStepCount)
      {
         KillTimer(3);
         m_bTransitionEffect = false;
      }
      RedrawWindow();

   }


   void button::TransitionEffectStart()
   {
      m_bTransitionEffect = true;
      m_iStepCount = 27;
      m_iStep = 0;
      SetTimer(3,20,NULL);
   }

   void button::SetColorSchema(ColorSchema *pschema)
   {
      m_pcolorschema = pschema;
   }


   bool button::LoadBitmaps(::var var,::var varSel,::var varFocus,::var varDisabled,::var varHover)
   {

      if(!var.is_empty())
      {

         m_dib.load_from_file(var);

      }

      if(!varSel.is_empty())
      {

         m_dibSel.load_from_file(varSel);

      }


      if(!varFocus.is_empty())
      {

         m_dibFocus.load_from_file(varFocus);

      }


      if(!varDisabled.is_empty())
      {

         m_dibDisabled.load_from_file(varDisabled);

      }


      if(!varHover.is_empty())
      {

         m_dibHover.load_from_file(varHover);

      }

      return m_dib.is_set() && m_dib->area() > 0;

   }





      //void button::UpdateHover()
      //{
      //   point point;
      //   GetCursorPos(&point);

      //   if(m_bHover || System.get_capture_uie() == this)
      //   {
      //      rect rectClient;
      //      GetWindowRect(rectClient);
      //      if(!rectClient.contains(point))
      //      {
      //         m_bHover = false;
      //         if(System.get_capture_uie() == this)
      //         {
      //            System.release_capture_uie();
      //         }
      //         RedrawWindow();
      //      }
      //      else
      //      {
      //         m_bHover = true;
      //         if(System.get_capture_uie() != this)
      //         {
      //            SetCapture();
      //         }
      //      }
      //   }
      //   else
      //   {
      //      if(!m_bHover)
      //      {
      //         rect rectClient;
      //         GetWindowRect(rectClient);
      //         if(rectClient.contains(point))
      //         {
      //            m_bHover = true;
      //            SetCapture();
      //            RedrawWindow();
      //         }
      //      }
      //   }

      //}

      
   void button::pre_translate_message(signal_details * pobj)
      {
         
         // Relay events from this button to the tool tip tool handler
         BaseToolTipRelayEvent(pobj);

         return ::user::control::pre_translate_message(pobj);

      }


      void button::BaseToolTipGetRect(LPRECT lprect)
      {
         // use window client rect as the tool rect
         GetClientRect(lprect);
      }

      int32_t button::BaseToolTipGetIndex()
      {
         // use window dialog control id as the index
         return (int32_t)GetDlgCtrlId();
      }


      void button::message_handler(signal_details * pobj)
      {
         if(pobj->m_bRet)
            return;

         return ::user::button::message_handler(pobj);
      }

   



   void button::_001OnDrawList(::draw2d::graphics * pdc)
   {
      rect rectClient;
      bool bItemHover;
      bool bSubItemHover;

      ::user::draw_context * pdrawcontext = pdc->::core::simple_chain < ::user::draw_context >::get_last();

      if(pdrawcontext != NULL)
      {
         rectClient     = pdrawcontext->m_rectClient;
         bItemHover     = pdrawcontext->m_bListItemHover;
         bSubItemHover  = pdrawcontext->m_bListSubItemHover;
      }
      else
      {
         if(get_form() != NULL)
            return;
         GetClientRect(rectClient);
         bItemHover     = get_hover() >= 0;
         bSubItemHover  = get_hover() >= 0;
      }

      point pt = rectClient.top_left();
      pt += size(1,1);

      if(bSubItemHover)
      {
         pdc->Draw3dRect(
            rectClient,
            RGB(255,255,255),
            RGB(155,155,105));

         if(m_pimagelistSubItemHover != NULL)
         {
            m_pimagelistSubItemHover->draw(
               pdc,
               m_iImageSubItemHover,
               pt,
               0);
         }
         else if(m_pimagelistItemHover != NULL)
         {
            m_pimagelistItemHover->draw(
               pdc,
               m_iImageItemHover,
               pt,
               0);
         }
         else if(m_pimagelistNormal != NULL)
         {
            m_pimagelistNormal->draw(
               pdc,
               m_iImageNormal,
               pt,
               0);
         }
      }
      else if(bItemHover)
      {
         if(m_pimagelistItemHover != NULL)
         {
            m_pimagelistItemHover->draw(
               pdc,
               m_iImageItemHover,
               pt,
               0);
         }
         else if(m_pimagelistSubItemHover != NULL)
         {
            m_pimagelistSubItemHover->draw(
               pdc,
               m_iImageSubItemHover,
               pt,
               0);
         }
         else if(m_pimagelistNormal != NULL)
         {
            m_pimagelistNormal->draw(
               pdc,
               m_iImageNormal,
               pt,
               0);
         }
      }
      else
      {
         if(m_pimagelistNormal != NULL)
         {
            m_pimagelistNormal->draw(
               pdc,
               m_iImageNormal,
               pt,
               0);
         }
         else if(m_pimagelistItemHover != NULL)
         {
            m_pimagelistItemHover->draw(
               pdc,
               m_iImageItemHover,
               pt,
               0);
         }
         else if(m_pimagelistSubItemHover != NULL)
         {
            m_pimagelistSubItemHover->draw(
               pdc,
               m_iImageSubItemHover,
               pt,
               0);
         }
      }

   }


   void button::BaseToolTipRelayEvent(class signal_details *)
   {
   }





} // namespace user




