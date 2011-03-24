#include "StdAfx.h"


UpdateDnsBkService::UpdateDnsBkService(::ca::application * papp) :
   ca(papp),
   plain_service(papp)
{
}

UpdateDnsBkService::~UpdateDnsBkService()
{
}

void UpdateDnsBkService::ServiceThread()
{
   while(!m_stopping)
   {
      string strConfigFile = System.dir().appdata("updatednsbk.conf");
      string str = Application.file().as_string(strConfigFile);
      stringa stra;
      stra.add_tokens(str, "\n", FALSE);
      for(int i = 0; i < stra.get_size(); i++)
      {
         string strLine = stra[i];
         strLine.trim();
         string strGet = "http://peer.veriwell.net/update?subdomain=" + str.trim();
         string strResult = System.http().get(strGet);
         TRACE0(strResult);
      }
      ::Sleep(60 * 1000);
   }
}

