#include "framework.h"


namespace userpresence
{


   userpresence::userpresence()
   {
      //m_strMainStringTable = "main_string_table.xml";
   }

   userpresence::~userpresence()
   {
   }

   bool userpresence::initialize()
   {

      //m_dwAlive = ::get_tick_count();
      
      //if(!::simpledb::userpresence::initialize())
        // return false;


      return true;

   }

   bool userpresence::finalize()
   {

      if(!m_papp->is_system())
      {
         defer_finalize_user_presence();
      }

/*      
      try
      {
         ::simpledb::userpresence::finalize();
      }
      catch(...)
      {
      }
*/

      return true;

   }

   void userpresence::defer_initialize_user_presence()
   {

      if(presence_central_container::is_initialized())
         return;

      if(Application.command()->m_varTopicQuery.has_property("install")
      || Application.command()->m_varTopicQuery.has_property("uninstall"))
         return;

      if(Application.command()->m_varTopicQuery["app"] == "simpledbcfg"
      || Application.command()->m_varTopicQuery["app"] == "core_netnodelite"
      || Application.command()->m_varTopicQuery["app"] == "netshareclient")
         return;

      if(Application.command()->m_varTopicQuery["app"] == "mydns")
         return;

      if(Application.command()->m_varTopicQuery["app"] == "app-core/netnodecfg")
         return;

      // it may not be initialized, due
      // licensing for example
      if(presence_central_container::initialize_central_container(m_papp))
      {
         TRACE("user presence enabled");
      }
      else
      {
         TRACE("user presence not enabled");
      }

   }

   void userpresence::defer_finalize_user_presence()
   {

      if(!presence_central_container::is_initialized())
         return;

      if(Application.command()->m_varTopicQuery.has_property("install")
      || Application.command()->m_varTopicQuery.has_property("uninstall"))
         return;

      if(Application.command()->m_varTopicQuery["app"] == "simpledbcfg"
      || Application.command()->m_varTopicQuery["app"] == "core_netnodelite")
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


