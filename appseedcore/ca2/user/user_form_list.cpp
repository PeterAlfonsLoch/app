#include "StdAfx.h"

namespace user
{

   form_list::form_list(::ca::application * papp) :
      ca(papp),
      form(papp), 
      ::user::interaction(papp), 
      scroll_view(papp),
      list(papp)
   {
      m_iControlItem = -1;
      m_iControlSubItem = -1;
      m_pcontrolEdit = NULL;


      m_iOnClickClickCount    = 0;
      m_iOnClickClickItem     = -1;
      m_iOnClickClickSubItem  = -1;

   }

   form_list::~form_list()
   {

   }

   void form_list::_001GetSelection(
      ::database::id & key, ::database::selection &selection)
   {
      list::_001GetSelection(key, selection);
   }

   void form_list::_001InstallMessageHandling( ::user::win::message::dispatch *pinterface)
   {
      IGUI_WIN_MSG_LINK(WM_KEYDOWN, pinterface, this, &form_list::_001OnKeyDown);

      form::_001InstallMessageHandling(pinterface);
      list::_001InstallMessageHandling(pinterface);

   }

   void form_list::_001OnClick(UINT uiFlags, point point)
   {
      //form::_000OnPosCreate
      list::_001OnClick(uiFlags, point);
      index iItem, iSubItem;
      if(_001HitTest_(point, iItem, iSubItem))
      {
         _001OnClick(uiFlags, point, iItem, iSubItem);
      }
   }

   void form_list::_001OnClick(UINT uiFlags, point point, index iItem, index iSubItem)
   {
      UNREFERENCED_PARAMETER(uiFlags);
      UNREFERENCED_PARAMETER(point);
      control * pcontrol = _001GetControlBySubItem(iSubItem);
      if(pcontrol != NULL)
      {
         //if(pcontrol->m_bEditOnSecondClick)
         if(m_columna.GetBySubItem(iSubItem).m_bEditOnSecondClick)
         {
            if(m_iOnClickClickItem == iItem &&
               m_iOnClickClickSubItem == iSubItem)
            {
               m_iOnClickClickCount++;
            }
            else
            {
               m_iOnClickClickCount = 1;
            }
            m_iOnClickClickItem = iItem;
            m_iOnClickClickSubItem = iSubItem;
            if(m_iOnClickClickCount == 2)
            {
               m_iOnClickClickCount = 0;
               pcontrol->m_iEditItem = iItem;
               _001PlaceControl(pcontrol);
            }
         }
         else
         {
            pcontrol->m_iEditItem = iItem;
            _001PlaceControl(pcontrol);
         }
      }
   }

   control * form_list::_001GetControlBySubItem(index iSubItem)
   {
      Column & column = m_columna.GetBySubItem(iSubItem);
      if(column.m_iControl >= 0)
         return m_controldescriptorset[column.m_iControl].m_pcontrol;
      else
         return NULL;
   }

   void form_list::_001PlaceControl(control * pcontrol)
   {
      rect rect;
      if(_001GetElementRect(rect, DisplayToStrict(pcontrol->m_iEditItem), pcontrol->m_iEditItem, _001MapSubItemToOrder(pcontrol->descriptor().m_iSubItem), -1, userbase::_list::ElementText))
      {
         _001Update(pcontrol);
         pcontrol->SetWindowPos(
            ZORDER_TOP,
            rect.left,
            rect.top,
            rect.width(),
            rect.height(),
            SWP_SHOWWINDOW);
         _001SetEditControl(pcontrol);
         pcontrol->SetFocus();
      }

   }

   void form_list::OnDrawInterfaceDraw(::ca::graphics *pdc)
   {
      _001OnDraw(pdc);
   }

   void form_list::_001SetEditControl(control * pcontrol)
   {
      if(pcontrol == NULL)
      {
         if(m_pcontrolEdit != NULL)
         {
            class control * pcontrolEdit = m_pcontrolEdit;
            _001HideControl(pcontrolEdit);
            m_pcontrolEdit = NULL;
         }
      }
      else
      {
         m_pcontrolEdit = pcontrol;
      }
   }

   control * form_list::_001GetEditControl()
   {
      return m_pcontrolEdit;
   }

   void form_list::_001OnVScroll(gen::signal_object * pobj)
   {
      //SCAST_PTR(::user::win::message::scroll, pscroll, pobj);
      pobj->previous();


      control * pcontrol = _001GetEditControl();

      if(pcontrol != NULL)
      {
         _001PlaceControl(pcontrol);
      }
   }

   void form_list::_001OnHScroll(gen::signal_object * pobj) 
   {
      pobj->previous();
      if(pobj->m_bRet)
         return;

      control * pcontrol = _001GetEditControl();

      if(pcontrol != NULL)
      {
         _001PlaceControl(pcontrol);
      }

   }

   bool form_list::_001OnMouseActivate(::ca::window* pDesktopWnd, UINT nHitTest, UINT message, LRESULT & iResult)
   {
      UNREFERENCED_PARAMETER(pDesktopWnd);
      UNREFERENCED_PARAMETER(nHitTest);
      UNREFERENCED_PARAMETER(message);
      UNREFERENCED_PARAMETER(iResult);
      return false;
   }

   bool form_list::_001OnNotify(WPARAM wparam, LPARAM lparam, LRESULT & lresult)
   {
      UNREFERENCED_PARAMETER(wparam);
      UNREFERENCED_PARAMETER(lparam);
      UNREFERENCED_PARAMETER(lresult);
      return false;
   }

   void form_list::_001OnTimer(gen::signal_object * pobj)
   {
      list::_001OnTimer(pobj);
   }

   bool form_list::_001OnMessageNotify(WPARAM wparam, LPARAM lparam, LRESULT & lresult)
   {
      UNREFERENCED_PARAMETER(wparam);
      UNREFERENCED_PARAMETER(lparam);
      UNREFERENCED_PARAMETER(lresult);
      // linux na verdade revamp
      /*
      lresult = user::NotifyRetContinue;

      control * pcontrol = m_controldescriptorset.get_control_by_id(wparam);

      if(pcontrol == NULL)
         return true;

      user::Notify * pnotify = (user::Notify *) lparam;

      switch(pcontrol->descriptor().get_type())
      {
      case control::type_edit:
         switch(pnotify->m_uiCode)
         {
         case user::NotifyKeyDown:
            {
               user::NotifyKey * pkey = (user::NotifyKey *) pnotify;
               switch(pkey->m_uiVKey)
               {
               case VK_RETURN:
                  _001SaveEdit(pcontrol);
                  pcontrol->ShowWindow(SW_HIDE);
                  lresult &= ~user::NotifyRetContinue;
                  return true;
               }
            }
            break;
         }
         break;
      }*/
      return true;
   }

   void form_list::_001UpdateColumns()
   {
      _001RemoveControls();
      list::_001UpdateColumns();
   }

   ::user::interaction * form_list::_GetWnd()
   {
      return dynamic_cast < ::user::interaction * > (this);
   }

   LRESULT form_list::_001BaseWndGetProperty(EProperty eprop, LPARAM lparam)
   {
      switch(eprop)
      {
      case list::PropertyBaseWndInterface:
      case list::PropertyDrawBaseWndInterface:
         {
            const ::user::window_interface ** ppinterface = (const ::user::window_interface **) lparam;
            *ppinterface = (list * )this;
         }
         return 1;
      default:
         return 0;
      }
   }

   void form_list::_001OnDraw(::ca::graphics *pdc)
   {
      list::_001OnDraw(pdc);
      form::_001OnDraw(pdc);
   }

   void form_list::_001HideEditingControls()
   {
      if(_001GetEditControl() != NULL)
      {
         _001SetEditControl(NULL);
      }
      for(int i = 0; i < m_controldescriptorset.get_count(); i++)
      {
         class ::user::control::descriptor & control = m_controldescriptorset[i];
         if(control.m_etype == type_edit
         || control.m_etype == type_edit_plain_text)
         {
            if(control.m_pcontrol != NULL)
            {
               control.m_pcontrol->ShowWindow(SW_HIDE);
            }
         }
      }
   }


   void form_list::_001HideControl(control * pcontrol)
   {
      pcontrol->ShowWindow(SW_HIDE);
   }


   void form_list::_001OnKeyDown(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::key, pkey, pobj)
      
      if(pkey->m_nChar == VK_RETURN)
      {
         _001SaveEdit(_001GetEditControl());
         _001HideEditingControls();
         pobj->m_bRet = true;
         return;
      }
      pkey->previous();
   }

   void form_list::_001DrawSubItem(
      ::ca::graphics * pdc,
      draw_item * pdrawitem,
      LPCRECT lpcrect,
      INT_PTR iSubItem,
      bool bItemHover,
      bool bSubItemHover,
      bool bFocus)
   {
      control * pcontrol = _001GetControlBySubItem(iSubItem);
      if(pcontrol != NULL)
      {
         control_keep controlkeep(this, pdrawitem->m_itemId, iSubItem);
         pcontrol->_003CallCustomDraw(
            pdc, 
            lpcrect,
            bItemHover, 
            bSubItemHover,
            bFocus);
      }
   }


   bool form_list::_001IsEditing()
   {
      return m_pcontrolEdit != NULL;
   }

   bool form_list::_001IsPointInside(control * pcontrol, point64 point)
   {
      if(pcontrol->m_pdescriptor != NULL)
      {
         if(pcontrol->m_pdescriptor->m_etype == type_edit
         || pcontrol->m_pdescriptor->m_etype == type_edit_plain_text)
         {
            if(pcontrol == _001GetEditControl())
            {
               rect64 rectWindow;
               pcontrol->GetWindowRect(rectWindow);
               return rectWindow.contains(point) != FALSE;
            }
            else
            {
               return false;
            }
         }
      }
      rect rectControl;
      _001GetElementRect(rectControl, DisplayToStrict(_001GetTopIndex()), _001GetTopIndex(), _001MapSubItemToOrder(pcontrol->descriptor().m_iSubItem), -1, userbase::_list::ElementSubItem);
      ClientToScreen(rectControl);
      rect64 rectForm;
      GetWindowRect(rectForm);
      rect64 rectClient;
      rectClient.top = rectForm.top;
      rectClient.bottom = rectForm.bottom;
      rectClient.left = rectControl.left;
      rectClient.right = rectControl.right;
      return rectClient.contains(point) != FALSE;
   }

   void form_list::_000OnMouse(::user::win::message::mouse * pmouse)
   {
      
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
/*      if(uiMessage == WM_LBUTTONDOWN)
      {
         int iItem;
         int iSubItem;
         Range range;
         _001GetSelection(range);
         if(_001DisplayHitTest(pt, iItem, iSubItem))
         {
            class ::user::control::descriptor * pcontrol = m_controldescriptorset.get_by_sub_item(iSubItem);
            if(pcontrol != NULL 
            && pcontrol->m_pcontrol != NULL
            && (pcontrol->m_etype == type_edit 
             || pcontrol->m_etype == type_edit_plain_text)
            && !range.HasSubItem(iItem, iSubItem))
            {
               _001HideEditingControls();
               return false;
            }
         }
      }
      else if(uiMessage == WM_LBUTTONUP)
      {
         int iItem;
         int iSubItem;
         Range range;
         _001GetSelection(range);
         if(_001DisplayHitTest(pt, iItem, iSubItem))
         {
            class ::user::control::descriptor * pcontrol = m_controldescriptorset.get_by_sub_item(iSubItem);
            if(pcontrol != NULL 
            && pcontrol->m_pcontrol != NULL
            && !pcontrol->m_pcontrol->IsWindowVisible()
            && (pcontrol->m_etype == type_edit 
             || pcontrol->m_etype == type_edit_plain_text))
            {
               return false;
            }
         }
      }*/
      control_keep controlkeep(this, pt);
      user::interaction * pui = get_top_child();
      while(pui != NULL)
      {
         if(pui->IsWindowVisible() && pui->_001IsPointInside(pmouse->m_pt))
         {
            pui->_000OnMouse(pmouse);
            if(pmouse->m_bRet)
               return;
            pui->SendMessage(pmouse);
            if(pmouse->get_lresult() != 0)
               return;
         }
         pui = pui->under_sibling();
      }
      try
      {
         (m_pimpl->*m_pimpl->m_pfnDispatchWindowProc)(dynamic_cast < gen::signal_object * > (pmouse));
         if(pmouse->get_lresult() != 0)
            return;
      }
      catch(...)
      {
      }

   }

   void form_list::control_get_client_rect(LPRECT lprect)
   {
      rect rectControl;
      _001GetElementRect(rectControl, DisplayToStrict(m_iControlItem), m_iControlItem, _001MapSubItemToOrder(m_iControlSubItem), -1, userbase::_list::ElementSubItem);
      class rect rect(rectControl);
      *lprect = rect;
   }

   void form_list::control_get_window_rect(LPRECT lprect)
   {
      control_get_client_rect(lprect);
      ClientToScreen(lprect);
   }

   bool form_list::control_001DisplayHitTest(POINT pt)
   {
      return _001DisplayHitTest(pt, m_iControlItem, m_iControlSubItem);
   }

   bool form_list::BaseOnControlEvent(::user::control_event * pevent)
   {
      class control::descriptor * pdescriptor = m_controldescriptorset.get(pevent->m_puie);
      if(pdescriptor != NULL)
      {
         pdescriptor->m_pcontrol->m_iEditItem = m_iControlItem;
      }
      return form::BaseOnControlEvent(pevent);
   }


} // namespace user