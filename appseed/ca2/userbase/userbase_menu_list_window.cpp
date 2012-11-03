#include "framework.h"

namespace userbase
{

   const int BaseWndMenuCmdUi = 117;
   const int g_base_menu_indent = 11;


   menu_list_window::menu_list_window(::ca::application * papp) :
      ca(papp),
      menu_base(papp),
      m_buttonClose(papp)
   {
      m_bAutoDelete        = true;
      m_bOwnItem           = false;
      m_pwndNotify         = NULL;
      m_pitem(new menu_item(papp));
      m_etranslucency      = TranslucencyPresent;
      m_pschema            = NULL;
      m_bAutoClose         = true;
   }

   menu_list_window::menu_list_window(::ca::application * papp, menu_item * pitem) :
      ca(papp),
      menu_base(papp),
      m_buttonClose(papp)
   {
      m_pwndNotify         = NULL;
      m_bAutoClose         = true;
      m_bAutoDelete        = true;
      m_etranslucency      = TranslucencyPresent;
      m_pschema            = NULL;
      m_pitem              = pitem;
      m_bOwnItem           = false;
   }


   menu_list_window::~menu_list_window()
   {
   }

   void menu_list_window::install_message_handling(::gen::message::dispatch * pinterface)
   {
      control::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &menu_list_window::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &menu_list_window::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &menu_list_window::_001OnTimer);
   }

   // // BEGIN_MESSAGE_MAP(menu_list_window, ::user::interaction)
   // // END_MESSAGE_MAP()

   void menu_list_window::_001OnCreate(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      m_pschema            = &userbase::GetUfeSchema(get_app())->m_menu;
   }

   void menu_list_window::_001OnDestroy(gen::signal_object * pobj)
   {
      pobj->m_bRet = false;
   }




   bool menu_list_window::TrackPopupMenu(::user::interaction * pwndParent, ::user::interaction * pwndNotify)
   {
      ASSERT(pwndParent != NULL);
      //_m_pmenu = new menu_list_window(m_pitem);
      return _TrackPopupMenu(pwndParent, pwndNotify);
   }

   bool menu_list_window::_TrackPopupMenu(::user::interaction * pwndParent, ::user::interaction * pwndNotify)
   {

      m_pwndNotify = pwndNotify;

//      LPVOID lpvoid = NULL;
      if(!IsWindow())
      {

         if(!create(NULL, NULL,
            WS_VISIBLE | WS_CHILD,
            rect(0, 0, 0, 0), pwndParent, 0))
            return false;

         if(!m_buttonClose.create(this, ChildIdClose))
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


      SetWindowPos(NULL, 0, 0, rectClient.width(), rectClient.height(), SWP_SHOWWINDOW | SWP_NOZORDER);

      SetTimer(BaseWndMenuCmdUi, 300, NULL);

      return true;
   }


   bool menu_list_window::MenuFill(::user::interaction * pwndFill, ::user::interaction * pwndNotify)
   {

      m_pwndNotify = pwndNotify;

//      LPVOID lpvoid = NULL;
      if(!IsWindow())
      {

         if(!create(NULL, NULL,
            WS_VISIBLE | WS_CHILD,
            rect(0, 0, 0, 0), pwndFill, 0))
            return false;

      }
      else
      {
         if(get_parent() != pwndFill)
         {
            set_parent(pwndFill);
         }
      }

      if(!m_buttonClose.IsWindow())
      {
         if(!m_buttonClose.create(this, ChildIdClose))
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


      SetWindowPos(NULL, 0, 0, rectClient.width(), rectClient.height(), SWP_SHOWWINDOW | SWP_NOZORDER);

      SetTimer(BaseWndMenuCmdUi, 300, NULL);

      return true;
   }

   void menu_list_window::_UpdateCmdUi(menu_item * pitemParent)
   {
      
      if(pitemParent->m_spitema == NULL)
         return;
      
      menu_button_cmd_ui cmdui(get_app());
      
      cmdui.m_pitema = pitemParent->m_spitema;

      for(int i = 0; i < pitemParent->m_spitema->get_size(); i++)
      {
         
         menu_item * pitem = pitemParent->m_spitema->ptr_at(i);
         
         cmdui.m_iIndex       = i;
         cmdui.m_id           = pitem->m_id;
         cmdui.m_pOther       = (::user::interaction *) &pitem->m_button;

         if(m_pwndNotify->_001OnUpdateCmdUi(&cmdui))
            continue;

         _UpdateCmdUi(pitem);

      }

   }

   void menu_list_window::_001OnTimer(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::timer, ptimer, pobj)
      if(ptimer->m_nIDEvent == BaseWndMenuCmdUi)
      {
         _UpdateCmdUi(m_pitem);
         RedrawWindow();
      }
      pobj->m_bRet = false;
   }

   void menu_list_window::_CalcSize(menu_item * pitemParent, ::ca::graphics * pdc, int & iMaxWidth, int & iMaxHeight)
   {
      if(pitemParent->m_spitema == NULL)
         return;
      for(int i = 0; i < pitemParent->m_spitema->get_size(); i++)
      {
         menu_item * pitem = pitemParent->m_spitema->ptr_at(i);
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
      if(get_parent() == NULL)
         return;
      rect rectClient;
      get_parent()->GetClientRect(rectClient);
      ::ca::graphics * pdc = GetDC();
      pdc->SelectObject(m_pschema->m_font);
      size size = pdc->GetTextExtent("XXXMMM");
      int iMaxHeight = size.cy;
      int iMaxWidth = size.cx;
      m_iHeaderHeight = size.cy;
      _CalcSize(m_pitem, pdc, iMaxWidth, iMaxHeight);
      m_iItemHeight = iMaxHeight + 6 + 2;
      m_size.cx = iMaxWidth + 4;
      m_size.cy = m_iHeaderHeight +
         m_pitem->m_iSeparatorCount * 3 + m_pitem->m_iFullHeightItemCount * m_iItemHeight + 4;
   //   int iMaxHeight = 0;
     // int iMaxWidth = 0;
      rect rect(4, m_iHeaderHeight + 4, m_size.cx - 8, 4);
      string str;
      _LayoutButtons(m_pitem, iMaxWidth + 4, rect, rectClient);

      if(m_buttonClose.IsWindow())
      {
         m_buttonClose.ResizeToFit();
         m_buttonClose.GetWindowRect(rect);
         m_buttonClose.SetWindowPos(NULL, m_size.cx - rect.width() - 2,
            2, 0, 0, SWP_NOSIZE);
         //m_buttonClose.ShowWindow(SW_NORMAL);
      }



      ReleaseDC(pdc);
   }


   void menu_list_window::_LayoutButtons(menu_item * pitemParent, int iMaxWidth, LPRECT lprect, LPCRECT lpcrectBound)
   {
      if(pitemParent->m_spitema == NULL)
         return;
      for(int i = 0; i < pitemParent->m_spitema->get_size(); i++)
      {
         menu_item * pitem = pitemParent->m_spitema->ptr_at(i);
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
            NULL,
            lprect->left + pitem->m_iLevel * g_base_menu_indent,
            lprect->top,
            iMaxWidth - pitem->m_iLevel * g_base_menu_indent,
            lprect->bottom - lprect->top,
            0);

         lprect->top = lprect->bottom + 2;
         _LayoutButtons(pitem, iMaxWidth, lprect, lpcrectBound);
      }
   }


   void menu_list_window::_001OnDraw(::ca::graphics *pdc)
   {
      rect rectClient;
      GetClientRect(rectClient);
      if(_001IsTranslucent())
      {
         class imaging & imaging = System.imaging();
         imaging.color_blend(
            pdc,
            rectClient,
            RGB(200, 255, 255),
            127);
      }
      else
      {
         pdc->FillSolidRect(rectClient, GetSysColor(COLOR_WINDOW));
      }

      ::user::interaction::_001OnDraw(pdc);
   }


   void menu_list_window::_CreateButtons(menu_item * pitemParent)
   {
      if(pitemParent->m_spitema == NULL)
         return;
      for(int i = 0; i < pitemParent->m_spitema->get_size(); i++)
      {
         menu_item * pitem = pitemParent->m_spitema->ptr_at(i);
         if(!pitem->m_button.IsWindow())
         {
            pitem->m_button.create(this, pitem->m_id);
            pitem->m_button.m_id = pitem->m_id;
            pitem->m_button.m_etranslucency = TranslucencyPresent;
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
      if(pevent->m_eevent == ::user::event_button_clicked)
      {
         if(pevent->m_puie == &m_buttonClose)
         {
            if(m_bAutoClose)
            {
               send_message(WM_CLOSE);
            }
            if(base < ::user::place_holder > ::bases(get_parent()))
            {
               get_parent()->get_parent()->send_message(m_uiMessage, 0, 0);
            }
            else
            {
               get_parent()->send_message(m_uiMessage, 0, 0);
            }
         }
         else
         {
            if(pevent->m_puie->m_id != "separator")
            {
               menu_item * pitem = m_pitem->find(pevent->m_puie->m_id);
               if(pitem != NULL && !pitem->m_bPopup)
               {
                  m_pwndNotify->_001SendCommand(pitem->m_id);
                  if(m_bAutoClose)
                  {
                     send_message(WM_CLOSE);
                  }
                  if(base < ::user::place_holder > ::bases(get_parent()))
                  {
                     get_parent()->get_parent()->send_message(m_uiMessage, 0, 0);
                  }
                  else
                  {
                     get_parent()->send_message(m_uiMessage, 0, 0);
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
      ::userbase::menu_base::clear();
   }

} // namespace userbase
