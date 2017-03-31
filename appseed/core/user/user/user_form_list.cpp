#include "framework.h"


namespace user
{


   form_list::form_list()
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
      ::database::id & key,::database::selection &selection)
   {
      list::_001GetSelection(key,selection);
   }

   void form_list::install_message_handling(::message::dispatch *pinterface)
   {
      IGUI_WIN_MSG_LINK(WM_KEYDOWN,pinterface,this,&form_list::_001OnKeyDown);

      form_mesh::install_message_handling(pinterface);
      list::install_message_handling(pinterface);

   }

   bool form_list::_001OnClick(uint_ptr uiFlags,point point)
   {
      //form::_000OnPosCreate
      list::_001OnClick(uiFlags,point);
      index iItem,iSubItem;
      if(_001HitTest_(point,iItem,iSubItem))
      {
         _001OnClick(uiFlags,point,iItem,iSubItem);
      }
      return true;
   }

   bool form_list::_001OnClick(uint_ptr uiFlags,point point,index iItem,index iSubItem)
   {
      UNREFERENCED_PARAMETER(uiFlags);
      UNREFERENCED_PARAMETER(point);
      sp(control) pcontrol = _001GetControl(iItem, iSubItem);
      if(pcontrol != NULL)
      {
         if(pcontrol->descriptor().has_function(::user::control::function_action))
         {
            if(pcontrol->descriptor().get_type() == ::user::control_type_button)
            {


               Session.m_puiLastLButtonDown      = NULL;

               ::user::control_event ev;
               ev.m_puie                  = pcontrol;
               ev.m_eevent                = ::user::event_button_clicked;

               m_iControlItem             = iItem;

               send_message(::message::message_event,0,(LPARAM)&ev);

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
               //pcontrol->m_iEditItem = iItem;
               _001PlaceControl(pcontrol, iItem);
            }
         }
         else
         {
      
            //pcontrol->m_iEditItem = iItem;
            _001PlaceControl(pcontrol, iItem);

         }

      }

      return true;

   }


   sp(control) form_list::_001GetControl(index iItem, index iSubItem)
   {

      synch_lock sl(m_pmutex);

      ::user::list_column * pcolumn = m_columna._001GetBySubItem(iSubItem);

      if(pcolumn == NULL || pcolumn->m_iControl < 0)
      {

         return NULL;

      }

      sp(class ::user::control::descriptor) pdescriptor = m_controldescriptorset[pcolumn->m_iControl];

      if(pdescriptor.is_null())
      {

         return NULL;

      }

      return pdescriptor->get_control(this, iItem);

   }
   void form_list::_001OnShowControl(sp(control) pcontrol)
   {


   }

   void form_list::_001PlaceControl(sp(control) pcontrol, int iEditItem)
   {
      //rect rect;
      
      
      if (_001GetEditControl() != NULL)
      {

         _001SaveEdit(_001GetEditControl());

      }

      _001HideEditingControls();

      draw_list_item item(this);

      pcontrol->m_iEditItem = iEditItem;

      item.m_iDisplayItem = DisplayToStrict(iEditItem);

      item.m_iItem = iEditItem;

      _001EnsureVisible(item.m_iItem);

      item.m_iSubItem = pcontrol->descriptor().m_iSubItem;

      item.m_iOrder = _001MapSubItemToOrder(item.m_iSubItem);

      item.m_iListItem = -1;

      _001GetElementRect(&item,::user::mesh::element_text);

      if(item.m_bOk)
      {

         rect rectControl(item.m_rectSubItem);

         rectControl.offset(get_viewport_offset());

         _001Update(pcontrol);

         pcontrol->SetWindowPos(
            ZORDER_TOP,
            rectControl.left,
            rectControl.top,
            rectControl.width(),
            rectControl.height(),
            SWP_SHOWWINDOW);

         _001SetEditControl(pcontrol);

         pcontrol->SetFocus();

         _001OnShowControl(pcontrol);

      }

   }


   void form_list::_001UpdateEdit(sp(control) pcontrol)
   {
      ASSERT(pcontrol != NULL);
      if (pcontrol == NULL)
         return;

      if (m_bOnEditUpdate)
         return;
      keep<bool> keepUpdateLock(&m_bOnEditUpdate, true, false, true);

      ASSERT(pcontrol->descriptor().get_type() == control_type_edit
         || pcontrol->descriptor().get_type() == control_type_edit_plain_text);

      sp(::user::plain_edit) pedit = pcontrol;

      if (pedit.is_set())
      {

         pedit->m_spfont = m_font;

      }

      if (pcontrol->descriptor().has_function(control::function_vms_data_edit))
      {

         

         draw_list_item item(this);

         item.m_iItem = pcontrol->m_iEditItem;
         item.m_iSubItem = pcontrol->descriptor().m_iSubItem;

         _001GetItemText(&item);

         if (item.m_bOk)
         {

            pcontrol->_001SetText(item.m_strText, ::action::source_initialize);

         }

         //var var;
         //::database::selection selection;
         //_001GetSelection(pcontrol->descriptor().m_dataid, selection);
         //if (selection.get_item_count() > 0)
         //{
         //   ::database::selection_item & item = selection.get_item(0);
         //   sp(::user::elemental) ptext = NULL;
         //   if (get_child_by_id(pcontrol->m_id) != NULL)
         //   {
         //      ptext = get_child_by_id(pcontrol->m_id);
         //   }
         //   if (ptext == NULL && pcontrol != NULL)
         //   {
         //      ptext = pcontrol;
         //   }
         //   if (ptext == NULL)
         //      return;
         //   if (data_get(pcontrol->descriptor().m_dataid.m_id + "." + item.m_id.m_id, var))
         //   {
         //      switch (var.get_type())
         //      {
         //      case var::type_string:
         //      {
         //         string str;
         //         str = var.m_str;
         //         ptext->_001SetText(str, ::action::source_database);
         //      }
         //      break;
         //      case var::type_int32:
         //      {
         //         string str;
         //         str.Format("%d", var.int32());
         //         ptext->_001SetText(str, ::action::source_database);
         //      }
         //      break;
         //      default:
         //         ASSERT(FALSE);
         //         break;
         //      }
         //   }
         //}
      }
   }

   bool form_list::_001SaveEdit(sp(control) pcontrol)
   {

      if (pcontrol == NULL)
         return false;

      ASSERT(pcontrol->descriptor().get_type() == control_type_edit || pcontrol->descriptor().get_type() == control_type_edit_plain_text
      || pcontrol->descriptor().get_type() == control_type_combo_box);

      sp(::user::elemental) pedit = get_child_by_id(pcontrol->m_id);

      string str;

      if (pedit == NULL)
      {

         sp(::user::elemental) ptext = pcontrol;

         if (ptext == NULL)
            return false;

         ptext->_001GetText(str);

      }
      else
      {

         pedit->_001GetText(str);

      }

      if (!pcontrol->Validate(str))
      {
         // que tal um balão para indicar o erro
         return false;
      }

      var var;
      if (!pcontrol->get_data(pedit, var))
      {
         return false;
      }

      if (!_001Validate(pcontrol, var))
      {
         return false;
      }

      if (pcontrol->descriptor().has_function(control::function_vms_data_edit))
      {
         
         draw_list_item item(this);

         item.m_iItem = pcontrol->m_iEditItem;

         item.m_iSubItem = pcontrol->descriptor().m_iSubItem;

         item.m_strText = var.get_string();

         _001SetItemText(&item);

         on_update(NULL, ::user::impact::hint_control_saved, pcontrol);

      }

      return true;

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

         _001PlaceControl(pcontrol, pcontrol->m_iEditItem);

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
         
         _001PlaceControl(pcontrol, pcontrol->m_iEditItem);

      }

   }

   bool form_list::_001OnMouseActivate(::window_sp pDesktopWnd,UINT nHitTest,UINT message,LRESULT & iResult)
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

   void form_list::_001OnTimer(::timer * ptimer)
   {
      list::_001OnTimer(ptimer);
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
      case control_type_edit:
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

      synch_lock sl(m_pmutex);

      _001RemoveControls();

      list::_001UpdateColumns();

   }

   LRESULT form_list::_001BaseWndGetProperty(EProperty eprop,LPARAM lparam)
   {
      switch(eprop)
      {
      case list::PropertyBaseWndInterface:
      case list::PropertyDrawBaseWndInterface:
      {
         const ::user::interaction_base ** ppinterface = (const ::user::interaction_base **) lparam;
         *ppinterface = (list *)this;
      }
      return 1;
      default:
         return 0;
      }
   }


   void form_list::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      list::_001OnDraw(pgraphics);

   }

   void form_list::_001DrawChildren(::draw2d::graphics * pgraphics)
   {

      form_mesh::_001DrawChildren(pgraphics);

   }


   void form_list::_001HideEditingControls()
   {

      form_mesh::_001HideEditingControls();

      //if(_001GetEditControl() != NULL)
      //{
      //   _001SetEditControl(NULL);
      //}
      //for(int32_t i = 0; i < m_controldescriptorset.get_count(); i++)
      //{
      //   class ::user::control::descriptor & descriptor = m_controldescriptorset(i);
      //   if(control.m_etype == control_type_edit
      //      || control.m_etype == control_type_edit_plain_text)
      //   {
      //      if(control.m_pcontrol != NULL)
      //      {
      //         control.m_pcontrol->ShowWindow(SW_HIDE);
      //      }
      //   }
      //}
   }


   void form_list::_001HideControl(sp(control) pcontrol)
   {
      pcontrol->ShowWindow(SW_HIDE);
   }


   void form_list::_001OnKeyDown(signal_details * pobj)
   {
      SCAST_PTR(::message::key,pkey,pobj);

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

         sp(control) pcontrol = _001GetControl(pdrawitem->m_iItem, pdrawitem->m_iSubItem);

         if(pcontrol != NULL)
         {

            pdrawitem->m_rectClient = pdrawitem->m_rectSubItem;

            pdrawitem->m_rectWindow = pdrawitem->m_rectClient;

            ClientToScreen(pdrawitem->m_rectWindow);

            ::rect rectWindow;

            pcontrol->GetWindowRect(rectWindow);

            ScreenToClient(rectWindow);

            if(rectWindow != pdrawitem->m_rectClient)
            {

               pcontrol->SetWindowPos(0,pdrawitem->m_rectClient,SWP_SHOWWINDOW | SWP_NOZORDER);

            }

            //control_keep controlkeep(this,pdrawitem->m_iItem,pdrawitem->m_iSubItem);

            if(pcontrol != Session.get_keyboard_focus())
            {

               sp(::user::plain_edit) pedit = pcontrol;

               if(pedit.is_set())
               {
                  pdrawitem->m_bOk = false;
                  _001GetItemText(pdrawitem);
                  if(pdrawitem->m_bOk)
                  {

                     string strText;

                     pedit->_001GetText(strText);


                     if(strText != pdrawitem->m_strText)
                     {

                        pedit->_001SetText(pdrawitem->m_strText,::action::source_sync);

                     }

                  }

               }

            }

            //pcontrol->_003CallCustomDraw(pdrawitem->m_pgraphics,pdrawitem);
            //pdrawitem->m_pgraphics->SelectClipRgn(NULL);
            //_001OnClip(pdrawitem->m_pgraphics);
         }
      }
   }


   bool form_list::_001IsEditing()
   {
      return m_pcontrolEdit != NULL;
   }

   bool form_list::_001IsPointInside(sp(control) pcontrol,point64 point)
   {
      if(pcontrol->m_pdescriptor != NULL)
      {
         if(pcontrol->m_pdescriptor->m_etype == control_type_edit
            || pcontrol->m_pdescriptor->m_etype == control_type_edit_plain_text)
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
      //_001GetElementRect(&item, ::user::mesh::element_sub_item);
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

      synch_lock sl(m_pmutex);

      ::user::list::_001OnColumnChange();

      for(int32_t i = 0; i < m_columna.get_size(); i++)
      {
         if(m_columna[i]->m_iControl >= 0 && m_columna[i]->m_iControl < m_controldescriptorset.get_size())
         {
            class control::descriptor * pdescriptor = m_controldescriptorset.element_at(m_columna[i]->m_iControl);
            if(pdescriptor != NULL)
            {
               if(m_columna[i]->m_iSubItem >= 0)
               {
                  pdescriptor->m_iSubItem = m_columna[i]->m_iSubItem;
               }
               else if(pdescriptor->m_iSubItem >= 0)
               {
                  m_columna[i]->m_iSubItem = pdescriptor->m_iSubItem;
               }
            }
         }
      }
   }

   void form_list::_000OnMouse(::message::mouse * pmouse)
   {

      form_mesh::_000OnMouse(pmouse);

      //point pt = pmouse->m_pt;
      //ScreenToClient(&pt);
      ///*      if(uiMessage == WM_LBUTTONDOWN)
      //      {
      //      int32_t iItem;
      //      int32_t iSubItem;
      //      range range;
      //      _001GetSelection(range);
      //      if(_001DisplayHitTest(pt, iItem, iSubItem))
      //      {
      //      class ::user::control::descriptor * pcontrol = m_controldescriptorset.get_by_sub_item(iSubItem);
      //      if(pcontrol != NULL
      //      && pcontrol->m_pcontrol != NULL
      //      && (pcontrol->m_etype == type_edit
      //      || pcontrol->m_etype == type_edit_plain_text)
      //      && !range.has_sub_item(iItem, iSubItem))
      //      {
      //      _001HideEditingControls();
      //      return false;
      //      }
      //      }
      //      }
      //      else if(uiMessage == WM_LBUTTONUP)
      //      {
      //      int32_t iItem;
      //      int32_t iSubItem;
      //      range range;
      //      _001GetSelection(range);
      //      if(_001DisplayHitTest(pt, iItem, iSubItem))
      //      {
      //      class ::user::control::descriptor * pcontrol = m_controldescriptorset.get_by_sub_item(iSubItem);
      //      if(pcontrol != NULL
      //      && pcontrol->m_pcontrol != NULL
      //      && !pcontrol->m_pcontrol->IsWindowVisible()
      //      && (pcontrol->m_etype == type_edit
      //      || pcontrol->m_etype == type_edit_plain_text))
      //      {
      //      return false;
      //      }
      //      }
      //      }*/
      //control_keep controlkeep(this,pt);
      //sp(::user::interaction) pui = top_child();
      //sp(::user::interaction) puiBefore = NULL;
      //bool bError;
      //try
      //{
      //   while(pui != NULL)
      //   {
      //      bError = false;
      //      try
      //      {
      //         if(pui->IsWindowVisible() && pui->_001IsPointInside(pmouse->m_pt))
      //         {
      //            pui->_000OnMouse(pmouse);
      //            if(pmouse->m_bRet)
      //               return;
      //            pui->send(pmouse);
      //            if(pmouse->get_lresult() != 0)
      //               return;
      //         }
      //      }
      //      catch(...)
      //      {
      //         bError = true;
      //         puiBefore = pui;
      //      }
      //      pui = under_sibling(pui);
      //      if(bError)
      //      {
      //         m_uiptraChild.remove(puiBefore);
      //      }
      //   }
      //}
      //catch(...)
      //{
      //}
      //try
      //{
      //   (m_pimpl->*m_pimpl->m_pfnDispatchWindowProc)(dynamic_cast <signal_details *> (pmouse));
      //   if(pmouse->get_lresult() != 0)
      //      return;
      //}
      //catch(...)
      //{
      //}

   }

   void form_list::control_get_client_rect(sp(control) pcontrol,LPRECT lprect)
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

      if(m_bGroup)
      {
         item.m_iGroupTopIndex = 0;
         //            int32_t igroup;
         for(item.m_iGroup = 0; item.m_iGroup < m_nGroupCount; item.m_iGroup++)
         {
            item.m_iGroupCount = _001GetGroupItemCount(item.m_iGroup);
            if(item.m_iItem >= item.m_iGroupTopIndex && item.m_iItem < (item.m_iGroupTopIndex + item.m_iGroupCount))
               break;
         }
      }


      item.m_iSubItem = pcontrol->descriptor().m_iSubItem;
      item.m_iOrder = _001MapSubItemToOrder(item.m_iSubItem);
      item.m_iListItem = -1;
      _001GetElementRect(&item,::user::mesh::element_sub_item);
      rectControl = item.m_rectSubItem;
      class rect rect(rectControl);
      *lprect = rect;
   }

   void form_list::control_get_window_rect(sp(control) pcontrol,LPRECT lprect)
   {
      control_get_client_rect(pcontrol,lprect);
      ClientToScreen(lprect);
   }

   bool form_list::control_001DisplayHitTest(POINT pt)
   {
      return _001DisplayHitTest(pt,m_iControlItem,m_iControlSubItem);
   }


   bool form_list::_001PreviousEditableControl(int & iItem, int & iSubItem)
   {

      int iPreviousItem = iItem;

      int iColumnCount = _001GetColumnCount();

      ::user::list_column * pcolumn = m_columna._001GetBySubItem(iSubItem);

      ::user::list_column * pcolumnPrevious = NULL;

      for (index i = pcolumn->m_iKeyVisible -1; i >= 0; i--)
      {

         if (m_columna._001GetVisible(i)->m_iControl >= 0)
         {


            pcolumnPrevious = m_columna._001GetVisible(i);

            break;

         }

      }

      if (pcolumnPrevious == NULL)
      {

         iPreviousItem--;

         for (index i = iColumnCount - 1; i >= pcolumn->m_iKeyVisible; i--)
         {

            if (m_columna._001GetVisible(i)->m_iControl >= 0)
            {

               pcolumnPrevious = m_columna._001GetVisible(i);

               break;

            }

         }

      }

      if (pcolumnPrevious != NULL)
      {

         if (iPreviousItem < 0)
         {

            iPreviousItem = _001GetItemCount() - 1;

         }

         if (iPreviousItem < 0)
         {

            return false;

         }

         iItem = iPreviousItem;

         iSubItem = pcolumnPrevious->m_iSubItem;

         return true;

      }

      return false;

   }


   bool form_list::_001NextEditableControl(int & iItem, int & iSubItem)
   {

      int iNextItem = iItem;

      int iColumnCount = _001GetColumnCount();

      ::user::list_column * pcolumn = m_columna._001GetBySubItem(iSubItem);

      ::user::list_column * pcolumnNext = NULL;

      for (index i = pcolumn->m_iKeyVisible + 1; i < iColumnCount; i++)
      {

         if (m_columna._001GetVisible(i)->m_iControl >= 0)
         {


            pcolumnNext = m_columna._001GetVisible(i);

            break;

         }

      }

      if (pcolumnNext == NULL)
      {

         iNextItem++;

         for (index i = 0; i <= pcolumn->m_iKeyVisible; i++)
         {

            if (m_columna._001GetVisible(i)->m_iControl >= 0)
            {

               pcolumnNext = m_columna._001GetVisible(i);

               break;

            }

         }

      }

      if (pcolumnNext != NULL)
      {

         if (iNextItem >= _001GetItemCount())
         {

            iNextItem = 0;

         }

         if (iNextItem >= _001GetItemCount())
         {

            return false;

         }

         iItem = iNextItem;

         iSubItem = pcolumnNext->m_iSubItem;

         return true;

      }

      return false;

   }

   bool form_list::_001UpperEditableControl(int & iItem, int & iSubItem)
   {

      int iUpperItem = iItem - 1;

      if (iUpperItem < 0)
      {

         iUpperItem = _001GetItemCount() - 1;

      }

      if (iUpperItem < 0)
      {

         return false;

      }

      iItem = iUpperItem;

      return true;

   }


   bool form_list::_001LowerEditableControl(int & iItem, int & iSubItem)
   {

      int iLowerItem = iItem + 1;

      if (iLowerItem >= _001GetItemCount())
      {

         iLowerItem = 0;

      }

      if (iLowerItem >= _001GetItemCount())
      {

         return false;

      }

      iItem = iLowerItem;

      return true;

   }



   bool form_list::BaseOnControlEvent(::user::control_event * pevent)
   {
      //class control::descriptor * pdescriptor = m_controldescriptorset.get(pevent->m_puie);
      //if(pdescriptor != NULL)
      //{
      //   pdescriptor->m_pcontrol->m_iEditItem = m_iControlItem;
      //}

      if (pevent->m_eevent == ::user::event_enter_key)
      {

         if(m_pcontrolEdit != NULL)
         {

            _001SaveEdit(m_pcontrolEdit);
            _001HideControl(m_pcontrolEdit);

            pevent->m_bRet = true;
            pevent->m_bProcessed = true;

         }

      }
      else if (pevent->m_eevent == ::user::event_tab_key)
      {

         int iItem = 0;
         int iSubItem = 0;

         if (m_pcontrolEdit != NULL)
         {

            iItem = m_pcontrolEdit->m_iEditItem;

            iSubItem = m_pcontrolEdit->descriptor().m_iSubItem;

            _001SaveEdit(m_pcontrolEdit);
            _001HideControl(m_pcontrolEdit);

            pevent->m_bRet = true;
            pevent->m_bProcessed = true;

         }

         bool bOk;

         if (Session.is_key_pressed(::user::key_shift))
         {

            bOk = _001PreviousEditableControl(iItem, iSubItem);

         }
         else
         {

            bOk = _001NextEditableControl(iItem, iSubItem);

         }

         if(bOk)
         { 
         
            sp(control) pcontrol = _001GetControl(iItem, iSubItem);

            _001PlaceControl(pcontrol, iItem);

            pevent->m_bRet = true;

            pevent->m_bProcessed = true;  

         }

      }
      else if (pevent->m_eevent == ::user::event_key_down)
      {

         SCAST_PTR(::message::key, pkey, pevent->m_pobj);

         if (pkey->m_ekey == key_down || pkey->m_ekey == key_up
            || pkey->m_ekey == key_left || pkey->m_ekey == key_right)
         {

            int iItem = 0;

            int iSubItem = 0;

            if (m_pcontrolEdit != NULL)
            {

               sp(::user::plain_edit) pedit = m_pcontrolEdit;

               if (pedit.is_set())
               {

                  strsize iSel;

                  strsize iSelEnd;

                  pedit->_001GetSel(iSel, iSelEnd);

                  if (iSel != iSelEnd)
                  {

                     iSel = -1;

                  }

                  if (pkey->m_ekey == key_left && iSel != 0)
                  {

                     return false;

                  }
                  else if (pkey->m_ekey == key_right)
                  {

                     strsize iLen = pedit->_001GetTextLength();

                     if (iSel != iLen)
                     {

                        return false;

                     }

                  }

               }

               iItem = m_pcontrolEdit->m_iEditItem;

               iSubItem = m_pcontrolEdit->descriptor().m_iSubItem;

               _001SaveEdit(m_pcontrolEdit);
               _001HideControl(m_pcontrolEdit);

               pevent->m_bRet = true;
               pevent->m_bProcessed = true;

            }

            bool bOk;

            if (pkey->m_ekey == key_left)
            {

               bOk = _001PreviousEditableControl(iItem, iSubItem);

            }
            else if (pkey->m_ekey == key_right)
            {

               bOk = _001NextEditableControl(iItem, iSubItem);

            }
            else if (pkey->m_ekey == key_up)
            {

               bOk = _001UpperEditableControl(iItem, iSubItem);

            }
            else if (pkey->m_ekey == key_down)
            {

               bOk = _001LowerEditableControl(iItem, iSubItem);

            }

            if (bOk)
            {

               sp(control) pcontrol = _001GetControl(iItem, iSubItem);

               _001PlaceControl(pcontrol, iItem);


               sp(::user::plain_edit) pedit = m_pcontrolEdit;


               if(pedit.is_set())
               {

                  if (pkey->m_ekey == key_left)
                  {

                     strsize iLen = pedit->_001GetTextLength();

                     pedit->_001SetSel(iLen, iLen);


                  }
                  else if (pkey->m_ekey == key_right)
                  {

                     pedit->_001SetSel(0, 0);


                  }

               }

               pevent->m_bRet = true;

               pevent->m_bProcessed = true;

            }

         }

      }

      if (pevent->m_bRet)
         return pevent->m_bProcessed;

      return form_mesh::BaseOnControlEvent(pevent);
   }


   bool form_list::_001HitTest_(point point,index &iItem,index &iSubItem)
   {

      return ::user::list::_001HitTest_(point,iItem,iSubItem);

   }



} // namespace user









