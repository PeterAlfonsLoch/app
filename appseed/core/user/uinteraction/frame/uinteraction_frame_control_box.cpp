#include "framework.h"


namespace uinteraction
{


   namespace frame
   {


      control_box::control_box(sp(base_application) papp) :
         element(papp),
         ::user::interaction(papp),
         m_fontMarlett(allocer()),
         m_brushButtonBack(allocer()),
         m_brushButtonBackSel(allocer()),
         m_brushButtonBackFocus(allocer()),
         m_brushButtonBackDisabled(allocer()),
         m_penButtonBack(allocer()),
         m_penButtonBackSel(allocer()),
         m_penButtonBackFocus(allocer()),
         m_penButtonBackDisabled(allocer())
      {

            set_control_box_button_id(button_close, "frame::ButtonClose");
            set_control_box_button_id(button_up, "frame::button_up");
            set_control_box_button_id(button_down, "frame::button_down");
            set_control_box_button_id(button_minimize, "frame::button_minimize");
            set_control_box_button_id(button_maximize, "frame::button_maximize");
            set_control_box_button_id(button_restore, "frame::button_restore");
            set_control_box_button_id(button_notify_icon, "frame::button_notify_icon");
            m_bDrag = false;
            m_iButtonMargin = 2;

            m_fontMarlett->create_point_font("Marlett", 9.0);




         }


      control_box::~control_box()
      {

      }

      void control_box::_001OnLButtonDown(signal_details * pobj)
      {

         SCAST_PTR(::message::mouse, pmouse, pobj);


         m_bDrag = true;

         m_ptDrag = pmouse->m_pt;

         ScreenToClient(&m_ptDrag);

         set_capture();

         pmouse->m_bRet = true;

      }


      void control_box::_001OnLButtonUp(signal_details * pobj)
      {

         SCAST_PTR(::message::mouse, pmouse, pobj);

         drag(pmouse->m_pt);

         m_bDrag = false;

         release_capture();


         pmouse->m_bRet = true;
      }


      void control_box::_001OnMouseMove(signal_details * pobj)
      {

         SCAST_PTR(::message::mouse, pmouse, pobj);

         if (m_bDrag)
         {
            drag(pmouse->m_pt);
         }

         pmouse->m_bRet = true;

      }

      void control_box::drag(point pt)
      {

         int x = pt.x - m_ptDrag.x;

         if (x < 0)
            x = 0;

         rect rectParent;

         get_parent()->GetWindowRect(rectParent);

         rect rectClient;

         GetClientRect(rectClient);

         if (x > rectParent.right - rectClient.width())
            x = rectParent.right - rectClient.width();

         if (x < rectParent.left)
            x = rectParent.left;

         rect rectWindow;

         GetWindowRect(rectWindow);

         point ptClient(x, rectWindow.top);

         get_parent()->ScreenToClient(ptClient);

         SetWindowPos(ZORDER_TOP, ptClient.x, ptClient.y, 0, 0, SWP_NOSIZE);


      }

      void control_box::_001OnShowWindow(signal_details * pobj)
      {

         SCAST_PTR(::message::show_window, pshow, pobj)

            m_bDrag = false;

         m_bShowAttempt = false;

         if (pshow->m_bShow)
         {

            m_dwShowTime = ::get_tick_count();

         }

      }


      void control_box::_001OnTimer(signal_details * pobj)
      {

         //         SCAST_PTR(::message::timer, ptimer, pobj)

         if (IsWindowVisible())
         {
            if (m_bDrag)
            {
               m_dwShowTime = ::get_tick_count();
            }
            else
            {
               if (m_pworkset->get_draw_window().cast < simple_frame_window >() != NULL)
               {

                  if (m_pworkset->get_draw_window().cast < simple_frame_window >()->WfiIsFullScreen())
                  {

                     rect rectWindow;

                     GetWindowRect(rectWindow);

                     if (rectWindow.contains(Session.m_ptCursor))
                     {
                        m_dwShowTime = ::get_tick_count();
                     }
                     else
                     {
                        if ((::get_tick_count() - m_dwShowTime) > (884))
                        {


                           ShowWindow(SW_HIDE);

                        }

                     }

                  }


               }

            }
         }
         else if (m_bShowAttempt)
         {
            if ((::get_tick_count() - m_dwShowTime) > 284)
            {
               if (m_pworkset->get_draw_window().cast < simple_frame_window >() != NULL)
               {

                  if (m_pworkset->get_draw_window().cast < simple_frame_window >()->WfiIsFullScreen())
                  {

                     rect rectWindow;

                     GetWindowRect(rectWindow);

                     if (Session.m_ptCursor.x >= rectWindow.left && Session.m_ptCursor.y <= rectWindow.right && Session.m_ptCursor.y == 0)
                     {

                        ShowWindow(SW_SHOW);

                     }

                     m_bShowAttempt = false;

                  }

               }

            }
         }
         else
         {

            if (m_pworkset->get_draw_window().cast < simple_frame_window >()->WfiIsFullScreen())
            {

               rect rectWindow;

               GetWindowRect(rectWindow);

               point pt(0, 0);

               try
               {

                  pt = Session.m_ptCursor;

               }
               catch (...)
               {
               }




               if (pt.x >= rectWindow.left && pt.x <= rectWindow.right && pt.y == 0)
               {

                  m_bShowAttempt = true;
                  m_dwShowTime = ::get_tick_count();

               }

            }

         }

      }


      void control_box::_001OnCreate(signal_details * pobj)
      {

         pobj->previous();

         if (pobj->m_bRet)
            return;

         create_buttons();

         SetTimer(123, 184, NULL);

      }


      void control_box::install_message_handling(::message::dispatch *pinterface)
      {

         ::user::interaction::install_message_handling(pinterface);

         IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &control_box::_001OnShowWindow);
         IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &control_box::_001OnTimer);
         IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &control_box::_001OnCreate);
         IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &control_box::_001OnMouseMove);
         IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &control_box::_001OnLButtonDown);
         IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &control_box::_001OnLButtonUp);
         IGUI_WIN_MSG_LINK(WM_MOVE, pinterface, this, &control_box::_001OnMove);
         IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &control_box::_001OnSize);

      }


      ::uinteraction::frame::appearance * control_box::get_appearance()
      {

         return m_pworkset->get_appearance();

      }


      void control_box::layout()
      {

         reset_layout();

         appearance * pappearance = get_appearance();

         int32_t iButtonSize = get_button_size();

         ::rect rectClient;

         GetClientRect(rectClient);

         int iWidth = rectClient.width();

         ::rect rect;

         rect.left = m_iButtonMargin;
         rect.right = iWidth - m_iButtonMargin;
         rect.top = m_iButtonMargin;
         rect.bottom = iButtonSize + rect.top;


         rect.left = rect.right - iButtonSize;
         get_box_button(button_close)->::user::interaction::SetWindowPos(ZORDER_TOP, rect.left, rect.top, rect.width(), rect.height(), SWP_SHOWWINDOW);
         get_box_button(button_close)->UpdateWndRgn();


         if (pappearance->WndFrameworkDownUpGetUpEnable())
         {
            rect.right = rect.left - m_iButtonMargin;
            rect.left = rect.right - iButtonSize;
            get_box_button(button_up)->::user::interaction::SetWindowPos(ZORDER_TOP, rect.left, rect.top, rect.width(), rect.height(), SWP_SHOWWINDOW);
            get_box_button(button_up)->UpdateWndRgn();
         }
         else
         {
            get_box_button(button_up)->ShowWindow(SW_HIDE);
         }

         if (pappearance->WndFrameworkDownUpGetDownEnable())
         {
            rect.right = rect.left - m_iButtonMargin;
            rect.left = rect.right - iButtonSize;
            get_box_button(button_down)->::user::interaction::SetWindowPos(
               ZORDER_TOP,
               rect.left,
               rect.top,
               rect.width(),
               rect.height(),
               SWP_SHOWWINDOW);
            get_box_button(button_down)->UpdateWndRgn();
         }
         else
         {
            get_box_button(button_down)->ShowWindow(SW_HIDE);
         }

         if (pappearance->IsZoomed() || !has_button(button_maximize))
         {
            get_box_button(button_maximize)->ShowWindow(SW_HIDE);
         }
         else
         {
            rect.right = rect.left - m_iButtonMargin;
            rect.left = rect.right - iButtonSize;
            get_box_button(button_maximize)->::user::interaction::SetWindowPos(
               ZORDER_TOP,
               rect.left,
               rect.top,
               rect.width(),
               rect.height(),
               SWP_SHOWWINDOW);
            get_box_button(button_maximize)->UpdateWndRgn();
         }

         if (pappearance->IsIconic()
            || pappearance->IsFullScreen()
            || pappearance->IsZoomed())
         {
            rect.right = rect.left - m_iButtonMargin;
            rect.left = rect.right - iButtonSize;
            get_box_button(button_restore)->::user::interaction::SetWindowPos(
               ZORDER_TOP,
               rect.left,
               rect.top,
               rect.width(),
               rect.height(),
               SWP_SHOWWINDOW);
            get_box_button(button_restore)->UpdateWndRgn();
         }
         else
         {
            get_box_button(button_restore)->ShowWindow(SW_HIDE);
         }

         if (pappearance->IsIconic() || !has_button(button_minimize))
         {
            get_box_button(button_minimize)->ShowWindow(SW_HIDE);
         }
         else
         {
            rect.right = rect.left - m_iButtonMargin;
            rect.left = rect.right - iButtonSize;
            get_box_button(button_minimize)->::user::interaction::SetWindowPos(ZORDER_TOP, rect.left, rect.top, rect.width(), rect.height(), SWP_SHOWWINDOW);
            get_box_button(button_minimize)->UpdateWndRgn();
         }

         if (pappearance->IsNotifyIconEnabled())
         {
            rect.right = rect.left - m_iButtonMargin;
            rect.left = rect.right - iButtonSize;
            get_box_button(button_notify_icon)->::user::interaction::SetWindowPos(ZORDER_TOP, rect.left, rect.top, rect.width(), rect.height(), SWP_SHOWWINDOW);
            get_box_button(button_notify_icon)->UpdateWndRgn();
         }
         else
         {
            get_box_button(button_notify_icon)->ShowWindow(SW_HIDE);
         }

      }


      void control_box::reset_layout()
      {

         m_iButtonSize = calc_button_size();

      }


      int32_t control_box::get_button_size()
      {

         return m_iButtonSize;

      }


      int32_t control_box::calc_button_size()
      {

         ::draw2d::graphics_sp pdc(allocer());

         pdc->CreateCompatibleDC(NULL);



         TEXTMETRICW tm;
         pdc->SelectObject(m_fontMarlett);
         pdc->get_text_metrics(&tm);

         //      int32_t iMargin = get_margin();
         int32_t iButtonSize = tm.tmHeight + m_iButtonMargin * 3;



         return iButtonSize;


      }

      void control_box::update_control_box_button(e_button ebutton)
      {
         sp(control_box_button) pbutton;
         if (m_buttonmap.Lookup(ebutton, pbutton))
         {
            string strCaption;
            get_control_box_button_caption(ebutton, strCaption);
            pbutton->set_parent(this);
            pbutton->SetWindowText(strCaption);
            pbutton->SetFont(m_fontMarlett);
            pbutton->SetEllipseBrushs(m_brushButtonBack, m_brushButtonBackSel, m_brushButtonBackFocus, m_brushButtonBackDisabled);
            pbutton->SetEllipsePens(m_penButtonBack, m_penButtonBackSel, m_penButtonBackFocus, m_penButtonBackDisabled);
            pbutton->SetTextColors(m_crButtonFore, m_crButtonForeSel, m_crButtonForeFocus, m_crButtonForeDisabled);
         }
      }



      bool control_box::create_button(e_button ebutton)
      {

         sp(::user::interaction) pwnd = m_pworkset->get_draw_window();

         sp(control_box_button) pbutton;

         if (!m_buttonmap.Lookup(ebutton, pbutton))
         {

            m_buttonmap.set_at(ebutton, (Application.alloc(m_pworkset->m_pframeschema->m_typeinfoControlBoxButton)));

         }

         string strCaption;

         get_control_box_button_caption(ebutton, strCaption);

         id id = get_control_box_button_id(ebutton);

         if (m_buttonmap.Lookup(ebutton, pbutton))
         {

            if (!pbutton->IsWindow() && !pbutton->create(this, id))
               return false;

            update_control_box_button(ebutton);

         }
         else
         {

            return false;

         }

         return true;

      }


      void control_box::update_control_box_buttons()
      {
         POSITION pos = m_buttonmap.get_start_position();
         e_button ebutton;
         sp(control_box_button) pbutton;
         while (pos != NULL)
         {
            m_buttonmap.get_next_assoc(pos, ebutton, pbutton);
            update_control_box_button(ebutton);
         }
      }



      bool control_box::create_buttons()
      {

         create_button(button_close);
         create_button(button_up);
         create_button(button_down);
         create_button(button_minimize);
         create_button(button_maximize);
         create_button(button_restore);
         create_button(button_notify_icon);

         return true;

      }

      bool control_box::get_control_box_button_caption(e_button ebutton, string &strCaption)
      {
         bool bOk = true;
         switch (ebutton)
         {
         case button_close:
            strCaption = (CHAR)114;
            break;
         case button_up:
            strCaption = (CHAR)53;
            break;
         case button_down:
            strCaption = (CHAR)54;
            break;
         case button_minimize:
            strCaption = (CHAR)48;
            break;
         case button_maximize:
            strCaption = (CHAR)49;
            break;
         case button_restore:
            strCaption = (CHAR)50;
            break;
         case button_notify_icon:
            strCaption = (CHAR)0x69;
            break;

         default:
            bOk = false;
         }
         return bOk;

      }

      void control_box::set_control_box_button_id(e_button ebutton, id id)
      {
         m_mapButtonId[ebutton] = id;
         m_mapIdButton[id] = ebutton;
      }

      id control_box::get_control_box_button_id(e_button ebutton)
      {
         return m_mapButtonId[ebutton];
      }

      e_button control_box::get_control_box_button_type(id id)
      {
         return m_mapIdButton[id];
      }

      void control_box::hide_button(e_button ebutton, bool bHide)
      {
         m_buttonmapPresent[ebutton] = !bHide;
      }

      bool control_box::has_button(e_button ebutton)
      {
         bool bPresent;
         if (m_buttonmapPresent.Lookup(ebutton, bPresent))
            return bPresent;
         else
         {
            m_buttonmapPresent[ebutton] = true;
            return true;
         }
      }


      int32_t control_box::calc_control_box_height()
      {

         ::draw2d::graphics_sp pdc(allocer());

         pdc->CreateCompatibleDC(NULL);

         TEXTMETRICW tm;
         pdc->SelectObject(m_fontMarlett);
         pdc->get_text_metrics(&tm);

         int32_t iButtonHeight = tm.tmHeight + m_iButtonMargin * 3;

         return iButtonHeight;

      }


      int32_t control_box::calc_control_box_normal_width()
      {

         int iWidth;

         iWidth = (m_iButtonSize + m_iButtonMargin) * 8;

         return iWidth;

      }


      int32_t control_box::calc_control_box_zoomed_width()
      {

         int iWidth;

         iWidth = (m_iButtonSize + m_iButtonMargin) * 8;

         return iWidth;

      }


      int32_t control_box::calc_control_box_full_screen_width()
      {

         int iWidth;

         iWidth = (m_iButtonSize + m_iButtonMargin) * 13;

         return iWidth;

      }


      int32_t control_box::get_button_margin()
      {

         return m_iButtonMargin;

      }


      sp(control_box_button) control_box::get_button(e_button ebutton)
      {
         sp(control_box_button) pbutton = NULL;
         m_buttonmap.Lookup(ebutton, pbutton);
         return pbutton;
      }


      sp(::uinteraction::frame::control_box_button) control_box::get_box_button(e_button ebutton)
      {

         return get_button(ebutton);

      }

      void control_box::set_button_color_system_default_001()
      {

         m_brushButtonBack->create_solid(Session.get_default_color(COLOR_BTNFACE) | 0xff000000);
         m_brushButtonBackSel->create_solid(Session.get_default_color(COLOR_WINDOW) | 0xff000000);
         m_brushButtonBackFocus->create_solid(RGB(0, 255, 255) | 0xff000000);
         m_brushButtonBackDisabled->create_solid(Session.get_default_color(COLOR_BTNFACE) | 0xff000000);
         m_penButtonBack->create_solid(1, Session.get_default_color(COLOR_BTNFACE) | 0xff000000);
         m_penButtonBackSel->create_solid(1, Session.get_default_color(COLOR_BTNFACE) | 0xff000000);
         m_penButtonBackFocus->create_solid(1, RGB(0, 255, 255) | 0xff000000);
         m_penButtonBackDisabled->create_solid(1, Session.get_default_color(COLOR_BTNFACE) | 0xff000000);
         m_crButtonFore = Session.get_default_color(COLOR_BTNTEXT) | (0xff << 24);
         m_crButtonForeSel = Session.get_default_color(COLOR_BTNTEXT) | (0xff << 24);
         m_crButtonForeFocus = Session.get_default_color(COLOR_BTNTEXT) | (0xff << 24);
         m_crButtonForeDisabled = Session.get_default_color(COLOR_GRAYTEXT) | (0xff << 24);

      }


      void control_box::_001OnMove(signal_details * pobj)
      {

         ::rect rectWindow;

         m_pworkset->GetWndDraw()->GetWindowRect(rectWindow);

         ::rect rect;

         GetWindowRect(rect);

         m_pworkset->GetWndDraw()->ScreenToClient(rect);
         
         m_pworkset->m_pframeschema->m_iRRight = rectWindow.width() - rect.right;

      }

      void control_box::_001OnSize(signal_details * pobj)
      {

         ::rect rectWindow;

         m_pworkset->GetWndDraw()->GetWindowRect(rectWindow);

         ::rect rect;

         GetWindowRect(rect);

         m_pworkset->GetWndDraw()->ScreenToClient(rect);

         m_pworkset->m_pframeschema->m_iRRight = rectWindow.width() - rect.right;

      }


   } // namespace frame


} // namespace uinteraction




