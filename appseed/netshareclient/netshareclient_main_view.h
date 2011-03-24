#pragma once

namespace netshareclient
{

   class document;

   class view;

   class CLASS_DECL_CA2_NETSHARECLIENT main_view : public ::userbase::split_view
   {
   public:


      collection::string_map < netshareclient::view * > m_mapView;


      main_view(::ca::application * papp);
      void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnTimer)

      document * get_document();

      void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
   };


} // namespace netshareclient