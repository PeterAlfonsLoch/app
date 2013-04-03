#include "framework.h"

#ifdef WINDOWS
#include <ShlObj.h>
#endif

namespace simpledb
{


   service::service(::ca::application * papp) :
      ca(papp),
      plain_service(papp)
   {
   }

   service::~service()
   {
   }

   void service::serve()
   {
      ::ca::application * pcaapp = get_app();

      Sys(pcaapp).set_thread(&Sys(pcaapp->m_psystem));


      m_pmanager = new ::simpledb::manager(pcaapp);


      /*App(pcaapp).m_strFontopusServer		= System.m_simpledb.db().data_load("fontopus_server", ::database::id(), ::database::id());
      App(pcaapp).m_strDatabaseServerHost	= System.m_simpledb.db().data_load("database_server", ::database::id(), ::database::id());
      App(pcaapp).m_iDatabaseServerPort	= System.m_simpledb.db().data_load("database_port", ::database::id(), ::database::id());
      if(App(pcaapp).m_strDatabaseServerHost.is_empty())
      {
         App(pcaapp).m_strDatabaseServerHost = "localhost";
      }
      if(App(pcaapp).m_iDatabaseServerPort <= 0)
      {
	      App(pcaapp).m_iDatabaseServerPort = 0;
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
            pthread->post_thread_message(WM_APP, 0, 0);
         }
      }

      while (!is_stopping())
      {
         Sleep(1000);
      }
      Sleep(10000);

   }


} // namespace simpledb

