#include "framework.h"

namespace user
{

#ifdef WINDOWSEX
   const uint32_t control::g_uiMessage = ::RegisterWindowMessage("user::control::g_uiMessage");
#endif

   control::descriptor::descriptor()
   {
      clear();
   }

   control::descriptor::~descriptor()
   {
      if(m_pcontrol != NULL)
      {
         if(m_bCreated)
         {
            m_pcontrol->DestroyWindow();
         }
         else if(m_bSubclassed)
         {
            m_pcontrol->unsubclass_window();
         }
         m_pcontrol.release();
      }
   }



   void control::descriptor::clear()
   {
      m_id.is_empty();
      m_etype                    = type_none;
      m_bTransparent             = false;
      m_bCreated                 = false;
      m_edatatype                = DataTypeString;
      m_flagsfunction.unsignalize_all();
      m_pcontrol.release();
      m_pform                    = NULL;
      m_bSubclassed              = false;
      m_iSubItem                 = -1;
   }

   control::descriptor::descriptor(const class descriptor & descriptor)
   {
      operator =(descriptor);
   }

   class control::descriptor & control::descriptor::operator = (const descriptor & descriptor)
   {
      if(&descriptor == this)
         return *this;
      m_id                    = descriptor.m_id;
      m_etype                 = descriptor.m_etype;
      m_dataid                = descriptor.m_dataid;
      m_bTransparent          = descriptor.m_bTransparent;
      m_flagsfunction         = descriptor.m_flagsfunction;
      m_typeinfo              = descriptor.m_typeinfo;
      m_bCreated              = descriptor.m_bCreated;
      m_edatatype             = descriptor.m_edatatype;
      m_idPrivateDataSection  = descriptor.m_idPrivateDataSection;
      m_pcontrol              = descriptor.m_pcontrol;
      m_eddx                  = descriptor.m_eddx;
      m_ddx.m_pvoid           = descriptor.m_ddx.m_pvoid;
      m_pform                 = descriptor.m_pform;
      m_iSubItem              = descriptor.m_iSubItem;
      return *this;
   }

   bool control::descriptor::operator == (const descriptor & descriptor) const
   {
      return m_id       == descriptor.m_id
         && m_etype     == descriptor.m_etype
         && m_dataid    == descriptor.m_dataid
         && m_pform     == descriptor.m_pform
         && m_pcontrol  == descriptor.m_pcontrol;
   }


   void control::descriptor::add_function(efunction efunction)
   {
      m_flagsfunction.signalize(efunction);
   }

   void control::descriptor::remove_function(efunction efunction)
   {
      m_flagsfunction.unsignalize(efunction);
   }

      bool control::descriptor::has_function(efunction efunction)
      {
         return m_flagsfunction.is_signalized(efunction);
      }


   void control::descriptor::set_data_type(edatatype edatatype)
   {

      m_edatatype = edatatype;

   }

   control::edatatype control::descriptor::get_data_type()
   {

      return m_edatatype;

   }


   void control::descriptor::set_ddx_dbflags(::database::id idSection, ::database::id idKey, ::database::id idIndex, int_ptr value)
   {

      m_eddx = ::user::control::ddx_dbflags;

      class ::database::key key(NULL, idSection, idKey, idIndex);

      m_ddx.m_pdbflags = new class ::user::control::ddx_dbflags(key, value);


   }

   control::descriptor_set::descriptor_set()
   {

   }

   control::descriptor_set::~descriptor_set()
   {

   }



   sp(control) control::descriptor_set::get_control_by_id(id id)
   {
      for(int32_t i = 0; i < this->get_size(); i++)
      {
         class descriptor & descriptor = *this->element_at(i);
         if(descriptor.m_id == id)
         {
            return descriptor.m_pcontrol;
         }
      }
      return NULL;
   }

   class control::descriptor * control::descriptor_set::get(sp(::user::interaction) puie)
   {
      sp(control) pcontrol =  (puie.m_p);
      if(pcontrol == NULL)
         return NULL;
      for(int32_t i = 0; i < this->get_size(); i++)
      {
         class descriptor & descriptor = *this->element_at(i);
         if(descriptor.m_pcontrol == pcontrol)
         {
            return &descriptor;
         }
      }
      return NULL;
   }

   class control::descriptor * control::descriptor_set::get_by_sub_item(int32_t iSubItem)
   {
      for(int32_t i = 0; i < this->get_size(); i++)
      {
         class descriptor & descriptor = *this->element_at(i);
         if(descriptor.m_iSubItem == iSubItem)
         {
            return &descriptor;
         }
      }
      return NULL;
   }


   control::~control()
   {

   }

   void control::install_message_handling(::message::dispatch * pdispatch)
   {

      ::user::impact::install_message_handling(pdispatch);
      ::database::user::interaction::install_message_handling(pdispatch);
      IGUI_MSG_LINK(WM_MOUSEMOVE, pdispatch, this, &::user::control::_001OnMouseMove);

#ifdef WINDOWS

      IGUI_MSG_LINK(WM_MOUSELEAVE, pdispatch, this, &::user::control::_001OnMouseLeave);

#else

      //throw not_implemented(get_app());

#endif


   }


   void control::_003OnCustomDraw(::draw2d::graphics *pdc, ::user::draw_context * pdrawcontext)
   {
      pdc->chain(pdrawcontext);
      _001OnDraw(pdc);
      pdc->unchain(pdrawcontext);
   }

   bool control::_003IsCustomMessage()
   {
      return m_bCustomWindowProc;
   }


   void control::_003CallCustomDraw(::draw2d::graphics *pdc, ::user::draw_context * pdrawcontext)
   {
      _003OnCustomDraw(pdc, pdrawcontext);
   }

   bool control::_003CallCustomWindowProc(sp(::user::interaction) pwnd, UINT message, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
   {
      m_pwndCustomWindowProc = pwnd;
      keep <bool> keepOnCustomMessage(&m_bCustomWindowProc, true, false, true);
      ::message::base base(get_app(), pwnd, message, wparam, lparam, lresult);
      _003CustomWindowProc(&base);
      return base.m_bRet;
   }

   void control::_003CustomWindowProc(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   bool control::operator == (const class descriptor & descriptor) const
   {
      return *m_pdescriptor == descriptor;
   }


   bool control::operator == (const class control & control) const
   {
      return operator == (*control.m_pdescriptor);
   }

   void control::descriptor::set_type(e_type e_type)
   {
      m_etype = e_type;

      switch(m_etype)
      {
      case type_edit:
      //         m_typeinfo = System.type_info < CSimpleFormListEdit > ();
         break;
      case type_combo_box:
         {
                            throw todo(get_app());
//            m_data.m_pcombobox = new Ex1FormInterfaceComboBox;
         }
         break;
         default:
            break;
      }
   }


   control::e_type control::descriptor::get_type()
   {
      return m_etype;
   }


   index control::GetEditItem()
   {
      return m_iEditItem;
   }

   index control::GetEditSubItem()
   {
      return descriptor().m_iSubItem;
   }

   void control::SetEditItem(index iItem)
   {
      m_iEditItem = iItem;
   }

   void control::SetEditSubItem(index iSubItem)
   {
      descriptor().m_iSubItem = iSubItem;
   }


   bool control::get_data(sp(::user::interaction)pwnd, var &var)
   {
      string str;

      if(descriptor().get_type() == type_edit)
      {
         sp(text_interface) ptext = pwnd.m_p;
         if(ptext == NULL)
            return false;
         ptext->_001GetText(str);
      }
      else
      {
         sp(text_interface) ptext = this;
         if(ptext == NULL)
            return false;
         ptext->_001GetText(str);
      }

      switch(descriptor().get_data_type())
      {
      case DataTypeString:
         {
            var = str;
         }
         return true;
      case DataTypeNatural:
         {
            var = atoi(str);
            return true;
         }
         break;
      default:
         return false;
      }

   }

   bool control::Validate(string & strParam)
   {

      switch(descriptor().get_data_type())
      {
      case DataTypeString:
         return true;
      case DataTypeNatural:
         {
            string str = strParam;
            str.trim_left();
            str.trim_right();
            for(int32_t i = 0; i < str.get_length(); i++)
            {
               if(str[i] >= L'0'
                  && str[i] <= L'9')
               {
               }
               else
               {
                  return false;
               }

            }
            return true;
         }
         break;
      default:
         return true;
      }
   }


   Ex1FormInterfaceComboBox * control::GetComboBox()
   {
      return descriptor().m_data.m_pcombobox;
   }

   control::ddx_dbflags::ddx_dbflags(::database::key key, int_ptr value)
   {
      m_key       = key;
      m_value     = value;
   }


   bool control::_001IsPointInside(point64 point)
   {
      if(get_form() != NULL)
      {
         return get_form()->_001IsPointInside(this, point);
      }
      else
      {
         return ::user::interaction::_001IsPointInside(point);
      }
   }

   form_interface * control::get_form()
   {
      if(m_pdescriptor == NULL)
         return NULL;
      else
         return descriptor().m_pform;
   }

   /*form_list * control::get_form_list()
   {
      if(get_form() != NULL)
         return dynamic_cast < form_list * > (get_form());
      else
         return NULL;
   }*/

   class control::descriptor & control::descriptor()
   {
      return *m_pdescriptor;
   }

   bool control::create_control(class control::descriptor * pdescriptor)
   {
      m_pdescriptor = pdescriptor;
      m_pdescriptor->m_bCreated = true;
      m_pdescriptor->m_pcontrol = this;
      return true;
   }

   void control::GetWindowRect(LPRECT lprect)
   {
      if(get_form() != NULL)
      {
         get_form()->control_get_window_rect(this, lprect);
      }
      else
      {
         ::user::interaction::GetWindowRect(lprect);
      }
   }

   void control::GetClientRect(LPRECT lprect)
   {
      if(get_form() != NULL)
      {
         get_form()->control_get_client_rect(this, lprect);
      }
      else
      {
         ::user::interaction::GetClientRect(lprect);
      }
   }

   index control::get_hover()
   {
      POINT pt;
      // netshare
      // System.get_cursor_position(&pt);
      session().get_cursor_pos(&pt);
      ScreenToClient(&pt);
      rect rect;
      GetWindowRect(rect);
      if(rect.contains(pt))
         return 0;
      else
         return -1;
   }


   control::control()
   {
      m_pdescriptor                 = NULL;
      m_iHover                      = -1;
      m_bControlExCommandEnabled    = true;
      m_pform                       = NULL;
      m_pformcallback               = NULL;
      m_ulFlags                     &= ~element::flag_auto_delete;
   }


   bool control::IsControlCommandEnabled()
   {
      return m_bControlExCommandEnabled;
   }

   void control::EnableControlCommand(bool bEnable)
   {
      m_bControlExCommandEnabled = bEnable;
      ControlExGetWnd()->RedrawWindow();
   }

   sp(::user::interaction) control::ControlExGetWnd()
   {
      return  (this);
   }


   void control_cmd_ui::Enable(bool bOn)
   {
       m_pcmdui->m_bEnableChanged = TRUE;
       sp(::user::interaction) pwnd = (sp(::user::interaction))m_pcmdui->m_pOther;
       ASSERT(pwnd != NULL);
       ASSERT_KINDOF(::user::interaction, pwnd);
       //ASSERT(m_nIndex < m_nIndexMax);

      sp(::user::interaction) pcontrol = pwnd->get_child_by_id(m_pcmdui->m_idControl);
      sp(control) pcontrolex =  (pcontrol.m_p);
      if(pcontrolex != NULL)
      {
         if(bOn)
         {
            if(pwnd->is_window_enabled() &&
               !pcontrolex->IsControlCommandEnabled())
            {
               pcontrolex->EnableControlCommand(true);
            }
         }
         else
         {
            if(pcontrolex->IsControlCommandEnabled())
            {
               pcontrolex->EnableControlCommand(false);
            }
         }
      }
      else
      {
         if(pcontrol != NULL)
         {
            if(bOn)
            {
               if(!pcontrol->is_window_enabled())
               {
                  pcontrol->enable_window();
               }
            }
            else
            {
               if(pcontrol->is_window_enabled())
               {
                  pcontrol->enable_window(FALSE);
               }
            }
          }
      }
   }

   void control_cmd_ui::SetCheck(int32_t nCheck)
   {
       ASSERT(nCheck >= 0 && nCheck <= 2); // 0=>off, 1=>on, 2=>indeterminate
       /*sp(::user::interaction) pwnd = (sp(::user::interaction))m_pOther;
       ASSERT(pToolBar != NULL);
       ASSERT_KINDOF(simple_toolbar, pToolBar);
       ASSERT(m_nIndex < m_nIndexMax);

       UINT nNewStyle = pToolBar->GetButtonStyle(m_nIndex) &
                   ~(TBBS_CHECKED | TBBS_INDETERMINATE);
       if (nCheck == 1)
           nNewStyle |= TBBS_CHECKED;
       else if (nCheck == 2)
           nNewStyle |= TBBS_INDETERMINATE;
       ASSERT(!(nNewStyle & TBBS_SEPARATOR));
       pToolBar->SetButtonStyle(m_nIndex, nNewStyle | TBBS_CHECKBOX);*/
   }

   void control_cmd_ui::SetText(const char *)
   {
       // ignore it
   }


   id control_cmd_ui::GetControlCommand(id id)
   {
      class id idCommand;
      if(m_mapControlCommand.Lookup(id, idCommand))
      {
         return id;
      }
      return id;
   }


   LRESULT control_view_impl::BaseControlExOnIdleUpdateCmdUI(WPARAM wParam, LPARAM)
   {
      sp(::user::interaction) pview = get_window();

       // handle delay hide/show
       bool bVis = (pview->GetStyle() & WS_VISIBLE) != 0;

       // the style must be visible
       if (bVis)
       {
           sp(::user::frame_window) pTarget = pview->GetOwner();
           if (pTarget == NULL)
               pTarget = pview->GetParentFrame();
           if (pTarget != NULL)
               BaseControlExOnUpdateCmdUI(pTarget, wParam != FALSE);
       }
       return 0L;
   }


   void control_view_impl::BaseControlExOnUpdateCmdUI(sp(::user::frame_window) pTarget, bool bDisableIfNoHndler)
   {
      sp(::user::interaction) pview = get_window();

      cmd_ui & state = *m_cmdui.m_pcmdui;
      state.m_pOther = pview;

      sp(::user::interaction) pwndIterator = pview->GetTopWindow();
      sp(::user::interaction) pwnd;
      sp(control) pcontrolex;
       for (; pwndIterator != NULL; pwndIterator = pwndIterator->GetNextWindow())
       {
         pwnd = pwndIterator->GetTopLevel();
         pcontrolex = NULL;
         if(pwnd != NULL)
         {
#ifdef WINDOWSEX
            pwnd->send_message(control::g_uiMessage, control::MessageParamGetBaseControlExPtr, (LPARAM) &pcontrolex);
#else
            throw todo(pwnd->get_app());
#endif
         }
         if(pcontrolex != NULL)
         {
            id idControl = pwnd->GetDlgCtrlId();

   // xxx         state.m_nIndex = uiID;
            state.m_iCount = -1;
            state.m_id = m_cmdui.GetControlCommand(idControl);
            state.m_bContinueRouting = FALSE;

              // ignore separators
              if ((pwnd->GetStyle() & WS_VISIBLE))
              {
                  // allow reflections
                  if (pview->on_simple_update(&state))
                  {
                      continue;
                  }

                  // allow the toolbar itself to have update handlers
                  if (pview->on_simple_update(&state))
   //               {
     //                state.DoUpdate(pTarget, bDisableIfNoHndler);
                      continue;
       //           }

                  // allow the owner to process the update
                  state.DoUpdate(pTarget, bDisableIfNoHndler);
              }
         }
       }

       // update the dialog controls added to the toolbar
   //  UpdateDialogControls(pTarget, bDisableIfNoHndler);
   }

   sp(::user::interaction) control_view_impl::get_window()
   {
      return  (this);
   }


   bool control_view_impl::BaseControlExOnCommand(WPARAM wParam, LPARAM lParam)
   {

      UNREFERENCED_PARAMETER(lParam);

      if(get_window() != NULL)
      {

#ifdef WINDOWS

         UINT uiMessage = ((wParam >> 16) & 0xffff);


         if(uiMessage == BN_CLICKED)
         {
            //xxx id idCommand = m_cmdui.GetControlCommand(wParam & 0xffff);
            //xxx get_window()->GetParentFrame()->_001SendCommand(idCommand);
         }

#endif

      }

      return FALSE;

   }



   void control::BaseControlExOnMouseMove(UINT nFlags, point point)
   {
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(point);
      sp(::user::interaction) pwnd = ControlExGetWnd();

      class point ptCursor;
      session().get_cursor_pos(&ptCursor);

      e_element eelement;

      index iHover = hit_test(ptCursor, eelement);
      if(iHover != -1)
      {
         if(m_iHover == -1 || System.get_capture_uie() != pwnd)
         {
            m_iHover = iHover;
            pwnd->RedrawWindow(0, 0, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_FRAME);
            pwnd->SetCapture();
         }
      }
      else
      {
         if(m_iHover != -1)
         {
            m_iHover = -1;
            pwnd->RedrawWindow(0, 0, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_FRAME);
            System.release_capture_uie();
         }
      }
   }


   void control::_001OnMouseMove(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj);

      index iHover = hit_test(pmouse->m_pt, m_eelementHover);

      if(m_iHover != iHover)
      {

         m_iHover = iHover;

         if(m_iHover >= 0)
         {
            track_mouse_leave();
         }

      }

   }


   void control::_001OnMouseLeave(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

      m_iHover = -1;
      m_eelementHover = element_none;

   }


   // the value -1 indicates outside the control,
   // other values may be control specific and are client hits
   index control::hit_test(point ptScreen, e_element & eelement)
   {

      sp(::user::interaction) pwnd = ControlExGetWnd();

      rect rectWindow;

      pwnd->GetWindowRect(rectWindow);

      if(rectWindow.contains(ptScreen))
      {

         eelement = element_client;

         return 0;

      }
      else
      {

         eelement = element_none;

         return -1;

      }

   }


   control_cmd_ui::control_cmd_ui(class ::signal * psignal) :
      ::base::cmd_ui(psignal)
   {
   }


   control_view_impl::control_view_impl() :
      m_cmdui(NULL)
   {
   }



} // namespace core
