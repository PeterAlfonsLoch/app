#include "framework.h"
#include "base/net/net_sockets.h"
#include "core/database/simpledb/simpledb_socket_thread.h"

#ifdef WINDOWS
#include <ShlObj.h>
#endif

namespace simpledb
{


   service::service(sp(::aura::application) papp) :
      element(papp),
      plain_service(papp)
   {
   }

   service::~service()
   {
   }

   void service::serve()
   {

      sp(::aura::application) pbaseapp = get_app();

      ::set_thread(&Sys(pbaseapp));


      m_pmanager = new ::simpledb::manager(pbaseapp);


      /*App(pbaseapp).m_strFontopusServer		= System.m_simpledb.db().data_load("fontopus_server", ::database::id(), ::database::id());
      App(pbaseapp).m_strDatabaseServerHost	= System.m_simpledb.db().data_load("database_server", ::database::id(), ::database::id());
      App(pbaseapp).m_iDatabaseServerPort	= System.m_simpledb.db().data_load("database_port", ::database::id(), ::database::id());
      if(App(pbaseapp).m_strDatabaseServerHost.is_empty())
      {
         App(pbaseapp).m_strDatabaseServerHost = "localhost";
      }
      if(App(pbaseapp).m_iDatabaseServerPort <= 0)
      {
	      App(pbaseapp).m_iDatabaseServerPort = 0;
      }*/


      stringa stra;
      stra = System.m_simpledb.db().data_load(NULL, "simpledb", ::database::id(), ::database::id());
      for(int32_t i = 0; i < stra.get_size(); i++)
      {
         m_threadptra.add(__begin_thread < socket_thread > (get_app()));
         socket_thread * pthread = m_threadptra.last_element();
         {
            pthread->m_evInitialized.wait();
            pthread->m_strIp = stra[i];
            pthread->m_iPort = 443;
            pthread->m_pservice = this;
            pthread->post_thread_message(WM_APP);
         }
      }

      while (get_run())
      {
         Sleep(1000);
      }
      Sleep(10000);

   }


} // namespace simpledb

