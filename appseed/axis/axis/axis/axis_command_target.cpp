#include "framework.h"


bool command_target_interface::_001SendCommand(id id)
{
   ::aura::cmd_msg msg(id);
   return _001OnCmdMsg(&msg);
}

bool command_target_interface::_001SendUpdateCmdUi(cmd_ui * pcmdui)
{
   ::aura::cmd_msg msg(pcmdui);
   return _001OnCmdMsg(&msg);
}

bool command_target_interface::_001OnCmdMsg(::aura::cmd_msg * pcmdmsg)
{

   if(pcmdmsg->m_etype == ::aura::cmd_msg::type_command)
   {

      CTestCmdUI cmdui(get_app());

      cmdui.m_id = pcmdmsg->m_id;

      if(on_simple_update(&cmdui))
      {
         if(!cmdui.m_bEnabled)
            return false;
      }

      if(on_simple_action(pcmdmsg->m_id))
         return true;

   }
   else
   {

      if(on_simple_update(pcmdmsg->m_pcmdui))
         return true;

      if(_001HasCommandHandler(pcmdmsg->m_pcmdui->m_id))
      {
         pcmdmsg->m_pcmdui->Enable();
         return true;
      }

   }

   return false;

}

command_target_interface::command_signalid::~command_signalid()
{
}

command_target_interface::command_signalrange::~command_signalrange()
{
}

command_target_interface::command_target_interface()
{
}

command_target_interface::command_target_interface(::aura::application * papp)
   : element(papp)
{
}

bool command_target_interface::on_simple_action(id id)
{
   ::dispatch::signal_item_ptr_array signalptra;
   get_command_signal_array(::aura::cmd_msg::type_command,signalptra,id);
   bool bOk = false;
   for(int32_t i = 0; i < signalptra.get_size(); i++)
   {
      ::aura::command command(signalptra[i]->m_psignal);
      command.m_id = id;
      signalptra[i]->m_psignal->emit(&command);
      if(command.m_bRet)
         bOk = true;
   }
   return bOk;
}

bool command_target_interface::_001HasCommandHandler(id id)
{

   ::dispatch::signal_item_ptr_array signalptra;

   get_command_signal_array(::aura::cmd_msg::type_command,signalptra,id);

   return signalptra.get_size() > 0;

}


bool command_target_interface::on_simple_update(cmd_ui * pcmdui)
{
   ::dispatch::signal_item_ptr_array signalptra;
   get_command_signal_array(::aura::cmd_msg::type_cmdui,signalptra,pcmdui->m_id);
   bool bOk = false;
   for(int32_t i = 0; i < signalptra.get_size(); i++)
   {
      ::aura::cmd_ui cmdui(signalptra[i]->m_psignal);
      cmdui.m_pcmdui = pcmdui;
      signalptra[i]->m_psignal->emit(&cmdui);
      if(cmdui.m_bRet)
         bOk = true;
   }
   return bOk;
}

void command_target_interface::get_command_signal_array(::aura::cmd_msg::e_type etype,::dispatch::signal_item_ptr_array & signalptra,id id)
{
   command_signalid signalid;
   signalid.m_id = id;
   // collect all signals with the specified command id (pszId)
   for(int32_t i = 0; i < m_signalidaCommand.get_size(); i++)
   {
      class signalid * pid = m_signalidaCommand[i];
      if(pid->matches(&signalid))
      {
         if(etype == ::aura::cmd_msg::type_command)
         {
            m_dispatchCommand.m_signala.GetSignalsById(signalptra,&signalid);
         }
         else if(etype == ::aura::cmd_msg::type_cmdui)
         {
            m_dispatchUpdateCmdUi.m_signala.GetSignalsById(signalptra,&signalid);
         }
         else
         {
            ASSERT(FALSE);
         }
      }
   }
}

void command_target_interface::install_message_handling(::message::dispatch * pdispatch)
{

   UNREFERENCED_PARAMETER(pdispatch);

}
cmd_ui::cmd_ui(::aura::application * papp):
element(papp)
{

   m_iIndex                      = 0;
   m_iCount                      = 0;
   m_pMenu                       = NULL;
   m_pSubMenu                    = NULL;
   m_pParentMenu                 = NULL;
   m_pOther                      = NULL;
   m_bEnableChanged              = FALSE;
   m_bContinueRouting            = FALSE;
   m_bEnableIfHasCommandHandler  = true;

}

// default cmd_ui implementation only works for Menu Items
void cmd_ui::Enable(bool bOn,::action::context actioncontext)
{

   if(m_pMenu != NULL)
   {

      if(m_pSubMenu != NULL)
         return; // don't change popup menus indirectly

      ENSURE(m_iIndex < m_iCount);

   }
   else
   {

      // enable/disable a control (i.e. child interaction_impl)
      ENSURE(m_pOther != NULL);

      // if control has the focus, move the focus before disabling
      if(!bOn && (System.get_focus_guie() == m_pOther))
         Application.send_message(Application.get_parent(m_pOther),WM_NEXTDLGCTL,0,(LPARAM)FALSE);

      Application.enable_window(m_pOther,bOn);

   }

   m_bEnableChanged = TRUE;

}

void cmd_ui::_001SetCheck(bool bCheck,::action::context actioncontext)
{

   _001SetCheck((check::e_check) (bCheck ? check::checked : check::unchecked),actioncontext);

}


void cmd_ui::_001SetCheck(check::e_check nCheck,::action::context actioncontext)
{

   if(m_pMenu != NULL)
   {
      if(m_pSubMenu != NULL)
         return; // don't change popup menus indirectly

      // place checkmark next to menu item
      ENSURE(m_iIndex < m_iCount);
   }
   else if(m_pOther != NULL)
   {

#ifdef WINDOWS

      // we can only check buttons or controls acting like buttons
      ENSURE(m_pOther != NULL);
      if(Application.send_message(m_pOther,WM_GETDLGCODE) & DLGC_BUTTON)
         Application.send_message(m_pOther,BM_SETCHECK,nCheck);
      // otherwise ignore it

#endif

   }
}


__STATIC void __load_dot_bitmap(); // for swap tuning

void cmd_ui::SetRadio(bool bOn,::action::context actioncontext)
{
   _001SetCheck(bOn != FALSE,actioncontext); // this default works for most things as well
   if(m_pMenu != NULL)
   {
      if(m_pSubMenu != NULL)
         return; // don't change popup menus indirectly

      // for menu item - use dot instead of checkmark
      ENSURE(m_iIndex < m_iCount);

      /*      if (afxData.hbmMenuDot == NULL)
      __load_dot_bitmap();    // in INIT segment
      */
   }
}

void cmd_ui::SetText(const char * lpszText,::action::context actioncontext)
{
   ENSURE_ARG(lpszText != NULL);
   ASSERT(__is_valid_string(lpszText));

   {
      ENSURE(m_pOther != NULL);
      Application.set_window_text(m_pOther,lpszText);
   }
}

bool cmd_ui::DoUpdate(command_target* pTarget,bool bDisableIfNoHndler)
{
   if(m_id.is_empty())
      return TRUE;     // ignore invalid IDs

   ENSURE_VALID(pTarget);

   m_bEnableChanged = FALSE;
   bool bResult = pTarget->_001SendUpdateCmdUi(this);

   if(!bResult)
      Enable(FALSE);

   return bResult;
}




CTestCmdUI::CTestCmdUI(::aura::application * papp):
element(papp),
cmd_ui(papp)
{

   m_bEnabled        = TRUE;  // assume it is enabled
   m_echeck          = ::check::undefined;
   m_bRadio          = false;
   m_bRadioChanged   = false;

}


void CTestCmdUI::Enable(bool bOn,::action::context)
{

   m_bEnabled        = bOn;
   m_bEnableChanged  = true;

}


void CTestCmdUI::_001SetCheck(bool bCheck,::action::context context)
{

   ::cmd_ui::_001SetCheck(bCheck,context);

}


void CTestCmdUI::_001SetCheck(check::e_check echeck,::action::context)
{

   m_echeck = echeck;

}

void CTestCmdUI::SetRadio(bool bOn,::action::context)
{

   m_bRadio = bOn;
   m_bRadioChanged = true;


}

void CTestCmdUI::SetText(const char * lpszText,::action::context)
{

   m_strText = lpszText;

}


