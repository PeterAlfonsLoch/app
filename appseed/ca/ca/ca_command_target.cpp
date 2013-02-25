#include "framework.h"

base_cmd_ui::base_cmd_ui(::ca::signal * psignal) :
   signal_object(psignal)
{
}

BaseCommand::BaseCommand(::ca::signal * psignal) :
   signal_object(psignal)
{
}


BaseCmdMsg::BaseCmdMsg()
{


   m_etype                       = type_command;


}


BaseCmdMsg::BaseCmdMsg(id id)
{


   m_etype                       = type_command;
   m_id                          = id;


}


BaseCmdMsg::BaseCmdMsg(cmd_ui * pcmdui)
{


   m_etype                       = type_cmdui;
   m_pcmdui                      = pcmdui;


}


bool BaseCmdMsg::handle(::command_target * pcommandtarget)
{
   return m_commandtargetptraHandle.add_unique(pcommandtarget);
}

bool BaseCmdMsg::is_handled(::command_target * pcommandtarget)
{
   return m_commandtargetptraHandle.contains(pcommandtarget);
}

bool command_target_interface::_001SendCommand(id id)
{
   BaseCmdMsg msg(id);
   return _001OnCmdMsg(&msg);
}

bool command_target_interface::_001SendUpdateCmdUi(cmd_ui * pcmdui)
{
   BaseCmdMsg msg(pcmdui);
   return _001OnCmdMsg(&msg);
}

bool command_target_interface::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
{

   if(pcmdmsg->m_etype == BaseCmdMsg::type_command)
   {

      CTestCmdUI cmdui(get_app());

      cmdui.m_id = pcmdmsg->m_id;

      if(_001OnUpdateCmdUi(&cmdui))
      {
         if(!cmdui.m_bEnabled)
            return false;
      }

      if(_001OnCommand(pcmdmsg->m_id))
         return true;

   }
   else
   {

      if(_001OnUpdateCmdUi(pcmdmsg->m_pcmdui))
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

command_target_interface::command_target_interface(::ca::application * papp)
: ca(papp)
{
}

bool command_target_interface::_001OnCommand(id id)
{
   ::ca::dispatch::signal_ptr_array signalptra;
   get_command_signal_array(BaseCmdMsg::type_command, signalptra, id);
   bool bOk = false;
   for(int32_t i = 0; i < signalptra.get_size(); i++)
   {
      BaseCommand command(signalptra[i]->m_psignal);
      command.m_id = id;
      signalptra[i]->m_psignal->emit(&command);
      if(command.m_bRet)
         bOk = true;
   }
   return bOk;
}

bool command_target_interface::_001HasCommandHandler(id id)
{

   ::ca::dispatch::signal_ptr_array signalptra;

   get_command_signal_array(BaseCmdMsg::type_command, signalptra, id);

   return signalptra.get_size() > 0;

}


bool command_target_interface::_001OnUpdateCmdUi(cmd_ui * pcmdui)
{
   ::ca::dispatch::signal_ptr_array signalptra;
   get_command_signal_array(BaseCmdMsg::type_cmdui, signalptra, pcmdui->m_id);
   bool bOk = false;
   for(int32_t i = 0; i < signalptra.get_size(); i++)
   {
      base_cmd_ui cmdui(signalptra[i]->m_psignal);
      cmdui.m_pcmdui = pcmdui;
      signalptra[i]->m_psignal->emit(&cmdui);
      if(cmdui.m_bRet)
         bOk = true;
   }
   return bOk;
}

void command_target_interface::get_command_signal_array(
   BaseCmdMsg::e_type etype,
   ::ca::dispatch::signal_ptr_array & signalptra, id id)
{
   command_signalid signalid;
   signalid.m_id = id;
   // collect all signals with the specified command id (pszId)
   for(int32_t i = 0; i < m_signalidaCommand.get_size(); i++)
   {
      class ::ca::signalid * pid = m_signalidaCommand[i];
      if(pid->matches(&signalid))
      {
         if(etype == BaseCmdMsg::type_command)
         {
            m_dispatchCommand.m_signala.GetSignalsById(signalptra, &signalid);
         }
         else if(etype == BaseCmdMsg::type_cmdui)
         {
            m_dispatchUpdateCmdUi.m_signala.GetSignalsById(signalptra, &signalid);
         }
         else
         {
            ASSERT(FALSE);
         }
      }
   }
}
