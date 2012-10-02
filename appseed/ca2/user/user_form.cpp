#include "framework.h"


namespace ca2
{


   namespace user
   {


      form::form(::ca::application * papp) :
         ca(papp),
         ::user::form(papp),
         ::user::interaction(papp)
      {
         m_bOnEditUpdate      = false;
         m_bOnLanguageChange  = false;
         m_pcallback          = NULL;
         m_bInitialized       = false;
      }

      form::~form()
      {

      }

      index form::_001AddControl(class control::descriptor & descriptorParam)
      {
         index indexNew = m_controldescriptorset.add(descriptorParam);
         descriptorParam.clear();
         class control::descriptor * pdescriptor = m_controldescriptorset.ptr_at(indexNew);
         pdescriptor->m_pform = this;
         if(pdescriptor->m_bTransparent)
         {
            switch(pdescriptor->m_etype)
            {
            case control::type_static:
               {
      /*xxx            CTransparentStatic * pstatic = (CTransparentStatic *) ::ca::window::FromHandlePermanent(pform->get_child_by_id(pcontrol->m_id)->GetSafeHwnd());
                  if(pstatic == NULL || !base < CTransparentStatic >::bases(pstatic))
                  {
                     pstatic = new CTransparentStatic;
                     VERIFY(pstatic->SubclassWindow(pform->get_child_by_id(pcontrol->m_id)->GetSafeHwnd()));
                  }
                  pcontrol->m_unionwndptr.m_pstatic = pstatic;*/
               }
               break;

            }
         }
         if(pdescriptor->m_typeinfo)
         {
            if(pdescriptor->m_bCreated && pdescriptor->m_pcontrol != NULL)
            {
               pdescriptor->m_bCreated = false;
               delete pdescriptor->m_pcontrol;
               pdescriptor->m_pcontrol = NULL;
            }
            if(dynamic_cast < ::user::interaction * > (pdescriptor->m_pcontrol) != NULL)
            {
               //window_id wndidTemp = pform->get_child_by_id(descriptor.m_id)->GetSafeHwnd();
               //if(wndidTemp != NULL)
               {
                  /*xxx ::user::window_interface * pwnd = dynamic_cast < ::user::window_interface * > (pcontrol->m_typeinfo->CreateObject());
                  if(pwnd != NULL)
                  {
                     if(pwnd->SubclassWindow(wndidTemp))
                     {
                        pcontrol->m_bSubclassed = true;
                        pcontrol->m_pwnd = pwnd;
                     }
                     else
                     {
                        // Failed creation
                        ASSERT(FALSE);
                        delete pwnd;
                     }
                  }*/
               }
            }
            else
            {
               if(create_control(pdescriptor))
               {
               }
               else
               {
                  // Failed creation
                  ASSERT(FALSE);
               }
            }
         }
         else if(create_control(pdescriptor))
         {
         }
         if(pdescriptor->m_pcontrol != NULL)
         {
            ::ca::type_info ti = typeid(pdescriptor->m_pcontrol);
            if(ti == System.template type_info < ::user::list > ())
            {
               if(pdescriptor->m_etype == control::type_simple_list)
               {
                  ::user::list * plist = dynamic_cast <::user::list *>(pdescriptor->m_pcontrol);
                  plist->m_dataid = pdescriptor->m_idPrivateDataSection;
                  plist->_001SetSingleColumnMode(false);
               }
            }
            /*else if(ti == System.template type_info < simple_static > ())
            {
               simple_static * pstatic = (simple_static *) pcontrol->m_pwnd;
               pstatic->m_bTransparent = pcontrol->m_bTransparent;
            }*/
            _001OnInitializeForm(pdescriptor->m_pcontrol);
         }
         return indexNew;
      }

      bool form::OnCommand(WPARAM wparam, LPARAM lparam)
      {
         UINT uiNotificationCode = HIWORD(wparam);
         UINT uiId = LOWORD(wparam);

         control * pcontrol = m_controldescriptorset.get_control_by_id(uiId);
         if(pcontrol == NULL)
            return false;
         switch(pcontrol->descriptor().get_type())
         {
         case control::type_button:
            OnCommandButton(pcontrol, uiNotificationCode, lparam);
            break;
         case control::type_check_box:
            OnCommandCheckBox(pcontrol, uiNotificationCode, lparam);
            break;
         case control::type_combo_box:
            OnCommandComboBox(pcontrol, uiNotificationCode, lparam);
            break;
         case control::type_edit:
            OnCommandEdit(pcontrol, uiNotificationCode, lparam);
            break;
         default:
            break;
         }

         return false;
      }

      bool form::OnCommandButton(control * pcontrol, UINT uiNotificationCode, LPARAM lparam)
      {
         UNREFERENCED_PARAMETER(lparam);
         ASSERT(pcontrol != NULL);
         if(pcontrol == NULL)
            return false;
         ASSERT(pcontrol->descriptor().get_type() == control::type_button);

         switch(uiNotificationCode)
         {
         case BN_CLICKED:
            {
               if(pcontrol->descriptor().has_function(control::function_action))
               {
                  _001OnButtonAction(pcontrol);
                  return true;
               }
            }
            break;
         default:
            break;
         }

         return false;
      }

      bool form::OnCommandCheckBox(control * pcontrol, UINT uiNotificationCode, LPARAM lparam)
      {
         UNREFERENCED_PARAMETER(lparam);
         ASSERT(pcontrol != NULL);
         if(pcontrol == NULL)
            return false;
         ASSERT(pcontrol->descriptor().get_type() == control::type_check_box);

         switch(uiNotificationCode)
         {
         case BN_CLICKED:
            {
      /*      linux   simple_button * pbutton = (simple_button *) get_child_by_id(pcontrol->m_id);
               int i = pbutton->get_check() != 0;
               VmsDataSet(pcontrol->descriptor().m_dataid, 0, 0, i);*/
            }
            break;
         default:
            break;
         }

         return false;
      }

      bool form::OnCommandComboBox(control * pcontrol, UINT uiNotificationCode, LPARAM lparam)
      {
         UNREFERENCED_PARAMETER(lparam);
         ASSERT(pcontrol != NULL);
         if(pcontrol == NULL)
            return false;
         ASSERT(pcontrol->descriptor().get_type() == control::type_combo_box);

         switch(uiNotificationCode)
         {
         case CBN_SELCHANGE:
            {
      /* linux         simple_combo_box * pcombo = (simple_combo_box *) get_child_by_id(pcontrol->m_id);
               int iSel = pcombo->get_cur_sel();
               if(iSel != CB_ERR)
               {
                  DWORD dwData = pcontrol->GetComboBox()->m_dwaData[iSel];
                  VmsDataSet(pcontrol->descriptor().m_dataid, 0, 0, (int) dwData);
               }*/
            }
            break;
         case EN_KILLFOCUS:
            {
               //_001SaveEdit(control);
            }
         default:
            break;
         }

         return false;
      }

      bool form::OnCommandEdit(control * pcontrol, UINT uiNotificationCode, LPARAM lparam)
      {
         UNREFERENCED_PARAMETER(lparam);
         ASSERT(pcontrol != NULL);
         if(pcontrol == NULL)
            return false;
         ASSERT(pcontrol->descriptor().get_type() == control::type_edit);

         switch(uiNotificationCode)
         {
         case EN_CHANGE:
            {
               if(pcontrol->descriptor().has_function(control::function_save_on_change))
               {
                  _001SaveEdit(pcontrol);
               }
            }
            break;
         case EN_KILLFOCUS:
            {
               _001SaveEdit(pcontrol);
            }
         default:
            break;
         }

         return false;
      }

      bool form::_001SaveEdit(control * pcontrol)
      {
         if(pcontrol == NULL)
            return false;
         ASSERT(pcontrol->descriptor().get_type() == control::type_edit
            || pcontrol->descriptor().get_type() == control::type_edit_plain_text);


         text_interface * pedit = dynamic_cast < text_interface * >( get_child_by_id(pcontrol->m_id));
         string str;
         if(pedit == NULL)
         {
            text_interface * ptext = dynamic_cast < text_interface * > (pcontrol);
            if(ptext == NULL)
               return false;
            ptext->_001GetText(str);
         }
         else
         {
            pedit->_001GetText(str);
         }

         if(!pcontrol->Validate(str))
         {
            // que tal um balão para indicar o erro
            return false;
         }

         var var;
         if(!pcontrol->get_data(dynamic_cast < ::ca::window * > (pedit), var))
         {
            return false;
         }

         if(!_001Validate(pcontrol, var))
         {
            return false;
         }

         if(pcontrol->descriptor().has_function(control::function_vms_data_edit))
         {
            ::database::selection selection;
            _001GetSelection(pcontrol->descriptor().m_dataid, selection);

            ::database::update_hint uh;
            uh.add_self(this);

            data_set(selection, var, &uh);
         }
         return true;
      }


      void form::_001OnUpdate(::view * pviewSender, LPARAM lhint, ::radix::object* phint)
      {
         UNREFERENCED_PARAMETER(pviewSender);
         UNREFERENCED_PARAMETER(lhint);
         UNREFERENCED_PARAMETER(phint);
         for(int i = 0; i < m_controldescriptorset.get_size(); i++)
         {
            control * pcontrol = m_controldescriptorset[i].m_pcontrol;
            if(pcontrol == NULL)
               continue;
            _001Update(pcontrol);
         }
      }

      void form::_001Update(control * pcontrol)
      {
         ASSERT(pcontrol != NULL);
         if(pcontrol == NULL)
            return;
         switch(pcontrol->descriptor().get_type())
         {
         case control::type_check_box:
            _001UpdateCheckBox(pcontrol);
            break;
         case control::type_combo_box:
            _001UpdateComboBox(pcontrol);
            break;
         case control::type_edit:
         case control::type_edit_plain_text:
            _001UpdateEdit(pcontrol);
            break;
         case control::type_simple_list:
            _001UpdateSimpleList(pcontrol);
            break;
         default:
            break;
         }
      }

      void form::_001UpdateDbFlags(control * pcontrol)
      {
         ASSERT(pcontrol != NULL);
         if(pcontrol == NULL)
            return;
         switch(pcontrol->descriptor().get_type())
         {
         case control::type_check_box:
            _001UpdateDbFlagsCheckBox(pcontrol);
            break;
      /*   case control::type_combo_box:
            _001UpdateComboBox(control);
            break;
         case control::type_edit:
         case control::type_edit_plain_text:
            _001UpdateEdit(control);
            break;
         case control::type_simple_list:
            _001UpdateSimpleList(control);
            break;*/
         default:
            break;
         }
      }

      void form::_001UpdateDbFlagsCheckBox(control * pcontrol)
      {
         ASSERT(pcontrol != NULL);
         if(pcontrol == NULL)
            return;
         ASSERT(pcontrol->descriptor().get_type() == control::type_check_box);
         ASSERT(pcontrol->descriptor().m_eddx == control::ddx_dbflags);
         base_sort_serializable_int_ptr_array ia;
         if(m_pdataserver->data_server_load(
            pcontrol->descriptor().m_ddx.m_pdbflags->m_key.m_idSection,
            pcontrol->descriptor().m_ddx.m_pdbflags->m_key.m_idKey,
            pcontrol->descriptor().m_ddx.m_pdbflags->m_key.m_idIndex,
            dynamic_cast < ::ex1::byte_serializable & > (ia)))
         {
            ::user::check_box * pcheck = dynamic_cast < ::user::check_box * > (pcontrol);
            if(pcheck != NULL)
            {
               index i = 0;
               if(ia.BaseSortFind(pcontrol->descriptor().m_ddx.m_pdbflags->m_value, i))
               {
                  pcheck->_001SetCheck(check::checked, false);
               }
               else
               {
                  pcheck->_001SetCheck(check::unchecked, false);
               }
            }
         }
      }


      void form::_001UpdateCheckBox(control * pcontrol)
      {
         ASSERT(pcontrol != NULL);
         if(pcontrol == NULL)
            return;
         ASSERT(pcontrol->descriptor().get_type() == control::type_check_box);
         int i;
         if(data_get(pcontrol->descriptor().m_dataid, ::radix::system::idEmpty, i))
         {
      /* linux      simple_button * pbutton = (simple_button *) get_child_by_id(pcontrol->m_id);
            pbutton->SetCheck((i != 0) ? 1 : 0); */
         }
      }

      void form::_001UpdateComboBox(control * pcontrol)
      {
         ASSERT(pcontrol != NULL);
         if(pcontrol == NULL)
            return;
      /* linux   ASSERT(pcontrol->descriptor().get_type() == control::type_combo_box);
         int i;
         if(VmsDataGet(pcontrol->descriptor().m_dataid, 0, 0, i))
         {
            int_ptr iSel = pcontrol->GetComboBox()->m_dwaData.find_first((DWORD) i);
            if(iSel >= 0)
            {
               simple_combo_box * pcombo = (simple_combo_box *) get_child_by_id(pcontrol->m_id);
               pcombo->set_cur_sel(iSel);
            }
         }*/
      }

      void form::_001UpdateEdit(control * pcontrol)
      {
         ASSERT(pcontrol != NULL);
         if(pcontrol == NULL)
            return;

         if(m_bOnEditUpdate)
            return;
         keeper<bool> keepUpdateLock(&m_bOnEditUpdate, true, false, true);

         ASSERT(pcontrol->descriptor().get_type() == control::type_edit
            || pcontrol->descriptor().get_type() == control::type_edit_plain_text);

         if(pcontrol->descriptor().has_function(control::function_vms_data_edit))
         {
            var var;
            ::database::selection selection;
            _001GetSelection(pcontrol->descriptor().m_dataid, selection);
            if(selection.get_item_count() > 0)
            {
               ::database::selection_item & item = selection.get_item(0);
               text_interface * ptext = NULL;
               if(get_child_by_id(pcontrol->m_id) != NULL)
               {
                  ptext = dynamic_cast < text_interface * > (get_child_by_id(pcontrol->m_id));
               }
               if(ptext == NULL && pcontrol != NULL)
               {
                  ptext = dynamic_cast < text_interface * > (pcontrol);
               }
               if(ptext == NULL)
                  return;
               if(data_get(pcontrol->descriptor().m_dataid, item.m_idIndex, var))
               {
                  switch(var.get_type())
                  {
                  case var::type_string:
                     {
                        string str;
                        str = var.m_str;
                        ptext->_001SetText(str);
                     }
                     break;
                  case var::type_integer:
                     {
                        string str;
                        str.Format("%d", var.m_i);
                        ptext->_001SetText(str);
                     }
                     break;
                  default:
                     ASSERT(FALSE);
                     break;
                  }
               }
            }
         }
      }

      void form::_001UpdateSimpleList(control * pcontrol)
      {
         ASSERT(pcontrol != NULL);
         if(pcontrol == NULL)
            return;

         ASSERT(pcontrol->descriptor().get_type() == control::type_simple_list);

         ::user::list * plist = dynamic_cast<::user::list *>(get_child_by_id(pcontrol->m_id));

         if(typeid(plist->GetDataInterface()) == System.template type_info < ::user::simple_list_data > ())
         {
            ::user::simple_list_data * pdata = dynamic_cast < ::user::simple_list_data * > (plist->GetDataInterface());
            stringa stra;
            data_get(pcontrol->descriptor().m_dataid, ::radix::system::idEmpty, stra);
            ASSERT(plist != NULL);
            pdata->set_data(plist, stra);
         }
      }

      void form::_000OnPosCreate(gen::signal_object * pobj)
      {
         UNREFERENCED_PARAMETER(pobj);
   //      SCAST_PTR(::gen::message::base, pbase, pobj)
      }

      void form::_001InitializeFormPreData()
      {
         if(m_pcallback != NULL)
         {
            m_pcallback->_001InitializeFormPreData(this);
         }

      /*
         if(GetOwner() != NULL)
         {
            GetOwner()->SendMessage(
               WM_USER + 723,
               GetDlgCtrlId(),
               (LPARAM) this);
         }
      */

      }


      bool form::_001GetData(id uiId, bool &bData)
      {
         control * pcontrol = m_controldescriptorset.get_control_by_id(uiId);
         if(pcontrol == NULL)
            return false;

         int i;
         if(!data_get(pcontrol->descriptor().m_dataid, ::radix::system::idEmpty, i))
            return false;

         bData = (i != 0) ? 1 : 0;

         return true;

      }

      bool form::_001SetData(id uiId, bool bData)
      {
         control * pcontrol = m_controldescriptorset.get_control_by_id(uiId);
         if(pcontrol == NULL)
            return false;

         int i = bData ? 1 : 0;
         data_set(pcontrol->descriptor().m_dataid, ::radix::system::idEmpty, i);
         return true;

      }

      void form::Update(bool bSave)
      {
         if(bSave)
         {

         }
         else
         {
            for(int i = 0; i < m_controldescriptorset.get_size(); i++)
            {
               control * pcontrol = m_controldescriptorset[i].m_pcontrol;
               if(pcontrol == NULL)
                  continue;
               _001Update(pcontrol);
            }
         }
      }

      void form::install_message_handling( ::gen::message::dispatch *pinterface)
      {
      /*   InstallOnDrawInterface(pinterface);
         VMSGEN_WINDOW_ON_SIZE_CONDITIONAL(pinterface, this, _001OnSize);
         VMSGEN_WINDOW_ON_VSCROLL_CONDITIONAL(pinterface, this, _001OnVScroll);
         VMSGEN_WINDOW_ON_HSCROLL_CONDITIONAL(pinterface, this, _001OnHScroll);
      //   VMSGEN_WINDOW_ON_PAINT_CONDITIONAL(pinterface, this, _001OnPaint);
         VMSGEN_WINDOW_ON_LBUTTONDOWN_CONDITIONAL(pinterface, this, _001OnLButtonDown);
         VMSGEN_WINDOW_ON_LBUTTONUP_CONDITIONAL(pinterface, this, _001OnLButtonUp);
         VMSGEN_WINDOW_ON_LBUTTONDBLCLK_CONDITIONAL(pinterface, this, _001OnLButtonDblClk);
         VMSGEN_WINDOW_ON_TIMER_CONDITIONAL(pinterface, this, _001OnTimer);*/
         IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &form::_001OnCreate);
         IGUI_MSG_LINK(::gen::message_pos_create, pinterface, this, &form::_000OnPosCreate);
   //      IGUI_WIN_MSG_LINK(WM_COMMAND, pinterface, this, &form::_001OnCommand);
     //    IGUI_WIN_MSG_LINK(WM_NOTIFY, pinterface, this, &form::_001OnNotify);
         // revamp IGUI_WIN_MSG_LINK(user::MessageNotify, pinterface, this, &form::_001OnMessageNotify);
         IGUI_WIN_MSG_LINK(gen::application::APPM_LANGUAGE, pinterface, this, &form::_001OnAppLanguage);

      //   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &::user::interaction::_001OnLButtonDown);
      //   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &::user::interaction::_001OnLButtonUp);
         IGUI_WIN_MSG_LINK(WM_KEYDOWN, pinterface, this, &::user::interaction::_001OnKeyDown);
         IGUI_WIN_MSG_LINK(WM_KEYUP, pinterface, this, &::user::interaction::_001OnKeyUp);
      }

      void form::_001GetSelection(
         ::database::id & id, ::database::selection &selection)
      {
         selection.add_item(id, ::radix::system::idEmpty);
      }

      bool form::_001OnCommand(id id)
      {
         return control::_001OnCommand(id);
      }


      void form::_001OnNotify(gen::signal_object * pobj)
      {
         SCAST_PTR(::gen::message::notify, pnotify, pobj)
         pnotify->m_bRet = false;
      }

      void form::_001OnMessageNotify(gen::signal_object * pobj)
      {
         SCAST_PTR(::gen::message::base, pbase, pobj)
         // revamp pbase->set_lresult(user::NotifyRetContinue);
         pbase->m_bRet = false;
      }

      bool form::_001Validate(
         control * pcontrol,
         var & var)
      {
         UNREFERENCED_PARAMETER(pcontrol);
         UNREFERENCED_PARAMETER(var);
         return true;
      }

      void form::_001RemoveControls()
      {
         m_controldescriptorset.remove_all();
      }

      bool form::_001OnBeforeSave(control * pcontrol)
      {
         UNREFERENCED_PARAMETER(pcontrol);
         return true;
      }

      void form::data_on_after_change(gen::signal_object * pobj)
      {
         SCAST_PTR(::database::change_event, pchange, pobj);
         if(pchange->m_puh != NULL)
         {
            if(pchange->m_puh->has_self(this))
            {
               return;
            }
         }
         for(int iControl = 0; iControl < m_controldescriptorset.get_size(); iControl++)
         {
            control * pcontrol = m_controldescriptorset[iControl].m_pcontrol;
            if(pcontrol == NULL)
               continue;
            if(m_controldescriptorset[iControl].m_eddx == control::ddx_dbflags)
            {
               _001UpdateDbFlags(pcontrol);
            }
            else if(m_controldescriptorset[iControl].m_dataid == pchange->m_key.m_idKey)
            {
               _001Update(pcontrol);
            }
         }
      }

      void form::_001UpdateFunctionStatic()
      {
         for(int i = 0; i < m_controldescriptorset.get_size(); i++)
         {
            class control::descriptor & descriptor = m_controldescriptorset[i];
            if(descriptor.has_function(control::function_static))
            {
               throw not_implemented_exception(get_app());
               /*
               string str;
               str.load_string(descriptor.m_id);*/
               //ASSERT(pcontrol != NULL);
            //xxx   pcontrol->m_pwnd->SetWindowText(str);
            }
            /*else if(descriptor.has_function(control::function_static2))
            {
               string str;
               str.load_string(descriptor.m_uiText);
               ASSERT(pcontrol != NULL);
            //xxx pcontrol->m_pwnd->SetWindowText(str);
            }*/
         }
      }

      void form::WfiOnClose()
      {
         PostMessage(WM_CLOSE);
      }

      void form::_001OnInitializeForm(control * pcontrol)
      {
         ::user::control_event ev;
         ev.m_puie      = pcontrol;
         ev.m_bUser     = false;
         ev.m_eevent     = ::user::event_initialize_control;
         ev.m_uiEvent   = 0;
         BaseOnControlEvent(&ev);
      }

      void form::_001OnButtonAction(control * pcontrol)
      {
         UNREFERENCED_PARAMETER(pcontrol);
      }


      void form::_001OnAppLanguage(gen::signal_object * pobj)
      {
         SCAST_PTR(::gen::message::base, pbase, pobj)
         keeper < bool > keepOnLanguageChange(&m_bOnLanguageChange, true, false, true);

         _017OnAppLanguage();

         pbase->m_bRet = false;
      }

      void form::_001OnCreate(gen::signal_object * pobj)
      {
   //      SCAST_PTR(::gen::message::create, pcreate, pobj)
         if(pobj->previous())
            return;

         //PostMessage(::gen::message::message_pos_create);

      }

      void form::_001FillCombo(control * pcontrol)
      {
         ASSERT(pcontrol != NULL);
         if(pcontrol == NULL)
            return;
      /* linux  if(pcontrol->GetComboBox() != NULL)
         {
            if(!pcontrol->GetComboBox()->m_datakeyFill.IsNull())
            {
               pcontrol->GetComboBox()->m_wstra.remove_all();
               pcontrol->GetComboBox()->m_dwaData.remove_all();
               var var;
               var.m_etype = var::type_ca2;
               var.m_pca2 = pcontrol->GetComboBox();
               VmsDataGet(
                  pcontrol->GetComboBox()->m_datakeyFill,
                  0, 0,
                  var);
               simple_combo_box * pcombo = (simple_combo_box *) pcontrol->m_pwnd;
               pcombo->ResetContent();
               string str;
               for(int i = 0; i < pcontrol->GetComboBox()->m_wstra.get_size(); i++)
               {
                  str = pcontrol->GetComboBox()->m_wstra[i];
                  pcombo->AddString(str);
               }

            }
         } */
      }

      void form::_017OnAppLanguage()
      {
         for(int i = 0; i < m_controldescriptorset.get_size() ; i++)
         {
            class control::descriptor & descriptor = m_controldescriptorset[i];
            if(descriptor.m_typeinfo)
            {
               if(descriptor.m_bCreated && descriptor.m_pcontrol != NULL)
               {
               }
               else if(descriptor.m_bSubclassed && descriptor.m_pcontrol != NULL)
               {
      //            if(::IsWindow(pcontrol->m_pwnd->GetSafeHwnd()))
                  {
                     //xxx pcontrol->m_pwnd->UnsubclassWindow();
                  }
      //            ASSERT(pcontrol->m_typeinfo->IsDerivedFrom(System.template type_info < ::ca::window > ()));
                  if(dynamic_cast < ::ca::window * >(descriptor.m_pcontrol) != NULL)
                  {
                     //window_id wndidTemp = get_child_by_id(pcontrol->m_id)->GetSafeHwnd();
                     //if(wndidTemp != NULL)
                     {
                //xxx        VERIFY(pcontrol->m_pwnd->SubclassWindow(wndidTemp));
                     }
                  }
               }
               if(descriptor.m_pcontrol != NULL)
               {
                  ::ca::type_info ti = typeid(descriptor.m_pcontrol);
                  if(ti == System.template type_info < ::user::list > ())
                  {
                     if(descriptor.m_etype == control::type_simple_list)
                     {
                        ::user::list * plist = dynamic_cast <::user::list *>(descriptor.m_pcontrol);
                        plist->m_dataid = descriptor.m_idPrivateDataSection;
                        plist->_001SetSingleColumnMode(false);
                     }
                  }
      /*            else if(pcontrol->m_typeinfo->IsDerivedFrom(System.template type_info < simple_static > ()))
                  {
                     simple_static * pstatic = (simple_static *) pcontrol->m_pwnd;
                     pstatic->m_bTransparent = pcontrol->m_bTransparent;
                  }*/
                  _001OnInitializeForm(descriptor.m_pcontrol);
               }
            }
         }

      }

      bool form::create_control(class control::descriptor * pdescriptor)
      {
         if(!normalize_control_descriptor_typeinfo(pdescriptor))
         {
            TRACE("form::create_control: failed to create control, could not find proper type_info for allocation");
            return false;
         }
         ::ca::ca * pca = Application.alloc(pdescriptor->m_typeinfo);
         if(pca == NULL)
         {
            TRACE("form::create_control: failed to create control, allocation error");
            return false;
         }
         class control * pcontrol = dynamic_cast < control * > (pca);
         if(pcontrol == NULL)
         {
            delete pca;
            TRACE("form::create_control: failed to create control, object is not derived from user::control::descriptor");
            return false;
         }
         if(!pcontrol->create_control(pdescriptor))
         {
            delete pcontrol;
            return false;
         }
         return true;
      }
      void form::_001SetControlFactory()
      {
      }

      string form::get_path()
      {
         return "";
      }

      bool form::open_document(var varFile)
      {
         UNREFERENCED_PARAMETER(varFile);
         return true;
      }

      bool form::BaseOnControlEvent(::user::control_event * pevent)
      {
         if(pevent->m_eevent == ::user::event_tab_key)
         {
            ::user::keyboard_focus * pfocus = pevent->m_puie->keyboard_get_next_focusable();
            if(pfocus != NULL)
            {
               Application.set_keyboard_focus(pfocus);
            }
         }
         else if(pevent->m_eevent == ::user::event_button_clicked)
         {
            class control::descriptor * pdescriptor = m_controldescriptorset.get(pevent->m_puie);
            if(pdescriptor == NULL)
               return false;
            if(pdescriptor->has_function(control::function_action))
            {
               if(pdescriptor->m_pcontrol != NULL)
               {
                  _001OnButtonAction(pdescriptor->m_pcontrol);
                  return true;
               }
               else
               {
                  return false;
               }
            }
         }
         else if(pevent->m_eevent == ::user::event_set_check
            && pevent->m_bUser)
         {
            class control::descriptor * pdescriptor = m_controldescriptorset.get(pevent->m_puie);
            if(pdescriptor == NULL)
               return false;
            if(pdescriptor->m_eddx == control::ddx_dbflags)
            {
               base_sort_serializable_int_ptr_array ia;
               m_pdataserver->data_server_load(
                  pdescriptor->m_ddx.m_pdbflags->m_key.m_idSection,
                  pdescriptor->m_ddx.m_pdbflags->m_key.m_idKey,
                  pdescriptor->m_ddx.m_pdbflags->m_key.m_idIndex,
                  dynamic_cast < ::ex1::byte_serializable & > (ia));
               check_interface * pcheck = dynamic_cast < check_interface * > (pevent->m_puie);
               if(pcheck->_001GetCheck() == check::checked)
               {
                  index i = 0;
                  if(!ia.BaseSortFind(pdescriptor->m_ddx.m_pdbflags->m_value, i))
                  {
                     ia.add(pdescriptor->m_ddx.m_pdbflags->m_value);
                  }
               }
               else
               {
                  index i = 0;
                  while(ia.BaseSortFind(pdescriptor->m_ddx.m_pdbflags->m_value, i))
                  {
                     ia.remove_at(i);
                  }
               }
               m_pdataserver->data_server_save(
                  pdescriptor->m_ddx.m_pdbflags->m_key.m_idSection,
                  pdescriptor->m_ddx.m_pdbflags->m_key.m_idKey,
                  pdescriptor->m_ddx.m_pdbflags->m_key.m_idIndex,
                  dynamic_cast < ::ex1::byte_serializable & > (ia));
            }
         }
         return false;
      }

      bool form::_001Initialize()
      {
         if(m_bInitialized)
            return true;
         _001InitializeFormPreData();
      /*   ::view * pview = dynamic_cast <::view *>(get_guie());
         if(pview != NULL)
         {
            if(pview->get_document() != NULL)
            {
               pview->get_document()->update_all_views(NULL);
            }
         }*/
         _001UpdateFunctionStatic();
      //   CVmsGuiApp * papp = (CVmsGuiApp *) &System;
      //   papp->TwfInitializeDescendants(pview->GetSafeHwnd(), true);
         for(int i = 0; i < m_controldescriptorset.get_size(); i++)
         {
            control * pcontrol = m_controldescriptorset[i].m_pcontrol;
            if(pcontrol == NULL)
               continue;
            _001Update(pcontrol);
         }
         m_bInitialized = true;
         return true;
      }

      bool form::_001IsPointInside(control * pcontrol, point64 point)
      {
         if(pcontrol == NULL)
            return false;
         return pcontrol->_001IsPointInside(point);
      }

      bool form::normalize_control_descriptor_typeinfo(class ::user::control::descriptor * pdescriptor)
      {
         if(pdescriptor->m_typeinfo)
         {
            return true;
         }
         pdescriptor->m_typeinfo = System.controltype_to_typeinfo(pdescriptor->get_type());
         if(pdescriptor->m_typeinfo)
         {
            return true;
         }
         return false;
      }

      void form::OnBeforeNavigate2(var & varFile, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, bool* pbCancel)
      {
         UNREFERENCED_PARAMETER(varFile);
         UNREFERENCED_PARAMETER(nFlags);
         UNREFERENCED_PARAMETER(lpszTargetFrameName);
         UNREFERENCED_PARAMETER(baPostedData);
         UNREFERENCED_PARAMETER(lpszHeaders);
         UNREFERENCED_PARAMETER(pbCancel);
      }

      void form::control_get_window_rect(control * pcontrol, LPRECT lprect)
      {
         pcontrol->::user::interaction::GetWindowRect(lprect);
      }

      void form::control_get_client_rect(control * pcontrol, LPRECT lprect)
      {
         pcontrol->::user::interaction::GetClientRect(lprect);
      }


   } // namespace user


} // namespace ca2



