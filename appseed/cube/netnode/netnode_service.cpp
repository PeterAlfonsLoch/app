#include "StdAfx.h"
#include "netnodeSocket.h"
#include "netnodeService.h"
#include <ShlObj.h>


netnodeService::netnodeService(::ca::application * papp) :
   ca(papp),
   plain_service(papp)
{
}

netnodeService::~netnodeService(void)
{
}

void netnodeService::ServiceThread()
{
   ::ca::application * pcaapp = get_app();

   pcaapp->m_psystem->set_thread(pcaapp->m_psystem);

   m_stopping = false;

   netnode::application * papp = &Application;

   papp->m_pscriptmanager = new netnodeScriptManager(pcaapp);


   stringa stra;
   stra = System.db().data_load("netnode", ::database::id(), ::database::id());
   for(int i = 0; i < stra.get_size(); i++)
   //for(int i = 0; i < 1; i++)
   {
      m_threadptra.add(AfxBeginThread < netnodeSocketThread > (get_app()));
      netnodeSocketThread * pthread = m_threadptra.last_element();
      {
         CSingleLock sl(&pthread->m_evInitialized, TRUE);
         pthread->m_strIp = stra[i];
         pthread->m_iPort = 80;
         pthread->m_pservice = this;
         pthread->PostThreadMessage(WM_APP, 0, 0);
      }
   }
   stra = System.db().data_load("netnodes", ::database::id(), ::database::id());
   for(int i = 0; i < stra.get_size(); i++)
   //for(int i = 0; i < 1; i++)
   {
      m_threadptra.add(AfxBeginThread < netnodeSocketThread > (get_app()));
      netnodeSocketThread * pthread = m_threadptra.last_element();
      {
         CSingleLock sl(&pthread->m_evInitialized, TRUE);
         pthread->m_strIp = stra[i];
         pthread->m_iPort = 443;
         pthread->m_pservice = this;
         pthread->PostThreadMessage(WM_APP, 0, 0);
      }
   }


   while (!m_stopping)
   {
      Sleep(1000);
   }
   Sleep(10000);
   
}



