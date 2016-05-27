//#include "framework.h"
//#include "core/user/user/user.h"


namespace user
{


   const int32_t BaseWndMenuTimer = 500;
   const int32_t BaseWndMenuCmdUi = 117;


   menu::menu():
      menu(get_app())
   {
   }

   menu::menu(::aura::application * papp) :
      object(papp),
      menu_base(papp),
      m_buttonClose(papp)
   {

      m_bAutoDelete        = true;
      m_pschema            = NULL;
      //m_pitem              = new ::user::menu_item(papp);
      m_bOwnItem           = true;
      m_oswindowParent         = NULL;
      m_pmenuParent        = NULL;
      m_psubmenu           = NULL;
      m_iHoverSubMenu      = -1;

   }


   menu::menu(::aura::application * papp,sp(::user::menu_item) pitem):
      object(papp),
      menu_base(papp),
      m_buttonClose(papp)
   {

      m_iHoverSubMenu      = -1;
      m_oswindowParent         = NULL;
      m_pmenuParent        = NULL;
      m_psubmenu           = NULL;
      m_bAutoDelete        = true;
      m_pschema            = NULL;
      m_pitem              = pitem;
      m_bOwnItem           = false;

   }


   menu::~menu()
   {

   }


   ::user::menu_item * menu::GetSubMenu(int32_t i)
   {

      return get_item()->m_spitema->element_at(i);

   }


   bool menu::TrackPopupMenu(int32_t iFlags, POINT pt, ::user::interaction * oswindowParent)
   {

      ASSERT(oswindowParent != NULL);

      if (!menu_base::TrackPopupMenu(iFlags, pt, oswindowParent))
         return false;

      return _TrackPopupMenu(iFlags, pt, oswindowParent, NULL);

   }


   bool menu::_TrackPopupMenu(int32_t iFlags, POINT pt, sp(::user::interaction) oswindowParent, menu * pmenuParent)
   {

      UNREFERENCED_PARAMETER(iFlags);



   //   HookMenu(this);

      m_oswindowParent   = oswindowParent;
      m_pmenuParent  = pmenuParent;
      //pwndParent->SendMessage(CA2M_BERGEDGE, BERGEDGE_GETAPP, (LPARAM) &m_pauraapp);

//      const char * lpcsz = System.RegisterWndClass(CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW);

      //      const char * lpcsz = NULL;

      LPVOID lpvoid = NULL;
      if(!create_window_ex(WS_EX_LAYERED | WS_EX_TOOLWINDOW,NULL,NULL,0,rect(0,0,0,0),Session.get_view(),id(),lpvoid))
         return false;

      SetOwner(oswindowParent);

      if(!m_buttonClose.create_window(null_rect(), this, ChildIdClose))
         return false;


      m_buttonClose.SetWindowText("r");
      m_buttonClose.set_stock_icon(stock_icon_close);
      m_buttonClose.m_pschema = m_pschema->m_pschemaSysMenuCloseButton;
      //m_buttonClose.SetFont(m_buttonClose.m_pschema->m_font);

      //System.add_frame(this);

      layout_menu(pt);

      SetActiveWindow();

      SetForegroundWindow();

      BringWindowToTop();
      //set_capture();

      return true;
   }

   void menu::layout_menu(point pt)
   {

      if(GetParent() != NULL)
      {

         GetParent()->ScreenToClient(&pt);

      }

      m_ptTrack = pt;

      ::draw2d::memory_graphics pgraphics(allocer());

      pgraphics->SelectObject(m_pschema->m_font);
      size size = pgraphics->GetTextExtent("XXXMMM");
      int32_t iMaxHeight = size.cy;
      int32_t iMaxWidth = size.cx;
      m_iHeaderHeight = size.cy;

      sp(::user::menu_item) pitem = get_item();

      sp(::user::menu_item_ptra) spitema = pitem->m_spitema;

      for (int32_t i = 0; i < spitema->get_size(); i++)
      {
         class size size = pgraphics->GetTextExtent(spitema->element_at(i)->m_button.GetWindowText());
         if (spitema->element_at(i)->IsPopup())
            size.cx += 12 + 16;
         if(size.cy > iMaxHeight)
            iMaxHeight = size.cy;
         if(size.cx > iMaxWidth)
            iMaxWidth = size.cx;
      }
      m_iItemHeight = iMaxHeight + 6 + 2;
      m_size.cx = iMaxWidth + 4 + 20 + 8;

      ::count iItemCount = spitema->get_size();
      int32_t iSeparatorCount = pitem->m_iSeparatorCount;
//      int32_t iFullHeightItemCount = m_pitem->m_iFullHeightItemCount;

   //   int32_t iMaxHeight = 0;
     // int32_t iMaxWidth = 0;
      rect rect(4, m_iHeaderHeight, m_size.cx - 8, 4);
      string str;
      for(int32_t i = 0; i < iItemCount; i++)
      {
         ::user::menu_item * pitem = spitema->element_at(i);
         if(pitem->m_id == "separator")
         {
            rect.bottom = rect.top + 3;
            iSeparatorCount--;
         }
         else
         {
            rect.bottom = rect.top + m_iItemHeight;
         }
         pitem->m_button.create_window(null_rect(), this, pitem->m_id);
         pitem->m_button.SetWindowPos(0, rect.left, rect.top, rect.width(), rect.height(), 0);
         pitem->m_button.m_pschema = m_pschema->m_pschemaItemButton;
         pitem->m_button.m_pitem = pitem;
         pitem->m_pbase = this;
   /*      if(pitem->IsPopup())
         {
            rect rectPopupArrow(rect);
            rectPopupArrow.left = rectPopupArrow.right - 5;
            array < point, point & > pta;
            pta.add(point(rectPopupArrow.left, rectPopupArrow.bottom - 2));
            pta.add(point(rectPopupArrow.right, (rectPopupArrow.bottom + rectPopupArrow.top) / 2));
            pta.add(point(rectPopupArrow.left, rectPopupArrow.top + 2));
            pta.add(point(rectPopupArrow.left, rectPopupArrow.bottom - 2));
            pgraphics->Polygon(pta.get_data(), pta.get_size());
         }*/
         rect.top = rect.bottom;
      }

      m_size.cy = rect.bottom;


      m_buttonClose.ResizeToFit();

   //   rect rect;
      m_buttonClose.GetWindowRect(rect);
      m_buttonClose.SetWindowPos(0, 0, 0, 0, 0, SWP_NOSIZE);
      //m_buttonClose.ShowWindow(SW_NORMAL);

      SetWindowPos(ZORDER_TOPMOST,pt.x,pt.y,m_size.cx,m_size.cy,SWP_FRAMECHANGED | SWP_SHOWWINDOW);

      SetTimer(::user::BaseWndMenuCmdUi,100,NULL);


   }


   void menu::_001OnDraw(::draw2d::graphics * pgraphics)
   {
//      bool bEnabled = is_window_enabled();
//      rect rectClient;
//      GetClientRect(rectClient);
//      if(_001IsTranslucent())
//      {
//         class imaging & imaging = System.visual().imaging();
//         imaging.color_blend(
//            pgraphics,
//            rectClient,
//            RGB(200, 255, 255),
//            127);
//      }
//      else
//      {
//
//#ifdef WINDOWSEX
//
//         pgraphics->FillSolidRect(rectClient, Session.get_default_color(COLOR_WINDOW));
//
//#else
//
//         throw todo(get_app());
//
//#endif
//
//      }

      /*int32_t iMaxHeight = 0;
      int32_t iMaxWidth = 0;
      rect rect(4, m_iHeaderHeight + 4, m_size.cx - 8, 4);
      pgraphics->set_text_color(RGB(0, 0, 0));
      pgraphics->SetBkMode(TRANSPARENT);
      pgraphics->SelectObject(m_pschema->m_font);
      string str;
      for(int32_t i = 0; i < m_pitem->m_pitema->get_size(); i++)
      {
         menu_item * pitem = m_pitem->m_pitema->element_at(i);
         if(pitem->m_iId  == -1)
         {
            rect.bottom = rect.top + 3;
         }
         else
         {
            rect.bottom = rect.top + m_iItemHeight;
            str = pitem->m_str;
            pgraphics->draw_text(str, rect, DT_LEFT | DT_BOTTOM);
         }
         if(pitem->IsPopup())
         {
            rect rectPopupArrow(rect);
            rectPopupArrow.left = rectPopupArrow.right - 5;
            array < point, point & > pta;
            pta.add(point(rectPopupArrow.left, rectPopupArrow.bottom - 2));
            pta.add(point(rectPopupArrow.right, (rectPopupArrow.bottom + rectPopupArrow.top) / 2));
            pta.add(point(rectPopupArrow.left, rectPopupArrow.top + 2));
            pta.add(point(rectPopupArrow.left, rectPopupArrow.bottom - 2));
            pgraphics->Polygon(pta.get_data(), pta.get_size());
         }
         rect.top = rect.bottom;
      }*/

      ::user::interaction::_001OnDraw(pgraphics);

   }



   void menu::_001OnDestroy(signal_details * pobj)
   {
      //System.remove_frame(this);
      if(m_pmenuParent != NULL)
      {
         m_pmenuParent->m_psubmenu = NULL;
         m_pmenuParent->m_idSubMenu.is_empty();
      }
      if(m_psubmenu != NULL)
      {
         m_psubmenu->m_pmenuParent = NULL;
      }
   //   if(user::GetUfe()->m_pmenu == this)
     // {
       //  user::GetUfe()->m_pmenu = NULL;
      //}
      pobj->m_bRet = false;
   }


   //void menu::PostNcDestroy()
   //{
   // //  if(m_bAutoDelete)      // Automatic cleanup?
   //   //   delete_this();
   //}

   void menu::_001OnLButtonDown(signal_details * pobj)
   {
      pobj->previous();
   }


   void menu::OnMessageDestroyWindow(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      DestroyWindow();
   }


   /*void menu::OnBnClickedClose()
   {
      PostMessage(MessageDestroyWindow);
   }*/

   bool menu::BaseOnControlEvent(::user::control_event * pevent)
   {

      if(pevent->m_eevent == ::user::event_mouse_enter)
      {

         sp(::user::menu_item) pitem = get_item(pevent->m_puie);

         if(pitem.is_set())
         {

            ::user::control_event ev;

            ev.m_eevent = ::user::event_menu_hover;

            ev.m_id = pitem->m_id;

            m_oswindowParent->BaseOnControlEvent(&ev);

         }

      }
      else if(pevent->m_eevent == ::user::event_button_clicked)
      {
         if(pevent->m_puie == &m_buttonClose)
         {
            ::user::control_event ev;

            ev.m_eevent = ::user::event_context_menu_close;

            m_oswindowParent->BaseOnControlEvent(&ev);

            post_message(WM_CLOSE);
         }
         else
         {

            sp(::user::menu_item) pitemThis = get_item();

            sp(::user::menu_item_ptra) spitema = pitemThis->m_spitema;

            sp(::user::menu_item) pitem = spitema->find(pevent->m_puie->m_id);

            if(pitem != NULL && !pitem->m_bPopup)
            {
               if(::str::begins((const char *) pevent->m_puie->m_id, astr.stringSysCommand))
               {
                  m_oswindowParent->_001SendCommand(pevent->m_puie->m_id);
               }
               else
               {
                  sp(::user::interaction) pwndParent = m_oswindowParent;
                  id id = pevent->m_puie->m_id;
                  send_message(WM_CLOSE);
                  // this may be destroyed by WM_CLOSE above
                  pwndParent->_001SendCommand(id);
                  pevent->m_bProcessed = true;
               }
            }
         }
      }
      else if(pevent->m_eevent == ::user::event_mouse_enter)
      {
         if(pevent->m_puie == &m_buttonClose)
         {
         }
         else
         {
            if(pevent->m_puie->m_id != m_idSubMenu)
            {
               if(m_psubmenu != NULL
               && m_idSubMenu.has_char())
               {
                  m_psubmenu->send_message(WM_CLOSE);
                  m_psubmenu = NULL;
                  m_idSubMenu = "";
               }
   /*
                  SetTimer(BaseWndMenuTimer, BaseWndMenuTiming, NULL);
                  if(m_pitem->m_pitema->element_at(pevent->m_pcontrol->m_uiId)->m_bPopup)
                  {
                     m_iTimerMenu = pevent->m_pcontrol->m_uiId;
                  }
                  else
                  {
                     m_iTimerMenu = -1;
                  }
               }
               else*/
               {

                  sp(::user::menu_item) pitemThis = get_item();

                  sp(::user::menu_item_ptra) spitema = pitemThis->m_spitema;

                  sp(::user::menu_item) pitem = spitema->find(pevent->m_puie->m_id);

                  if(pitem != NULL)
                  {
                     if(pitem->m_bPopup)
                     {
                        m_idSubMenu = pevent->m_puie->m_id;
                        m_psubmenu = canew(menu(get_app(), spitema->find(pevent->m_puie->m_id)));
                        rect rect;
                        spitema->find(pevent->m_puie->m_id)->m_button.GetWindowRect(rect);
                        m_psubmenu->_TrackPopupMenu(0,
                           rect.top_right(), m_oswindowParent, this);
                     }
                  }
               }
            }
         }
      }
      else if(pevent->m_eevent == ::user::event_mouse_leave)
      {
         if(pevent->m_puie->m_id == m_idTimerMenu)
         {
            KillTimer(BaseWndMenuTimer);
            m_idTimerMenu.is_empty();
         }
      }
      return true;
   }


   void menu::_001OnTimer(::timer * ptimer)
   {

      ::user::control::_001OnTimer(ptimer);;

      sp(::user::menu_item) pitemThis = get_item();

      sp(::user::menu_item_ptra) spitema = pitemThis->m_spitema;

      if(ptimer->m_nIDEvent == BaseWndMenuTimer)
      {
         KillTimer(BaseWndMenuTimer);
         if(m_idSubMenu.has_char())
         {
            m_psubmenu->send_message(WM_CLOSE);
            m_psubmenu = NULL;
            m_idSubMenu.is_empty();
         }
         if(m_idTimerMenu.has_char())
         {
            m_idSubMenu = m_idTimerMenu;
            m_psubmenu = canew(menu(get_app(), spitema->find(m_idTimerMenu)));
            rect rect;
            spitema->find(m_idTimerMenu)->m_button.GetWindowRect(rect);
            m_psubmenu->_TrackPopupMenu(0,
               rect.top_right(), m_oswindowParent, this);
         }
         m_idTimerMenu.is_empty();
      }
      else if(ptimer->m_nIDEvent == ::user::BaseWndMenuCmdUi)
      {
         if(spitema != NULL)
         {
            ::user::menu_button_cmd_ui cmdui(get_app());
            cmdui.m_pitema          = spitema;
            for(int32_t i = 0; i < spitema->get_size(); i++)
            {

               cmdui.m_iIndex    = i;
               cmdui.m_id        = spitema->element_at(i)->m_id;
               cmdui.m_pOther    = (sp(::user::interaction)) &spitema->element_at(i)->m_button;

               sp(::user::interaction) pwndParent = m_oswindowParent;
               if(pwndParent != NULL)
               {
                 /* xxx if(pwndParent->on_simple_action(0,
                     MAKELONG((int32_t)CN_UPDATE_COMMAND_UI, WM_COMMAND+WM_REFLECT_BASE),
                     &cmdui, NULL))
                     continue;*/

                  if(pwndParent->_001SendUpdateCmdUi(&cmdui))
                     continue;
               }
            }
         }
      }
      

   }


   void menu::install_message_handling(::message::dispatch * pinterface)
   {
      
      ::user::control::install_message_handling(pinterface);
      ::user::menu_base::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(MessageDestroyWindow, pinterface, this, &menu::OnMessageDestroyWindow);
      IGUI_WIN_MSG_LINK(WM_IDLEUPDATECMDUI  , pinterface, this, &menu::_001OnIdleUpdateCmdUI);
      IGUI_WIN_MSG_LINK(WM_CREATE           , pinterface, this, &menu::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_DESTROY          , pinterface, this, &menu::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_NCACTIVATE       , pinterface, this, &menu::_001OnNcActivate);
      IGUI_WIN_MSG_LINK(WM_NCCALCSIZE       , pinterface, this, &menu::_001OnNcCalcSize);
      IGUI_WIN_MSG_LINK(WM_ENABLE           , pinterface, this, &menu::_001OnEnable);
      IGUI_WIN_MSG_LINK(WM_SHOWWINDOW       , pinterface, this, &menu::_001OnShowWindow);
   }

   void menu::_001OnCreate(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::message::create, pcreate, pobj);
      m_pschema            = &::userex::GetUfeSchema(get_app())->m_menu;
      return;
   }



   void menu::_001OnIdleUpdateCmdUI(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::message::base, pbase, pobj);

      sp(::user::menu_item) pitemThis = get_item();

      sp(::user::menu_item_ptra) spitema = pitemThis->m_spitema;

      if(spitema != NULL)
      {
         ::user::menu_button_cmd_ui cmdui(get_app());
         cmdui.m_pitema          = spitema;
         for(int32_t i = 0; i < spitema->get_size(); i++)
         {

            cmdui.m_iIndex    = i;
            cmdui.m_id        = spitema->element_at(i)->m_id;
            cmdui.m_pOther    = (sp(::user::interaction)) &spitema->element_at(i)->m_button;

            sp(::user::interaction) pwndParent = m_oswindowParent;
            if(pwndParent != NULL)
            {
               /*
               if(pwndParent->on_simple_action(0,
                  MAKELONG((int32_t)CN_UPDATE_COMMAND_UI, WM_COMMAND+WM_REFLECT_BASE),
                  &cmdui, NULL))
                  continue;
                  */

               if(pwndParent->_001SendUpdateCmdUi(&cmdui))
                  continue;
            }

         }
      }
   }


   void menu::_001OnEnable(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::message::enable, penable, pobj);
   }


   void menu::_001OnNcActivate(signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj);
      pbase->m_bRet = true;
      pbase->set_lresult(DefWindowProc(WM_NCACTIVATE, pbase->m_wparam, -1));
   }

   void menu::_001OnNcCalcSize(signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj);

      if(pbase->m_wparam == TRUE)
      {
         pbase->m_bRet = true;
         pbase->set_lresult(0);
      }
      else
      {
         LPRECT lprect = (LPRECT) pbase->m_lparam.m_lparam;
         lprect->left      = m_ptTrack.x;
         lprect->top       = m_ptTrack.y;
         lprect->right     = lprect->left + m_size.cx;
         lprect->bottom    = lprect->left + m_size.cx;
         pbase->m_bRet = true;
         pbase->set_lresult(0);
      }
   }


   bool menu::pre_create_window(::user::create_struct& cs)
   {

      cs.dwExStyle = WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TOOLWINDOW;

      cs.style &= ~WS_VISIBLE;

      return TRUE;

   }


   void menu::_001OnShowWindow(signal_details * pobj)
   {
      
      SCAST_PTR(::message::show_window, pshow, pobj);
   
      TRACE("menu::_001OnShowWindow bShow = %d", pshow->m_bShow);

   }


   sp(::user::menu_item) menu::get_item()
   {

      return m_pitem;

   }


   sp(::user::menu_item) menu::get_item(::user::interaction * pui)
   {

      sp(::user::menu_item) pitemThis = get_item();

      sp(::user::menu_item_ptra) spitema = pitemThis->m_spitema;

      sp(::user::menu_button) pbutton = pui;

      if(pbutton.is_null())
         return NULL;

      for(auto & pitem : *spitema.m_p)
      {
         
         if(&pitem->m_button == pbutton.m_p)
         {

            return pitem;

         }

      }

      return NULL;

   }

   bool menu::get_color(COLORREF & cr,::user::e_color ecolor)
   {

      if(ecolor == ::user::color_background)
      {

         cr = ARGB(84+77,185,184,177);

         return true;

      }
      else
      {

         return ::user::control::get_color(cr,ecolor);

      }

   }


   bool menu::get_translucency(::user::ETranslucency & etranslucency)
   {

      etranslucency = ::user::TranslucencyPresent;

      return true;
   }



} // namespace user




