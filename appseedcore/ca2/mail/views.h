#pragma once

namespace mail
{

   class document;

   class CLASS_DECL_ca main_view : public ::userbase::split_view
   {
   public:
      main_view(::ca::application * papp);
      void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnTimer)

      document * get_document();
   };


   class CLASS_DECL_ca right_view : public ::userbase::split_view
   {
   public:
      right_view(::ca::application * papp);
      void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
      DECL_GEN_SIGNAL(_001OnCreate)

      document * get_document();
   };


} // namespace mail