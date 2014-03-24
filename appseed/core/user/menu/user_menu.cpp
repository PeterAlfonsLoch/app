#include "framework.h"

namespace user
{

   const int32_t BaseWndMenuTimer = 500;
   const int32_t BaseWndMenuCmdUi = 117;
   const int32_t BaseWndMenuTiming = 200;

   menu::menu(sp(base_application) papp) :
      element(papp),
      menu_base(papp),
      m_buttonClose(papp)
   {
      m_bAutoDelete        = true;
      m_pschema            = NULL;
      m_etranslucency      = TranslucencyNone;
      m_pitem              = new menu_item(papp);
      m_bOwnItem           = true;
      m_oswindowParent         = NULL;
      m_pmenuParent        = NULL;
      m_psubmenu           = NULL;
      m_iHoverSubMenu      = -1;

      set_default_background_color(ARGB(255, 185, 184, 177));

   }

   menu::menu(sp(base_application) papp, sp(menu_item) pitem) :
      element(papp),
      menu_base(papp),
      m_buttonClose(papp)
   {
      m_iHoverSubMenu      = -1;
      m_oswindowParent         = NULL;
      m_pmenuParent        = NULL;
      m_psubmenu           = NULL;
      m_bAutoDelete        = true;
      m_etranslucency      = TranslucencyNone;
      m_pschema            = NULL;
      m_pitem              = pitem;
      m_bOwnItem           = false;

      set_default_background_color(ARGB(255, 185, 184, 177));

   }

   menu::~menu()
   {
   }


   /* // BEGIN_MESSAGE_MAP(menu, ::user::interaction)
      ON_MESSAGE(MessageDestroyWindow, OnMessageDestroyWindow)
   //   ON_BN_CLICKED(ChildIdClose, OnBnClickedClose)
    // END_MESSAGE_MAP()
   */



   // CBaseWndMenu message handlers




   menu_item * menu::GetSubMenu(int32_t i)
   {

      return get_item()->m_spitema->element_at(i);

   }


   bool menu::TrackPopupMenu(int32_t iFlags, int32_t x, int32_t y, sp(::user::interaction) oswindowParent, sp(menu_base) * pthis)
   {

      ASSERT(oswindowParent != NULL);

      if (!menu_base::TrackPopupMenu(iFlags, x, y, oswindowParent, pthis))
         return false;

      return _TrackPopupMenu(iFlags, x, y, oswindowParent, NULL);

   }


   bool menu::_TrackPopupMenu(int32_t iFlags, int32_t x, int32_t y, sp(::user::interaction) oswindowParent, menu * pmenuParent)
   {

      UNREFERENCED_PARAMETER(iFlags);



   //   HookMenu(this);

      m_oswindowParent   = oswindowParent;
      m_pmenuParent  = pmenuParent;
      //pwndParent->SendMessage(CA2M_BERGEDGE, BERGEDGE_GETAPP, (LPARAM) &m_pbaseapp);

//      const char * lpcsz = System.RegisterWndClass(CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW);

      //      const char * lpcsz = NULL;

      LPVOID lpvoid = NULL;
      if(!CreateEx(WS_EX_LAYERED | WS_EX_TOOLWINDOW, NULL, NULL, 0, rect(0, 0, 0, 0), Session.get_view(), id(), lpvoid))
         return false;

      set_owner(oswindowParent);

      if(!m_buttonClose.create(this, ChildIdClose))
         return false;


      m_buttonClose._001SetButtonText("r");
      m_buttonClose.m_pschema = m_pschema->m_pschemaSysMenuButton;

      //System.add_frame(this);

      layout();

   //   ModifyStyle(

      point pt(x, y);

      if(get_parent() != NULL)
      {
         get_parent()->ScreenToClient(&pt);
      }

      m_ptTrack = pt;

      SetWindowPos(ZORDER_TOPMOST, pt.x, pt.y, m_size.cx, m_size.cy, SWP_FRAMECHANGED | SWP_SHOWWINDOW);

      SetTimer(BaseWndMenuCmdUi, 100, NULL);

      //set_capture();

      return true;
   }

   void menu::layout()
   {

      ::draw2d::memory_graphics pdc(allocer());

      pdc->SelectObject(m_pschema->m_font);
      size size = pdc->GetTextExtent("XXXMMM");
      int32_t iMaxHeight = size.cy;
      int32_t iMaxWidth = size.cx;
      m_iHeaderHeight = size.cy;

      sp(menu_item) pitem = get_item();

      sp(menu_item_ptra) spitema = pitem->m_spitema;

      for (int32_t i = 0; i < spitema->get_size(); i++)
      {
         class size size = pdc->GetTextExtent(spitema->element_at(i)->m_button._001GetButtonText());
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
         menu_item * pitem = spitema->element_at(i);
         if(pitem->m_id == "separator")
         {
            rect.bottom = rect.top + 3;
            iSeparatorCount--;
         }
         else
         {
            rect.bottom = rect.top + m_iItemHeight;
         }
         pitem->m_button.create(this, pitem->m_id);
         pitem->m_button.SetWindowPos(0, rect.left, rect.top, rect.width(), rect.height(), 0);
         pitem->m_button.m_etranslucency = TranslucencyPresent;
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
            pdc->Polygon(pta.get_data(), pta.get_size());
         }*/
         rect.top = rect.bottom;
      }

      m_size.cy = rect.bottom;


      m_buttonClose.ResizeToFit();

   //   rect rect;
      m_buttonClose.GetWindowRect(rect);
      m_buttonClose.SetWindowPos(0, 0, 0, 0, 0, SWP_NOSIZE);
      //m_buttonClose.ShowWindow(SW_NORMAL);





      SetWindowPos(0, 0, 0, m_size.cx, m_size.cy, SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOMOVE);
   }


   void menu::_001OnDraw(::draw2d::graphics *pdc)
   {
//      bool bEnabled = IsWindowEnabled();
      rect rectClient;
      GetClientRect(rectClient);
      if(_001IsTranslucent())
      {
         class imaging & imaging = System.visual().imaging();
         imaging.color_blend(
            pdc,
            rectClient,
            RGB(200, 255, 255),
            127);
      }
      else
      {

#ifdef WINDOWSEX

         pdc->FillSolidRect(rectClient, Session.get_default_color(COLOR_WINDOW));

#else

         throw todo(get_app());

#endif

      }

      /*int32_t iMaxHeight = 0;
      int32_t iMaxWidth = 0;
      rect rect(4, m_iHeaderHeight + 4, m_size.cx - 8, 4);
      pdc->set_text_color(RGB(0, 0, 0));
      pdc->SetBkMode(TRANSPARENT);
      pdc->SelectObject(m_pschema->m_font);
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
            pdc->draw_text(str, rect, DT_LEFT | DT_BOTTOM);
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
            pdc->Polygon(pta.get_data(), pta.get_size());
         }
         rect.top = rect.bottom;
      }*/
      ::user::interaction::_001OnDraw(pdc);
   }



   void menu::_001OnDestroy(signal_details * pobj)
   {
      System.remove_frame(this);
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


   void menu::PostNcDestroy()
   {
      if(m_bAutoDelete)      // Automatic cleanup?
         delete_this();
   }

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
      if(pevent->m_eevent == ::user::event_button_clicked)
      {
         if(pevent->m_puie == &m_buttonClose)
         {
            post_message(WM_CLOSE);
         }
         else
         {

            sp(menu_item) pitemThis = get_item();

            sp(menu_item_ptra) spitema = pitemThis->m_spitema;

            sp(menu_item) pitem = spitema->find(pevent->m_puie->m_id);

            if(pitem != NULL && !pitem->m_bPopup)
            {
               if(::str::begins((const char *) pevent->m_puie->m_id, "syscommand::"))
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

                  sp(menu_item) pitemThis = get_item();

                  sp(menu_item_ptra) spitema = pitemThis->m_spitema;

                  sp(menu_item) pitem = spitema->find(pevent->m_puie->m_id);

                  if(pitem != NULL)
                  {
                     if(pitem->m_bPopup)
                     {
                        m_idSubMenu = pevent->m_puie->m_id;
                        m_psubmenu = new menu(get_app(), spitema->find(pevent->m_puie->m_id));
                        rect rect;
                        spitema->find(pevent->m_puie->m_id)->m_button.GetWindowRect(rect);
                        m_psubmenu->_TrackPopupMenu(0,
                           rect.right,
                           rect.top, m_oswindowParent, this);
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

   void menu::_001OnTimer(signal_details * pobj)
   {
      SCAST_PTR(::message::timer, ptimer, pobj);

      sp(menu_item) pitemThis = get_item();

      sp(menu_item_ptra) spitema = pitemThis->m_spitema;

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
            m_psubmenu = new menu(get_app(), spitema->find(m_idTimerMenu));
            rect rect;
            spitema->find(m_idTimerMenu)->m_button.GetWindowRect(rect);
            m_psubmenu->_TrackPopupMenu(0,
               rect.right,
               rect.top, m_oswindowParent, this);
         }
         m_idTimerMenu.is_empty();
      }
      else if(ptimer->m_nIDEvent == BaseWndMenuCmdUi)
      {
         if(spitema != NULL)
         {
            menu_button_cmd_ui cmdui(get_app());
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
      pobj->m_bRet = false;
   }

   void menu::install_message_handling(::message::dispatch * pinterface)
   {
      
      ::user::menu_base::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(MessageDestroyWindow, pinterface, this, &menu::OnMessageDestroyWindow);
      IGUI_WIN_MSG_LINK(WM_IDLEUPDATECMDUI  , pinterface, this, &menu::_001OnIdleUpdateCmdUI);
      IGUI_WIN_MSG_LINK(WM_CREATE           , pinterface, this, &menu::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_DESTROY          , pinterface, this, &menu::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_TIMER            , pinterface, this, &menu::_001OnTimer);
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
//      SCAST_PTR(::message::base, pbase, pobj)

      sp(menu_item) pitemThis = get_item();

      sp(menu_item_ptra) spitema = pitemThis->m_spitema;

      if(spitema != NULL)
      {
         menu_button_cmd_ui cmdui(get_app());
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


   bool menu::pre_create_window(CREATESTRUCT& cs)
   {

      cs.dwExStyle = WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TOOLWINDOW;

      cs.style &= ~WS_VISIBLE;

      return TRUE;

   }


   void menu::_001OnShowWindow(signal_details * pobj)
   {
      
      SCAST_PTR(::message::show_window, pshow, pobj)
   
      TRACE("menu::_001OnShowWindow bShow = %d", pshow->m_bShow);

   }


   sp(menu_item) menu::get_item()
   {

      return m_pitem;

   }

} // namespace user
