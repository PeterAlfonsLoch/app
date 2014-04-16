#pragma once


class command_target;
class cmd_ui;


class CLASS_DECL_BASE base_cmd_ui :
   public signal_details
{
public:


   cmd_ui * m_pcmdui;


   base_cmd_ui(class ::signal * psignal);


};


class CLASS_DECL_BASE base_command :
   public signal_details
{
public:


   id   m_id;


   base_command(class ::signal * psignal);


};


class CLASS_DECL_BASE base_cmd_msg :
   public object
{
public:


   enum e_type
   {
      type_command,
      type_cmdui
   };


   cmd_ui  *                                    m_pcmdui;
   id                                           m_id;
   e_type                                       m_etype;
   comparable_array < ::command_target * >      m_commandtargetptraHandle;


   base_cmd_msg();
   base_cmd_msg(id id);
   base_cmd_msg(cmd_ui * pcmdui);


   bool handle(::command_target * pcommandtarget);
   bool is_handled(::command_target * pcommandtarget);


};


