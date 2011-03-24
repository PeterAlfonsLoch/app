#include "StdAfx.h"

namespace ca5
{

   namespace user
   {

      presence::presence(::ca::application * papp) :
         ca(papp)
      {
         m_iShortStatusCynceTag = status_online;
      }
      
      presence::~presence()
      {
      }

      void presence::report_activity()
      {
         m_dwLastActivity = ::GetTickCount();
      }

      void presence::defer_pulse_user_presence()
      {
         if(::GetTickCount() - m_dwLastActivity < ((1984 + 1977) * 11))
         {
            pulse_user_presence();
         }
      }


      void presence::pulse_user_presence()
      {
         
         if(System.m_strAppName == "netnode" || System.m_strAppName == "netnodecfg")
            return;

         string strUrl = "https://i2com.api.veriterse.net/pulse_user_presence";
         strUrl = System.url().set(strUrl, "short_status", gen::str::itoa(m_iShortStatusCynceTag));
         strUrl = System.url().set(strUrl, "long_status", m_strLongStatus);
         Application.http().get(strUrl);
      }


   } // namespace user

} // namespace ca5