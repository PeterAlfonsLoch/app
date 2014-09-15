#include "framework.h"


namespace user
{


   const int32_t BaseWndMenuCmdUi = 117;
   const int32_t g_base_menu_indent = 11;


   menu_list_window::menu_list_window(sp(::aura::application) papp) :
      element(papp),
      menu_base(papp),
      menu(papp),
      m_buttonClose(papp)
   {

      m_bAutoDelete        = true;
      m_bOwnItem           = false;
      m_pwndNotify         = NULL;
      m_pitem              = new menu_item(papp);
      m_pschema            = NULL;
      m_bAutoClose         = true;

   }


   menu_list_window::menu_list_window(sp(::aura::application) papp, sp(menu_item) pitem) :
      element(papp),
      menu_base(papp),
      menu(papp),
      m_buttonClose(papp)
   {

      m_pwndNotify         = NULL;
      m_bAutoClose         = true;
      m_bAutoDelete        = true;
      m_pschema            = NULL;
      m_pitem              = pitem;
      m_bOwnItem           = false;

   }


   menu_list_window::~menu_list_window()
   {

   }


   void menu_list_window::install_message_handling(::message::dispatch * pinterface)
   {

      control::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &menu_list_window::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &menu_list_window::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &menu_list_window::_001OnTimer);

   }

   
   void menu_list_window::_001OnCreate(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

      m_pschema            = &::userex::GetUfeSchema(get_app())->m_menu;

   }


   void menu_list_window::_001OnDestroy(signal_details * pobj)
   {

      pobj->m_bRet = false;

   }

   bool menu_list_window::TrackPopupMenu(sp(::user::interaction) pwndParent, sp(::user::interaction) pwndNotify)
   {
      ASSERT(pwndParent != NULL);
      //_m_pmenu = new menu_list_window(m_pitem);
      return _TrackPopupMenu(pwndParent, pwndNotify);
   }

   bool menu_list_window::_TrackPopupMenu(sp(::user::interaction) pwndParent, sp(::user::interaction) pwndNotify)
   {

      m_pwndNotify = pwndNotify;

//      LPVOID lpvoid = NULL;
      if(!IsWindow())
      {

         if(!create_window(NULL, NULL, WS_VISIBLE | WS_CHILD, null_rect(), pwndParent, 0))
            return false;

         if(!m_buttonClose.create_window(null_rect(), this, ChildIdClose))
            return false;

         m_buttonClose.install_message_handling(this);

         m_buttonClose._001SetButtonText("r");
         m_buttonClose.m_pschema = m_pschema->m_pschemaSysMenuButton;
      }

      _UpdateCmdUi(m_pitem);
      _CreateButtons(m_pitem);

      //user::AppGet()->AddFrame(this);

      layout();

      rect rectClient;

      pwndParent->GetClientRect(rectClient);


      SetWindowPos(0, 0, 0, rectClient.width(), rectClient.height(), SWP_SHOWWINDOW | SWP_NOZORDER);

      SetTimer(BaseWndMenuCmdUi, 300, NULL);

      return true;
   }


   bool menu_list_window::MenuFill(sp(::user::interaction) pwndFill, sp(::user::interaction) pwndNotify)
   {

      m_pwndNotify = pwndNotify;

//      LPVOID lpvoid = NULL;
      if(!IsWindow())
      {

         if(!create_window(NULL,NULL,WS_VISIBLE | WS_CHILD,null_rect(),pwndFill,0))
            return false;

      }
      else
      {
         if(GetParent() != pwndFill)
         {
            SetParent(pwndFill);
         }
      }

      if(!m_buttonClose.IsWindow())
      {
         if(!m_buttonClose.create_window(null_rect(), this, ChildIdClose))
            return false;

         m_buttonClose.install_message_handling(this);

         m_buttonClose._001SetButtonText("r");
         m_buttonClose.m_pschema = m_pschema->m_pschemaSysMenuButton;
      }

      _UpdateCmdUi(m_pitem);
      _CreateButtons(m_pitem);

      //user::AppGet()->AddFrame(this);

      layout();

      rect rectClient;

      pwndFill->GetClientRect(rectClient);


      SetWindowPos(0, 0, 0, rectClient.width(), rectClient.height(), SWP_SHOWWINDOW | SWP_NOZORDER);

      SetTimer(BaseWndMenuCmdUi, 300, NULL);

      return true;
   }

   void menu_list_window::_UpdateCmdUi(sp(menu_item) pitemParent)
   {

      if(pitemParent->m_spitema == NULL)
         return;

      menu_button_cmd_ui cmdui(get_app());

      cmdui.m_pitema = pitemParent->m_spitema;

      for(int32_t i = 0; i < pitemParent->m_spitema->get_size(); i++)
      {

         menu_item * pitem = pitemParent->m_spitema->element_at(i);

         cmdui.m_iIndex       = i;
         cmdui.m_id           = pitem->m_id;
         cmdui.m_pOther       = (sp(::user::interaction)) &pitem->m_button;

         if(m_pwndNotify->on_simple_update(&cmdui))
            continue;

         _UpdateCmdUi(pitem);

      }

   }

   void menu_list_window::_001OnTimer(signal_details * pobj)
   {
      SCAST_PTR(::message::timer, ptimer, pobj)
      if(ptimer->m_nIDEvent == BaseWndMenuCmdUi)
      {
         _UpdateCmdUi(m_pitem);
         RedrawWindow();
      }
      pobj->m_bRet = false;
   }

   void menu_list_window::_CalcSize(sp(menu_item) pitemParent, ::draw2d::graphics * pdc, int32_t & iMaxWidth, int32_t & iMaxHeight)
   {
      if(pitemParent->m_spitema == NULL)
         return;
      for(int32_t i = 0; i < pitemParent->m_spitema->get_size(); i++)
      {
         menu_item * pitem = pitemParent->m_spitema->element_at(i);
         size size = pdc->GetTextExtent(pitem->m_button._001GetButtonText());
         size.cx += pitem->m_iLevel * g_base_menu_indent;
         if(pitem->IsPopup())
            size.cx += 12 + 16;
         if(size.cy > iMaxHeight)
            iMaxHeight = size.cy;
         if(size.cx > iMaxWidth)
            iMaxWidth = size.cx;
         _CalcSize(pitem, pdc, iMaxWidth, iMaxHeight);
      }

   }


   void menu_list_window::layout()
   {
      if(GetParent() == NULL)
         return;
      rect rectClient;
      GetParent()->GetClientRect(rectClient);
      ::draw2d::memory_graphics pdc(allocer());
      pdc->SelectObject(m_pschema->m_font);
      size size = pdc->GetTextExtent("XXXMMM");
      int32_t iMaxHeight = size.cy;
      int32_t iMaxWidth = size.cx;
      m_iHeaderHeight = size.cy;
      _CalcSize(m_pitem, pdc, iMaxWidth, iMaxHeight);
      m_iItemHeight = iMaxHeight + 6 + 2;
      m_size.cx = iMaxWidth + 4;

      sp(menu_item) pitem = get_item();

      m_size.cy = m_iHeaderHeight + pitem->m_iSeparatorCount * 3 + pitem->m_iFullHeightItemCount * m_iItemHeight + 4;
   //   int32_t iMaxHeight = 0;
     // int32_t iMaxWidth = 0;
      rect rect(4, m_iHeaderHeight + 4, m_size.cx - 8, 4);
      string str;
      _LayoutButtons(m_pitem, iMaxWidth + 4, rect, rectClient);

      if(m_buttonClose.IsWindow())
      {
         m_buttonClose.ResizeToFit();
         m_buttonClose.GetWindowRect(rect);
         m_buttonClose.SetWindowPos(0, m_size.cx - rect.width() - 2, 2, 0, 0, SWP_NOSIZE);
         //m_buttonClose.ShowWindow(SW_NORMAL);
      }




   }


   void menu_list_window::_LayoutButtons(sp(menu_item) pitemParent, int32_t iMaxWidth, LPRECT lprect, LPCRECT lpcrectBound)
   {

      if(pitemParent->m_spitema == NULL)
         return;

      for(int32_t i = 0; i < pitemParent->m_spitema->get_size(); i++)
      {
         menu_item * pitem = pitemParent->m_spitema->element_at(i);
         if(pitem->m_id  == "separator")
         {
            lprect->bottom = lprect->top + 3;
         }
         else
         {
            lprect->bottom = lprect->top + m_iItemHeight - 2;
         }
         if(lprect->bottom > lpcrectBound->bottom)
         {
            lprect->left += iMaxWidth + 16;
            lprect->top = lpcrectBound->top;
            if(pitem->m_id == "separator")
               continue;
            lprect->bottom = lprect->top + m_iItemHeight - 2;
         }
         pitem->m_button.SetWindowPos(
            0,
            lprect->left + pitem->m_iLevel * g_base_menu_indent,
            lprect->top,
            iMaxWidth - pitem->m_iLevel * g_base_menu_indent,
            lprect->bottom - lprect->top,
            0);

         lprect->top = lprect->bottom + 2;
         _LayoutButtons(pitem, iMaxWidth, lprect, lpcrectBound);
      }
   }


   void menu_list_window::_001OnDraw(::draw2d::graphics *pdc)
   {
/*      rect rectClient;
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
      }*/

      ::user::interaction::_001OnDraw(pdc);
   }


   bool menu_list_window::get_color(COLORREF & cr,e_color ecolor)
   {
      
      bool bOk = menu::get_color(cr,ecolor);

      if(ecolor == color_background)
      {
         cr &= 0x00ffffff;
         cr |= (84 << 24);
      }


      return bOk;

   }


   void menu_list_window::_CreateButtons(sp(menu_item) pitemParent)
   {
      if(pitemParent->m_spitema == NULL)
         return;
      for(int32_t i = 0; i < pitemParent->m_spitema->get_size(); i++)
      {
         menu_item * pitem = pitemParent->m_spitema->element_at(i);
         if(!pitem->m_button.IsWindow())
         {
            pitem->m_button.create_window(null_rect(), this, pitem->m_id);
            pitem->m_button.m_id = pitem->m_id;
            
            if(pitem->m_bPopup)
            {

               pitem->m_button.m_pschema = m_pschema->m_pschemaPopupButton;

            }
            else
            {

               pitem->m_button.m_pschema = m_pschema->m_pschemaItemButton;

            }

            pitem->m_button.m_pitem = pitem;
            pitem->m_pbase = this;
         }
        _CreateButtons(pitem);
      }
   }

   bool menu_list_window::BaseOnControlEvent(::user::control_event * pevent)
   {

      sp(menu_item) pitemThis = get_item();

      sp(menu_item_ptra) spitema = pitemThis->m_spitema;

      if(pevent->m_eevent == ::user::event_button_clicked)
      {
         if(pevent->m_puie == &m_buttonClose)
         {
            if(m_bAutoClose)
            {
               send_message(WM_CLOSE);
            }
            if(base_class < ::user::place_holder > ::bases(GetParent()))
            {
               GetParent()->GetParent()->send_message(m_uiMessage);
            }
            else
            {
               GetParent()->send_message(m_uiMessage);
            }
         }
         else
         {
            if(pevent->m_puie->m_id != "separator")
            {

               menu_item * pitem = pitemThis->find(pevent->m_puie->m_id);

               if(pitem != NULL && !pitem->m_bPopup)
               {
                  m_pwndNotify->_001SendCommand(pitem->m_id);
                  if(m_bAutoClose)
                  {
                     send_message(WM_CLOSE);
                  }
                  if(base_class < ::user::place_holder > ::bases(GetParent()))
                  {
                     GetParent()->GetParent()->send_message(m_uiMessage);
                  }
                  else
                  {
                     GetParent()->send_message(m_uiMessage);
                  }
               }
            }
         }
      }
      return true;
   }

   void menu_list_window::clear()
   {
      /*if(IsWindow())
      {
         DestroyWindow();
      }*/
      ::user::menu_base::clear();
   }

} // namespace user
