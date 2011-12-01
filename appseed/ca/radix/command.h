#pragma once

class ::ca::application;

class CLASS_DECL_ca base_cmd_ui :
   public gen::signal_object
{
public:
   base_cmd_ui(gen::signal * psignal);
   cmd_ui * m_pcmdui;
};

class CLASS_DECL_ca BaseCommand :
   public gen::signal_object
{
public:
   BaseCommand(gen::signal * psignal);
   id   m_id;
};

class CLASS_DECL_ca BaseCmdMsg :
   public ::radix::object
{
public:
   BaseCmdMsg();
   BaseCmdMsg(id id);
   BaseCmdMsg(cmd_ui * pcmdui);
   enum e_type
   {
      type_command,
      type_cmdui
   };
   cmd_ui  *   m_pcmdui;
   id          m_id;
   e_type      m_etype;

   bool handle(::command_target * pcommandtarget);
   bool is_handled(::command_target * pcommandtarget);

   comparable_array < ::command_target * > m_commandtargetptraHandle;
};
