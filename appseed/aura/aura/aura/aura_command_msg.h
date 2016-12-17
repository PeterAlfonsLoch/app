#pragma once


class command_target_interface;


namespace aura
{


   class CLASS_DECL_AURA cmd_msg:
      public object
   {
   public:


      enum e_type
      {
         type_command,
         type_cmdui
      };

      ::command_target_interface *                 m_pcommandtargetSource;
      ::cmd_ui  *                                  m_pcmdui;
      id                                           m_id;
      e_type                                       m_etype;
      ref_array < ::command_target >               m_commandtargetptraHandle;


      cmd_msg();
      cmd_msg(id id);
      cmd_msg(::cmd_ui * pcmdui);


      bool handle(::command_target * pcommandtarget);
      bool is_handled(::command_target * pcommandtarget);


   };


} // namespace aura

















