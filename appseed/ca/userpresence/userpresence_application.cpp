#include "framework.h"


namespace userpresence
{


   application::application()
   {
      //m_strMainStringTable = "main_string_table.xml";
   }

   application::~application()
   {
   }

   bool application::initialize()
   {

      m_dwAlive = ::GetTickCount();
      
      if(!::simpledb::application::initialize())
         return false;


      return true;

   }

   bool application::finalize()
   {

      if(!is_system())
      {
         defer_finalize_user_presence();
      }

      
      try
      {
         ::simpledb::application::finalize();
      }
      catch(...)
      {
      }


      return true;

   }

   void application::defer_initialize_user_presence()
   {

      if(presence_central_container::is_initialized())
         return;

      if(command().m_varTopicQuery.has_property("install")
      || command().m_varTopicQuery.has_property("uninstall"))
         return;

      if(command().m_varTopicQuery["app"] == "simpledbcfg"
      || command().m_varTopicQuery["app"] == "core_netnodelite"
      || command().m_varTopicQuery["app"] == "netshareclient")
         return;

      if(command().m_varTopicQuery["app"] == "mydns")
         return;

      if(command().m_varTopicQuery["app"] == "app-core/tesseract/netnodecfg")
         return;

      // it may not be initialized, due
      // licensing for example
      if(presence_central_container::initialize_central_container(this))
      {
         TRACE("user presence enabled");
      }
      else
      {
         TRACE("user presence not enabled");
      }

   }

   void application::defer_finalize_user_presence()
   {

      if(!presence_central_container::is_initialized())
         return;

      if(command().m_varTopicQuery.has_property("install")
      || command().m_varTopicQuery.has_property("uninstall"))
         return;

      if(command().m_varTopicQuery["app"] == "simpledbcfg"
      || command().m_varTopicQuery["app"] == "core_netnodelite")
         return;

      // it may not be initialized, due
      // licensing for example
      if(presence_central_container::finalize_central_container())
      {
         TRACE("user presence finalized");
      }
      else
      {
         TRACE("user presence finalization failed");
      }

   }


} //namespace ca5


