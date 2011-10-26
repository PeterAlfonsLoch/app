#include "StdAfx.h"
#include <ShlObj.h>

namespace netshareserver
{

   service::service(::ca::application * papp) :
      ca(papp),
      plain_service(papp)
   {
      m_rgbquada.create_web_palette();
      m_papp = dynamic_cast < ::netshareserver::application * > (papp);
   }

   service::~service()
   {
   }

   
   void service::ServiceThread()
   {
//      ::ca::application * pcaapp = get_app();

      m_stopping = false;

      stringa stra;
      stra = Application.db().data_load("netshareserver", ::database::id(), ::database::id());
      for(int i = 0; i < stra.get_size(); i++)
      {
         m_threadptra.add(AfxBeginThread < socket_thread > (&Application));
         socket_thread * pthread = m_threadptra.last_element();
         {
            single_lock sl(&pthread->m_evInitialized, TRUE);
            pthread->m_strIp = stra[i];
            pthread->m_iPort = 443;
            pthread->m_pservice = this;
            pthread->PostThreadMessage(WM_APP, 0, 0);
         }
      }

      char szPath[MAX_PATH *4];
      string strGet;
      SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA | CSIDL_FLAG_CREATE, NULL, 0, szPath);
      string strPath;
      strPath = szPath;
      if(strPath.Right(1) != "\\")
      {
	      strPath += "\\";
      }
      strPath += "ca2core\\";
      string strConfigFile = strPath + "updatednsbk.conf";
      m_stopping = false;

      while (!m_stopping)
      {
         Sleep(50);
      }
   }

} // namespace netshareserver