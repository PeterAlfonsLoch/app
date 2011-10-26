#pragma once

namespace veiev
{

   class CLASS_DECL_CA2_VEIEV second_command_view : public ::userbase::split_view
   {
   public:
      second_command_view(::ca::application * papp);
      void install_message_handling(::user::win::message::dispatch * pinterface);
      DECL_GEN_SIGNAL(_001OnCreate)

      document * get_document();
   };

} // namespace veiev