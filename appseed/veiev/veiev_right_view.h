#pragma once

namespace veiev
{

   class CLASS_DECL_CA2_VEIEV right_view : public ::userbase::split_view
   {
   public:
      right_view(::ca::application * papp);
      void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
      DECL_GEN_SIGNAL(_001OnCreate)

      document * get_document();
   };

} // namespace veiev