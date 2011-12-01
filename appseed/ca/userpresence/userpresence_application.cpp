#include "StdAfx.h"


namespace ca5
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
      
      if(!::userbase::application::initialize())
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
         ::userbase::application::finalize();
      }
      catch(...)
      {
      }


      return true;

   }

   void application::defer_initialize_user_presence()
   {

      if(user::presence_central_container::is_initialized())
         return;

      if(command().m_varTopicQuery.has_property("install")
      || command().m_varTopicQuery.has_property("uninstall"))
         return;

      if(command().m_varTopicQuery["app"] == "simpledbcfg"
      || command().m_varTopicQuery["app"] == "netnode")
         return;

      if(command().m_varTopicQuery["app"] == "mydns")
         return;

      // it may not be initialized, due
      // licensing for example
      if(user::presence_central_container::initialize_central_container(this))
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

      if(!user::presence_central_container::is_initialized())
         return;

      if(command().m_varTopicQuery.has_property("install")
      || command().m_varTopicQuery.has_property("uninstall"))
         return;

      if(command().m_varTopicQuery["app"] == "simpledbcfg"
      || command().m_varTopicQuery["app"] == "netnode")
         return;

      // it may not be initialized, due
      // licensing for example
      if(user::presence_central_container::finalize_central_container())
      {
         TRACE("user presence finalized");
      }
      else
      {
         TRACE("user presence finalization failed");
      }

   }

} //namespace ca5