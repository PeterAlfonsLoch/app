#include "framework.h"


namespace user
{


   form_list::form_list(sp(::axis::application) papp) :
      element(papp),
      ::user::interaction(papp),
      ::user::form_interface(papp),
      ::user::form(papp),
      ::user::scroll_view(papp),
      ::user::list(papp)
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

   void form_list::install_message_handling( ::message::dispatch *pinterface)
   {
      IGUI_WIN_MSG_LINK(WM_KEYDOWN, pinterface, this, &form_list::_001OnKeyDown);

      form::install_message_handling(pinterface);
      list::install_message_handling(pinterface);

   }

   void form_list::_001OnClick(uint_ptr uiFlags, point point)
   {
      //form::_000OnPosCreate
      list::_001OnClick(uiFlags, point);
      index iItem, iSubItem;
      if(_001HitTest_(point, iItem, iSubItem))
      {
         _001OnClick(uiFlags, point, iItem, iSubItem);
      }
   }

   void form_list::_001OnClick(uint_ptr uiFlags, point point, index iItem, index iSubItem)
   {
      UNREFERENCED_PARAMETER(uiFlags);
      UNREFERENCED_PARAMETER(point);
      sp(control) pcontrol = _001GetControlBySubItem(iSubItem);
      if(pcontrol != NULL)
      {
         if(pcontrol->descriptor().has_function(::user::control::function_action))
         {
            if(pcontrol->descriptor().get_type() == ::user::control::type_button)
            {


               session().m_puiLastLButtonDown      = NULL;

               ::user::control_event ev;
               ev.m_puie                  = pcontrol;
               ev.m_eevent                = ::user::event_button_clicked;

               m_iControlItem             = iItem;

               send_message(::message::message_event, 0, (LPARAM) &ev);

            }
         }
         else if(m_columna._001GetBySubItem(iSubItem)->m_bEditOnSecondClick)
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

   sp(control) form_list::_001GetControlBySubItem(index iSubItem)
   {
      ::user::list_column * pcolumn = m_columna._001GetBySubItem(iSubItem);
      if(pcolumn != NULL && pcolumn->m_iControl >= 0)
         return m_controldescriptorset[pcolumn->m_iControl].m_pcontrol;
      else
         return NULL;
   }

   void form_list::_001PlaceControl(sp(control) pcontrol)
   {
      rect rect;
      draw_list_item item(this);
      item.m_iDisplayItem = DisplayToStrict(pcontrol->m_iEditItem);
      item.m_iItem = pcontrol->m_iEditItem;
      item.m_iSubItem = pcontrol->descriptor().m_iSubItem;
      item.m_iOrder = _001MapSubItemToOrder(item.m_iSubItem);
      item.m_iListItem = -1;
      _001GetElementRect(&item, ::user::list::ElementText);
      if(item.m_bOk)
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

   void form_list::_001SetEditControl(sp(control) pcontrol)
   {

      if(pcontrol == NULL)
      {
         if(m_pcontrolEdit != NULL)
         {
            sp(class control) pcontrolEdit = m_pcontrolEdit;
            _001HideControl(pcontrolEdit);
            m_pcontrolEdit = NULL;
         }
      }
      else
      {
         m_pcontrolEdit = pcontrol;
      }
   }

   sp(control) form_list::_001GetEditControl()
   {
      return m_pcontrolEdit;
   }

   void form_list::_001OnVScroll(signal_details * pobj)
   {
      //SCAST_PTR(::message::scroll, pscroll, pobj);
      pobj->previous();


      sp(control) pcontrol = _001GetEditControl();

      if(pcontrol != NULL)
      {
         _001PlaceControl(pcontrol);
      }
   }

   void form_list::_001OnHScroll(signal_details * pobj)
   {
      pobj->previous();
      if(pobj->m_bRet)
         return;

      sp(control) pcontrol = _001GetEditControl();

      if(pcontrol != NULL)
      {
         _001PlaceControl(pcontrol);
      }

   }

   bool form_list::_001OnMouseActivate(::window_sp pDesktopWnd, UINT nHitTest, UINT message, LRESULT & iResult)
   {
      UNREFERENCED_PARAMETER(pDesktopWnd);
      UNREFERENCED_PARAMETER(nHitTest);
      UNREFERENCED_PARAMETER(message);
      UNREFERENCED_PARAMETER(iResult);
      return false;
   }

   void form_list::_001OnNotify(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void form_list::_001OnTimer(signal_details * pobj)
   {
      list::_001OnTimer(pobj);
   }

   void form_list::_001OnMessageNotify(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      // linux na verdade revamp
      /*
      lresult = user::NotifyRetContinue;

      sp(control) pcontrol = m_controldescriptorset.get_control_by_id(wparam);

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
//             //  case VK_RETURN:
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
      //return true;
   }

   void form_list::_001UpdateColumns()
   {
      _001RemoveControls();
      list::_001UpdateColumns();
   }

   sp(::user::interaction) form_list::_GetWnd()
   {
      return  (this);
   }

   LRESULT form_list::_001BaseWndGetProperty(EProperty eprop, LPARAM lparam)
   {
      switch(eprop)
      {
      case list::PropertyBaseWndInterface:
      case list::PropertyDrawBaseWndInterface:
         {
            const ::user::interaction_base ** ppinterface = (const ::user::interaction_base **) lparam;
            *ppinterface = (list * )this;
         }
         return 1;
      default:
         return 0;
      }
   }

   
   void form_list::_001OnDraw(::draw2d::graphics *pdc)
   {

      list::_001OnDraw(pdc);

   }


   void form_list::_001HideEditingControls()
   {
      if(_001GetEditControl() != NULL)
      {
         _001SetEditControl(NULL);
      }
      for(int32_t i = 0; i < m_controldescriptorset.get_count(); i++)
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


   void form_list::_001HideControl(sp(control) pcontrol)
   {
      pcontrol->ShowWindow(SW_HIDE);
   }


   void form_list::_001OnKeyDown(signal_details * pobj)
   {
      SCAST_PTR(::message::key, pkey, pobj)

      if(pkey->m_ekey == ::user::key_return)
      {
         _001SaveEdit(_001GetEditControl());
         _001HideEditingControls();
         pobj->m_bRet = true;
         return;
      }
      pkey->previous();
   }

   void form_list::_001DrawSubItem(draw_list_item * pdrawitem)
   {
      ::user::list::_001DrawSubItem(pdrawitem);
      if(pdrawitem->m_pcolumn->m_bCustomDraw)
      {
         sp(control) pcontrol = _001GetControlBySubItem(pdrawitem->m_iSubItem);
         if(pcontrol != NULL)
         {
            pdrawitem->m_rectClient = pdrawitem->m_rectSubItem;
            control_keep controlkeep(this, pdrawitem->m_iItem, pdrawitem->m_iSubItem);
            pcontrol->_003CallCustomDraw(pdrawitem->m_pgraphics, pdrawitem);
         }
      }
   }


   bool form_list::_001IsEditing()
   {
      return m_pcontrolEdit != NULL;
   }

   bool form_list::_001IsPointInside(sp(control) pcontrol, point64 point)
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
      rect rect;
      draw_list_item item(this);


      return m_iControlItem >= 0 && m_iControlSubItem == pcontrol->descriptor().m_iSubItem;

      //int32_t iEditItem;
      //int32_t iEditSubItem;

      //_001DisplayHitTest(point, iEditItem, iEditSubItem);

//      item.m_iDisplayItem = DisplayToStrict(pcontrol->m_iEditItem);
  //    item.m_iItem = pcontrol->m_iEditItem;
      item.m_iDisplayItem = DisplayToStrict(pcontrol->m_iEditItem);

      item.m_iSubItem = pcontrol->descriptor().m_iSubItem;
      item.m_iOrder = _001MapSubItemToOrder(item.m_iSubItem);
      item.m_iListItem = -1;
      //_001GetElementRect(&item, ::user::list::ElementSubItem);
      rectControl = item.m_rectSubItem;
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

   void form_list::_001OnColumnChange()
   {
      ::user::list::_001OnColumnChange();
      for(int32_t i = 0; i < m_columna.get_size(); i++)
      {
         if(m_columna[i].m_iControl >= 0 && m_columna[i].m_iControl < m_controldescriptorset.get_size())
         {
            class control::descriptor * pdescriptor = m_controldescriptorset.element_at(m_columna[i].m_iControl);
            if(pdescriptor != NULL)
            {
               if(m_columna[i].m_iSubItem >= 0)
               {
                  pdescriptor->m_iSubItem = m_columna[i].m_iSubItem;
               }
               else if(pdescriptor->m_iSubItem >= 0)
               {
                  m_columna[i].m_iSubItem = pdescriptor->m_iSubItem;
               }
            }
         }
      }
   }

   void form_list::_000OnMouse(::message::mouse * pmouse)
   {

      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
/*      if(uiMessage == WM_LBUTTONDOWN)
      {
         int32_t iItem;
         int32_t iSubItem;
         range range;
         _001GetSelection(range);
         if(_001DisplayHitTest(pt, iItem, iSubItem))
         {
            class ::user::control::descriptor * pcontrol = m_controldescriptorset.get_by_sub_item(iSubItem);
            if(pcontrol != NULL
            && pcontrol->m_pcontrol != NULL
            && (pcontrol->m_etype == type_edit
             || pcontrol->m_etype == type_edit_plain_text)
            && !range.has_sub_item(iItem, iSubItem))
            {
               _001HideEditingControls();
               return false;
            }
         }
      }
      else if(uiMessage == WM_LBUTTONUP)
      {
         int32_t iItem;
         int32_t iSubItem;
         range range;
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
      sp(::user::interaction) pui = get_top_child();
      sp(::user::interaction) puiBefore = NULL;
      bool bError;
      try
      {
         while(pui != NULL)
         {
            bError = false;
            try
            {
               if(pui->IsWindowVisible() && pui->_001IsPointInside(pmouse->m_pt))
               {
                  pui->_000OnMouse(pmouse);
                  if(pmouse->m_bRet)
                     return;
                  pui->send(pmouse);
                  if(pmouse->get_lresult() != 0)
                     return;
               }
            }
            catch(...)
            {
               bError = true;
               puiBefore = pui;
            }
            pui = under_sibling(pui);
            if(bError)
            {
               m_uiptraChild.remove(puiBefore);
            }
         }
      }
      catch(...)
      {
      }
      try
      {
         (m_pimpl->*m_pimpl->m_pfnDispatchWindowProc)(dynamic_cast < signal_details * > (pmouse));
         if(pmouse->get_lresult() != 0)
            return;
      }
      catch(...)
      {
      }

   }

   void form_list::control_get_client_rect(sp(control) pcontrol, LPRECT lprect)
   {
      if(pcontrol == NULL)
      {
         SetRectEmpty(lprect);
         return;
      }
      rect rectControl;
      draw_list_item item(this);
      item.m_iDisplayItem = m_iItemHover;
      item.m_iItem = DisplayToStrict(m_iItemHover);
      item.m_iSubItem = pcontrol->descriptor().m_iSubItem;
      item.m_iOrder = _001MapSubItemToOrder(item.m_iSubItem);
      item.m_iListItem = -1;
      _001GetElementRect(&item, ::user::list::ElementSubItem);
      rectControl = item.m_rectSubItem;
      class rect rect(rectControl);
      *lprect = rect;
   }

   void form_list::control_get_window_rect(sp(control) pcontrol, LPRECT lprect)
   {
      control_get_client_rect(pcontrol, lprect);
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
