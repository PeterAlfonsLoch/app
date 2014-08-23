#pragma once


namespace aura
{


   class CLASS_DECL_AURA cmd_ui:
      public signal_details
   {
   public:


      ::cmd_ui * m_pcmdui;


      cmd_ui(class ::signal * psignal);


   };


   class CLASS_DECL_AURA command:
      public signal_details
   {
   public:


      id   m_id;


      command(class ::signal * psignal);


   };


   class CLASS_DECL_AURA cmd_msg:
      public object
   {
   public:


      enum e_type
      {
         type_command,
         type_cmdui
      };


      ::cmd_ui  *                                    m_pcmdui;
      id                                           m_id;
      e_type                                       m_etype;
      comparable_array < ::command_target * >      m_commandtargetptraHandle;


      cmd_msg();
      cmd_msg(id id);
      cmd_msg(::cmd_ui * pcmdui);


      bool handle(::command_target * pcommandtarget);
      bool is_handled(::command_target * pcommandtarget);


   };


} // namespace aura




